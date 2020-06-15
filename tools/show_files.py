import matplotlib.pyplot as plt
import math
import numpy

def read_file(file_path, absolute=False):
    f = open(file_path, "r")
    lines = f.read().replace('\r', '').split('\n')

    samples = []
    for index in range(0, round(len(lines))):
        if len(lines[index]):
            if absolute:
                samples.append(abs(float(lines[index])))
            else:
                samples.append(float(lines[index]))
    
    return samples

samples_in_real = read_file("../src/Debug/in_real")
samples_out_real = read_file("../src/Debug/out_real", absolute=True)


plt.subplot(211)
axes = plt.gca()
axes.set_xlim([0, len(samples_in_real) - 1])
axes.set_ylim([min(samples_in_real) * 1.1, max(samples_in_real) * 1.1])
plt.plot(samples_in_real, ".-")
plt.xlabel("Numer próbki sygnału wejściowego")
plt.ylabel("Amplituda sygnału wejściowego")

plt.title("Sinusoidalny sygnał 20 kHz i jego widmo. Okno: Blackman")

samples_out_real_dB = []
for sample_out in samples_out_real:
    samples_out_real_dB.append(20.0 * math.log(sample_out))

freqs = numpy.linspace(start=0, stop=(44.1/2.0), num=len(samples_out_real_dB))

plt.subplot(212)
axes = plt.gca()
axes.set_xlim([0, max(freqs)])
axes.set_ylim([min(samples_out_real_dB) * 1.1, max(samples_out_real_dB) * 1.1])
plt.plot(freqs, samples_out_real_dB, ".-")
plt.xticks(numpy.arange(min(freqs), max(freqs), 1.0))
plt.xlabel("Częstotliwość [kHz]")
plt.ylabel("Rrzeczywista absolutna amplituda DFT [dB]")

plt.show()