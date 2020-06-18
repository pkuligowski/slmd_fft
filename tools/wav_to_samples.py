from scipy.io import wavfile
sampling_frequency, samples = wavfile.read('stuk.wav')

print("Sampling frequency: " + str(sampling_frequency))
print("Number of samples: " + str(len(samples)))

samples_float = []
for index in range(0, 4095):
    samples_float.append(str(samples[index] / 32768.0))

file_real = open('../src/Debug/in_real', 'wb')
file_real.write("\n".join(samples_float).encode() + "\n".encode())
file_real.close()
