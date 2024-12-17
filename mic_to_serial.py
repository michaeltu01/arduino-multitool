import aubio
from aubio import pitch
import music21
import pyaudio
import numpy as np
import serial
import serial.tools.list_ports as serial_ports


def find_serial_port() -> str:
    """Find the serial port associated with the Arduino."""

    for port in serial_ports.comports():
        if "USB" in port.description:
            return port.device

    raise ValueError("No serial port found")

PORT = find_serial_port()

# Attempt to open serial port
try:
    arduino = serial.Serial(port=PORT, baudrate=9600, timeout=.1)
except serial.SerialException:
    print("Serial port cannot be configured")
    print("Here are the available ports: ")
    for port in serial_ports.comports():
        print(f"Port: {port.device}, Description: {port.description}")
    exit()

# Define constants
SAMPLE_RATE = 44100
WIN_S = 512
HOP_S = 512
TOLERANCE = 0.8

# Open stream.
# PyAudio object.
p = pyaudio.PyAudio()
stream = p.open(format=pyaudio.paFloat32,
                channels=1, rate=SAMPLE_RATE, input=True,
                input_device_index=0, frames_per_buffer=512)
current_pitch = music21.pitch.Pitch()

pitch_o = pitch("default",WIN_S,HOP_S,SAMPLE_RATE)
pitch_o.set_tolerance(TOLERANCE)

# total number of frames read
total_frames = 0

def get_current_note() -> None:
    """ Get the current note from the microphone. """
    pitch_values = []
    confidence_values = []
    current_pitch = music21.pitch.Pitch()

    while True:
        audio_data = stream.read(HOP_S, exception_on_overflow=False)
        samples = np.frombuffer(audio_data,dtype=aubio.float_type)        
        detected_pitch = (pitch_o(samples)[0])
        pitch_confidence = pitch_o.get_confidence()
        pitch_values.append(detected_pitch)
        confidence_values.append(pitch_confidence)
        current='Nan'
        if detected_pitch>0:
            current_pitch.frequency = float(detected_pitch)
            current=current_pitch.nameWithOctave
            print(detected_pitch,'----',current,'----',current_pitch.microtone.cents)        
            value = serial_write_read(f"{str(detected_pitch)},{current.replace('-', '').replace('~', '')}\n") 
            print(f"Serial out: {value}") # printing the value

def serial_write_read(write_to_arduino: str) -> str: 
    arduino.write(bytes(write_to_arduino, 'utf-8')) 
    data_from_arduino = arduino.readline()
    return data_from_arduino

if __name__ == '__main__':
    get_current_note()
    