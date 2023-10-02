#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

// Función Bubble Sort
void bubbleSort(vector<float>& array) {
    int n = array.size();
    bool intercambio;
    do 
    {
        intercambio = false;
        for (int i = 1; i < n; ++i) 
        {
            if (array[i - 1] > array[i]) 
            {
                swap(array[i - 1], array[i]);
                intercambio = true;
            }
        }
        n--;
    } 
    while(intercambio);
}

int main() {
    ifstream archivo("numAleatorios.txt");
    if (!archivo) 
    {
        cout << "Error abriendo archivo numAleatorios.txt" << endl;
        return 1;
    }

    ofstream archivo2("tiemposBubbleSort.txt"); // Archivo que guardará los tiempos de ordenamiento
    if (!archivo2) 
    {
        cout << "No se pudo crear el archivo de tiempos." << endl;
        return 1;
    }

    ofstream archivo3("numOrdenadosBubbleSort.txt"); // Archivo que guardará los tiempos de ordenamiento
    if (!archivo3) 
    {
        cout << "No se pudo crear el archivo de tiempos." << endl;
        return 1;
    }

    int numerosTotal = 1000000;
    int puntoCantidadDatos = 100000;
    vector<float> vectNumeros;
    vectNumeros.reserve(numerosTotal);//reservamso spacio
    float numeroAux;

    while (archivo >> numeroAux) 
    {   //leemos
        vectNumeros.push_back(numeroAux);

        // se da el Bubble Sort y se saca los tiempos cada vez que se alcanza el punto 
        if (vectNumeros.size() == puntoCantidadDatos) 
        {
            //USAMOS la biblioteca CHRONO
            auto inicioTime = chrono::high_resolution_clock::now();
            bubbleSort(vectNumeros);
            auto FinalTime = chrono::high_resolution_clock::now();
            chrono::duration<double> duracion = FinalTime - inicioTime;
            archivo2 << duracion.count() << endl;
            // Guardar los números ordenados en el archivo
            for (const float& num : vectNumeros)
                archivo3 << num << endl;

            // Limpiamos vector para seguir
            vectNumeros.clear();
        }
    }

    // Ordenar los demás datos si no se llegó
    if (!vectNumeros.empty()) 
    {
        auto inicioTime = chrono::high_resolution_clock::now();
        bubbleSort(vectNumeros);
        auto FinalTime = chrono::high_resolution_clock::now();
        chrono::duration<double> duracion = FinalTime - inicioTime;
        // archivo2 << duracion.count() << endl;
        // Guardar los números ordenados en el archivo
        for (const float& num : vectNumeros)
            archivo3 << num << endl;
    }

    archivo.close();
    archivo2.close();
    archivo3.close();
    return 0;
}
