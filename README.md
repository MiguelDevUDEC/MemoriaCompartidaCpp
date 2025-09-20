# Comunicación entre procesos con Memoria Compartida en C++

Este proyecto demuestra cómo dos programas en C++ pueden **compartir
datos en memoria** utilizando la **API de Windows**.\
Se usan dos archivos principales:

-   `Index.cpp`: actúa como **escritor** (crea y escribe en la memoria
    compartida).
-   `Result.cpp`: actúa como **lector** (accede y lee el valor
    almacenado).

------------------------------------------------------------------------

## 🚀 Objetivo

Permitir que múltiples procesos se comuniquen sin usar archivos ni
sockets, sino mediante **memoria compartida** en Windows.

------------------------------------------------------------------------

## 📂 Archivos del proyecto

### 1. `Index.cpp` (Escritor)

Este programa: 1. **Crea un objeto de memoria compartida** con
`CreateFileMappingA`. 2. **Mapea la memoria** en el espacio de
direcciones del proceso con `MapViewOfFile`. 3. **Escribe un valor
entero** (`100`) en la memoria. 4. Espera a que el usuario presione
`ENTER` para mantener la memoria disponible mientras el lector la usa.
5. **Libera los recursos** con `UnmapViewOfFile` y `CloseHandle`.

👉 Código clave:

``` cpp
HANDLE hMapFile = CreateFileMappingA(
    INVALID_HANDLE_VALUE, // Memoria virtual del sistema
    NULL,
    PAGE_READWRITE,
    0,
    sizeof(int),          // Tamaño de memoria (4 bytes para un int)
    "MiMemoriaCompartida" // Nombre de la memoria compartida
);

int* pBuf = (int*) MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int));
*pBuf = 100; // Escribir valor
```

------------------------------------------------------------------------

### 2. `Result.cpp` (Lector)

Este programa: 1. **Abre la memoria compartida existente** con
`OpenFileMappingA`. 2. **Mapea la memoria** en su espacio de
direcciones. 3. **Lee el valor entero** escrito por el escritor. 4.
Imprime el valor en consola. 5. **Libera los recursos** al finalizar.

👉 Código clave:

``` cpp
HANDLE hMapFile = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, "MiMemoriaCompartida");
int* pBuf = (int*) MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int));
cout << "El valor leído es: " << *pBuf << endl;
```

⚠️ **Nota importante**: en el código actual de `Result.cpp` aparece esta
parte:

``` cpp
int* ptr = (int*)0xcc8e9ff8cc;
int number = *ptr;
cout << "Number is: " << number << endl;
```

Esto es **peligroso** porque accede a una dirección de memoria fija y
arbitraria.\
✅ Lo recomendable es **eliminar esa sección** ya que puede producir un
**error de acceso a memoria (segmentation fault)**.

------------------------------------------------------------------------

## 📊 Flujo de ejecución

1.  **Ejecutar primero** `Index.exe` (crea la memoria y escribe el valor
    `100`).
2.  Luego ejecutar `Result.exe` (abre la memoria y lee el valor).
3.  El lector imprimirá en consola:

```{=html}
<!-- -->
```
    El valor leído es: 100

------------------------------------------------------------------------

## 🛠️ Requisitos

-   Sistema operativo: **Windows** (ya que se usa la API `windows.h`).
-   Compilador compatible con C++ (ejemplo: **MinGW** o **MSVC**).

Para compilar con MinGW:

``` bash
g++ Index.cpp -o Index.exe
g++ Result.cpp -o Result.exe
```

------------------------------------------------------------------------

## ✅ Buenas prácticas y mejoras

-   **Eliminar punteros con direcciones fijas** en `Result.cpp`.
-   Manejar correctamente errores con `GetLastError()` para obtener más
    detalles.
-   Ampliar el ejemplo para **más tipos de datos** (estructuras,
    cadenas, etc.).
-   Usar sincronización (mutex/semaforos) si múltiples procesos
    escriben/leen simultáneamente.
