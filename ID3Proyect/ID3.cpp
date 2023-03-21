#include <cmath>
#include <cstdlib>

#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <vector>
#define NOMBRE_ARCHIVO "Juego.csv"
using namespace std;

/// Floating point error.
constexpr float EPS = 1e-7;



struct tDato {
    string id, TiempoExterior, Temperatura, Humedad;
    bool Viento, Jugar;

    void show() {
        cout << "[" << id << "]" << "Tiempo: " << TiempoExterior << "Temperatura: " << Temperatura << "Humedad: " << Humedad << "Viento: " << (Viento ? "si" : "no") << "Jugar: " << (Jugar ? "si":"no") << endl;
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

    archivo.close();
    return true;
}

/**
 * Entry point of the application.
 */
int main(int argc, char** argv)
{


    // Read the samples.
    {
        std::ifstream is(argc >= 2 ? argv[1] : "data");
        while (!is.eof()) {
            Sample<N> sample;
            for (auto i = 0; i < N; ++i) {
                if (!(is >> sample.attributes[i])) {
                    break;
                }
            }
            if (!(is >> sample.clazz)) {
                break;
            }
            samples.push_back(std::move(sample));
        }
    }

    // Train the ID3.
    auto id3 = ID3Train<N>(std::move(samples)).train();

    // Print the ID3 tree.
    id3->print(std::cout);

    // Classify some samples from stdin.
    {
        std::string line;
        while (line.resize(512), cin.getline(&line[0], line.size())) {
            line.resize(line.find_first_of('\0'));
            if (line.size() == 0) {
                break;
            }
            std::stringstream is(line);
            std::array<std::string, N> sample;
            for (auto i = 0; i < N; ++i) {
                if (!(is >> sample[i])) {
                    return EXIT_SUCCESS;
                }
            }
            std::cout << id3->classify(sample) << std::endl;
        }
    }

    return 0;
}