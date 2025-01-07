"""
********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Lista Doble                                              *
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

class ListaDoble:
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
            self.cabeza.siguiente = self.cabeza
            self.cabeza.anterior = self.cabeza
        else:
            temp = self.cabeza
            while temp.siguiente != self.cabeza:
                temp = temp.siguiente
            temp.siguiente = nuevo_nodo
            nuevo_nodo.anterior = temp
            nuevo_nodo.siguiente = self.cabeza
            self.cabeza.anterior = nuevo_nodo

        print(f"Persona agregada: {persona.nombre}")
        if not self.evitarGuardar:
            self.guardarPersonasEnArchivo()

    def limpiarLista(self):
        if not self.cabeza:
            return
        temp = self.cabeza
        while True:
            siguiente = temp.siguiente
            if siguiente == self.cabeza:
                break
            temp = siguiente
        self.cabeza = None

    def imprimirPersonas(self):
        if not self.cabeza:
            print("No hay personas registradas.")
            return
        temp = self.cabeza
        print(f"{'Primer Nombre':<20}{'Segundo Nombre':<20}{'Apellido':<15}{'Cedula':<20}{'Correo':<30}{'Fecha de Nacimiento':<30}")
        print('-' * 130)
        while True:
            temp.persona.mostrar()
            temp = temp.siguiente
            if temp == self.cabeza:
                break

    def buscarPersona(self, nombre):
        if not self.cabeza:
            return None
        temp = self.cabeza
        while True:
            if temp.persona.nombre == nombre:
                return temp
            temp = temp.siguiente
            if temp == self.cabeza:
                break
        return None

    def buscarPersonaPorCedula(self, cedula):
        if not self.cabeza:
            return None
        temp = self.cabeza
        while True:
            if temp.persona.cedula == cedula:
                return temp
            temp = temp.siguiente
            if temp == self.cabeza:
                break
        return None

    def eliminarPersona(self, nombre):
        if not self.cabeza:
            return
        temp = self.cabeza
        while True:
            if temp.persona.nombre == nombre:
                if temp == self.cabeza:
                    if temp.siguiente == self.cabeza:
                        self.cabeza = None
                    else:
                        last = self.cabeza.anterior
                        self.cabeza = temp.siguiente
                        self.cabeza.anterior = last
                        last.siguiente = self.cabeza
                else:
                    temp.anterior.siguiente = temp.siguiente
                    temp.siguiente.anterior = temp.anterior
                print(f"Persona eliminada: {nombre}")
                break
            temp = temp.siguiente
            if temp == self.cabeza:
                print(f"Persona no encontrada: {nombre}")
                break
        self.guardarPersonasEnArchivo()

    def eliminarPersonaPorCedula(self, cedula):
        if not self.cabeza:
            return
        temp = self.cabeza
        while True:
            if temp.persona.cedula == cedula:
                if temp == self.cabeza:
                    if temp.siguiente == self.cabeza:
                        self.cabeza = None
                    else:
                        last = self.cabeza.anterior
                        self.cabeza = temp.siguiente
                        self.cabeza.anterior = last
                        last.siguiente = self.cabeza
                else:
                    temp.anterior.siguiente = temp.siguiente
                    temp.siguiente.anterior = temp.anterior
                print(f"Persona eliminada: {cedula}")
                break
            temp = temp.siguiente
            if temp == self.cabeza:
                print(f"Persona no encontrada: {cedula}")
                break
        self.guardarPersonasEnArchivo()

    def guardarPersonasEnArchivo(self):
        with open("personas_temp.txt", 'w') as archivo:
            if not self.cabeza:
                return
            temp = self.cabeza
            while True:
                archivo.write(f"{temp.persona.nombre};{temp.persona.segundoNombre};{temp.persona.apellido};{temp.persona.cedula};{temp.persona.correo};{temp.persona.fechaNacimiento.strftime('%d-%m-%Y')}\n")
                temp = temp.siguiente
                if temp == self.cabeza:
                    break

        # Ensure the file is closed before replacing
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
            if not self.cabeza:
                return
            temp = self.cabeza
            while True:
                archivo.write(f"{temp.persona.nombre};{temp.persona.segundoNombre};{temp.persona.apellido};{temp.persona.cedula};{temp.persona.correo};{temp.persona.fechaNacimiento.strftime('%d-%m-%Y')}\n")
                temp = temp.siguiente
                if temp == self.cabeza:
                    break
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