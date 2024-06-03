# TareaRedes

##############################################################
#                   4 en Línea - Juego en C++                #
##############################################################

Este repositorio contiene la implementación del juego "4 en Línea", un juego de estrategia utilizando sockets en C++. El proyecto consta de un servidor y un cliente que se comunican a través de la red para jugar al juego.

## Contenido

1. [Requisitos](#requisitos)
2. [Compilación](#compilación)
3. [Ejecución](#ejecución)
4. [Reglas del Juego](#reglas-del-juego)
5. [Observaciones](#observaciones)
6. [Limpieza](#limpieza)

---

## Requisitos <a name="requisitos"></a>

Para compilar y ejecutar este proyecto, necesitarás tener instalados los siguientes elementos:

- Compilador de C++ (por ejemplo, g++)
- Utilidad `make` para compilar el proyecto

---

## Compilación <a name="compilación"></a>

### Clonar el Repositorio

Para obtener una copia del repositorio, ejecuta los siguientes comandos:

git clone https://github.com/PabloCastilloFer/TareaRedes
cd TareaRedes

### Compilar el Servidor y el Cliente

Utiliza el comando `make` para compilar `server.cpp` y `client.cpp`:

make

Esto generará dos ejecutables: `server` y `client`.

---

## Ejecución <a name="ejecución"></a>

### Servidor

Para iniciar el servidor, utiliza el siguiente comando:

./server <puerto>

Por ejemplo, para iniciar el servidor en el puerto 7777:

./server 7777

El servidor comenzará a escuchar conexiones en el puerto especificado.

### Cliente

Para ejecutar el cliente, utiliza el siguiente comando:

./client <IP> <puerto> 

Por ejemplo, para conectar el cliente al servidor en 192.168.1.100 (localhost) y el puerto 7777:

./client 192.168.1.100 7777

El cliente se conectará al servidor y comenzará la partida.

---

## Reglas del Juego <a name="reglas-del-juego"></a>

El objetivo es conectar cuatro fichas del mismo tipo en línea (horizontal, vertical o diagonal). Los jugadores y el servidor se turnan para hacer movimientos. El juego finaliza cuando uno de los jugadores gana o hay un empate.

---

## Observaciones <a name="observaciones"></a>

- Al inicio de la partida, se elige aleatoriamente quién comienza.
- Se permite más de una conexión al servidor simultáneamente.
- Después de lanzar una ficha ganadora, al cliente puede aparecerle el tablero para lanzar una "ficha extra", aunque esta no se jugará y la partida terminará.
- El total de fichas entre ambos jugadores está limitado a 21 para facilitar la visualización de la funcionalidad de Empate.

---

## Limpieza <a name="limpieza"></a>

Para eliminar los archivos compilados (`server`, `client` y los archivos objeto `*.o`), ejecuta el siguiente comando:

make clean

----------------------------------------------

PROYECTO REALIZADO PARA ASIGNATURA "COMUNICACIÓN DE REDES Y DATOS"
AUTORES PROYECTO
PABLO CASTILLO
HECTOR TORO
