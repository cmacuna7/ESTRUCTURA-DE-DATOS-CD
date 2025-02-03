"""
********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Lista Simple                                             *
 * Autor:                          Abner Arboleda, Marcelo Acuña, Christian bonifaz         *
 * Fecha de creacion:              26/12/2024                                               *
 * Fecha de modificacion:          26/12/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************
"""
import os
from fecha import Fecha
from persona import Persona
from nodo import Nodo

class ListaSimple:
    def __init__(self):
        self.cabeza = None
        self.archivoPersonas = "personas.txt"
        self.evitarGuardar = False

    def agregarPersona(self, persona):
        if self.buscarPersonaPorCedula(persona.cedula):
            print(f"Error: La cédula {persona.cedula} ya existe.")
            return

        nuevo_nodo = Nodo(persona)
        if not self.cabeza:
            self.cabeza = nuevo_nodo
        else:
            temp = self.cabeza
            while temp.siguiente is not None:
                temp = temp.siguiente
            temp.siguiente = nuevo_nodo

        print(f"Persona agregada: {persona.nombre}")
        if not self.evitarGuardar:
            self.guardarPersonasEnArchivo()

    def limpiarLista(self):
        self.cabeza = None

    def imprimirPersonas(self):
        if not self.cabeza:
            print("No hay personas registradas.")
            return
        temp = self.cabeza
        print(f"{'Primer Nombre':<20}{'Segundo Nombre':<20}{'Apellido':<15}{'Cedula':<20}{'Correo':<30}{'Fecha de Nacimiento':<30}")
        print('-' * 130)
        while temp is not None:
            temp.persona.mostrar()
            temp = temp.siguiente

    def buscarPersona(self, nombre):
        temp = self.cabeza
        while temp is not None:
            if temp.persona.nombre == nombre:
                return temp
            temp = temp.siguiente
        return None

    def buscarPersonaPorCedula(self, cedula):
        temp = self.cabeza
        while temp is not None:
            if temp.persona.cedula == cedula:
                return temp
            temp = temp.siguiente
        return None

    def eliminarPersona(self, nombre):
        temp = self.cabeza
        prev = None
        while temp is not None:
            if temp.persona.nombre == nombre:
                if prev:
                    prev.siguiente = temp.siguiente
                else:
                    self.cabeza = temp.siguiente
                print(f"Persona eliminada: {nombre}")
                break
            prev = temp
            temp = temp.siguiente
        self.guardarPersonasEnArchivo()

    def eliminarPersonaPorCedula(self, cedula):
        temp = self.cabeza
        prev = None
        while temp is not None:
            if temp.persona.cedula == cedula:
                if prev:
                    prev.siguiente = temp.siguiente
                else:
                    self.cabeza = temp.siguiente
                print(f"Persona eliminada: {cedula}")
                break
            prev = temp
            temp = temp.siguiente
        self.guardarPersonasEnArchivo()

    def guardarPersonasEnArchivo(self):
        with open("personas_temp.txt", 'w') as archivo:
            temp = self.cabeza
            while temp is not None:
                archivo.write(f"{temp.persona.nombre};{temp.persona.segundoNombre};{temp.persona.apellido};{temp.persona.cedula};{temp.persona.correo};{temp.persona.fechaNacimiento.strftime('%d-%m-%Y')}\n")
                temp = temp.siguiente

        if os.path.exists("personas_temp.txt"):
            try:
                os.replace("personas_temp.txt", self.archivoPersonas)
                print(f"Personas guardadas en el archivo: {self.archivoPersonas}")
            except PermissionError as e:
                pass

    def cargarPersonasDesdeArchivo(self):
        try:
            with open(self.archivoPersonas, 'r') as archivo:
                for linea in archivo:
                    nombre, segundoNombre, apellido, cedula, correo, fechaNacimientoStr = linea.strip().split(';')
                    fechaNacimiento = Fecha.crearDesdeCadena(fechaNacimientoStr)
                    persona = Persona(nombre, segundoNombre, apellido, cedula, fechaNacimiento, correo)
                    self.agregarPersona(persona)
            print("Personas cargadas desde el archivo.")
        except FileNotFoundError:
            print("Error al abrir el archivo para cargar las personas.")

    def crearBackup(self, nombreArchivo):
        carpetaBackup = "backup"
        os.makedirs(carpetaBackup, exist_ok=True)
        rutaCompleta = os.path.join(carpetaBackup, nombreArchivo)
        with open(rutaCompleta, 'w') as archivo:
            temp = self.cabeza
            while temp is not None:
                archivo.write(f"{temp.persona.nombre};{temp.persona.segundoNombre};{temp.persona.apellido};{temp.persona.cedula};{temp.persona.correo};{temp.persona.fechaNacimiento.strftime('%d-%m-%Y')}\n")
                temp = temp.siguiente
        print(f"Backup creado correctamente en: {rutaCompleta}")

    def restaurarBackup(self, nombreArchivo):
        try:
            with open(nombreArchivo, 'r') as archivo:
                self.limpiarLista()
                self.evitarGuardar = True
                for linea in archivo:
                    nombre, segundoNombre, apellido, cedula, correo, fechaNacStr = linea.strip().split(';')
                    fechaNacimiento = Fecha.crearDesdeCadena(fechaNacStr)
                    persona = Persona(nombre, segundoNombre, apellido, cedula, fechaNacimiento, correo)
                    self.agregarPersona(persona)
                self.evitarGuardar = False
                self.guardarPersonasEnArchivo()
                print(f"Backup restaurado: {nombreArchivo}")
        except FileNotFoundError:
            print("Error al abrir el archivo de backup.")

    def ordenarPorCedula(self):
        self.guardarPersonasEnArchivo()
        try:
            with open(self.archivoPersonas, 'r') as archivo:
                personas = []
                for linea in archivo:
                    nombre, segundoNombre, apellido, cedula, correo, fechaNacimientoStr = linea.strip().split(';')
                    fechaNacimiento = Fecha.crearDesdeCadena(fechaNacimientoStr)
                    persona = Persona(nombre, segundoNombre, apellido, cedula, fechaNacimiento, correo)
                    personas.append(persona)
            personas.sort(key=lambda p: p.cedula)
            with open(self.archivoPersonas, 'w') as archivo:
                for persona in personas:
                    archivo.write(f"{persona.nombre};{persona.segundoNombre};{persona.apellido};{persona.cedula};{persona.correo};{persona.fechaNacimiento.strftime('%d-%m-%Y')}\n")
            self.limpiarLista()
            self.cargarPersonasDesdeArchivo()
        except FileNotFoundError:
            print("Error al abrir el archivo para ordenar las personas.")