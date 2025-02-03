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

class Utilidades:
    @staticmethod
    def generarCorreo(nombre, sNombre, apellido):
        nombreLower = nombre.lower()
        sNombreLower = sNombre.lower()
        apellidoLower = apellido.lower()

        correoBase = f"{nombreLower[0]}{sNombreLower[0]}{apellidoLower}@espe.edu.ec"
        correoGenerado = correoBase

        if os.path.exists("personas.txt"):
            with open("personas.txt", 'r') as archivo:
                lineas = archivo.readlines()
                contador = 0
                for linea in lineas:
                    datos = linea.strip().split(';')
                    if len(datos) > 4 and datos[4] == correoGenerado:
                        contador += 1
                        correoGenerado = f"{correoBase.split('@')[0]}{contador}@espe.edu.ec"

        return correoGenerado