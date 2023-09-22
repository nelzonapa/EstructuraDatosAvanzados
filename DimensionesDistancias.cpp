/*
Para cada dimensión d (10, 50, 100, 500, 1000, 2000, 5000) que ejecutaré en el programa, 
realizaré lo siguiente:

a. Generaré 100 puntos aleatorios en un espacio de dimensión d(opción que 
ingresará el usuario, probaremos las 9 dimensiones propuestas), 
donde cada coordenada de un punto es un número aleatorio entre 0 y 1. 
Usaremos “std::uniform_real_distribution”.

b. Calcularé la distancia euclidiana entre todos los pares de puntos que se 
debió generar en el punto A. Esto generará 100 * 99 / 2 = 4950 distancias en total.
Utilizaré la fórmula de distancia euclidiana en C++ para calcular las distancias.

c. Exportaré los resultados de las distancias obtenidas para cada dimensión en un 
archivo TXT. Para que luego Python logre graficar los histogramas.
*/
/*
    Nelzon Jorge Apaza Apaza
    EDA LABORATORIO
    La MALDICIÓN DE LA DIMENSIONALIDAD
*/
#include <iostream>
#include <random> //aqui tenmos a uniform_real_distribution
#include <cmath>//operacion pow y sqrt
#include <fstream>

using namespace std;

int main() {
    // d: dimension
    int d;
    cout<<"Ingrese la dimension: "<<endl;
    cin>>d;
    int numPuntosAleatorios = 100; //100 numeros aleatorios

    // Aquí generamos el número aleatorio
    // Tal y como indica el ejemplo de uniform_real_distribution
    random_device rd;  //rd se utilizará para obtener una semilla para el motor de números aleatorios
    mt19937 gen(rd()); //usamos la semilla
    uniform_real_distribution<double> dis(0.0, 1.0);//desde 0 a 1


    // Abre un archivo para escribir las distancias
    std::ofstream archivo("distanciasEuclidianas.txt");

    // Verifica que el archivo se haya abierto correctamente
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo para escritura." << std::endl;
        return 1;
    }


    //Solo usaremos una matriz de tamaño numPuntos*dimension
    double MatrizPuntos[numPuntosAleatorios][d];

    // Generamos los puntos aleatorios
    for (int i = 0; i < numPuntosAleatorios; ++i) {
        for (int j = 0; j < d; ++j) {
            MatrizPuntos[i][j] = dis(gen);
            /*
            Asigna un número aleatorio en el rango [0.0, 1.0] 
            a la coordenada j del punto i en la matriz MatrizPuntos.
            */
        }
    }

    // Aquí calculamos la distancia eucladiana, imitando la formula
    /*
    * No se debe calcular la distancia entre un punto y sí mismo.
    * No se debe calcular dos veces la misma distancia.
    */
    for (int i = 0; i < numPuntosAleatorios; ++i) {
        for (int j = i + 1; j < numPuntosAleatorios; ++j) {
            double distEuclidiana = 0.0;//Acumulador

            /*
            * Calculamos la diferencia al cuadrado entre las coordenadas k de 
            los puntos i y j.
            * Se suma a distEuclidiana y se acumulan estas diferencias al 
            cuadrado (pow) para todas las dimensiones.
            */
            for (int k = 0; k < d; ++k) {
                distEuclidiana += pow(MatrizPuntos[i][k] - MatrizPuntos[j][k], 2);
            }
            distEuclidiana = sqrt(distEuclidiana);//sacamos raiz
            //Resultado
            cout << "Distancia Euclidiana entre punto " << i << " y punto " << j << ": " << distEuclidiana << endl;
            //Guardamos distancias
            archivo << distEuclidiana << std::endl;
        }
    }

    // Cierra el archivo txt
    archivo.close();

    return 0;
}