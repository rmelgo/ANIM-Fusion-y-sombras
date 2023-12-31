# Realización de efectos de fusión y sombras en OpenGL

![opengl](https://github.com/rmelgo/ANIM-Fusion-y-sombras/assets/145989723/dad6a6fd-cf54-4788-a849-667931fb83d5)

# - Introducción

Proyecto realizado en la asignatura de ***Animación Digital*** del grado de Ingenieria Informática de la Universidad de Salamanca. El enunciado del proyecto se encuentra subido en el repositorio en un archivo PDF llamado <a href="https://github.com/rmelgo/ANIM-Fusion-y-sombras/blob/main/Enunciado.pdf" target="_blank">*Enunciado.pdf*</a>.

El principal objetivo de este proyecto es la realización de una serie de programas utilizando el entorno de **OpenGL** (lenguaje C) y las librerías de ***glut*** que incluyan distintos efectos de fusión y sombras.
De esta manera, se utilizarán las disintas funciones que proporciona la librería *glut* para realizar ejemplos básicos del uso de efectos visuales como la fusión o la niebla.

# - Comentarios sobre el entorno de ejecución

Para ejecutar este programa, se requerirá de una distribución del Sistema Operativo **Windows** y en concreto la herramienta ***Dev-C++***.

Es posible utilizar otros entornos, pero se desconoce como realizar la configuración del entorno necesaria para poder ejecutar los programas de ejemplo.

En primer lugar, se requieren descargar las librerias de *glut* en su versión 3.0. Para ello, se puede utilizar el siguiente enlace:

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
  
  - Una carpeta llamada **Ejemplo 1** que contiene un proyecto en **Dev-C++** llamado ***Proyecto1.dev*** que contiene el código un programa *OpenGL* que aplica un efecto de fusión entre 2 triángulos de distintos colores solapados.
  - Una carpeta llamada **Ejemplo 2** que contiene un proyecto en **Dev-C++** llamado ***Fusion2.dev*** que contiene el código un programa *OpenGL* que aplica un efecto de fusión entre un objeto opaco y un objeto transparente de distintos colores.

- Una carpeta llamada **Efectos** que contiene las siguientes carpetas:
  
  - Una carpeta llamada **Niebla** que contiene 2 carpetas:
    
    - Una carpeta llamada **Niebla 1** que contiene un proyecto en **Dev-C++** llamado ***Proyecto2.dev*** que contiene el código un programa *OpenGL* que aplica un efecto de niebla en esferas con distinta escala de opacidad.
    - Una carpeta llamada **Niebla 2** que contiene un proyecto en **Dev-C++** llamado ***Proyecto1.dev*** que contiene el código un programa *OpenGL* que aplica un efecto de niebla en un cubo giratorio.
      
  - Una carpeta llamada **Particulas** que contiene un proyecto en **Dev-C++** llamado ***particulas.dev*** que contiene el código un programa *OpenGL* que aplica un efecto de partículas que va rotando.
  - Una carpeta llamada **Reflejos** que contiene un proyecto en **Dev-C++** llamado ***reflejos.dev*** que contiene el código un programa *OpenGL* que aplica un efecto de reflejo de un cubo giratorio sobre un plano.
    
- Un documento llamado ***EntregaOpenGL.docx*** en el que se describe detalladamente la construcción de los distintos programas *OpenGL* así como los distintos conceptos teóricos utilizados para ello.
- Un documento llamado ***Presentación OpenGL.pptx*** que contiene una presentación con los distintos programas *OpenGL* realizados así como los conceptos básicos necesarios para comprender los distintos efectos presentados.

# - Fusión

## Primer ejemplo

### Conceptos teóricos

Para entender como funciona la fusión básica en *OpenGL*, es importante comentar en primer lugar varios conceptos teóricos:

**Modelo RGB y RGBA**

- Los colores en los píxeles de la pantalla un ordenador se representan a través de una combinación de luces roja, azul, verde lo que da lugar al modelo RGB. A este modelo RGB se le puede añadir un cuarto valor llamado alfa o A dando lugar así al modelo RGBA.
- De esta manera, en cada píxel de la pantalla se almacenan 4 valores correspondientes a estos 4 parámetros que en su conjunto definen el color que va a emitir el píxel.
  
**Valores alfa**

El **valor alfa** o **A** suele estar comunmente asociado al porcentaje de transparencia. Pero realmente es la proporción de color del objeto dibujado que se fusiona con el color del objeto que se va a dibujar.

En *OpenGL*, exite una macro llamada estado de mezcla o GL_BLEND.

- Cuando el estado de mezcla (GL_BLEND) está activado, este valor alfa se utiliza para definir la proporción de mezcla con la que se fusiona el objeto dibujado (que se encuentra en los bufferes) con el objeto que se esta procesando o dibujando.

- Cuando el estado de mezcla (GL_BLEND) no está activado, no existe ningún tipo de combinación o mezcla.

**Factores de origen y destino**

Como hemos dicho anteriormente, en la fusión los valores del fragmento que se está procesando (origen) se combinan con los valores de los píxeles almacenados en los buffers de fotogramas (destino). Esta fusión se realiza en 2 etapas:

- En primer lugar, se especifica cómo calcular los factores del origen y destino. Estos factores son una cuádrupla de valores R, G, B, A que se obtienen por la multiplicación de los componentes RGBA del origen y el destino respectivamente.

- En segundo lugar, se calcula el valor RGBA resultante de la mezcla a partir de los factores de origen y destino y los valores RGBA de origen y destino siguiendo la siguiente fórmula:

```(RsSr+RdDr, GsSg+GdDg, BsSb+BdDb, AsSa+AdDa)```

Donde:
- Factor de origen: (Sr, Sg, Sb, Sa)
- Factor de destino: (Dr, Dg, Db, Da)
- RGBA origen: (Rs, Gs, Bs, As)
- RGBA destino: (Rd, Gd, Bd, Ad)

Nota: Cada valor R, G, B y A tiene valores que oscilan entre 0 y 1 (ambos incluidos).

### Ejecución del primer ejemplo de fusión

Este ejemplo va a consistir en la representación de 2 triángulos con distintos colores (azul y amarillo) donde estos 2 triángulos van a compartir un área en común, en la que queremos que se fusionen los colores de ambos triángulos.
Si el usuario pulsa la tecla *T*, se cambia el orden en el que se dibujan los triángulos, lo que supone un cambio en el color de la mezcla. Para la fusión se ha definido un valor alfa de 0.75.

Posibles casuísticas:

- Si dibujamos primero el triángulo izquierdo (amarillo) y después el derecho (azul), en la fusión vamos a tener un 75 % del color del segundo triángulo que es el azul (figura origen) y un 25 % del color del primer triángulo que es el amarillo (figura destino) por lo que el color azul del segundo triángulo predominará sobre el color amarillo del primer triángulo.

- Si dibujamos primero el triángulo derecho (azul) y después el izquierdo (amarillo), en la fusión vamos a tener un 75 % del color del segundo triángulo que es el amarillo (figura origen) y un 25 % del color del primer triángulo que es el azul (figura destino) por lo que el color amarillo del segundo triángulo predominará sobre el color azul del primer triángulo.

En la siguiente imagen, se mostrará un ejemplo de ejecución en el que se dibuja primero el triángulo izquierdo (amarillo):

<p align="center">
  <img src="https://github.com/rmelgo/ANIM-Fusion-y-sombras/assets/145989723/196ac0c4-a959-4f8c-a33a-9e95d21958f9">
</p>

En la siguiente imagen, se mostrará un ejemplo de ejecución en el que se dibuja primero el triángulo derecho (azul):

<p align="center">
  <img src="https://github.com/rmelgo/ANIM-Fusion-y-sombras/assets/145989723/d01ccbfd-cc6c-48be-be60-929cd6412cf8">
</p>

## Segundo ejemplo

### Conceptos teóricos

Como se pudo observar al final del ejemplo anterior, el orden en el que se dibujan los triángulos afecta en gran medida a la mezcla resultante. Esto para los objetos en 3D sucede de la misma manera ya que al realizar mezcla entre objetos translúcidos tridimensionales, esta mezcla también va a depender si el dibujado de estos objetos se realiza de atrás hacia adelante o de adelante hacia atrás. Además para los objetos en 3D, hay que tener en cuenta el efecto del buffer de profundidad.

Este **buffer de profundidad** realiza un seguimiento de la distancia entre el punto de vista y la parte del objeto que ocupa un píxel determinado en una ventana de la pantalla. De esta manera, cuando aparecen varios colores de varios objetos en un píxel, solo se dibuja el objeto que está más cerca del punto de vista. Así no se dibujan partes ocultas de un objeto que no se van a ver. Esto sucede así con objetos opacos.

Si se da el caso de que un objeto translúcido esta por delante de un objeto opaco, queremos que se produzca una fusión entre los colores de ambos objetos en vez de ocultar el objeto que se encuentra detrás.

### Ejecución del segundo ejemplo de fusión

Este ejemplo va a consistir en la representación de una esfera opaca amarilla y un cubo translúcido azul donde estas 2 objetos van a compartir un área en común.
Si el usuario pulsa la tecla *R*, se cambia la profundidad de los objetos de manera que los distintos efectos producidos dependen de la profundidad con la que se dibujen ambos objetos.

Posibles casuísticas:

- Si la esfera opaca se encuentra por delante del cubo translúcido, la parte del cubo translúcido que se encuentra detrás de la esfera opaca no se dibujará ya que se encuentra detrás de un objeto opaco.

- Si el cubo translúcido se encuentra por delante de la esfera opaca, la parte de la esfera opaca que se encuentra detrás de la del cubo translúcido se dibujará y mezclará con el color del cubo ya que se encuentra detrás de un objeto translúcido.

En la siguiente imagen, se mostrará un ejemplo de ejecución en el que se dibuja por delante la esfera opaca:

<p align="center">
  <img src="https://github.com/rmelgo/ANIM-Fusion-y-sombras/assets/145989723/6b833044-b1d1-4bba-b598-673c40eadcff">
</p>

En la siguiente imagen, se mostrará un ejemplo de ejecución en el que se dibuja por delante el cubo translúcido:

<p align="center">
  <img src="https://github.com/rmelgo/ANIM-Fusion-y-sombras/assets/145989723/92fd2e34-62c0-49ed-ba0d-7823b8246b08">
</p>

# - Efectos

## Niebla

### Conceptos teóricos

El uso de la niebla en *OpenGL* es un concepto muy simple ya que se trabaja con escalas de grises para generar este efecto. Para hacer esto posible, se usarán distintas funciones que se aplicarán a cada píxel dependiendo de su distancia respecto al ojo. Un píxel el cual esté más alejado de la cámara tendrá menos visibilidad que uno que esté más cerca. Ahí es donde entran las escalas de grises antes mencionadas. Cuando un píxel sea más lejano, se le aplicará un tono gris más denso. Al contrario, cuanto más cerca esté el píxel, más ligero será el tono de gris.

También debemos aclarar que no es obligatorio usar solo el color gris, por ejemplo, si queremos hacer un efecto de noche en un bosque, podríamos usar el color negro en vez del gris para crear este otro tipo de atmósferas. El color es un valor que se puede modificar para aplicar efectos de niebla.

Otro factor que se puede modificar es la densidad de la niebla. Así podemos determinar la distancia a la que un objeto le afecta este efecto.

Existen 3 tipos de niebla en función de la forma de calcular el peso de los tonos grises:

- Lineal
- Exponencial
- Exponencial al cuadrado

### Ejecución del primer ejemplo de niebla

Este ejemplo va a consistir en la representación de una serie de esferas rojas a las cuales se le aplican distintos efectos de niebla más o menos intensos.
Si el usuario pulsa la tecla *F*, se cambia el tipo de niebla aplicado sobre las distintas esferas. El orden seguido es el siguiente:

- Inicialmente se aplica un tipo de niebla *exponencial* sobre las esferas.
- Si se pulsa la tecla F, el tipo de niebla se cambia a *exponencial al cuadrado*.
- Si se vuelve a pulsar la tecla F, el tipo de niebla se cambia a *lineal*.
- Si se vuelve a pulsar la tecla F, el tipo de niebla se cambia de nuevo a *exponencial* y así sucesivamente.

En la siguiente imagen, se mostrará un ejemplo de niebla ***exponencial*** sobre las esferas:

<p align="center">
  <img src="https://github.com/rmelgo/ANIM-Fusion-y-sombras/assets/145989723/c26b244f-3585-4873-a366-a28d2d621316">
</p>

En la siguiente imagen, se mostrará un ejemplo de niebla ***exponencial al cuadrado*** sobre las esferas:

<p align="center">
  <img src="https://github.com/rmelgo/ANIM-Fusion-y-sombras/assets/145989723/f54fece1-e4e8-4100-a1b8-5c9aea28bc2c">
</p>

En la siguiente imagen, se mostrará un ejemplo de niebla ***lineal*** sobre las esferas:

<p align="center">
  <img src="https://github.com/rmelgo/ANIM-Fusion-y-sombras/assets/145989723/edd1b36d-4741-4a05-bec7-e11e1fb53997">
</p>

### Ejecución del segundo ejemplo de niebla

Este ejemplo va a consistir en la representación de un cubo giratorio en 3D al que se le ha aplicado niebla a cada una de sus caras.  
En la siguiente imagen, se mostrará el resultado:

<p align="center">
  <img src="https://github.com/rmelgo/ANIM-Fusion-y-sombras/assets/145989723/9081ab2c-6cdd-4d17-8b7d-1f021a470a2e">
</p>

## Reflejo

### Conceptos teóricos

El efecto de reflejo en *OpenGL* se basa en dos ideas:

- La primera idea será redibujar el objeto u objetos que queremos que se reflejen en una superficie en concreto.
- La segunda idea es usar los efectos de fusión ya explicados anteriormente.

Para redibujar un objeto sobre una superficie, se utilizarán los conceptos de ***Stencil Test*** y ***Stencil Buffer***.

A la hora de renderizar un objeto con *OpenGL* se le puede aplicar el ***Stencil Test*** para descartar una serie de píxeles los cuales se encuentran marcados en el ***Stencil Buffer***. Dentro de este buffer, nos encontramos un conjunto de 1 y 0. 
De esta manera, al renderizar el ***Stencil Test*** solo se renderizan los píxeles de la imagen original que coincidan con las casillas que tengan un 1 en el stencil buffer.

<p align="center">
  <img src="https://github.com/rmelgo/ANIM-Fusion-y-sombras/assets/145989723/32c30d3c-0c04-4402-a35f-d0d204a04fe5">
</p>

### Ejemplo de reflejo

Este ejemplo va a partir del ejemplo del cubo anterior. En este caso, se va a representar en un plano horizontal el reflejo del cubo giratorio 3D.
En la siguiente imagen, se mostrará el resultado:

<p align="center">
  <img src="https://github.com/rmelgo/ANIM-Fusion-y-sombras/assets/145989723/d05bea9d-b58e-44ba-bee1-a5ee223ab488">
</p>

## Partículas

### Conceptos teóricos

Para representar partículas en *OpenGL*, La idea será crear una imagen la cual al pasarla por este canal, a cada píxel se le aplicará un valor de alfa equivalente a la del canal. Por así decirlo, será como aplicar un filtro de alfa a cada píxel de la imagen. 

En nuestro caso, vamos a utilizar las siguientes imágenes para generar las partículas:

<p align="center">
  <img src="https://github.com/rmelgo/ANIM-Fusion-y-sombras/assets/145989723/fcbee8bf-d27f-4adb-a272-b2f5893c9853">
</p>

Podemos ver como solo se utilizan los colores blanco, negro y diferentes tonos de gris. Estos colores representan el valor alfa, siendo el blanco un valor 1f (completamente opaco) y el negro el valor 0f (completamente transparente). Con esta idea entendemos que si un objeto se aleja más del centro, su valor alfa decrece. 

La forma de hacerlo es parecida a como cargamos una imagen con el bitmap en *OpenGL*, vamos a ir recorriendo la imagen pixel a pixel y pondremos en un array de color cual es su RGB. Ahora, además de ese primer recorrido, vamos a comparar cada casilla del array con el Alpha Channel para darle el valor alfa correspondiente según su escala de grises. Al tratarse de una escala de grises podemos coger el valor R, G o B sin diferencias.

### Ejemplo de partículas

Este ejemplo va a contener un efecto de partículas giratorio que va a estar sujeto al efecto de la gravedad. El color de las partículas ira cambiando a lo largo de tiempo a medida que se va produciendo el giro.
En las siguientes imágenes, se mostrará el resultado:

<p align="center">
  <img src="https://github.com/rmelgo/ANIM-Fusion-y-sombras/assets/145989723/1d992985-8f27-405c-98a1-d802412262bf">
</p>

<p align="center">
  <img src="https://github.com/rmelgo/ANIM-Fusion-y-sombras/assets/145989723/f8e6cdbe-3533-4591-936f-e8f2048e419c">
</p>

# - Participantes

<table>
  <td align="center"><a href="https://github.com/rmelgo"><img src="https://avatars.githubusercontent.com/u/145989723?s=400&u=e5c06adba3f3c418207178abc845d398b3d5f77f&v=4" width="100px;" alt=""/><br /><sub><b>Raúl Melgosa</b></sub></a><br/> 
  <td align="center"><a href="https://github.com/Manuelsantaisabel"><img src="https://avatars.githubusercontent.com/u/95097735?v=4" width="100px;" alt=""/><br /><sub><b>Manuel Santa Isabel</b></sub></a><br/> 
</table>
