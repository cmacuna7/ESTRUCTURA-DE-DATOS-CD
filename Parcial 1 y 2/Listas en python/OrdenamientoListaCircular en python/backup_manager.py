"""
********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Lista Circular                                           *
 * Autor:                          Abner Arboleda, Marcelo Acuña, Christian bonifaz         *
 * Fecha de creacion:              26/12/2024                                               *
 * Fecha de modificacion:          26/12/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************
"""
import os

class BackupManager:
    @staticmethod
    def crearCarpetaSiNoExiste(ruta):
        if not os.path.exists(ruta):
            try:
                os.makedirs(ruta)
                print(f"Carpeta creada: {ruta}")
            except OSError as e:
                print(f"Error al crear la carpeta: {ruta}\n{e}")
        else:
            print(f"La carpeta ya existe: {ruta}")

    @staticmethod
    def listarArchivosEnCarpeta(carpeta):
        try:
            archivos = [f for f in os.listdir(carpeta) if os.path.isfile(os.path.join(carpeta, f))]
            return archivos
        except OSError as e:
            print(f"Error al acceder a la carpeta: {carpeta}\n{e}")
            return []

    @staticmethod
    def restaurarBackup(lista):
        carpetaBackup = "backup"
        archivos = BackupManager.listarArchivosEnCarpeta(carpetaBackup)

        if not archivos:
            print(f"No se encontraron archivos de backup en la carpeta {carpetaBackup}.")
            return

        print("Archivos disponibles para restaurar:")
        for i, archivo in enumerate(archivos):
            print(f"{i + 1}. {archivo}")

        seleccion = int(input("Seleccione un archivo para restaurar (ingrese el número): "))

        if seleccion < 1 or seleccion > len(archivos):
            print("Selección invalida.")
            return

        archivoSeleccionado = os.path.join(carpetaBackup, archivos[seleccion - 1])
        lista.restaurarBackup(archivoSeleccionado)