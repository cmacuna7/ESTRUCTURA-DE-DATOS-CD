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
class Nodo:
    def __init__(self, persona):
        self.persona = persona
        self.siguiente = None
        self.anterior = None  # Añadido para lista doble