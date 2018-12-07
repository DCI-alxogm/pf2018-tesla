\documentclass{article}
\usepackage[spanish]{babel}
\usepackage[utf8x]{inputenc}
\usepackage[T1]{fontenc}
\usepackage{graphicx}
\usepackage{amsmath}
\usepackage[colorlinks=true, allcolors=blue]{hyperref}
\usepackage{vmargin}

\title{\textbf{Programación básica\\Proyecto Final: Simulación de la colisión entre galaxias}}
\author{Barco Gabriel Missael, Díaz Moya José Francisco \\Macías Padilla Brayhan Alan, Segura Gómez Guillermo}
\date{09 de Diciembre de 2018}

\begin{document}

\maketitle

\section{Introducción}
La humanidad ha observado desde tiempos muy remotos el universo, nuestros antepasados se han maravillado generación tras generación con lo hermoso que es el cosmos. Vivimos en uno de los millones de planetas, que está orbitando una de las millones de estrellas, que a su vez se encuentra en una de las millones de galaxias. En cierto sentido, podríamos parecer insignificantes, estamos condenados solamente a observar, nuestra tecnología no nos alcanza para mas, y es cada vez mas evidente que las leyes del espacio nos impiden ir mas allá de donde nuestra imaginación lo permite. Pero aun así, el observar es brutalmente hermoso, citando una frase del divulgador científico español Martí Montferrer, \textit{Lo que nos hace grandes es el hecho de que podamos ver lo pequeños que somos}, y es cierto, en nuestra insignificancia, estamos desentrañando los secretos que esconde el universo. Las galaxias, acumulaciones masivas de estrellas, cuerpos colosales que cada día nos maravillan mas; es increíble como somos insignificantes en el plano de una galaxia, y uno de los fenómenos mas increíbles que existen en el universo, es una colisión de dos de estos monstruos. En este proyecto, haremos una simulación de la colisión de dos galaxias utilizando nuestros conocimientos desarrollados durante el curso. 

\section{Marco Teórico}
Para la implementación de este proyecto, se tomará cada galaxia como conjuntos de puntos homogéneos distribuidos en una esfera, por lo tanto se tiene la colisión de dos esferas de n-puntos, o n-cuerpos, en donde cada cuerpo correspondería a una estrella, y están separadas por una distancia, y cada partícula tiene una velocidad inicial. Cabe aclarar que cada estrella tiene la misma masa, todos los puntos son iguales.
Para la solución matemática, se sabe que cada partícula \textit{j-ésima} se moverá de acuerdo a la segunda ley de Newton:
\begin{equation}
    \vec{F}=m_p\vec{a}_j
    \label{1}
\end{equation}
donde $m_p$ es la masa de una partícula, o una estrella, $\vec{a}_j$ es la aceleración, y $\vec{F}$ es la fuerza neta que siente la partícula. La fuerza neta que siente una partícula debido a la presencia de todas las demás es igual a la suma de la fuerza debida a cada una:
\begin{equation}
    \vec{F}=\sum_{i\neq j}^N\vec{f}_{ij}
    \label{2}
\end{equation}
donde $f_{ij}$ es la fuerza que siente la partícula \textit{j-ésima} debido a la partícula \textit{i-ésima}. Cabe aclarar que la suma es sobre todas las partículas, excepto aquella para cual se esta calculando la fuerza neta que se siente. 

Ahora, si consideramos que la fuerza gravitacional que sienten dos partículas de masa $m_p$ es igual a:
\begin{equation}
    \vec{f}_{ij}=-\frac{Gm_pm_p}{r³}\vec{r}_{ij}
    \label{3}
\end{equation}
en donde $G = 4\pi²yr^{-2}AUM^{-1}_{\circ}$ es la constante de gravitación universal en masas solares, unidades astronómicas y años.

Si combinamos la ecuación \ref{1}, y la ecuación \ref{3}, obtenemos la siguiente expresión:
\begin{equation}
    m_p\ddot{\vec{r}}_i=-\sum_{i\neq j}^{N}\frac{Gm_pm_p\vec{r}_{ij}}{r³_{ij}}
    \label{4}
\end{equation}

Para resolver la ecuación de movimiento \ref{4}, considerando que es una ecuación vectorial, podemos separarla en componentes:
\begin{equation*}
\begin{split}
    \ddot{x}_i=Fx \\
    \ddot{y}_i=Fy \\
    \ddot{z}_i=Fz
\end{split}
\end{equation*}
Las ecuaciones anteriores, son ecuaciones diferenciales, y se pueden reescribirse de la siguiente forma:
\begin{equation*}
    \begin{split}
        \dot{v}_{x,i} = Fx \\
        \dot{x}_i = v_{x,i} \\
        \dot{y}_{y,i} = Fy \\
        \dot{y}_i = v_{y,i} \\
        \dot{v}_{z,i} = Fz \\
        \dot{z}_i = v_{z,i}
    \end{split}
\end{equation*}
Para resolver la dinámica de las partículas, se tienen que resolver las ecuaciones anteriores para encontrar $x_i(t)$, $y_i(t)$, $z_i(t)$. Durante el proceso también se calcula $v_{x,i}(t)$, $v_{y,i}(t)$, $v_{z,i}(t)$. Esto se hace para todas las partículas, en otras palabras, se calculan las posiciones y velocidades de todas las ''estrellas'' a cada paso de tiempo. 

El método óptimo para resolver estas ecuaciones es el método Leap-frog, que consiste en establecer un conjunto de posiciones $(x_{i}, y_{i}, z_{i})$ y velocidades $(v_{x,i}, v_{y,i}, v_{z,i})$ iniciales, a un tiempo inicial $t$, y actualizarlas a un tiempo posterior $t+h$ para obtener las nuevas posiciones y velocidades en el tiempo $t=t+h$, siguiendo la siguiente regla:
\begin{equation}
    x_i(t+h)=x_i(t)+h*v_{x,i}(t)+1/2*F_x*h²
    \label{5}
\end{equation}
\begin{equation}
    v_{x,i}(t+h)=v_{x,i}(t)+1/2*(F_x(t)+F_x(t+h))*h
    \label{6}
\end{equation}
donde $h$ es el paso del tiempo. A cada paso de tiempo se reemplazan las posiciones y velocidades iniciales por las nuevas, para poder dar un nuevo paso del tiempo. La regla esta escrita en función de $x$, pero se aplica de forma similar para $y$ y $z$. El paso del tiempo $h$ se toma como un valor constante, y se le da un valor suficientemente pequeño para que la evolución de las partículas sea precisa. 

\section{Código}
Lo primero a considerar del programa es el hecho de que trabaja utilizando una librería para declarar las funciones. En la librería llamada \textit{galaxia.h}, se incluyen todas las funciones utilizadas por el programa. A continuación se explica cada una de las funciones que se encuentran en el archivo llamado \textit{funciones.c}:
\begin{itemize}
    \item \textbf{Imprime} es una función de tipo con entrada y sin salida. Lo que hace esta función es imprimir la matriz a la pantalla.
    \item \textbf{Crea} es una función de tipo con entrada y con salida. Lo que hace esta función es crear números aleatorios positivos o negativos, delimitándolos hasta un valor $M$, para esto se utiliza el comando \textit{rand}, el problema es que \textit{rand} únicamente te da números positivos, por lo que se tienen que convertir a negativos los valores pares y así tener números positivos y negativos.
    \item \textbf{Esfera} es una función de tipo con entrada y con salida. La función crea esferas de radio $r$ con $n$ puntos, con un desplazamiento $t$ en el eje $x$, y una velocidad máxima $v$. Para crear las esferas se utiliza una matriz de dos dimensiones $(i,j)$, en la que $i$ es igual al numero de puntos $n$ y $j$ es igual a 6, esto porque para cada punto se tiene una posición y una velocidad diferentes, y tres lugares de $j$ en la matriz son para las posiciones $x_i, y_i, z_i$ y los otros tres para las velocidades $v_{x,i}, v_{y,i}, v_{z,i}$. Como se tienen que encontrar valores aleatorios, se utiliza la función \textbf{crea}, y se generan valores hasta un radio máximo y una velocidad máxima. Cuando se tiene el punto junto con la velocidad, se checa si el punto se encuentra dentro de la esfera, esto se hace comparando el radio de la esfera con el valor de la magnitud del vector posición, si $r<|\vec{R}|$ entonces el punto se encuentra fuera de la esfera y se reinicia el contador para que genere otro punto diferente. Una vez que se tiene el punto, se desplaza una distancia $t$ en el eje $x$ y se calculan las velocidades relativas en $x$ y en $y$.
    \item \textbf{Archivo} es una función de tipo con entrada y sin salida. La función guarda los puntos de las dos esferas en un archivo. Los archivos que se crean son de la forma \textit{numero.txt}, en donde \textit{numero} es el número de iteración que representa. Se imprimen 6 columnas, las primeras 3 son las posiciones, y las siguientes 3 son las velocidades. Se imprimen los primeros $n$ puntos de la primera esfera e inmediatamente después se imprimen los siguientes $N$ puntos de la segunda esfera.
    \item \textbf{Fuerza} es una función de tipo con entrada y con salida. Lo que hace la función es calcular la fuerza neta actuante en $x, y, z$ de una partícula. La fuerza se calcula utilizando la ecuación \ref{4}, mediante ciclos, ya que una sumatoria se implementa de manera iterativa, se considera $m_p=1$ ya que estamos considerando partículas iguales al sol, por lo tanto la masa tiene un valor de 1. Se calculan los valores de las dos esferas. Los valores se guardan en una matriz en los lugares 6, 7, 8, ya que la matiz global que estamos utilizando es de 9 lugares, los primeros tres para las posiciones, los siguientes tres para las velocidades y los últimos tres para las fuerzas de cada partícula. 
\end{itemize}
Una vez que sabemos que es lo que hace cada función, pasemos al grueso del programa que esta en el archivo llamado \textit{main.c}. Lo primero que se hace es declarar las variables que se van a utilizar, los números de partículas en cada esfera $n$, $N$, los radios de cada esfera $r$\_$1$, $r$\_$2$, la distancia que separa las esferas $R$, la velocidad máxima $vo$, el paso del tiempo $h$, el tiempo total $T$ y algunas variables auxiliares para los cálculos $pos$, $rel$\_$x$, $rel$\_$y$. También se declara una variable llamada $gen$, la cual nos indica si nosotros tenemos que generar las esferas, o las esferas ya están, y solo tenemos que leer los datos. Después se leen las condiciones iniciales de un archivo llamado \textit{inicio.txt}, y se asignan a las variables anteriores. Se declaran cuatro matrices, dos para cada esfera, una para las condiciones actuales y otra para las condiciones anteriores ($es1$, $es2$, $nes1$, $nes2$). Las matrices que se utilizan son de dos dimensiones, cada matriz es de tamaño $n$ o $N$, (según sea el caso), en su lado $i$, en donde cada una de las columnas representa una partícula, y de tamaño 9 en su lado $j$, esto porque en los primeros tres lugares de $j$ se utilizan para las posiciones  $(x, y, z)$, los siguientes tres para las velocidades $(v_{x}, v_{y}, v_{z})$ y los últimos tres para las fuerzas $(Fx, Fy, Fz)$ de cada partícula. Las matrices se verían como se muestra a continuación:
\begin{equation*}
\left( \begin{array}{cccc}
 x_0 & x_1 & \cdots & x_n\\ 
 y_0 & y_1 & \cdots & y_n\\
 z_0 & z_1 & \cdots & z_n\\ 
 v_{x,0} & v_{x,1} & \cdots & v_{x,n} \\
 v_{y,0} & v_{y,1} & \cdots & v_{y,n} \\ 
 v_{z,0} & v_{z,1} & \cdots & v_{z,n} \\
 Fx_0 & Fx_1 & \cdots & Fx_n \\ 
 Fy_0 & Fy_1 & \cdots & Fy_n \\
 Fz_0 & Fz_1 & \cdots & Fz_n \\
\end{array} \right) 
\label{matej}
\end{equation*}
en donde cada columna $i$, representa una partícula, y los valores de las filas $j$, representan los parámetros a calcular. 

Se utiliza un condicional y la variable $gen$ para determinar si nosotros generamos las esferas o solo las leemos. En el caso en el que nosotros tengamos que generarlas, llamamos a la función \textbf{esfera}. Después de tener inicializadas las posiciones y velocidades iniciales, se inicicaliza la fuerza de las esferas utilizando la funcion \textbf{fuerza}.

Una vez que se tienen las esferas inicializadas, se prosigue a hacer el cálculo implementando el metodo Leap-frog, y se resuelve de manera iterativa las ecuaciones \ref{5} y \ref{6}, tomando como $h$ cada paso en el tiempo, y $T$ el tiempo máximo. Con cada iteración se van reescribiendo las matrices $nes1$ y $nes2$ que guardan las posiciones y velocidades nuevas, y para las posiciones y velocidades anteriores se utilizan $es1$ y $es2$. Con cada iteración se llama a la función \textbf{archivo} que imprime los resultados.


\section{Resultados}

\section{Referencias}

\begin{thebibliography}{X}
\bibitem{Baz} \textsc{Pérez Montiel, Héctor},
\textit{Fisica General}, cuarta edición, PATRIA, México, 2014.

\end{thebibliography}


\end{document}

