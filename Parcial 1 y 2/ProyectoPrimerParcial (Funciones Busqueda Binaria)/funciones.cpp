#include "funciones.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip> // Para std::setw y std::left

using namespace std;

// Función para dividir una línea por un delimitador
vector<string> dividir(const std::string& linea, char delimitador) {
    vector<string> partes;
    stringstream ss(linea);
    string parte;
    while (getline(ss, parte, delimitador)) {
        partes.push_back(parte);
    }
    return partes;
}

// Función para imprimir la cabecera formateada
void imprimirCabecera() {
    cout << left;
    cout << setw(40) << "Título"
         << setw(25) << "Autor"
         << setw(22) << "ISNI"
         << setw(20) << "ISBN"
         << setw(15) << "Publicación"
         << "Nac. Autor" << endl;

    cout << string(120, '-') << endl; // Línea divisoria
    cout << "\n";
}

// Función para buscar registros en un rango de años
void buscarPorRango(const std::string& rutaArchivo, int anioInicio, int anioFin) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    string linea;
    // Lambda para verificar si el año está en el rango
    auto filtrarPorRango = [anioInicio, anioFin](const string& fecha) {
        int anioPublicacion = stoi(fecha.substr(fecha.size() - 4));
        return anioPublicacion >= anioInicio && anioPublicacion <= anioFin;
    };

    bool cabeceraImprimida = false;

    while (getline(archivo, linea)) {
        vector<string> campos = dividir(linea, ';');
        if (campos.size() >= 6) {
            string titulo = campos[0];
            string autor = campos[1];
            string isni = campos[2];
            string fechaNacimiento = campos[3];
            string isbn = campos[4];
            string fechaPublicacion = campos[5];

            // Usamos la lambda para filtrar
            if (filtrarPorRango(fechaPublicacion)) {
                if (!cabeceraImprimida) {
                    imprimirCabecera();
                    cabeceraImprimida = true;
                }

                // Imprimimos el registro formateado
                cout << left;
                cout << setw(40) << titulo
                     << setw(25) << autor
                     << setw(22) << isni
                     << setw(20) << isbn
                     << setw(15) << fechaPublicacion
                     << fechaNacimiento << endl;
            }
        }
    }

    archivo.close();
}

// Funcion de busqueda binaria por rango de fecha de nacimiento del autor
void buscarPorRangoFechaNacimiento(const std::string& rutaArchivo, int anioInicio, int anioFin) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    string linea;
    // Lambda para verificar si el año está en el rango
    auto filtrarPorRango = [anioInicio, anioFin](const string& fecha) {
        int anioNacimiento = stoi(fecha.substr(fecha.size() - 4));
        return anioNacimiento >= anioInicio && anioNacimiento <= anioFin;
    };

    bool cabeceraImprimida = false;

    while (getline(archivo, linea)) {
        vector<string> campos = dividir(linea, ';');
        if (campos.size() >= 6) {
            string titulo = campos[0];
            string autor = campos[1];
            string isni = campos[2];
            string fechaNacimiento = campos[3];
            string isbn = campos[4];
            string fechaPublicacion = campos[5];

            // Usamos la lambda para filtrar
            if (filtrarPorRango(fechaNacimiento)) {
                if (!cabeceraImprimida) {
                    imprimirCabecera();
                    cabeceraImprimida = true;
                }

                // Imprimimos el registro formateado
                cout << left;
                cout << setw(40) << titulo
                     << setw(25) << autor
                     << setw(22) << isni
                     << setw(20) << isbn
                     << setw(15) << fechaPublicacion
                     << fechaNacimiento << endl;
            }
        }
    }

    archivo.close();
}

//Funcion de busqueda binaria por prefijo de ISBN
void buscarPorPrefijoISBN(const std::string& rutaArchivo, const std::string& prefijo) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    string linea;
    // Lambda para verificar si el ISBN empieza con el prefijo
    auto filtrarPorPrefijo = [prefijo](const string& isbn) {
        return isbn.find(prefijo) == 0;
    };

    bool cabeceraImprimida = false;

    while (getline(archivo, linea)) {
        vector<string> campos = dividir(linea, ';');
        if (campos.size() >= 6) {
            string titulo = campos[0];
            string autor = campos[1];
            string isni = campos[2];
            string fechaNacimiento = campos[3];
            string isbn = campos[4];
            string fechaPublicacion = campos[5];

            // Usamos la lambda para filtrar
            if (filtrarPorPrefijo(isbn)) {
                if (!cabeceraImprimida) {
                    imprimirCabecera();
                    cabeceraImprimida = true;
                }

                // Imprimimos el registro formateado
                cout << left;
                cout << setw(40) << titulo
                     << setw(25) << autor
                     << setw(22) << isni
                     << setw(20) << isbn
                     << setw(15) << fechaPublicacion
                     << fechaNacimiento << endl;
            }
        }
    }

    archivo.close();
}

//Busqueda binaria por prefijo de autor
void buscarPorPrefijoAutor(const std::string& rutaArchivo, const std::string& prefijo) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    string linea;
    // Lambda para verificar si el autor empieza con el prefijo
    auto filtrarPorPrefijo = [prefijo](const string& autor) {
        return autor.find(prefijo) == 0;
    };

    bool cabeceraImprimida = false;

    while (getline(archivo, linea)) {
        vector<string> campos = dividir(linea, ';');
        if (campos.size() >= 6) {
            string titulo = campos[0];
            string autor = campos[1];
            string isni = campos[2];
            string fechaNacimiento = campos[3];
            string isbn = campos[4];
            string fechaPublicacion = campos[5];

            // Usamos la lambda para filtrar
            if (filtrarPorPrefijo(autor)) {
                if (!cabeceraImprimida) {
                    imprimirCabecera();
                    cabeceraImprimida = true;
                }

                // Imprimimos el registro formateado
                cout << left;
                cout << setw(40) << titulo
                     << setw(25) << autor
                     << setw(22) << isni
                     << setw(20) << isbn
                     << setw(15) << fechaPublicacion
                     << fechaNacimiento << endl;
            }
        }
    }

    archivo.close();
}

//Búsqueda por Rango de ISBN
void buscarPorRangoISBN(const std::string& rutaArchivo, const std::string& isbnInicio, const std::string& isbnFin) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    string linea;
    // Lambda para verificar si el ISBN está en el rango
    auto filtrarPorRango = [isbnInicio, isbnFin](const string& isbn) {
        return isbn >= isbnInicio && isbn <= isbnFin;
    };

    bool cabeceraImprimida = false;

    while (getline(archivo, linea)) {
        vector<string> campos = dividir(linea, ';');
        if (campos.size() >= 6) {
            string titulo = campos[0];
            string autor = campos[1];
            string isni = campos[2];
            string fechaNacimiento = campos[3];
            string isbn = campos[4];
            string fechaPublicacion = campos[5];

            // Usamos la lambda para filtrar
            if (filtrarPorRango(isbn)) {
                if (!cabeceraImprimida) {
                    imprimirCabecera();
                    cabeceraImprimida = true;
                }

                // Imprimimos el registro formateado
                cout << left;
                cout << setw(40) << titulo
                     << setw(25) << autor
                     << setw(22) << isni
                     << setw(20) << isbn
                     << setw(15) << fechaPublicacion
                     << fechaNacimiento << endl;
            }
        }
    }

    archivo.close();
}

//Búsqueda por Prefijo de ISNI
void buscarPorPrefijoISNI(const std::string& rutaArchivo, const std::string& prefijo) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    string linea;
    // Lambda para verificar si el ISNI empieza con el prefijo
    auto filtrarPorPrefijo = [prefijo](const string& isni) {
        return isni.find(prefijo) == 0;
    };

    bool cabeceraImprimida = false;

    while (getline(archivo, linea)) {
        vector<string> campos = dividir(linea, ';');
        if (campos.size() >= 6) {
            string titulo = campos[0];
            string autor = campos[1];
            string isni = campos[2];
            string fechaNacimiento = campos[3];
            string isbn = campos[4];
            string fechaPublicacion = campos[5];

            // Usamos la lambda para filtrar
            if (filtrarPorPrefijo(isni)) {
                if (!cabeceraImprimida) {
                    imprimirCabecera();
                    cabeceraImprimida = true;
                }

                // Imprimimos el registro formateado
                cout << left;
                cout << setw(40) << titulo
                     << setw(25) << autor
                     << setw(22) << isni
                     << setw(20) << isbn
                     << setw(15) << fechaPublicacion
                     << fechaNacimiento << endl;
            }
        }
    }

    archivo.close();
}

//Búsqueda por Sufijo de Autor
void buscarPorSufijoAutor(const std::string& rutaArchivo, const std::string& sufijo) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    string linea;
    // Lambda para verificar si el autor termina con el sufijo
    auto filtrarPorSufijo = [sufijo](const string& autor) {
        return autor.find(sufijo) == autor.size() - sufijo.size();
    };

    bool cabeceraImprimida = false;

    while (getline(archivo, linea)) {
        vector<string> campos = dividir(linea, ';');
        if (campos.size() >= 6) {
            string titulo = campos[0];
            string autor = campos[1];
            string isni = campos[2];
            string fechaNacimiento = campos[3];
            string isbn = campos[4];
            string fechaPublicacion = campos[5];

            // Usamos la lambda para filtrar
            if (filtrarPorSufijo(autor)) {
                if (!cabeceraImprimida) {
                    imprimirCabecera();
                    cabeceraImprimida = true;
                }

                // Imprimimos el registro formateado
                cout << left;
                cout << setw(40) << titulo
                     << setw(25) << autor
                     << setw(22) << isni
                     << setw(20) << isbn
                     << setw(15) << fechaPublicacion
                     << fechaNacimiento << endl;
            }
        }
    }

    archivo.close();
}
