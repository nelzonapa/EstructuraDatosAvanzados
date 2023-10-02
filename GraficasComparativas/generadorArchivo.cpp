#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>


using namespace std;

int main() {

    /*Genero semilla*/
    srand(static_cast<unsigned>(time(nullptr)));
    //
    // Archivo a crear
    const char* archivoNumeros = "numAleatorios.txt";

    // Cantidad de numeros a generar
    int cantNumeros = 1000000;//establecemos que es un millón

    ofstream archivo(archivoNumeros);
    //
    // En caso erdror
    if (!archivo) {
        cerr << "Error al abrir: " << archivoNumeros << endl;
        return 1;
    }

    // Generamos y escribimos los numeros aleatorios en el archivo
    for (int i = 0; i < cantNumeros; ++i) {
        // Generamos un numero aleatorio en el rango [0, 1)
        double numAleatorio = static_cast<double>(rand()) / RAND_MAX;
        archivo << numAleatorio << "\n";
    }

    archivo.close();
    cout << "Numeros generados con exito.." <<endl;

    return 0;
}
