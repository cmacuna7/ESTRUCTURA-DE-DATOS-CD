import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt("data.txt")
inputs, times = data[:, 0], data[:, 1]

plt.plot(inputs, times, marker='o', linestyle='-', label='Tiempos de ejecución')
plt.xlabel("Tamaño de entrada (n)")
plt.ylabel("Tiempo de ejecución (µs)")
plt.title("Análisis de Complejidad Big-O")
plt.legend()
plt.grid()
plt.show()
