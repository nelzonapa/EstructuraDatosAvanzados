"""
Usaremos las bibliotecas como NumPy y Matplotlib para crear un 
histograma para cada dimensión con los datos guardados en el txt.
"""

import matplotlib.pyplot as plt #Para fácil uso

# lista vacía para las distanciasEuclidianas
distanciasEuclidianas = []

with open("distanciasEuclidianas.txt", "r") as archivo:
    for linea in archivo: #recorrerá cada línea del archivo
        distancia = float(linea.strip())    #convertir de a float
        distanciasEuclidianas.append(distancia) #distancias agregadas

# Partes del Histograma
# Partes automáticas para el histograma según manual Matplotlib
plt.hist(distanciasEuclidianas, bins=20, edgecolor="k") #hist: histograma
#bins: cantidad de contenedores
# k: color de los bordes de las barras, k es negro
plt.xlabel("Distancia Euclidiana")
plt.ylabel("Frecuencia")
plt.title("Histograma de Distancias")
plt.grid(True) # las líneas de la cuadrícula
plt.show() # Mostrar
