#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

// Función para que se de el max-heap
//  Nelzon
void convMaxHeap(vector<float>& array, int arraySize, int i) {
    int masGrande = i;
    int izq = 2*i+1;
    int dere = 2*i+2;

    /*Si el niño izquierdo del nodo actual es mayor que el elemento actual 
    más grande en el montón.El índice del niño izquierdo 
    se actualiza como el nuevo elemento más grande.*/
    if (izq < arraySize && array[izq] > array[masGrande])
        masGrande = izq;

    //Lo mismo que antes, solo que ahora hijo derecha
    if (dere < arraySize && array[dere] > array[masGrande])
        masGrande = dere;

    
    //Parte de Max HeAP
    if (masGrande != i) {
        swap(array[i], array[masGrande]);
        convMaxHeap(array, arraySize, masGrande);
    }
}

void heapSort(vector<float>& array) {
    int arraySize = array.size();
    // bucle for
    for (int i = arraySize / 2 - 1; i >= 0; --i)
        convMaxHeap(array, arraySize, i);

    for (int i = arraySize - 1; i > 0; --i) {
        swap(array[0], array[i]);
        convMaxHeap(array, i, 0);
    }
}

int main() {
    ifstream archivo1("numAleatorios.txt"); //para leer numeros
    if (!archivo1) {
        cout << "error archivo 1" << endl;
        return 1;
    }

    ofstream archivo2("tiemposHeapSort.txt"); // para guardar los tiempos
    if (!archivo2) {
        cout << "error archivo 2" << endl;
        return 1;
    }

    ofstream archivo3("numOrdenadosHeapSort.txt"); //para guardar los números ordenados
    if (!archivo3) {
        cout << "error archivo 3" << endl;
        return 1;
    }

    int numTotalEvaluar = 1000000;
    int puntoCantidadDatos = 100000;
    vector<float> vectNumeros;
    vectNumeros.reserve(numTotalEvaluar);
    float numberAux;

    while (archivo1 >> numberAux) {
        vectNumeros.push_back(numberAux);

        // Realizar el Heap Sort y medir el tiempo cuando se alcanza cada puntoCantidadDatos
        if (vectNumeros.size() == puntoCantidadDatos) {
            auto inicia = chrono::high_resolution_clock::now();
            heapSort(vectNumeros);
            auto termina = chrono::high_resolution_clock::now();
            chrono::duration<double> duration = termina - inicia;
            archivo2 << duration.count() <<endl;

            // Guardar los números ordenados en el archivo
            for (const float& num : vectNumeros)
                archivo3 << num << endl;

            // Limpia el vector para el siguiente chunk
            vectNumeros.clear();
        }
    }

    // ordenar los números restantes
    if (!vectNumeros.empty()) {
        auto inicia = chrono::high_resolution_clock::now();
        heapSort(vectNumeros);
        auto termina = chrono::high_resolution_clock::now();
        chrono::duration<double> duracion = termina - inicia;
        // archivo2 << duracion.count() << endl;

        // Guardar los números ordenados en el archivo
        for (const float& num : vectNumeros)
            archivo3 << num << endl;
    }

    archivo1.close();
    archivo2.close();
    archivo3.close();

    return 0;
}
