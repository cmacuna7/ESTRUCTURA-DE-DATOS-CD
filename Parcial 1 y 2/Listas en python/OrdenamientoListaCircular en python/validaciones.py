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
from datetime import datetime

class Validaciones:
    @staticmethod
    def validarFecha(fecha):
        pass

    @staticmethod
    def validarCedula(cedula):
        pass

    @staticmethod
    def validarTextoNoVacio(texto, campo):
        pass

    @staticmethod
    def validarTexto(texto, campo):
        pass

    @staticmethod
    def validarTituloNombre(texto, campo):
        pass

    @staticmethod
    def diasEnMes(mes, anio):
        pass

    @staticmethod
    def esBisiesto(anio):
        pass

# Implementación de los métodos de la clase Validaciones

def validarFecha(fecha):
    formatoFecha = re.compile(r"\d{2}-\d{2}-\d{4}")
    if not formatoFecha.match(fecha):
        print("Error: El formato de la fecha debe ser DD-MM-YYYY.")
        return False

    try:
        dia, mes, anio = map(int, fecha.split('-'))
    except ValueError:
        print("Error: Fecha no válida.")
        return False

    if anio <= 0 or mes < 1 or mes > 12 or dia < 1 or dia > Validaciones.diasEnMes(mes, anio):
        print("Error: Fecha no válida.")
        return False

    fecha_actual = datetime.now()
    fecha_ingresada = datetime(anio, mes, dia)

    if fecha_ingresada > fecha_actual:
        print("Error: La fecha no puede ser mayor a la fecha actual.")
        return False

    return True

def validarCedula(cedula):
    if len(cedula) != 10:
        print("Error: La cédula debe tener 10 dígitos.")
        return False

    try:
        provincia = int(cedula[:2])
    except ValueError:
        print("Error: La cédula debe contener solo números.")
        return False

    if provincia < 1 or provincia > 24:
        print("Error: Los dos primeros dígitos deben corresponder a una provincia válida.")
        return False

    tercer_digito = int(cedula[2])
    if tercer_digito >= 6:
        print("Error: El tercer dígito debe ser menor a 6.")
        return False

    suma = 0
    for i in range(9):
        digito = int(cedula[i])
        if i % 2 == 0:
            digito *= 2
            if digito > 9:
                digito -= 9
        suma += digito

    digito_verificador = (10 - (suma % 10)) % 10
    if digito_verificador != int(cedula[9]):
        print("Error: La cédula no es válida.")
        return False

    return True

def validarTextoNoVacio(texto, campo):
    if not texto.strip():
        print(f"Error: El campo {campo} no puede estar vacío o contener solo espacios.")
        return False
    return True

def validarTexto(texto, campo):
    formatoTexto = re.compile(r"[a-zA-ZñÑáéíóúÁÉÍÓÚ\s]+")
    if not texto.strip():
        print(f"Error: El campo {campo} no puede estar vacío o contener solo espacios.")
        return False
    elif not formatoTexto.match(texto):
        print(f"Error: El campo {campo} solo debe contener letras, espacios y caracteres válidos en español.")
        return False
    return True

def validarTituloNombre(texto, campo):
    formatoTituloNombre = re.compile(r"^[A-ZÁÉÍÓÚÑ][a-záéíóúñ]+$")
    if not texto.strip():
        print(f"Error: El campo {campo} no puede estar vacío o contener solo espacios.")
        return False
    elif not formatoTituloNombre.match(texto):
        print(f"Error: El campo {campo} debe comenzar con una letra mayúscula y no contener espacios.")
        return False
    return True

def diasEnMes(mes, anio):
    if mes in [1, 3, 5, 7, 8, 10, 12]:
        return 31
    elif mes in [4, 6, 9, 11]:
        return 30
    elif mes == 2:
        return 29 if Validaciones.esBisiesto(anio) else 28
    else:
        return 0

def esBisiesto(anio):
    return (anio % 4 == 0 and anio % 100 != 0) or (anio % 400 == 0)

# Asignar las implementaciones a los métodos de la clase Validaciones
Validaciones.validarFecha = validarFecha
Validaciones.validarCedula = validarCedula
Validaciones.validarTextoNoVacio = validarTextoNoVacio
Validaciones.validarTexto = validarTexto
Validaciones.validarTituloNombre = validarTituloNombre
Validaciones.diasEnMes = diasEnMes
Validaciones.esBisiesto = esBisiesto