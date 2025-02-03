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
import re
import time
from validaciones import Validaciones
from utilidades import Utilidades  # Importa la clase Utilidades desde el archivo utilidades.py
from fecha import Fecha  # Importa la clase Fecha desde el archivo fecha.py
from persona import Persona  # Importa la clase Persona desde el archivo persona.py
from nodo import Nodo  # Importa la clase Nodo desde el archivo nodo.py
from lista_circular import ListaCircular  # Importa la clase ListaCircular desde el archivo lista_circular.py
from backup_manager import BackupManager  # Importa la clase BackupManager desde el archivo backup_manager.py
import os
import time
import msvcrt

def mostrarAyuda():
    print("Ayuda: Use las flechas arriba y abajo para navegar, Enter para seleccionar una opción.")

def mostrarMenu(lista):
    opciones = [
        "Agregar persona",
        "Buscar persona",
        "Eliminar persona",
        "Ver todas las personas",
        "Crear backup",
        "Restaurar backup",
        "Ordenar por cédula",
        "Salir"
    ]
    seleccion = 0

    while True:
        os.system("cls")
        print("=== Menu Principal ===")
        for i, opcion in enumerate(opciones):
            if i == seleccion:
                print(f">> {opcion} <<")
            else:
                print(f"   {opcion}")

        tecla = msvcrt.getch()
        if tecla == b'H':  # Flecha Arriba
            seleccion = (seleccion - 1 + len(opciones)) % len(opciones)
        elif tecla == b'P':  # Flecha Abajo
            seleccion = (seleccion + 1) % len(opciones)
        elif tecla == b'\r':  # Enter
            if opciones[seleccion] == "Agregar persona":
                nombre = input("Ingrese Primer Nombre de la persona: ")
                while not Validaciones.validarTituloNombre(nombre, "Nombre"):
                    nombre = input("Ingrese Primer Nombre de la persona: ")

                sNombre = input("Ingrese Segundo Nombre de la persona: ")
                while not Validaciones.validarTituloNombre(sNombre, "Segundo Nombre"):
                    sNombre = input("Ingrese Segundo Nombre de la persona: ")

                apellido = input("Ingrese apellido de la persona: ")
                while not Validaciones.validarTituloNombre(apellido, "Apellido"):
                    apellido = input("Ingrese apellido de la persona: ")

                correo = Utilidades.generarCorreo(nombre, sNombre, apellido)
                print(f"El correo generado es: {correo}")

                cedula = input("Ingrese cédula: ")
                while not Validaciones.validarCedula(cedula):
                    cedula = input("Ingrese cédula: ")

                fechaNac = input("Ingrese fecha de nacimiento (DD-MM-YYYY): ")
                while not Validaciones.validarFecha(fechaNac):
                    fechaNac = input("Ingrese fecha de nacimiento (DD-MM-YYYY): ")

                fechaNacimiento = Fecha.crearDesdeCadena(fechaNac)
                persona = Persona(nombre, sNombre, apellido, cedula, fechaNacimiento)
                lista.agregarPersona(persona)
            elif opciones[seleccion] == "Buscar persona":
                cedula = input("Ingrese la cédula de la persona a buscar: ")
                persona = lista.buscarPersonaPorCedula(cedula)
                if persona:
                    persona.persona.mostrar()
                else:
                    print("Persona no encontrada.")
            elif opciones[seleccion] == "Eliminar persona":
                cedula = input("Ingrese la cédula de la persona a eliminar: ")
                personaAEliminar = lista.buscarPersonaPorCedula(cedula)
                if personaAEliminar:
                    lista.eliminarPersonaPorCedula(cedula)
                else:
                    print(f"Persona no encontrada con cédula: {cedula}")
            elif opciones[seleccion] == "Ver todas las personas":
                lista.imprimirPersonas()
            elif opciones[seleccion] == "Crear backup":
                ahora = time.localtime()
                filename = f"{ahora.tm_year}_{ahora.tm_mon}_{ahora.tm_mday}_{ahora.tm_hour}_{ahora.tm_min}_{ahora.tm_sec}.txt"
                lista.crearBackup(filename)
            elif opciones[seleccion] == "Restaurar backup":
                BackupManager.restaurarBackup(lista)
            elif opciones[seleccion] == "Ordenar por cédula":
                lista.ordenarPorCedula()
                print("Lista ordenada por cédula.")
            elif opciones[seleccion] == "Salir":
                break
            print("Presione cualquier tecla para continuar...")
            msvcrt.getch()
        elif tecla == b';':  # F1
            mostrarAyuda()

# Ejemplo de uso
lista = ListaCircular()
lista.cargarPersonasDesdeArchivo()
mostrarMenu(lista)