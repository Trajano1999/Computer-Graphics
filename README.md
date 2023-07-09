# Computer-Graphics

Práctica final de la asignatura de **Informática Gráfica**.

## Descripción


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
