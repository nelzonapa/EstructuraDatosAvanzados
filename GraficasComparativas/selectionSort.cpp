/*Mismas Bibliotecas*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>//Para el tiempo

using namespace std;

// Función para hacer el Selection Sort
void ordenamientoSeleccion(vector<float>& array) 
{
    int tamArray = array.size();
    for (int i = 0; i < tamArray - 1; ++i) 
    {
        int indiceMinimo = i;

        /*Encontramos el índice del elemento mínimo 
        en el subarreglo (no ordenado)*/
        //Nelzon
        for (int j = i + 1; j < tamArray; ++j) {
            if (array[j] < array[indiceMinimo]) {
                indiceMinimo = j;
            }
        }

        //intercambiar el elemento mínimo con el de la posición actual
        swap(array[i], array[indiceMinimo]);
    }
}

//Función Princiap
int main() 
{
    ifstream archivo1("numAleatorios.txt");
    if (!archivo1) 
    {
        cerr << "Error archivo1" << endl;
        return 1;
    }
    //guardar los tiempos de ordenamiento
    ofstream archivo2("tiemposSelectionSort.txt");
    if (!archivo2) 
    {
        cerr << "Error archivo2" << endl;
        return 1;
    }
    // para guardar los números ordenados
    ofstream archivo3("numOrdenadosSelectionSort.txt"); 
    if (!archivo3) 
    {
        cerr << "Error archivo3" << endl;
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

        /* Realizar el Selection Sort y medir el tiempo*/
        if (vectNumeros.size() == puntoCantidadDatos) 
        {
            auto inicio = chrono::high_resolution_clock::now();
            ordenamientoSeleccion(vectNumeros);
            auto fin = chrono::high_resolution_clock::now();
            chrono::duration<double> duracion = fin - inicio;
            archivo2 << duracion.count() << endl;

            // guardamos numeros ordenados
            for (const float& num : vectNumeros)
                archivo3 << num << endl;

            // Limpiaamos
            vectNumeros.clear();
        }
    }

    // Ordenar todo lo demás
    if (!vectNumeros.empty()) 
    {
        auto inicio = chrono::high_resolution_clock::now();
        ordenamientoSeleccion(vectNumeros);
        auto fin = chrono::high_resolution_clock::now();
        chrono::duration<double> duracion = fin - inicio;

        // Guardar los números ordenados en el archivo
        for (const float& num : vectNumeros)
            archivo3 << num << endl;
    }

    archivo1.close();
    archivo2.close();
    archivo3.close();

    return 0;
}
