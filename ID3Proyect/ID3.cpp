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
#include <queue>
#define NOMBRE_ARCHIVO "Juego.csv"
using namespace std;

/// Floating point error.
constexpr float EPS = 1e-7;

//Atributos TiempoExterior,Temperatura,Humedad,Viento,Jugar
enum Atributos { TiempoExterior, Temperatura, Humedad, Viento };
const int NUMAtribs = 4;
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
    double A=0, B=0;
    //A p log 2 (p)
    if (p > 0) {
        A = p * log2(p);
    }

    if (n > 0) {
        B = n * log2(n);
    }

    return -A - B;
}

double merito(const vector<tDato>& Data, Atributos atrib) {
    switch (atrib) {
    case TiempoExterior: {
        double N = 0, a1 = 0, a2 = 0, a3 = 0;
        double p1 = 0, p2 = 0, p3 = 0, n1 = 0, n2 = 0, n3 = 0;
        for (tDato data : Data) {
            if (data.TiempoExterior == "soleado") {
                a1++;
                data.Jugar ? p1++ : n1++;
            }else if (data.TiempoExterior == "lluvioso") {
                a2++;
                data.Jugar ? p2++ : n2++;
            }else if (data.TiempoExterior == "nublado") {
                a3++;
                data.Jugar ? p3++ : n3++;
            }
            N++;
        }
        double A, B, C;

        A = (a1 != 0) ? a1 / N * infor(p1 / a1, n1 / a1) : 0;
        B = (a2 != 0) ? a2 / N * infor(p2 / a2, n2 / a2) : 0;
        C = (a3 != 0) ? a3 / N * infor(p3 / a3, n3 / a3) : 0;
        return A + B + C;
        break;
    }
    case Temperatura: {
        double N = 0, a1 = 0, a2 = 0, a3 = 0;
        double p1 = 0, p2 = 0, p3 = 0, n1 = 0, n2 = 0, n3 = 0;
        for (tDato data : Data) {
            if (data.Temperatura == "caluroso") {
                a1++;
                data.Jugar ? p1++ : n1++;
            }else if (data.Temperatura == "templado") {
                a2++;
                data.Jugar ? p2++ : n2++;
            } else if (data.Temperatura == "frio") {
                a3++;
                data.Jugar ? p3++ : n3++;
            }
            N++;
        }
        double A, B, C;

        A = (a1 != 0) ? a1 / N * infor(p1 / a1, n1 / a1) : 0;
        B = (a2 != 0) ? a2 / N * infor(p2 / a2, n2 / a2) : 0;
        C = (a3 != 0) ? a3 / N * infor(p3 / a3, n3 / a3) : 0;
        return A + B + C;
        break;
    }
    case Humedad: {
        double N = 0, a1 = 0, a2 = 0, a3 = 0;
        double p1 = 0, p2 = 0, p3 = 0, n1 = 0, n2 = 0, n3 = 0;
        for (tDato data : Data) {
            if (data.Humedad == "alta") {
                a1++;
                data.Jugar ? p1++ : n1++;
            } else if (data.Humedad == "normal") {
                a2++;
                data.Jugar ? p2++ : n2++;
            }else if (data.Humedad == "baja") { // TO-DO preguntar si existe baja
                a3++;
                data.Jugar ? p3++ : n3++;
            }
            N++;
        }
        double A, B, C;

        A = (a1 != 0) ? a1 / N * infor(p1 / a1, n1 / a1) : 0;
        B = (a2 != 0) ? a2 / N * infor(p2 / a2, n2 / a2) : 0;
        C = (a3 != 0) ? a3 / N * infor(p3 / a3, n3 / a3) : 0;
        return A + B + C;
        break;
    }
    case Viento: {
        double N = 0, a1 = 0, a2 = 0;
        double p1 = 0, p2 = 0, n1 = 0, n2 = 0;
        for (tDato data : Data) {
            if (data.Viento) {
                a1++;
                data.Jugar ? p1++ : n1++;
            }else {
                a2++;
                data.Jugar ? p2++ : n2++;
            }
            N++;
        }
        double A, B;
        A = a1 != 0 ? a1 / N * infor(p1 / a1, n1 / a1) : 0;
        B = a2 != 0 ? a2 / N * infor(p2 / a2, n2 / a2) : 0;
        return A + B;
        break;
    }
    default:
        return 0;
    }
}

void mostrarMeritos(priority_queue<double, vector<double>, greater<double>> pq) {
    cout << "MERITOS: ";
    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
}

int main(int argc, char** argv)
{
    vector<tDato> Data;
    lectura(Data);

    priority_queue<double, vector<double>, greater<double>> meritos; //TiempoExterior, Temperatura, Humedad, Viento

    meritos.push(merito(Data, TiempoExterior));
    meritos.push(merito(Data, Temperatura));
    meritos.push(merito(Data, Humedad));
    meritos.push(merito(Data, Viento));

    cout << endl;
    mostrarMeritos(meritos);
    cout << endl;
    //// Train the ID3.
    //auto id3 = ID3Train<N>(std::move(samples)).train();

    //// Print the ID3 tree.
    //id3->print(std::cout);

    return 0;
}

