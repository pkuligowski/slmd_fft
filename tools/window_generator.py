import math
import matplotlib.pyplot as plt

WINDOW_WIDTH = 4096

window_lut = []
for n in range(0, WINDOW_WIDTH):
    a0 = 0.53836
    value = a0 - (1 - a0) * math.cos(2 * math.pi * n / WINDOW_WIDTH)
    window_lut.append(round(value, 3))

print("const float WINDOW_HAMMING[" + str(WINDOW_WIDTH) + "] = {" + str(window_lut) + "};")

plt.plot(window_lut, ".-")
plt.show()