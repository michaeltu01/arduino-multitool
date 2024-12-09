import aubio
from aubio import pitch
import queue
import music21
import pyaudio
import numpy as np
import serial
import serial.tools.list_ports as serial_ports

port = "COM18"

# attempt to open serial port
try:
    arduino = serial.Serial(port=port, baudrate=9600, timeout=.1)
except serial.SerialException:
    print("Serial port not found")
    print("Here are the available ports: ")
    ports = serial_ports.comports()
    for port in ports:
        print(f"Port: {port.device}, Description: {port.description}")
    exit()

# Open stream.
# PyAudio object.
p = pyaudio.PyAudio()
stream = p.open(format=pyaudio.paFloat32,
                channels=1, rate=44100, input=True,
                input_device_index=0, frames_per_buffer=512)

q = queue.Queue()  
current_pitch = music21.pitch.Pitch()

samplerate = 44100
win_s = 512 
hop_s = 512 

tolerance = 0.8

pitch_o = pitch("default",win_s,hop_s,samplerate)
#pitch_o.set_unit("")
pitch_o.set_tolerance(tolerance)

# total number of frames read
total_frames = 0


def get_current_note():
    pitches = []
    confidences = []
    current_pitch = music21.pitch.Pitch()

    while True:
        data = stream.read(hop_s, exception_on_overflow=False)
        samples = np.frombuffer(data,dtype=aubio.float_type)        
        pitch = (pitch_o(samples)[0])
        #pitch = int(round(pitch))
        confidence = pitch_o.get_confidence()
        #if confidence < 0.8: pitch = 0.
        pitches += [pitch]
        confidences += [confidence]
        current='Nan'
        if pitch>0:
            current_pitch.frequency = float(pitch)
            current=current_pitch.nameWithOctave
            print(pitch,'----',current,'----',current_pitch.microtone.cents)        
            value = serial_write_read(f"{str(pitch)},{current.replace('-', '').replace('~', '')}\n") 
            print(f"Serial out: {value}") # printing the value

def serial_write_read(x): 
    arduino.write(bytes(x, 'utf-8')) 
    data = arduino.readline()
    return data


if __name__ == '__main__':
    get_current_note()
    