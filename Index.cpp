#include <iostream>
#include <windows.h>
using namespace std;
int main() {
    const int TAMANO_MEMORIA = sizeof(int);
    LPCSTR NOMBRE_MEMORIA = "MiMemoriaCompartida";

    HANDLE hMapFile = CreateFileMappingA(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        TAMANO_MEMORIA,
        NOMBRE_MEMORIA
    );

    if (hMapFile == NULL) {
        cerr << "Error al crear la memoria compartida." << endl;
        return 1;
    }

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


    *pBuf = 100;

    cout << "Valor escrito en la memoria. Presiona ENTER para salir..." << endl;
    cin.get();


    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}