
#include <sstream>
#include <iostream>
#include <vector>

#ifndef VAR_ALEAT_HH
#define VAR_ALEAT_HH

//---------------------------------------------------------------------------
// Definición de la clase Aleatorio:
// Clase encargada de generar enteros aleatorios
//---------------------------------------------------------------------------

using namespace std;

class Aleatorio
{
  // Parte privada
  long z;
  long const static a=48271, q=44488, r=3399, m=0x7fffffff;

public:
  Aleatorio(long sem=1);
  // Inicializa el generador con la semilla indicada

  void semilla(long sem);
  // Cambia el valor de la semilla del generador

  long max(void);
  // Devuelve el siguiente entero al máximo generado por la clase.
  // Con el método MCG visto en teoría sera 0x7fffffff

  long sig(void);
  // Genera y devuelve el siguiente entero aleatorio
};


//---------------------------------------------------------------------------
// Definición de la clase VarAleat:
// Clase encargada de la generación de muestras de variables
// aleatorias
//---------------------------------------------------------------------------


 class VarAleat
 {
   char tipo;
   double min, max;
   double media;
   double desv;
   int n_exp;
   vector<double> peso;
   vector<double> vmedio;

   // Parte privada con lo que queráis.

 public:
   static Aleatorio gen;
   // Generador aleatorio común para todas las v.a.s
   

   VarAleat(const char *tipo_va = "D 1");

   /* inicializa una "variable aleatoria" con el tipo de distribución
      especificado por la cadena *tipo_var, que consta de los
      siguientes campos separados por espacios:
      - Tipo de distribución, indicado por una letra mayúscula o
        minúscula: D, E, U, H, N  (respectivamente Determinista,
        Exponencial, Uniforme, Hiperexponencial y Normal)
      - Primer parámetro: la media en los casos de distribución
        determinista, exponencial o normal, el extremo izquierdo en
        caso de distribución uniforme y el número de variables exponenciales
 		 en el caso de la distribución hiperexponencial.
      - Segundo parámetro: el extremo derecho en caso de distribución
        uniforme, un conjunto de pares formados por el valor medio y el peso
 		 de cada una de las variables aleatorias exponenciales (en este orden y
 		 separados por espacioes en blanco) en el caso de una hiperexponencial,
 		 y la desviación típica en el caso de la normal.
      Los campos estarán separados entre sí por un espacio, y los
      campos numéricos serán de tipo real.
      La comprobación de la correctitud de los parametros sera hecha en
      la inicialización, internamente a la clase.	  
   */

   double operator++();
   // Genera y devuelve la siguiente muestra de la variable aleatoria

   friend istream& operator>>(istream& in, VarAleat& v);
   // Permitirá cambiar el tipo de la v.a. entrada, por ejemplo desde
   // un fichero. Realizará las mismas tareas que el constructor pero ahora
   // seleccionando las líneas necesarias del fichero para procesarlas.
   // SERÁ POSITIVA LA NO REPETICIÓN DE CÓDIGO EN LAS FUNCIONES. POR EJEMPLO
   // SERÍA PREFERIBLE UTILIZAR ALGÚN MECANISMO QUE PERMITA NO REPETIR EL
   // CUERPO DEL CONSTRUCTOR ALLÍ Y EN LA FUNCIÓN AMIGA ">>"
   
   // Añadir destructor (~VarAleat) si se considera necesario
   
   
   
 };

 #endif
