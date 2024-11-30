#include "ListaCircularDoble.cpp"
#include "Menu.cpp"

int main() {
     // Verifica y crea la carpeta de backups si no existe
    crearCarpetaSiNoExiste("backup");

    ListaCircularDoble lista;
    // Cargar los libros desde el archivo al iniciar
    lista.cargarLibrosDesdeArchivo();
    mostrarMenu(lista);
    return 0;
}
