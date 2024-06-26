# TareaRedes

##############################################################
#                   4 en Línea - Implementación en C++       #
##############################################################

Este repositorio alberga la creación del juego "4 en Línea", desarrollado en C++ utilizando sockets. La aplicación consta de dos elementos esenciales: un servidor y un cliente, los cuales interactúan a través de conexiones de red para permitir a los jugadores disfrutar del juego.

## Contenido

1. [Requisitos](#requisitos)
2. [Compilación](#compilación)
3. [Ejecución](#ejecución)
4. [Descripcion del Juego](#descripcion-del-juego)
5. [Consideraciones adicionales](#consideraciones-adicionales)
6. [Limpieza](#limpieza)

---

## Requisitos <a name="requisitos"></a>

Para compilar y ejecutar esta aplicación, será necesario contar con:

- Un compilador de C++ instalado en el sistema.
- El programa `make` para gestionar la compilación.

---

## Compilación <a name="compilación"></a>

### Clonando el Repositorio

Se puede obtener una copia del repositorio utilizando los siguientes comandos:

git clone https://github.com/PabloCastilloFer/TareaRedes
cd TareaRedes

### Compilando el Servidor y el Cliente

La compilación de los archivos `server.cpp` y `client.cpp` se realiza mediante el comando `make`:

make

Esto generará los ejecutables `server` y `client`.

---

## Ejecución <a name="ejecución"></a>

### Servidor

Para iniciar el servidor, se debe ejecutar el siguiente comando:

./server <puerto>

Sustituye <puerto> por el puerto deseado para la conexión. Por ejemplo, para iniciar el servidor en el puerto 7777:

./server 7777

El servidor estará listo para aceptar conexiones en el puerto indicado.

### Cliente

Para conectar un cliente al servidor, usa el siguiente comando;

./client <IP> <puerto>

Reemplaza <IP> por la dirección IP del servidor (por ejemplo, localhost para el mismo equipo) y <puerto> por el puerto del servidor. Un ejemplo de conexión al servidor en el puerto 7777 sería:

./client 127.0.0.1 7777

El cliente establecerá conexión con el servidor para comenzar el juego.

---

## Descripción del Juego <a name="descripcion-del-juego"></a>

El objetivo del juego es conseguir cuatro fichas del mismo color en línea, ya sea horizontal, vertical o diagonal. Los jugadores, junto con el servidor, se turnan para realizar sus jugadas. El juego termina cuando un jugador gana o cuando se alcanza un empate.

---

## Consideraciones adicionales <a name="consideraciones-adicionales"></a>

- El primer jugador que inicia la partida es seleccionado al azar.
- Se permite que varios clientes se conecten al servidor simultáneamente.
- En caso de que un cliente lance una ficha ganadora, es posible que aparezca el tablero para lanzar una "ficha extra". Sin embargo, esta jugada no se realiza y la partida finaliza.
- Para facilitar la visualización de la funcionalidad de empate, se ha establecido un límite de 21 fichas en total entre ambos jugadores.

---

## Limpieza <a name="limpieza"></a>

Para eliminar los archivos compilados (`server`, `client` y los archivos objeto `*.o`), se puede utilizar el siguiente comando:

make clean

----------------------------------------------

PROYECTO REALIZADO PARA ASIGNATURA "COMUNICACIÓN DE REDES Y DATOS"
AUTORES PROYECTO
PABLO CASTILLO
HECTOR TORO
