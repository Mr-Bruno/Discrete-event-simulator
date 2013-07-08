
#include <sstream>
#include <iostream>
#include <vector>

#ifndef VAR_ALEAT_HH
#define VAR_ALEAT_HH

//---------------------------------------------------------------------------
// Definici�n de la clase Aleatorio:
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
  // Devuelve el siguiente entero al m�ximo generado por la clase.
  // Con el m�todo MCG visto en teor�a sera 0x7fffffff

  long sig(void);
  // Genera y devuelve el siguiente entero aleatorio
};


//---------------------------------------------------------------------------
// Definici�n de la clase VarAleat:
// Clase encargada de la generaci�n de muestras de variables
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

   // Parte privada con lo que quer�is.

 public:
   static Aleatorio gen;
   // Generador aleatorio com�n para todas las v.a.s
   

   VarAleat(const char *tipo_va = "D 1");

   /* inicializa una "variable aleatoria" con el tipo de distribuci�n
      especificado por la cadena *tipo_var, que consta de los
      siguientes campos separados por espacios:
      - Tipo de distribuci�n, indicado por una letra may�scula o
        min�scula: D, E, U, H, N  (respectivamente Determinista,
        Exponencial, Uniforme, Hiperexponencial y Normal)
      - Primer par�metro: la media en los casos de distribuci�n
        determinista, exponencial o normal, el extremo izquierdo en
        caso de distribuci�n uniforme y el n�mero de variables exponenciales
 		 en el caso de la distribuci�n hiperexponencial.
      - Segundo par�metro: el extremo derecho en caso de distribuci�n
        uniforme, un conjunto de pares formados por el valor medio y el peso
 		 de cada una de las variables aleatorias exponenciales (en este orden y
 		 separados por espacioes en blanco) en el caso de una hiperexponencial,
 		 y la desviaci�n t�pica en el caso de la normal.
      Los campos estar�n separados entre s� por un espacio, y los
      campos num�ricos ser�n de tipo real.
      La comprobaci�n de la correctitud de los parametros sera hecha en
      la inicializaci�n, internamente a la clase.	  
   */

   double operator++();
   // Genera y devuelve la siguiente muestra de la variable aleatoria

   friend istream& operator>>(istream& in, VarAleat& v);
   // Permitir� cambiar el tipo de la v.a. entrada, por ejemplo desde
   // un fichero. Realizar� las mismas tareas que el constructor pero ahora
   // seleccionando las l�neas necesarias del fichero para procesarlas.
   // SER� POSITIVA LA NO REPETICI�N DE C�DIGO EN LAS FUNCIONES. POR EJEMPLO
   // SER�A PREFERIBLE UTILIZAR ALG�N MECANISMO QUE PERMITA NO REPETIR EL
   // CUERPO DEL CONSTRUCTOR ALL� Y EN LA FUNCI�N AMIGA ">>"
   
   // A�adir destructor (~VarAleat) si se considera necesario
   
   
   
 };

 #endif
