#include <iostream>
#include <windows.h> // Necesario para la API de Windows
using namespace std;
int main() {
    const int TAMANO_MEMORIA = sizeof(int); // Solo 4 bytes para un int
    LPCSTR NOMBRE_MEMORIA = "MiMemoriaCompartida"; // Sin el prefijo L

    // 1. Crear el objeto de memoria compartida. Se usa la versión A (ANSI).
    HANDLE hMapFile = CreateFileMappingA(
        INVALID_HANDLE_VALUE, // Usar la memoria virtual del sistema.
        NULL,                 // Atributos de seguridad por defecto.
        PAGE_READWRITE,       // Permisos de lectura y escritura.
        0,                    // Tamaño (alto).
        TAMANO_MEMORIA,       // Tamaño (bajo).
        NOMBRE_MEMORIA        // Nombre del objeto.
    );

    if (hMapFile == NULL) {
        cerr << "Error al crear la memoria compartida." << endl;
        return 1;
    }

    // 2. Mapear una vista de la memoria.
    int* pBuf = static_cast<int*>(MapViewOfFile(
        hMapFile,                // Handle del objeto.
        FILE_MAP_ALL_ACCESS,     // Permisos de acceso.
        0, 0, TAMANO_MEMORIA     // Offset y tamaño.
    ));

    if (pBuf == NULL) {
        cerr << "Error al mapear la vista." << endl;
        CloseHandle(hMapFile);
        return 1;
    }

    // 3. Escribir el valor en la memoria compartida.
    *pBuf = 100;

    cout << "Valor escrito en la memoria. Presiona ENTER para salir..." << endl;
    cin.get();

    // 4. Limpiar recursos.
    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}