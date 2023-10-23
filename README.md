# Realización de efectos de fusión y sombras en OpenGL

![opengl](https://github.com/rmelgo/ANIM-Fusion-y-sombras/assets/145989723/dad6a6fd-cf54-4788-a849-667931fb83d5)

# - Introducción

Proyecto realizado en la asignatura de Animación Digital del grado de Ingenieria Informática de la Universidad de Salamanca. El enunciado del proyecto se encuentra subido en el repositorio en un archivo PDF llamado <a href="https://github.com/rmelgo/FSI-Sistema-de-busqueda-laberinto-backtrack/blob/main/Pra%CC%81cticaBu%CC%81squedaLaberinto.pdf" target="_blank">*Enunciado.pdf*</a>.

El principal objetivo de este proyecto es la realización de una serie de programas utilizando el entorno de **OpenGL** (lenguaje C) y las librerias de ***glut*** que incluyan distintos efectos de fusión y sombras.
De esta manera, se utilizán las disintas funciones que proporciona la librería glut para realzair ejemplos básicos del uso de efectos visuales como la fusión o la niebla.

# - Comentarios sobre el entorno de ejecución

Para ejecutar este programa, se requerirá de una distribución del Sistema Operativo **Windows** y en concreto la herramienta ***Dev-C++***.

Es posible utilizar otros entornos, pero se desconoce como realizar la configuación del entorno para poder ejecutar los programas de ejemplo.

En primer lugar, se requieren descargar las librerias de glut en su versión 3.0. Para ello, se puede utilizar el siguiente enlace:

https://www.transmissionzero.co.uk/software/freeglut-devel/

Para realizar la configuración del entorno, se deben realizar los siguientes pasos:

- **Paso 1**: Copiar los ficheros *libfreeglut.a* y *libfreeglut_static.a* que se encuentran dentro de la carpeta **lib** y pegarlos en la carpeta **lib** de ***Dev-C++***.
- **Paso 2**: Copiar los ficheros *freeglut.h*, *freeglut_ext.h*, *freeglut_std.h* y *glut.h* que se encuentran dentro de la carpeta **include/GL** y pegarlos en la carpeta **include/GL** de ***Dev-C++***.
- **Paso 3**: Copiar el ficheros *freeglut.dll* que se encuentran dentro de la carpeta **bin** y pegarlos en la carpeta **C:\Windows\System32** del equipo.

**Nota**: Los directorios lib y include de ***Dev-C++*** se encuentran en un directorio similar al siguiente:  

```C:\Program Files (x86)\Dev-Cpp\MinGW64\x86_64-w64-mingw32```

- **Paso 4**: Añadir las siguientes directivas de compilación en el compilador de ***Dev-C++***:
  
  - -lopengl32
  - -lfreeglut
  - -lglu32

**Nota**: Para acceder a las directivas de compilación, ir a la sección de *Herramientas -> Opciones del Compilador*.

# Comentarios sobre el material adjuntado

El proyecto cuenta con los siguientes ficheros:

- Una carpeta llamada **Fusión** que contiene las siguientes carpetas:
  
  - Una carpeta llamada **Ejemplo 1** que contiene un proyecto en **Dev-C++** llamado ***Proyecto1.dev*** que contiene el código un programa OpenGL que aplica un efecto de fusión entre 2 triángulos de distintos colores solapados.
  - Una carpeta llamada **Ejemplo 2** que contiene un proyecto en **Dev-C++** llamado ***Fusion2.dev*** que contiene el código un programa OpenGL que aplica un efecto de fusión entre un objeto opaco y un objeto transparente de distintos colores.

- Una carpeta llamada **Efectos** que contiene las siguientes carpetas:
  
  - Una carpeta llamada **Niebla** que contiene 2 carpetas:
    
    - Una carpeta llamada **Niebla 1** que contiene un proyecto en **Dev-C++** llamado ***Proyecto2.dev*** que contiene el código un programa OpenGL que aplica un efecto de niebla en esferas con distinta escala de opacidad.
    - Una carpeta llamada **Niebla 2** que contiene un proyecto en **Dev-C++** llamado ***Proyecto1.dev*** que contiene el código un programa OpenGL que aplica un efecto de niebla en un cubo giratorio.
      
  - Una carpeta llamada **Particulas** que contiene un proyecto en **Dev-C++** llamado ***particulas.dev*** que contiene el código un programa OpenGL que aplica un efecto de partículas que va rotando.
  - Una carpeta llamada **Reflejos** que contiene un proyecto en **Dev-C++** llamado ***reflejos.dev*** que contiene el código un programa OpenGL que aplica un efecto de reflejo de un cubo giratorio sobre un plano.
    
- Un documento llamado ***EntregaOpenGL.docx*** en el que se describe detalladamente la construcción de los distintos programas OpenGL así como los distintos conceptos teóricos utilizados para ello.
- Un documento llamado ***Presentación OpenGL.pptx*** que contiene una presentación con los distintos programas OpenGL realizados así como los conceptos básicos necesarios para comprender los distintos efectos presentados.

# - Ejemplo de ejecución
