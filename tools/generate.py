import math
import matplotlib.pyplot as plt
import random

FREQ_HZ = 20000
WINDOW_WIDTH = 4095
NOISE_AMPLITUDE = 0.0
SAMPLING_FREQ = 44100

output_str = []
output = []
imag = []
for i in range(0, WINDOW_WIDTH):
    value = math.sin(2 * math.pi * (i % (WINDOW_WIDTH / (FREQ_HZ/(SAMPLING_FREQ/WINDOW_WIDTH)))) / (WINDOW_WIDTH / (FREQ_HZ/(SAMPLING_FREQ/WINDOW_WIDTH)))) + (random.random()-0.5) * 2 * NOISE_AMPLITUDE
    output.append(value)
    output_str.append(str(value))
    imag.append(str(0))

file_real = open('../src/Debug/in_real', 'wb')
file_real.write("\n".join(output_str).encode() + "\n".encode())
file_real.close()

file_real = open('../src/Debug/in_imag', 'wb')
file_real.write("\n".join(imag).encode() + "\n".encode())
file_real.close()

plt.plot(output, ".-")
plt.show()