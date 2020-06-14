import matplotlib.pyplot as plt


f = open("src/Debug/out_real", "r")
lines = f.read().replace('\r', '').split('\n')

samples = []
for line in lines:
    if len(line):
        samples.append(float(line))

plt.plot(samples, ".-")
plt.show()