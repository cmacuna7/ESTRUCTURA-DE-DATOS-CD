import sys
import matplotlib.pyplot as plt
import numpy as np

# Se obtiene la notación asintótica desde los argumentos (si existe)
notation = sys.argv[1] if len(sys.argv) > 1 else "Big-O"

data = np.loadtxt("data.txt")
inputs, times = data[:, 0], data[:, 1]

plt.plot(inputs, times, marker='o', linestyle='-', label='Tiempos de ejecución')
plt.xlabel("Tamaño de entrada (n)")
plt.ylabel("Tiempo de ejecución (µs)")
plt.title("Análisis de Complejidad " + notation)
plt.legend()
plt.grid()
plt.show()
