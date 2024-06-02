# TareaRedes

# 4 en Línea

En este repositorio se encuentra la implementación del juego "4 en Línea", utilizando sockets en C++. El proyecto consta de un servidor y un cliente que se comunican a través de la red para jugar al juego.

## Estructura del Proyecto

- `server.cpp`: Contiene el código fuente del servidor.
- `client.cpp`: Contiene el código fuente del cliente.
- `Makefile`: Es el archivo utilizado para compilar el proyecto.

## Requisitos

Para compilar y ejecutar este proyecto, es necesario tener un compilador de C++ (por ejemplo, g++) y tener instalado `make` para utilizar el Makefile.

## Compilación

### Paso 1: Clonar el repositorio

Para obtener una copia del repositorio, puedes utilizar los siguientes comandos:

git clone https://github.com/PabloCastilloFer/TareaRedes
cd TareaRedes

### Paso 2: Compilar el servidor y el cliente

Utiliza `make` para compilar `server.cpp` y `client.cpp`:

make
Esto generará dos ejecutables: `server` y `client`.

## Ejecución

### Servidor

Para ejecutar el servidor, usa el siguiente comando:

./server <puerto>

Por ejemplo, para iniciar el servidor en el puerto 7777:

./server 7777

El servidor comenzará a escuchar conexiones en el puerto especificado.

### Cliente

Para ejecutar el cliente:

./client <IP> <puerto>

Por ejemplo, para conectar el cliente al servidor en 127.0.0.1 (localhost) y el puerto 7777:

./client 127.0.0.1 7777

El cliente se conectará al servidor y comenzará la partida.

## Reglas del Juego

El objetivo es conectar cuatro fichas del mismo tipo en línea (horizontal, vertical o diagonal). Los jugadores y el servidor se turnan para hacer movimientos. El juego finaliza cuando uno de los jugadores gana o hay un empate.

## Observaciones

- Al iniciar la partida, se elige aleatoriamente el jugador que comienza.
- Se permite más de una conexión al servidor simultáneamente.
- Es posible que al cliente, después de lanzar una ficha ganadora, le aparezca el tablero para lanzar una "ficha extra". Sin embargo, esta no se jugará y la partida terminará.
- Para determinar un empate, el total de fichas es de 21 entre ambos jugadores.

## Limpieza

Para eliminar los archivos compilados (`server`, `client` y los archivos objeto `*.o`), puedes utilizar el siguiente comando:

make clean

----------------------------------------------

PROYECTO REALIZADO PARA ASIGNATURA "COMUNICACIÓN DE REDES Y DATOS"
AUTORES PROYECTO
PABLO CASTILLO
HECTOR TORO
