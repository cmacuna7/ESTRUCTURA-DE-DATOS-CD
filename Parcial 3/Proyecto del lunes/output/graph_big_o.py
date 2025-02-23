import math
import sys
import matplotlib.pyplot as plt

def graficar_big_o(big_o):  # Modificado para recibir un argumento
    # Configurar valores según la notación
    n = []
    y = []
    titulo = ""
    
    if big_o == 'O(1)':
        n = list(range(1, 11))
        y = [1] * len(n)
        titulo = 'O(1) - Tiempo constante'
    elif big_o == 'O(log n)':
        n = list(range(2, 21))
        y = [math.log(x) for x in n]
        titulo = 'O(log n) - Tiempo logarítmico'
    elif big_o == 'O(n)':
        n = list(range(1, 101))
        y = n
        titulo = 'O(n) - Tiempo lineal'
    elif big_o == 'O(n log n)':
        n = list(range(2, 101))
        y = [x * math.log(x) for x in n]
        titulo = 'O(n log n) - Tiempo linealítmico'
    elif big_o == 'O(n^2)':
        n = list(range(1, 51))
        y = [x**2 for x in n]
        titulo = 'O(n^2) - Tiempo cuadrático'
    elif big_o == 'O(2^n)':
        n = list(range(1, 16))
        y = [2**x for x in n]
        titulo = 'O(2^n) - Tiempo exponencial'
    elif big_o == 'O(n!)':
        n = list(range(1, 11))
        y = [math.factorial(x) for x in n]
        titulo = 'O(n!) - Tiempo factorial'
    else:
        print("Notación no soportada")
        return
    
    # Crear la gráfica
    plt.figure(figsize=(10, 6))
    plt.plot(n, y, 'b-', linewidth=2)
    plt.xlabel('Tamaño de entrada (n)')
    plt.ylabel('Operaciones')
    plt.title(titulo)
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Uso: python graficar_big_o.py <Notacion_Big_O>")
        sys.exit(1)
    
    graficar_big_o(sys.argv[1])  # Ahora pasamos el argumento correctamente
