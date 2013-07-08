
#ifndef COLAS_HH
#define COLAS_HH

#include "usuario.hh"

#include <iostream>
#include <list>
#include <iomanip>

using namespace std;

class Colas{

	list<Usuario> vacios;					//cola de usuarios vacios
	list<Usuario> cola1;					//cola1
	list<Usuario> cola2;					//cola2
    list<Usuario>::iterator it,ref;			//iteradores genéricos
    list<Usuario>::iterator ind_usr;		//proximo usuario en salir de la cola2
    list<Usuario>::iterator lim_recursos;	//proximo usuario en entrar en recursos
   	double t_ref;							//instante desde la última entrada/salida en la cola2
   	int k;									//número de recursos
	const static int PRECISION = 5;			//precisión de representación de los datos

public:

	//constructor de Colas (se le pasa el número de recursos [1 - por defecto])
	Colas(int n_recursos = 1);
	//Fija el tiempo de la última entrada/salida en la cola2
	void setTRef(double v);
	//Devulve el tiempo de la última entrada/salida en la cola2
	double getTRef();
	//mete un nuevo usuario en la cola1
	void meterUsrCola1(double t_in, double s);
	//devuelve los datos del próximo usuario en salir de la cola1
	Usuario proximoSalirCola1();
	//pasa un usario a la cola2 (FCFS)
	void pasarUsrCola2FCFS(double t);
	//pasa un usario a la cola2 (RR)
	void pasarUsrCola2RR(double t);
	//saca un usario de la cola2 (FCFS)
	double sacarUsrCola2FCFS(double t);
	//saca un usario de la cola2 (RR)
	double sacarUsrCola2RR(double t);
	//devuelve el tamaño de la cola [0 - vacios; 1 - cola1; 2 - cola2]
	int size(int id_cola);
	//dice si está vacía la cola [0 - vacios; 1 - cola1; 2 - cola2]
	bool empty(int id_cola);
	//devuelve los datos del usuario que menos pide de la zona de recursos de la cola2 (FCFS)
	Usuario buscaMenor();
	//devuelve los datos del próximo usuario en salir (FCFS)
	Usuario proximoSalirFCFS();
	//devuelve los datos del próximo usuario en salir (RR)
	Usuario proximoSalirRR();
	//asigna el tiempo de la entrada del usuario en la zona de recursos
	void meterUsrRecursos(double t);
	//descuenta el tiempo ya procesado por los recursos a todos los usuario de la cola2
	void reiniciarTiempoProcesado(double t);
	//la función devuelve 0 cuando el valor de "val" es muy pequeño
	double funCero(double val);
	
	//----------------------------------------------------	
	
	//hace una monitorización general de todas las colas
	void monitorizarColas();
	//imprime valores de la cola 'vacios'
	void imprimirVacios();
	//imprime valores de la cola1
	void imprimirCola1();
	//imprime valores de la cola2
	void imprimirCola2();
	//añade un nodo a la lista de nodos vacios
	void llenarVacios();
	//devuelve el usuario al que apunta el lim_recursos
	Usuario usrlimiteRecursos();

};
#endif
