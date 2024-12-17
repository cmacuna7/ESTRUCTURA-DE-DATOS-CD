#ifndef BACKUPMANAGER_H
#define BACKUPMANAGER_H

#include <string>
#include <vector>
#include "ListaSimple.h"

class BackupManager {
public:
    // Métodos públicos de la clase
    static void crearCarpetaSiNoExiste(const std::string& ruta);
    static std::vector<std::string> listarArchivosEnCarpeta(const std::string& carpeta);
    static void restaurarBackup(ListaSimple& lista);
};

#endif // BACKUPMANAGER_H
