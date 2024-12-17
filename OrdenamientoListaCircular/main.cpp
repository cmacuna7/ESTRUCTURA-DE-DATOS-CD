#include "ListaCircularSimple.cpp"
#include "Menu.cpp"

int main() {
    // Configurar la consola para usar UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    // Verifica y crea la carpeta de backups si no existe
    BackupManager::crearCarpetaSiNoExiste("backup");

    ListaCircularSimple lista;
    // Cargar las personas desde el archivo al iniciar
    try {
        lista.cargarPersonasDesdeArchivo();
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error al cargar las personas desde el archivo: " << e.what() << std::endl;
        return 1;
    }

    mostrarMenu(lista);
    return 0;
}
