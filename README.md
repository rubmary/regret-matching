# regret-matching

Procedimientos que llevan a equilibrios de nash en juegos de suma cero con 2 jugadores.
Capítulo 2 de mi tesis.

Para compilar es necesario descargar la librería Eigen, disponible en http://eigen.tuxfamily.org/index.php?title=Main_Page

Para resolver un juego en forma normal se puede utilizar el script solve_normal_form.sh utilizando como argumento el nombre del juego, cuya matriz debe estar en un archivo de texto en la carpeta juegos/forma_normal

```
./forma_normal.sh name
```