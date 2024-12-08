# Pseudocode for audio frequency analysis
import time
import numpy as np
import sounddevice as sd
import serial

print(sd.query_devices())  # Lists all available devices
sd.default.device = 15


# def capture_audio_frequency():
#     # Set up audio input parameters
#     sample_rate = 44100  # Standard sampling rate
#     duration = 0.1  # Capture duration
    
#     # Record audio
#     audio_data = sd.rec(int(duration * sample_rate), 
#                         samplerate=sample_rate, 
#                         channels=2)
#     sd.wait()

#     left_channel = audio_data[:, 0]
#     right_channel = audio_data[:, 1]

#     # Debug prints
#     print("Audio data shape:", audio_data.shape)
#     print("Left channel max:", np.max(left_channel))
#     print("Right channel max:", np.max(right_channel))
    
#     # Perform Fast Fourier Transform (FFT)
#     # fft_data = np.fft.fft(audio_data)
#     # frequencies = np.fft.fftfreq(len(audio_data), 1/sample_rate)
#     fft_data = np.fft.fft(left_channel)
#     frequencies = np.fft.fftfreq(len(left_channel), 1/sample_rate)

#     # print("Frequencies: ", frequencies)
    
#     # Find dominant frequency
#     positive_freq_mask = frequencies > 0
#     dominant_freq = frequencies[positive_freq_mask][np.argmax(np.abs(fft_data[positive_freq_mask]))]
    
#     print("Dominant frequency:", dominant_freq)
#     return dominant_freq

import matplotlib.pyplot as plt

def capture_audio_frequency():
    sample_rate =  48000 
    duration = .1
   
      # Record audio
    audio_data = sd.rec(int(duration * sample_rate),
                        samplerate=sample_rate,
                        channels=2)
    sd.wait()
   
    # Combine channels (average method)
    combined_channel = (audio_data[:, 0] + audio_data[:, 1]) / 2
   
    # Remove DC offset
    combined_channel = combined_channel - np.mean(combined_channel)
    
    # Perform FFT
    window = np.hamming(len(combined_channel))
    fft_data = np.fft.rfft(combined_channel * window)

    frequencies = np.fft.rfftfreq(len(combined_channel), 1/sample_rate)
    
    # Get magnitude spectrum
    magnitude = np.abs(fft_data)
    
    noise_threshold = np.mean(magnitude) * 2
    significant_peaks = np.where(magnitude > noise_threshold)[0]
    first_significant_freq = frequencies[significant_peaks[0]] if len(significant_peaks) > 0 else 0
    
    # # Find dominant frequency
    # dominant_index = np.argmax(magnitude[1:]) + 1  # Skip DC component
    # dominant_freq = frequencies[dominant_index]
    
    # Optional: Plot spectrum for visualization
    plt.figure(figsize=(10, 4))
    plt.plot(audio_data[:, 0], label="Left Channel")
    plt.plot(audio_data[:, 1], label="Right Channel")
    plt.title("Captured Audio Signal")
    plt.xlabel("Sample Index")
    plt.ylabel("Amplitude")
    plt.legend()
    plt.show()
        
    print(f"first sig Frequency: {first_significant_freq:.2f} Hz")
    return first_significant_freq

def send_frequency_to_arduino():
    # Open serial connection
    # arduino_port = '/dev/ttyACM0'  # Adjust based on your system
    arduino_port = "COM6";
    baud_rate = 9600
    
    with serial.Serial(arduino_port, baud_rate) as ser:
        while True:
            # Capture and send frequency
            freq = capture_audio_frequency()
            print("Sending frequency:", freq)
            # ser.write(str(freq).encode())
            
            # Optional: Add delay or synchronization mechanism
            time.sleep(0.1)

if __name__ == "__main__":
    send_frequency_to_arduino()