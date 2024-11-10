# Computer-Graphics

Práctica final de la asignatura de **Informática Gráfica** del Doble Grado en Ingeniería Informática y Matemáticas de la Universidad de Granada.

## Descripción

Este programa ha sido el utilizado a lo largo de toda la asignatura, por lo que en él se encuentran todas las figuras creadas tanto para las prácticas como para los exámenes. Su uso es sencillo y se describe a continuación:

Para navegar en el entorno, utilizaremos el botón derecho del ratón, ya que el izquierdo se destina a la selección de objetos. Además, podemos usar la rueda del ratón para acercarnos o alejarnos del centro. También se emplean varias teclas para realizar distintas acciones:

- **Tecla P**: cambia la escena actual.
- **Tecla O**: cambia el objeto dentro de la escena actual.
- **Tecla M**: cambia el modo de visualización de polígonos actual (líneas, puntos o relleno).
- **Tecla B**: cambia el modo de envío actual de los vértices (modo inmediato con Begin/End, modo inmediato con DrawElements, o modo diferido con DrawElements y un VAO).
- **Tecla F**: activa o desactiva el modo de sombreado plano.
- **Tecla S**: cambia el cauce gráfico actual (cauce programable o cauce fijo).
- **Tecla I**: activa o desactiva la iluminación (no tiene efecto hasta la
práctica 4).
- **Tecla E**: activa o desactiva el dibujado de los ejes de coordenadas.
- **Tecla Q o ESC**: termina el programa.
- **Teclas de cursor**: aplica rotaciones de la cámara entorno al origen.
- **Teclas +/-, av.pág/re.pág**: aumenta/disminuye la distancia de la cámara al origen (zoom).
- **Teclas A y + (a la vez)**: activa las animaciones.
- **Teclas A y - (a la vez)**: desactiva las animaciones.

## Compilación y ejecución

Para compilar o ejecutar nuestro programa en Linux, es necesario tener instalados en el sistema varios componentes:

1. **Drivers necesarios**: para instalarlos, se debe utilizar el siguiente comando:

    ``sudo ubuntu-drivers autoinstall``

2. **Librerías necesarias**: se instalan de la siguiente manera:

    ``sudo apt install libglew-dev``: permite que las funciones de la versión 2.1 de OpenGL y posteriores pueden ser invocadas.

    ``sudo apt install libglfw3-dev``: esencial para la gestión de ventanas y eventos de entrada.

    ``sudo apt install libjpeg-dev``: permite leer y escribir archivos de imagen en formato ``JPEG``, necesarios para las texturas.

Una vez instalados estos componentes, para compilar y ejecutar el programa debemos acceder al directorio ``trabajo/make-unix``. 

En ese espacio, se debe ejecutar el comando ``make clean``, seguido de ``make``. A partir de este momento, cada vez que se realicen cambios en el código, será necesario volver a ejecutar ``make clean`` y ``make`` para que los cambios sean reflejados.

Finalmente, el programa se ejecutará al ejecutar ``make``.
