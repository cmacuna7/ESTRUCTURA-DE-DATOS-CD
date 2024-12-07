#include "Validaciones.h"

// Validación de fecha
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
    string isbnSinGuiones = isbn;
    isbnSinGuiones.erase(remove(isbnSinGuiones.begin(), isbnSinGuiones.end(), '-'), isbnSinGuiones.end());

    if (isbnSinGuiones.size() == 10) {
        return validarIsbn10(isbnSinGuiones);
    } else if (isbnSinGuiones.size() == 13) {
        return validarIsbn13(isbnSinGuiones);
    }
    cout << "Error: El ISBN debe tener 10 o 13 caracteres (sin contar los guiones).\n";
    return false;
}

bool Validaciones::validarIsbn10(const string& isbn) {
    if (isbn.size() != 10) {
        return false;
    }

    // Verificar que los primeros 9 caracteres sean dígitos y el último sea un dígito o 'X'
    for (int i = 0; i < 9; i++) {
        if (!isdigit(isbn[i])) {
            return false;
        }
    }

    char digitoControl = isbn[9];
    if (!(isdigit(digitoControl) || digitoControl == 'X')) {
        return false;
    }

    // Validar el dígito de control
    return calcularDigitoControlIsbn10(isbn) == 0;
}

bool Validaciones::validarIsbn13(const string& isbn) {
    if (isbn.size() != 13) {
        return false;
    }

    // Verificar que todos los caracteres sean dígitos
    for (int i = 0; i < 13; i++) {
        if (!isdigit(isbn[i])) {
            return false;
        }
    }

    // Validar el dígito de control
    return calcularDigitoControlIsbn13(isbn) == 0;
}

int Validaciones::calcularDigitoControlIsbn10(const string& isbn) {
    int suma = 0;
    for (int i = 0; i < 9; i++) {
        suma += (isbn[i] - '0') * (10 - i);
    }
    char digitoControl = isbn[9];
    if (digitoControl == 'X') {
        suma += 10;
    } else {
        suma += (digitoControl - '0');
    }
    return suma % 11;
}

int Validaciones::calcularDigitoControlIsbn13(const string& isbn) {
    int suma = 0;
    for (int i = 0; i < 12; i++) {
        if (i % 2 == 0) {
            suma += (isbn[i] - '0');
        } else {
            suma += (isbn[i] - '0') * 3;
        }
    }
    int digitoControlCalculado = (10 - (suma % 10)) % 10;
    return digitoControlCalculado == (isbn[12] - '0') ? 0 : -1;
}

// Validación de ISNI
bool Validaciones::validarIsni(const string& isni) {
    string isniSinEspacios = isni;
    isniSinEspacios.erase(remove(isniSinEspacios.begin(), isniSinEspacios.end(), ' '), isniSinEspacios.end());

    if (isniSinEspacios.size() != 16 || !all_of(isniSinEspacios.begin(), isniSinEspacios.end(), ::isdigit)) {
        cout << "Error: El ISNI debe contener exactamente 16 dígitos.\n";
        return false;
    }

    int suma = 0;
    int pesoAlternante = 1; // Alterna entre 1 y 2
    for (int i = 0; i < 15; ++i) {
        int digito = isniSinEspacios[i] - '0';
        suma += digito * pesoAlternante;
        pesoAlternante = (pesoAlternante == 1) ? 2 : 1;
    }

    int resto = suma % 11;
    int digitoControlEsperado = (12 - resto) % 11;

    // Si el dígito de control es 10, se representa como 'X' (caso extendido)
    int digitoControlReal = isniSinEspacios[15] - '0';
    if (isniSinEspacios[15] == 'X') {
        digitoControlReal = 10;
    }

    if (digitoControlEsperado != digitoControlReal) {
        cout << "Error: El dígito de control del ISNI no es válido.\n";
        return false;
    }

    return true;
}


// Validación de texto no vacío
bool Validaciones::validarTextoNoVacio(const string& texto, const string& campo) {
    regex formatoTexto(R"([a-zA-ZñÑáéíóúÁÉÍÓÚ\s]+)"); // Incluye letras con tildes y ñ
    if (texto.empty() || texto.find_first_not_of(' ') == string::npos) {
        cout << "Error: El campo " << campo << " no puede estar vacío o contener solo espacios.\n";
        return false;
    } else if (!regex_match(texto, formatoTexto)) {
        cout << "Error: El campo " << campo << " solo debe contener letras, espacios y caracteres válidos en español.\n";
        return false;
    }
    return true;
}

// Validación de texto
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

// Función auxiliar: días en un mes
int Validaciones::diasEnMes(int mes, int anio) {
    switch (mes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return (esBisiesto(anio)) ? 29 : 28;
        default: return 0;
    }
}

// Función auxiliar: año bisiesto
bool Validaciones::esBisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}
