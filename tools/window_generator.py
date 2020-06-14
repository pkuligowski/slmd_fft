import math
import matplotlib.pyplot as plt

WINDOW_WIDTH = 4096

window_lut = []
for n in range(0, WINDOW_WIDTH):
    # Hamming window
    # a0 = 0.53836
    # value = a0 - (1 - a0) * math.cos(2 * math.pi * n / WINDOW_WIDTH)

    # Blackman window
    alpha = 0.16
    a0 = (1.0 - alpha) / 2.0
    a1 = 0.5
    a2 = alpha / 2.0
    value = a0 - a1 * math.cos(2 * math.pi * n / WINDOW_WIDTH) + a2 * math.cos(4 * math.pi * n / WINDOW_WIDTH)
    window_lut.append(round(value, 3))

print("const float WINDOW_HAMMING[" + str(WINDOW_WIDTH) + "] = {" + str(window_lut) + "};")

plt.plot(window_lut, ".-")
plt.show()