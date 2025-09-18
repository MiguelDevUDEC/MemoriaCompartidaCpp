#include <iostream>
#include <windows.h> // Necesario para la API de Windows
using namespace std;

int main() {
    const int TAMANO_MEMORIA = sizeof(int);
    LPCSTR NOMBRE_MEMORIA = "MiMemoriaCompartida"; // Sin el prefijo L

    // 1. Abrir el objeto de memoria compartida por su nombre. Se usa la versión A (ANSI).
    HANDLE hMapFile = OpenFileMappingA(
        FILE_MAP_ALL_ACCESS,
        FALSE,
        NOMBRE_MEMORIA
    );

    if (hMapFile == NULL) {
        cerr << "No se encontro la memoria. Asegurate de que el Escritor este activo." << endl;
        return 1;
    }

    // 2. Mapear una vista de la memoria.
    int* pBuf = static_cast<int*>(MapViewOfFile(
        hMapFile,
        FILE_MAP_ALL_ACCESS,
        0, 0, TAMANO_MEMORIA
    ));

    if (pBuf == NULL) {
        cerr << "Error al mapear la vista." << endl;
        CloseHandle(hMapFile);
        return 1;
    }

    // 3. Leer el valor de la memoria compartida.
    cout << "El valor leido es: " << *pBuf << endl;
    int* ptr = (int*)0xcc8e9ff8cc;
    int number = *ptr;
    cout << "Number is: " << number << endl;

    // 4. Limpiar recursos.
    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}