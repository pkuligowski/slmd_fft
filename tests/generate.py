import math
import matplotlib.pyplot as plt
import random

FREQ_HZ = 50
SAMPLING_FREQ = 4096
NOISE_AMPLITUDE = 0.1

output_str = []
output = []
imag = []
for i in range(0, SAMPLING_FREQ):
    value = math.sin(2 * math.pi * (i % (SAMPLING_FREQ / FREQ_HZ)) / (SAMPLING_FREQ / FREQ_HZ)) + (random.random()-0.5) * 2 * NOISE_AMPLITUDE
    output.append(value)
    output_str.append(str(round(value, 3)))
    imag.append(str(0))

file_real = open('../src/Debug/in_real', 'wb')
file_real.write("\n".join(output_str).encode() + "\n".encode())
file_real.close()

file_real = open('../src/Debug/in_imag', 'wb')
file_real.write("\n".join(imag).encode() + "\n".encode())
file_real.close()

plt.plot(output, ".-")
plt.show()