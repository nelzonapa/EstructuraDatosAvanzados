#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {

    /*Genero semilla*/
    srand(static_cast<unsigned>(time(nullptr)));

    // Archivo a crear
    const char* archivoNumeros = "numAleatorios.txt";

    // Cantidad de numeros a generar
    int num_numeros = 1000000;//establecemos que es un millón

    ofstream archivo(archivoNumeros);

    // En caso error
    if (!archivo) {
        cerr << "Error al abrir: " << archivoNumeros << endl;
        return 1;
    }

    // Generamos y escribimos los numeros aleatorios en el archivo
    for (int i = 0; i < num_numeros; ++i) {
        // Generamos un numero aleatorio en el rango [0, 1)
        double numero_aleatorio = static_cast<double>(rand()) / RAND_MAX;

        archivo << numero_aleatorio << "\n";
    }

    archivo.close();
    cout << "Se han generado " << num_numeros << " numeros aleatorios en el archivo " << archivoNumeros << endl;

    return 0;
}
