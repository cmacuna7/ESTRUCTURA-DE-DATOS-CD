#include "Validaciones.h"

bool Validaciones::validarFecha(const string& fecha) {
    regex formatoFecha(R"(\d{2}-\d{2}-\d{4})");
    if (!regex_match(fecha, formatoFecha)) {
        cout << "Error: El formato de la fecha debe ser DD-MM-YYYY.\n";
        return false;
    }

    int dia, mes, anio;
    sscanf(fecha.c_str(), "%d-%d-%d", &dia, &mes, &anio);

    if (anio < 0 || mes < 1 || mes > 12 || dia < 1 || dia > diasEnMes(mes, anio)) {
        cout << "Error: Fecha no valida.\n";
        return false;
    }

    return true;
}

bool Validaciones::validarIsbn(const string& isbn) {
    regex formatoIsbn(R"(\d{3}-\d{1,5}-\d{1,7}-\d{1,7}-\d{1})");
    if (!regex_match(isbn, formatoIsbn)) {
        cout << "Error: El ISBN no cumple con el formato válido (ejemplo: 978-3-16-148410-0).\n";
        return false;
    }
    return true;
}

bool Validaciones::validarTextoNoVacio(const string& texto, const string& campo) {
    if (texto.empty() || texto.find_first_not_of(' ') == string::npos) {
        cout << "Error: El campo " << campo << " no puede estar vacío o contener solo espacios.\n";
        return false;
    }
    return true;
}

bool Validaciones::validarTexto(const string& texto, const string& campo) {
    regex formatoTexto(R"([a-zA-Z\s]+)");
    if (texto.empty() || texto.find_first_not_of(' ') == string::npos) {
        cout << "Error: El campo " << campo << " no puede estar vacío o contener solo espacios.\n";
        return false;
    } else if (!regex_match(texto, formatoTexto)) {
        cout << "Error: El campo " << campo << " solo debe contener letras y espacios.\n";
        return false;
    }
    return true;
}

int Validaciones::diasEnMes(int mes, int anio) {
    switch (mes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return (esBisiesto(anio)) ? 29 : 28;
        default: return 0;
    }
}

bool Validaciones::esBisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}
