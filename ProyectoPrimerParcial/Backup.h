// backup.h
#ifndef BACKUP_H  // Si no está definida la macro BACKUP_H
#define BACKUP_H  // Define la macro BACKUP_H

#include <string>
#include <vector>  // Para el tipo vector

void crearCarpetaSiNoExiste(const std::string& ruta);
std::vector<std::string> listarArchivosEnCarpeta(const std::string& carpeta);

#endif  // FIN DEL INCLUDE GUARD