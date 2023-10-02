/*Mismas Bibliotecas*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>   //Par tiempo
//#include
//Nelzon
using namespace std;

// Función para realizar el Shell Sort
void shellSort(vector<float>& array) 
{
    int tamanioArray = array.size();

    // Comenzar con un espacio grande y reducirlo en cada iteración
    for (int espacio = tamanioArray / 2; espacio > 0; espacio /= 2) 
    {
        for (int i = espacio; i < tamanioArray; ++i) 
        {
            float aux = array[i];
            int j;//para el for
            //logaritmo de Shell Sort
            for (j = i; j >= espacio && array[j - espacio] > aux; j -= espacio) 
            {
                array[j] = array[j - espacio];
            }
            array[j] = aux;
        }
    }
}

//Main funcion
int main() 
{
    ifstream archivo1("numAleatorios.txt");
    if (!archivo1) 
    {
        cout << "Error archivo1" << endl;
        return 1;
    }
    //guardar los tiempos de ordenamiento
    ofstream archivo2("tiemposShellSort.txt");
    if (!archivo2) 
    {
        cout << "Error archivo2" << endl;
        return 1;
    }
    // para guardar los números ordenados
    ofstream archivo3("numOrdenadosShellSort.txt"); 
    if (!archivo3) 
    {
        cout << "Error archivo3" << endl;
        return 1;
    }

    const int totalNumeros = 1000000;
    const int puntoCantidadDatos = 100000;
    vector<float> vectNumeros;
    vectNumeros.reserve(totalNumeros);
    float numeroAux;

    while (archivo1 >> numeroAux) 
    {
        vectNumeros.push_back(numeroAux);

        // aplicamos ShellSort y medimos time
        if (vectNumeros.size() == puntoCantidadDatos) 
        {
            auto inicio = chrono::high_resolution_clock::now();
            shellSort(vectNumeros);
            auto fin = chrono::high_resolution_clock::now();
            chrono::duration<double> duracion = fin - inicio;
            //Guardamos duración
            archivo2 << duracion.count() << endl;

            // Guardar los números ordenados en el archivo
            for (const float& num : vectNumeros)
                archivo3 << num << endl;

            // Limpiamos
            vectNumeros.clear();
        }
    }

    // Ordenar lo demás
    if (!vectNumeros.empty()) {
        auto inicio = chrono::high_resolution_clock::now();
        shellSort(vectNumeros);
        auto fin = chrono::high_resolution_clock::now();
        chrono::duration<double> duracion = fin - inicio;

        // Guardamos num ordenados
        for (const float& num : vectNumeros)
            archivo3 << num << endl;
    }

    archivo1.close();
    archivo2.close();
    archivo3.close();

    return 0;
}
