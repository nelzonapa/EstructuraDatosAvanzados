/*Mismas Bibliotecas*/
//Nelzon
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>//para time

using namespace std;
// Particionamos el array con un pivote
int particionar(vector<float>& array, int izq, int der) 
{
    float pivote = array[der]; // último elemento como pivote
    int i = (izq - 1); // elemento más pequeño

    for (int j = izq; j <= der - 1; j++) 
    {
        if (array[j] < pivote) {
            i++;
            swap(array[i], array[j]);
        }
    }

    swap(array[i + 1], array[der]);
    return (i + 1);
}

// Quick Sort
void quickSort(vector<float>& array, int izq, int der) 
{
    if (izq < der) 
    {
        int indiceParticion = particionar(array, izq, der);

        // Ordenar elementos antes y después de la partición
        quickSort(array, izq, indiceParticion - 1);
        quickSort(array, indiceParticion + 1, der);
    }
}

int main() {
    ifstream archivo1("numAleatorios.txt");
    if (!archivo1) 
    {
        cout << "Error archivo1" << endl;
        return 1;
    }
    //guardar los tiempos de ordenamiento
    ofstream archivo2("tiemposQuickSort.txt");
    if (!archivo2) 
    {
        cout << "Error archivo2" << endl;
        return 1;
    }
    // para guardar los números ordenados
    ofstream archivo3("numOrdenadosQuickSort.txt"); 
    if (!archivo3) 
    {
        cout << "Error archivo3" << endl;
        return 1;
    }

    int totalNumeros = 1000000;
    int puntoCantidadDatos = 100000;
    vector<float> vectNumeros;
    vectNumeros.reserve(totalNumeros);
    float numeroAux;

    while (archivo1 >> numeroAux) 
    {
        vectNumeros.push_back(numeroAux);

        // Realizamos el Quick Sort y medimos tiempo
        if (vectNumeros.size() == puntoCantidadDatos) 
        {
            auto inicio = chrono::high_resolution_clock::now();
            quickSort(vectNumeros, 0, vectNumeros.size() - 1);
            auto fin = chrono::high_resolution_clock::now();
            chrono::duration<double> duracion = fin - inicio;
            archivo2 << duracion.count() << endl;

            // Guardamos num Ordenados
            for (const float& num : vectNumeros)
                archivo3 << num << endl;

            // Limpiamos vector
            vectNumeros.clear();
        }
    }

    // El resto lo mismo
    if (!vectNumeros.empty()) 
    {
        auto inicio = chrono::high_resolution_clock::now();
        quickSort(vectNumeros, 0, vectNumeros.size() - 1);
        auto fin = chrono::high_resolution_clock::now();
        chrono::duration<double> duracion = fin - inicio;

        for (const float& num : vectNumeros)
            archivo3 << num << endl;
    }

    archivo1.close();
    archivo2.close();
    archivo3.close();

    return 0;
}
