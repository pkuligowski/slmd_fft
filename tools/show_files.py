import matplotlib.pyplot as plt
import math

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

samples_out_real_dB = []
for sample_out in samples_out_real:
    samples_out_real_dB.append(20.0 * math.log(sample_out))

plt.subplot(212)
axes = plt.gca()
axes.set_xlim([0, len(samples_out_real_dB) - 1])
axes.set_ylim([-50, max(samples_out_real_dB) * 1.1])
plt.plot(samples_out_real_dB, ".-")


plt.show()