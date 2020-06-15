import subprocess
import matplotlib.pyplot as plt
import math
import time

process = subprocess.Popen(["..\\src\\Debug\\fft_flpt.exe"], stdin=subprocess.PIPE, stderr=subprocess.PIPE) # stdout=subprocess.PIPE, 
process.stdin.write("0.55\n".encode())
process.stdin.close()
process.wait()

print(val)

#lines = val.stdout.decode().replace("\r", "").split("\n")

samples = []
for line in lines:
    if len(line)>1 and line[0]=='D' and line[1]=='|':
        samples.append(float(line.replace("D|", "")))

samples_dB = []
for sample in samples:
    samples_dB.append(20.0 * math.log(abs(sample)))

plt.subplot(212)
axes = plt.gca()
axes.set_xlim([0, len(samples_dB) - 1])
axes.set_ylim([-50, max(samples_dB) * 1.1])
plt.plot(samples_dB, ".-")

plt.show()