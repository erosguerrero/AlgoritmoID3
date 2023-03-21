#include <cmath>
#include <cstdlib>

#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <math.h>  
#define NOMBRE_ARCHIVO "Juego.csv"
using namespace std;

/// Floating point error.
constexpr float EPS = 1e-7;

//Atributos TiempoExterior,Temperatura,Humedad,Viento,Jugar
enum Atributos { TiempoExterior, Temperatura, Humedad, Viento };
struct tDato {
    int id;
    string TiempoExterior, Temperatura, Humedad;
    bool Viento, Jugar;

    void show() {
        cout << "[" << id << "]" << " Tiempo: " << TiempoExterior << ", Temperatura: " << Temperatura << ", Humedad: " << Humedad << ", Viento: " << (Viento ? "si" : "no") << ", Jugar: " << (Jugar ? "si" : "no") << endl;
    }
};

bool lectura(vector<tDato>& Data) {
    //LECTURA
    ifstream archivo(NOMBRE_ARCHIVO);
    string linea;
    char delimitador = ',';
    // Leemos todas las líneas
    int pos = 0;
    while (getline(archivo, linea))
    {
        if (!linea.length() == 0) {
            stringstream stream(linea); // Convertir la cadena a un stream
            tDato d; d.id = pos;

            // Extraer todos los valores de esa fila
            getline(stream, d.TiempoExterior, delimitador);
            getline(stream, d.Temperatura, delimitador);
            getline(stream, d.Humedad, delimitador);
            string Viento, Jugar;
            getline(stream, Viento, delimitador);
            getline(stream, Jugar, delimitador);
            d.Viento = Viento == "verdad";
            d.Jugar = Jugar == "si";
            // Imprimir
            d.show();
            Data.push_back(d);
            pos++;
        }
    }
    archivo.close();
    return true;
}

double infor(double p, double n) {
    double A, B;
    //A p log 2 (p)
    if (p > 0) {
        A = p * log2(p);
    }
    else {
        A = 0;
    }
    if (n > 0) {
        B = n * log2(n);
    }
    else {
        B = 0;
    }
    return -A - B;
}

double merito(const vector<tDato>& Data, Atributos atrib) {
    switch (atrib) {
    case TiempoExterior: {
        int N = 0, a1 = 0, a2 = 0, a3 = 0, pos = 0, neg = 0;
        for (tDato data : Data) {
            if (data.Jugar) {
                pos++;
            }
            else {
                neg++;
            }
            if (data.TiempoExterior == "soleado") {
                a1++;
            }
            else if (data.TiempoExterior == "lluvioso") {
                a2++;
            }
            else if (data.TiempoExterior == "nublado") {
                a3++;
            }
            N++;
        }
        return (a1 / N * infor(pos / a1, neg / a1) + a2 / N * infor(pos / a2, neg / a2) + a3 / N * infor(pos / a3, neg / a3));
        break;
    }
    case Temperatura: {
        int N = 0, a1 = 0, a2 = 0, a3 = 0, pos = 0, neg = 0;
        for (tDato data : Data) {
            if (data.Jugar) {
                pos++;
            }
            else {
                neg++;
            }
            if (data.Temperatura == "caluroso") {
                a1++;
            }
            else if (data.Temperatura == "templado") {
                a2++;
            }
            else if (data.Temperatura == "frio") {
                a3++;
            }
            N++;
        }
        return (a1 / N * infor(pos / a1, neg / a1) + a2 / N * infor(pos / a2, neg / a2) + a3 / N * infor(pos / a3, neg / a3));
        break;
    }
    case Humedad: {
        int N = 0, a1 = 0, a2 = 0, a3 = 0, pos = 0, neg = 0;
        for (tDato data : Data) {
            if (data.Jugar) {
                pos++;
            }
            else {
                neg++;
            }
            if (data.Humedad == "alta") {
                a1++;
            }
            else if (data.Humedad == "normal") {
                a2++;
            }
            else if (data.Humedad == "baja") { // TO-DO preguntar si existe baja
                a3++;
            }
            N++;
        }
        return (a1 / N * infor(pos / a1, neg / a1) + a2 / N * infor(pos / a2, neg / a2) + a3 / N * infor(pos / a3, neg / a3));
        break;
    }
    case Viento: {
        int N = 0, a1 = 0, a2 = 0, a3 = 0, pos = 0, neg = 0;
        for (tDato data : Data) {
            if (data.Jugar) {
                pos++;
            }
            else {
                neg++;
            }
            if (data.Viento) {
                a1++;
            }
            else {
                a2++;
            }
            N++;
        }
        return (a1 / N * infor(pos / a1, neg / a1) + a2 / N * infor(pos / a2, neg / a2));
        break;
    }
    default:
        return 0;
    }
}
/**
 * Entry point of the application.
 */
int main(int argc, char** argv)
{
    vector<tDato> Data;
    lectura(Data);

    //// Train the ID3.
    //auto id3 = ID3Train<N>(std::move(samples)).train();

    //// Print the ID3 tree.
    //id3->print(std::cout);

    return 0;
}
