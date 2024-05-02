#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem> // Para manejar archivos y directorios
#include <iomanip> // Para formatear la salida
#include <stdio.h>
using namespace std;
namespace fs = std::filesystem;

// Función para encriptar contenido
string encriptar(const string& contenido, const string& clave) {
    string contenidoEncriptado = contenido;
    // Algoritmo simple de encriptación
    for (size_t i = 0; i < contenidoEncriptado.length(); ++i) {
        contenidoEncriptado[i] += clave[i % clave.length()];
    }
    return contenidoEncriptado;
}

// Función para desencriptar contenido
string desencriptar(const string& contenidoEncriptado, const string& clave) {
    string contenidoDesencriptado = contenidoEncriptado;
    // Algoritmo simple de desencriptación
    for (size_t i = 0; i < contenidoDesencriptado.length(); ++i) {
        contenidoDesencriptado[i] -= clave[i % clave.length()];
    }
    return contenidoDesencriptado;
}
void encriptarArchivo(const string& rutaArchivo, const string& clave) {
    ifstream archivoEntrada(rutaArchivo);
    if (archivoEntrada.is_open()) {
        string contenido;
        getline(archivoEntrada, contenido, '\0'); // Lee todo el contenido del archivo

        string contenidoEncriptado = encriptar(contenido, clave);

        archivoEntrada.close();

        ofstream archivoSalida(rutaArchivo);
        if (archivoSalida.is_open()) {
            archivoSalida << contenidoEncriptado;
            archivoSalida.close();
            cout << "Archivo encriptado exitosamente." << endl;
        } else {
            cout << "No se pudo abrir el archivo para escritura." << endl;
        }
    } else {
        cout << "No se pudo abrir el archivo para lectura." << endl;
    }
}

void desencriptarArchivo(const string& rutaArchivo, const string& clave) {
    ifstream archivoEntrada(rutaArchivo);
    if (archivoEntrada.is_open()) {
        string contenido;
        getline(archivoEntrada, contenido, '\0'); // Lee todo el contenido del archivo

        string contenidoDesencriptado = desencriptar(contenido, clave);

        archivoEntrada.close();

        ofstream archivoSalida(rutaArchivo);
        if (archivoSalida.is_open()) {
            archivoSalida << contenidoDesencriptado;
            archivoSalida.close();
            cout << "Archivo desencriptado exitosamente." << endl;
        } else {
            cout << "No se pudo abrir el archivo para escritura." << endl;
        }
    } else {
        cout << "No se pudo abrir el archivo para lectura." << endl;
    }
}
void crearArchivo() {
    string directorio, nombreArchivo, contenido;
    cout << "Ingrese el directorio del archivo: ";
    getline(cin, directorio);

    cout << "Ingrese el nombre del archivo: ";
    getline(cin, nombreArchivo);

    string rutaArchivo = directorio + '/' + nombreArchivo;

    cout << "Ingrese el contenido del archivo:" << endl;
    getline(cin, contenido);
    rename("directorio+nombreArchivo","nombreArchivo");
    ofstream archivo(rutaArchivo);
    if (archivo.is_open()) {
        string contenidoEncriptado = encriptar(contenido, "clave"); // Encriptar con clave
        archivo << contenidoEncriptado << endl;
        archivo.close();
        cout << "Archivo creado exitosamente." << endl;
    } else {
        cout << "No se pudo abrir el archivo para escritura." << endl;
    }
}

void leerArchivo() {
    string directorio, nombreArchivo;
    cout << "Ingrese el directorio del archivo: ";
    getline(cin, directorio);

    cout << "Ingrese el nombre del archivo: ";
    getline(cin, nombreArchivo);

    string rutaArchivo = directorio + '/' + nombreArchivo;

    ifstream archivoEntrada(rutaArchivo);
    if (archivoEntrada.is_open()) {
        string linea;
        while (getline(archivoEntrada, linea)) {
            string lineaDesencriptada = desencriptar(linea, "clave"); // Desencriptar con clave
            cout << lineaDesencriptada << endl;
        }
        archivoEntrada.close();
    } else {
        cout << "No se pudo abrir el archivo para lectura." << endl;
    }
}

void escribirArchivo() {
    string directorio, nombreArchivo, contenido;
    cout << "Ingrese el directorio del archivo: ";
    getline(cin, directorio);

    cout << "Ingrese el nombre del archivo: ";
    getline(cin, nombreArchivo);

    string rutaArchivo = directorio + '/' + nombreArchivo;

    ofstream archivo(rutaArchivo, ios::app); // Abre el archivo en modo de añadir al final
    if (archivo.is_open()) {
        cout << "Ingrese el contenido que desea agregar al archivo:" << endl;
        getline(cin, contenido);
        string contenidoEncriptado = encriptar(contenido, "clave"); // Encriptar con clave
        archivo << contenidoEncriptado << endl;
        archivo.close();
        cout << "Contenido agregado al archivo exitosamente." << endl;
    } else {
        cout << "No se pudo abrir el archivo para escritura." << endl;
    }
}

void listarArchivosCreados(const string& directorio) {
    cout << "Archivos creados en el directorio '" << directorio << "':" << endl;
    for (const auto& entry : fs::directory_iterator(directorio)) {
        if (entry.is_regular_file()) {
            cout << entry.path().filename() << endl;
        }
    }
}

void verContenidoArchivos(const vector<string>& archivos) {
    for (const auto& archivo : archivos) {
        cout << "Contenido del archivo '" << archivo << "':" << endl;
        ifstream archivoEntrada(archivo);
        if (archivoEntrada.is_open()) {
            string linea;
            while (getline(archivoEntrada, linea)) {
                string lineaDesencriptada = desencriptar(linea, "clave"); // Desencriptar con clave
                cout << lineaDesencriptada << endl;
            }
            archivoEntrada.close();
        } else {
            cout << "No se pudo abrir el archivo para lectura." << endl;
        }
        cout << "------------------------------------------" << endl;
    }
}
void mover() {
    string directorio, nombreArchivo,directorio2;
    cout << "Ingrese el directorio del archivo: ";
    getline(cin, directorio);

    cout << "Ingrese el nombre del archivo: ";
    getline(cin, nombreArchivo);

    string rutaArchivo = directorio + '/' + nombreArchivo;

    cout << "Ingrese el nuevo directorio del archivo: ";
    getline(cin, directorio2);

    string rutaArchivo2 = directorio2 + '/' + nombreArchivo;

    // Construye las rutas completas tanto para el antiguo como para el nuevo nombre de archivo
    string ruta_antiguo = rutaArchivo;
    string ruta_nuevo = rutaArchivo2;

    // Intenta mover el archivo
    if (rename(ruta_antiguo.c_str(), ruta_nuevo.c_str()) == 0) {
        cout << "Archivo movido exitosamente a nueva ruta " << ruta_nuevo << ".txt" << endl;
    } else {
        cout << "Error al intentar mover el archivo. Verifique el nombre y la ruta." << endl;
    }
}

void eliminar() {
    string directorio, nombreArchivo;
    cout << "Ingrese el directorio del archivo: ";
    getline(cin, directorio);

    cout << "Ingrese el nombre del archivo: ";
    getline(cin, nombreArchivo);

    string rutaArchivo = directorio + '/' + nombreArchivo;
    if (remove(rutaArchivo.c_str())!=0) {
        cout << "Error al intentar eliminar el archivo." << endl;
    } else {
        cout << "Archivo eliminado exitosamente." << endl;
    }
}
int main() {
    int opcion;
    vector<string> archivos;
    string clave;

    cout << "Ingrese la clave para encriptar y desencriptar los archivos: ";
    getline(cin, clave);

    do {
        cout << "Seleccione una opción:" << endl;
        cout << "1. Crear archivo" << endl;
        cout << "2. Leer archivo" << endl;
        cout << "3. Escribir en archivo" << endl;
        cout << "4. Listar archivos creados" << endl;
        cout << "5. Ver contenido de varios archivos" << endl;
        cout <<"6. Mover un archivo"<<endl;
        cout <<"7. Eliminar un archivo"<<endl;
        cout << "8. Encriptar archivo" << endl;
        cout << "9. Desencriptar archivo" << endl;
        cout << "10. Salir" << endl;
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer de entrada

        switch (opcion) {
            case 1:
                crearArchivo();
                break;
            case 2:
                leerArchivo();
                break;
            case 3:
                escribirArchivo();
                break;
            case 4: {
                string directorio;
                cout << "Ingrese el directorio para listar archivos creados: ";
                getline(cin, directorio);
                listarArchivosCreados(directorio);
                break;
            }
            case 5: {
                int numArchivos;
                cout << "¿Cuántos archivos desea ver?: ";
                cin >> numArchivos;
                cin.ignore(); // Limpiar el buffer de entrada

                archivos.clear(); // Limpiamos la lista de archivos

                for (int i = 0; i < numArchivos; ++i) {
                    string nombreArchivo;
                    cout << "Ingrese el directorio y nombre del archivo " << i + 1 << ": ";
                    getline(cin, nombreArchivo);
                    archivos.push_back(nombreArchivo);
                }

                verContenidoArchivos(archivos);
                break;
            }
            case 6:
                mover();
                break;
            case 7:
                eliminar();
                break;
            case 8: {
                string rutaEncriptar;
                cout << "Ingrese la ruta del archivo a encriptar: ";
                getline(cin, rutaEncriptar);
                encriptarArchivo(rutaEncriptar, clave);
                break;
            }
            case 9: {
                string rutaDesencriptar;
                cout << "Ingrese la ruta del archivo a desencriptar: ";
                getline(cin, rutaDesencriptar);
                desencriptarArchivo(rutaDesencriptar, clave);
                break;
            }
            case 10:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción inválida. Por favor, seleccione una opción válida." << endl;
                break;
        }

        if (opcion != 6) {
            char continuar;
            cout << "¿Desea realizar otra operación? (s/n): ";
            cin >> continuar;
            cin.ignore(); // Limpiar el buffer de entrada

            if (continuar != 's') {
                break;
            }
        }
    } while (opcion != 6);

    return 0;
}