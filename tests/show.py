import matplotlib.pyplot as plt


f = open("../src/Debug/out_real", "r")
lines = f.read().replace('\r', '').split('\n')

samples = []
for index in range(0, round(len(lines)/2)):
    if len(lines[index]):
        samples.append(abs(float(lines[index])))

plt.plot(samples, ".-")
plt.show()