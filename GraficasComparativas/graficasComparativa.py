import matplotlib.pyplot as plt
#Usaremos MatplotLib
#Nelzon
# Lista de nombres de archivos
direc = "d:/UNSA/3ER AÑO/2do semestre/EDA/GraficasComparativas/tiempos"
nombresAlgoritmos = ["BubbleSort", "HeapSort", "InsercionSort",
                    "MergeSort", "QuickSort", "SelectionSort", "ShellSort"]

nombresDirecciones = [direc + "BubbleSort.txt", direc + "HeapSort.txt", direc + "InsercionSort.txt",
                    direc + "MergeSort.txt", direc + "QuickSort.txt", direc + "SelectionSort.txt", direc + "ShellSort.txt"]

# Lista de colores para distinguir cada línea
colores = ['b', 'g', 'r', 'c', 'm', 'y', 'k']

# Creamos una figura para la gráfica
plt.figure(figsize=(10, 6))

# Para cada archivo en la lista
for i, archivo_nombre in enumerate(nombresDirecciones):
    tiempos = []

    # Leemos los tiempos desde el archivo de texto
    with open(archivo_nombre, "r") as archivo:
        for linea in archivo:
            tiempo = float(linea.strip())
            tiempos.append(tiempo)

    # Creamos una lista que represente los puntos de cada 100,000 números
    cantidad_datos = [j * 100000 for j in range(1, len(tiempos) + 1)]

    # Crear la gráfica para el archivo actual
    plt.plot(cantidad_datos, tiempos, marker='o', linestyle='-', color=colores[i], label=nombresAlgoritmos[i])

# Las etiquetas, en si la LEYENDA
plt.title('Velocidad de Algoritmos de ordenamiento (Complejidad)')
plt.xlabel('Datos (1 000 000)')
plt.ylabel('Tiempo (segundos)')

# valores a mostrar en los ejes x e y
plt.xticks(cantidad_datos, rotation=45)
plt.yticks([i * 8 for i in range(0, int(max(tiempos) * 150))])#*8,*0.1, *0.01

plt.grid(True)
plt.legend()

# gráfica ejecutamos
plt.tight_layout()
plt.show()
