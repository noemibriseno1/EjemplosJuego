# Librerias utilizadas (Msys2)

Ejecutar los siguientes comandos en la terminal de msys2 para instalar las dependencias necesarias

### DevTools
Compiladores y herramientas necesarias para el desarrollo.

https://code.visualstudio.com/docs/cpp/config-mingw
> pacman -S --needed base-devel mingw-w64-x86_64-toolchain

### SFML
https://packages.msys2.org/package/mingw-w64-x86_64-sfml
> pacman -S mingw-w64-x86_64-sfml

### Box2D simulaciones de fisica - C++
https://box2d.org/documentation/
https://packages.msys2.org/package/mingw-w64-x86_64-box2d?repo=mingw64
> pacman -S mingw-w64-x86_64-box2d