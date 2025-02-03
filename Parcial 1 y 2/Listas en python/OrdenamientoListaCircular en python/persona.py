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
from fecha import Fecha
from utilidades import Utilidades

class Persona:
    def __init__(self, nombre="", segundoNombre="", apellido="", cedula="", fechaNacimiento=None, correo=""):
        self.nombre = nombre
        self.segundoNombre = segundoNombre
        self.apellido = apellido
        self.cedula = cedula
        self.fechaNacimiento = fechaNacimiento if fechaNacimiento else Fecha(1, 1, 1970)
        self.correo = correo if correo else Utilidades.generarCorreo(nombre, segundoNombre, apellido)

    def mostrar(self):
        print(f"{self.nombre:<20}{self.segundoNombre:<20}{self.apellido:<15}{self.cedula:<20}{self.correo:<30}{self.fechaNacimiento.strftime('%d-%m-%Y'):<30}")