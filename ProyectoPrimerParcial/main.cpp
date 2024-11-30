#include "ListaCircularDoble.cpp"
#include "Menu.cpp"

int main() {
    ListaCircularDoble lista;
    // Cargar los libros desde el archivo al iniciar
    lista.cargarLibrosDesdeArchivo();
    mostrarMenu(lista);
    return 0;
}
