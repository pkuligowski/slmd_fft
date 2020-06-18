import matplotlib.pyplot as plt
import math
import numpy


f = open("spectrum.txt", "r")
audacity_lines = f.read().replace('\r', '').split('\n')
audacity_samples = []
audacity_freqs = []
for index in range(1, len(audacity_lines)):
    if len(audacity_lines[index]):
        audacity_freqs.append(float(audacity_lines[index].split("\t")[0])/1000.0)
        audacity_samples.append(float(audacity_lines[index].split("\t")[1]))


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
plt.plot(samples_in_real, "g.-")
plt.xlabel("Numer próbki sygnału wejściowego")
plt.ylabel("Amplituda sygnału wejściowego")

plt.title("Próbka 'piano' i porównanie Audacity z systemem testowanym. Okno Blackmana.")

samples_out_real_dB = []
for sample_out in samples_out_real:
    samples_out_real_dB.append(10.0 * math.log(sample_out)-66)

freqs = numpy.linspace(start=0, stop=(44.1/2.0), num=len(samples_out_real_dB))

plt.subplot(212)
axes = plt.gca()
axes.set_xlim([0, max(freqs)])
axes.set_ylim([min(samples_out_real_dB) * 1.1, max(samples_out_real_dB) * 0.1])
plt.plot(audacity_freqs, audacity_samples, "b-", label='Audacity (referencyjny)')
plt.plot(freqs, samples_out_real_dB, "r.-", label='Testowany system')
plt.xticks(numpy.arange(min(freqs), max(freqs), 1.0))
plt.xlabel("Częstotliwość [kHz]")
#axes.set_xscale('log')
plt.ylabel("Rrzeczywista absolutna amplituda DFT [dB]")
plt.legend(loc="upper right")

plt.show()