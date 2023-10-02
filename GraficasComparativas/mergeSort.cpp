/*Mismas Bibliotecas*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>//para tiempo

using namespace std;
//Nelzon

// fusionamos arreglos
void fusionar(vector<float>& array, int izq, int medio, int der) 
{
    int a = medio - izq + 1;
    int b = der - medio;

    // subarreglos temporales
    vector<float> izqArray(a);
    vector<float> derArray(b);

    // Copiamos datos a los subarreglos temporales
    for (int i = 0; i < a; i++)
        izqArray[i] = array[izq + i];
    for (int j = 0; j < b; j++)
        derArray[j] = array[medio + 1 + j];

    // Fusionamos los subarreglos temporales en el array original
    int i = 0, j = 0, k = izq;
    while (i < a && j < b) 
    {
        if (izqArray[i] <= derArray[j]) {
            array[k] = izqArray[i];
            i++;
        } else {
            array[k] = derArray[j];
            j++;
        }
        k++;
    }

    // Copiamos los elementos restantes de izqArray y derArray
    while (i < a) 
    {
        array[k] = izqArray[i];
        i++;
        k++;
    }

    while (j < b) 
    {
        array[k] = derArray[j];
        j++;
        k++;
    }
}

//Merge Sort
void mergeSort(vector<float>& array, int izq, int der) 
{
    if (izq < der) 
    {
        int medio = izq + (der - izq) / 2;

        // Ordenar la primera mitad y la segunda mitad
        mergeSort(array, izq, medio);
        mergeSort(array, medio + 1, der);

        // Fusionar las mitades ordenadas
        fusionar(array, izq, medio, der);
    }
}

int main() 
{
    ifstream archivo1("numAleatorios.txt");
    if (!archivo1) 
    {
        cout << "Error archivo1" << endl;
        return 1;
    }
    //guardar los tiempos de ordenamiento
    ofstream archivo2("tiemposMergeSort.txt");
    if (!archivo2) 
    {
        cout << "Error archivo2" << endl;
        return 1;
    }
    // para guardar los números ordenados
    ofstream archivo3("numOrdenadosMergeSort.txt"); 
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

        // Realizamos el Merge Sort y medimos el tiempo
        if (vectNumeros.size() == puntoCantidadDatos) 
        {
            auto inicio = chrono::high_resolution_clock::now();
            mergeSort(vectNumeros, 0, vectNumeros.size() - 1);
            auto fin = chrono::high_resolution_clock::now();
            chrono::duration<double> duracion = fin - inicio;
            //Duración
            archivo2 << duracion.count() << endl;

            // Guardamos numeros ordenados
            for (const float& num : vectNumeros)
                archivo3 << num << endl;

            // Limpiamos
            vectNumeros.clear();
        }
    }

    // Ordenamos lo restante, casi lo mismo de antes
    if (!vectNumeros.empty()) 
    {
        auto inicio = chrono::high_resolution_clock::now();
        mergeSort(vectNumeros, 0, vectNumeros.size() - 1);
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
