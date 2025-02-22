import sys
import matplotlib.pyplot as plt
import numpy as np

# Se obtiene la notación asintótica desde los argumentos (si existe)
notation = sys.argv[1] if len(sys.argv) > 1 else "O(n)"
data = np.loadtxt("data.txt")
inputs, times = data[:, 0], data[:, 1]

plt.figure(figsize=(8,6))
plt.plot(inputs, times, marker='o', linestyle='-', label=f'Tiempos de ejecución ({notation})')
plt.xlabel("Tamaño de entrada (n)")
plt.ylabel("Tiempo de ejecución (µs)")
plt.title(f"Análisis de Complejidad {notation}")
plt.legend()
plt.grid(True)
plt.show()
