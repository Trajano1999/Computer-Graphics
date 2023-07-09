# Computer-Graphics

Práctica final de la asignatura de **Informática Gráfica**.

## Descripción

Este programa es el que he utilizado durante toda la asignatura y por tanto se ven en él todas las figuras creadas tanto para las prácticas como para los exámenes. Su uso es sencillo y se explica a continuación:

Para movernos por el entorno usaremos el click derecho del ratón porque el izquierdo lo reservamos para seleccionar objetos. También podemos usar el scroll para acercarnos o alejarnos del centro. Utilizamos además algunas teclas para distintas actividades:

- tecla P: cambia la escena actual.
- tecla O: cambia el objeto dentro de la escena actual.
- tecla M: cambia el modo de visualización de polígonos actual (líneas, puntos o relleno).
- tecla B: cambia el modo de envío actual de los vértices (modo inmediato con Begin/End, modo inmediato con DrawElements, o modo diferido con DrawElements y un VAO).
- tecla F: activa o desactiva el modo de sombreado plano.
- tecla S: cambia el cauce gráfico actual (cauce programable o cauce fijo).
- tecla I: activa o desactiva la iluminación (no tiene efecto hasta la
práctica 4)
- tecla E: activa o desactiva el dibujado de los ejes de coordenadas.
- tecla Q o ESC: terminar el programa.
- teclas de cursor: rotaciones de la cámara entorno al origen.
- teclas +/-, av.pág/re.pág.: aumentar/disminuir la distancia de la camara al origen (zoom).
- teclas A y + (a la vez) : activa animaciones.
- teclas A y - (a la vez) : desactiva animaciones.

## Compilación y ejecución

En primer lugar, para poder compilar o ejecutar nuestro programa en **Linux**, debemos tener instalado en nuestro ordenador varias cosas:

1. Drivers necesarios. Para ello usamos el siguiente comando:

    `sudo ubuntu-drivers autoinstall`

2. Librerías necesarias. Las instalamos de la siguiente forma:

    `sudo apt install libglew-dev` : permite que las funciones de la versión 2.1 de OpenGL y posteriores pueden ser invocadas.

    `sudo apt install libglfw3-dev` : necesaria para la gestión de ventanas y eventos de entrada.

    `sudo apt install libjpeg-dev` : sirve para leer y escribir archivos de imagen en formato jpeg, necesarios para las texturas.

Una vez instalado esto, tanto para compilar como para ejecutar nuestro programa, debemos acceder a `trabajo/make-unix`. 

En ese espacio, realizar un `make clean` y un `make` justo después. A partir de este momento, cada cambio en el código (si se realizase) nos obliga a volver a hacer el `make clean` y el `make` de nuevo para poder apreciar los cambios.

Al hacer make, se ejecutará el programa, por lo que podemos olvidarnos de buscar el ejecutable.
