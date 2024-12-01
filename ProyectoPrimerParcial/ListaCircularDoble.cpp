#include "ListaCircularDoble.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <direct.h>  // Para mkdir en Windows
#include <sys/stat.h>  // Para usar _stat
#include "Backup.h"  // Incluir el archivo de cabecera con la declaración de la función

using namespace std;

// Agregar libro
void ListaCircularDoble::agregarLibro(const Libro& libro) {
    Nodo* nuevo = new Nodo{libro, nullptr, nullptr};
    if (!cabeza) {
        cabeza = nuevo;
        cabeza->siguiente = cabeza;
        cabeza->anterior = cabeza;
    } else {
        Nodo* ultimo = cabeza->anterior;
        nuevo->siguiente = cabeza;
        nuevo->anterior = ultimo;
        cabeza->anterior = nuevo;
        ultimo->siguiente = nuevo;
    }
    cout << "Libro agregado: " << libro.getTitulo() << endl;
    // Guardar solo si no se está restaurando un backup
    if (!evitarGuardar) {
        guardarLibrosEnArchivo();
    }
}

// Limpiar la lista actual
void ListaCircularDoble::limpiarLista() {
    if (!cabeza) return;

    Nodo* actual = cabeza;
    do {
        Nodo* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    } while (actual != cabeza);

    cabeza = nullptr;
}

// Imprimir todos los libros
void ListaCircularDoble::imprimirLibros() {
    if (!cabeza) {
        cout << "No hay libros registrados.\n";
        return;
    }
    Nodo* actual = cabeza;
    cout << left << setw(20) << "Titulo" << setw(20) << "Autor" << setw(15) << "ISBN" << setw(6) << "Anio" << endl;
    cout << string(61, '-') << endl;
    do {
        cout << left << setw(20) << actual->libro.getTitulo()
            << setw(20) << actual->libro.getAutor()
            << setw(15) << actual->libro.getIsbn()
            << setw(6) << actual->libro.getAnio() << endl;
        actual = actual->siguiente;
    } while (actual != cabeza);
}

// Buscar libro
Nodo* ListaCircularDoble::buscarLibro(const string& titulo) {
    if (!cabeza) return nullptr;
    Nodo* actual = cabeza;
    do {
        if (actual->libro.getTitulo() == titulo) return actual;
        actual = actual->siguiente;
    } while (actual != cabeza);
    return nullptr;
}

// Eliminar libro y actualizar archivo
void ListaCircularDoble::eliminarLibro(const string& titulo) {
    if (!cabeza) return;
    Nodo* actual = cabeza;
    bool encontrado = false;
    do {
        if (actual->libro.getTitulo() == titulo) {
            encontrado = true;
            if (actual->siguiente == actual) {  // Si es el único libro
                cabeza = nullptr;
            } else {
                Nodo* anterior = actual->anterior;
                Nodo* siguiente = actual->siguiente;
                anterior->siguiente = siguiente;
                siguiente->anterior = anterior;
                if (actual == cabeza) cabeza = siguiente;
            }
            delete actual;
            cout << "Libro eliminado: " << titulo << endl;
            break;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);

    if (!encontrado) {
        cout << "Libro no encontrado: " << titulo << endl;
    }

    // Actualizar el archivo después de la eliminación
    guardarLibrosEnArchivo();  
}

// Guardar los libros en el archivo (actualizado)
void ListaCircularDoble::guardarLibrosEnArchivo() {
    ofstream archivo("libros_temp.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo temporal para guardar.\n\n";
        return;
    }

    Nodo* actual = cabeza;
    if (actual) {
        do {
            archivo << actual->libro.getTitulo() << ";" << actual->libro.getAutor() << ";" 
                    << actual->libro.getIsbn() << ";" << actual->libro.getAnio() << endl;
            actual = actual->siguiente;
        } while (actual != cabeza);
    }

    archivo.close();

    // Verificar si el archivo temporal se creó correctamente
    if (FILE* file = fopen("libros_temp.txt", "r")) {
        fclose(file);
    } else {
        cout << "No se pudo crear el archivo temporal correctamente.\n";
        return;
    }

    // Eliminar el archivo de destino si ya existe
    if (remove(archivoLibros.c_str()) != 0) {
        // Si el archivo no se puede eliminar, mostrar error
        cout << "Error al eliminar el archivo de destino: " << archivoLibros << endl;
    }

    // Renombrar el archivo temporal a la ubicación final
    if (rename("libros_temp.txt", archivoLibros.c_str()) != 0) {
        // Mostrar error si renombrar falla
        perror("Error al renombrar el archivo temporal");
    } else {
        cout << "Libros guardados en el archivo: " << archivoLibros << endl;
    }
}

// Cargar los libros desde el archivo
void ListaCircularDoble::cargarLibrosDesdeArchivo() {
    ifstream archivo(archivoLibros);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para cargar los libros.\n";
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string titulo, autor, isbn;
        int anio;
        getline(ss, titulo, ';');
        getline(ss, autor, ';');
        getline(ss, isbn, ';');
        ss >> anio;
        
        Libro libro(titulo, autor, isbn, anio);
        agregarLibro(libro);
    }
    archivo.close();
    cout << "Libros cargados desde el archivo.\n";
}

// Backup
void ListaCircularDoble::crearBackup(const string& nombreArchivo) {
    string carpetaBackup = "backup";  // Carpeta donde se almacenan los backups
    
    // Asegurarnos de que la carpeta de backups exista
    crearCarpetaSiNoExiste(carpetaBackup);

    // Crear la ruta completa para el archivo de backup dentro de la carpeta "backup"
    string rutaCompleta = carpetaBackup + "\\" + nombreArchivo;

    // Crear el archivo de backup
    ofstream archivo(rutaCompleta);
    if (!archivo.is_open()) {
        cout << "Error al crear el archivo de backup en la ruta: " << rutaCompleta << endl;
        return;
    }

    // Iterar sobre los elementos de la lista circular y guardar los datos de cada libro en el archivo
    Nodo* actual = cabeza;
    if (actual) {
        do {
            archivo << actual->libro.getTitulo() << ";" 
                    << actual->libro.getAutor() << ";" 
                    << actual->libro.getIsbn() << ";" 
                    << actual->libro.getAnio() << "\n";
            actual = actual->siguiente;
        } while (actual != cabeza);
    }

    // Cerrar el archivo después de escribir los datos
    archivo.close();
    cout << "Backup creado correctamente en: " << rutaCompleta << endl;
}

// Restaurar backup y sobreescribir archivo
void ListaCircularDoble::restaurarBackup(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de backup.\n";
        return;
    }

    cout << "Cargando backup desde: " << nombreArchivo << endl;

    limpiarLista();
    evitarGuardar = true; // Evitar guardar durante la restauración

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string titulo, autor, isbn;
        int anio;
        getline(ss, titulo, ';');
        getline(ss, autor, ';');
        getline(ss, isbn, ';');

        if (!(ss >> anio)) {
            cout << "Error al leer el año del libro. Línea ignorada.\n";
            continue;
        }

        Libro libro(titulo, autor, isbn, anio);
        agregarLibro(libro);
    }

    evitarGuardar = false; // Volver a guardar normalmente
    archivo.close();

    guardarLibrosEnArchivo();
    cout << "Backup restaurado: " << nombreArchivo << endl;
}