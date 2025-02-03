#include <iostream>
#include "ListaDobleCircular.cpp"  // Asegúrate de incluir el archivo correcto

int main() {
    // Crear una lista de cadenas de texto
    ListaCircular<std::string> miLista;

    // Insertar algunos elementos en la lista
    miLista.insertar("Hola");
    miLista.insertar("Mundo");
    miLista.insertar("Ejemplo");

    // Mostrar la lista antes de la codificación
    std::cout << "Lista original:" << std::endl;
    miLista.mostrar();

    // Llamar a la función templada para codificar un caracter
    // En este caso, 'a' se codificará con un desplazamiento de 3
    codificarCaracter<std::string>(miLista, 'a', 3);

    // Mostrar la lista después de la codificación
    std::cout << "\nLista después de codificar el caracter 'a' con desplazamiento de 3:" << std::endl;
    miLista.mostrar();

    return 0;
}