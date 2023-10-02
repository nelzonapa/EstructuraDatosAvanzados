/*Mismas Bibliotecas*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

// Función para el Insertion Sort
void ordenamientoInsercion(vector<float>& array) {
    int tamArray = array.size();
    
    for (int i = 1; i < tamArray; ++i) {
        float valorActual = array[i];
        int j = i - 1;

        /* Movemos elementos del array[0 a i-1] que son mayores 
        que el valorActual una posición hacia adelante*/
        while (j >= 0 && array[j] > valorActual) {
            array[j + 1] = array[j];
            --j;
        }
        
        // colocamos valorActual a su posición correcta
        array[j + 1] = valorActual;
    }
}

int main() {
    ifstream archivo1("numAleatorios.txt");
    if (!archivo1) 
    {
        cout << "Archivo1 error" << endl;
        return 1;
    }
    //tiempos
    ofstream archivo2("tiemposInsercionSort.txt");
    if (!archivo2) 
    {
        cout << "Archivo2 error" << endl;
        return 1;
    }
    //vectNumeros ordenados
    ofstream archivo3("numOrdenadosInsertionSort.txt");
    if (!archivo3) 
    {
        cout << "Archivo3 error" << endl;
        return 1;
    }

    int totalNumeros = 1000000;
    int puntoCantidadDatos = 100000;
    vector<float> vectNumeros;
    vectNumeros.reserve(totalNumeros);
    float numAux;

    while (archivo1 >> numAux) 
    {
        vectNumeros.push_back(numAux);

        // Realizamos el Insertion Sort y medimos tiempo
        if (vectNumeros.size() == puntoCantidadDatos) 
        {
            auto inicio = chrono::high_resolution_clock::now();
            ordenamientoInsercion(vectNumeros);
            auto fin = chrono::high_resolution_clock::now();
            chrono::duration<double> duracion = fin - inicio;
            archivo2 << duracion.count() << endl;

            // Guardamos los números ordenados en el archivo
            for (const float& num : vectNumeros)
                archivo3 << num << endl;

            // Limpiamos el vector para el siguiente bloque
            vectNumeros.clear();
        }
    }

    // Ordenamos los números restantes aparte del Punto de Datos
    if (!vectNumeros.empty()) 
    {
        auto inicio = chrono::high_resolution_clock::now();
        ordenamientoInsercion(vectNumeros);
        auto fin = chrono::high_resolution_clock::now();
        chrono::duration<double> duracion = fin - inicio;
        //Nelzon

        // Guardar los números ordenados en el archivo
        for (const float& num : vectNumeros)
            archivo3 << num << endl;
    }

    archivo1.close();
    archivo2.close();
    archivo3.close();

    return 0;
}
