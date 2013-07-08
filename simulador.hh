
#ifndef SIMULADOR_HH
#define SIMULADOR_HH

#include "colas.hh"

#define RR true
#define FCFS false

using namespace std;

class Simulador{

   	double t_event[3];	//temporizadores de vencimiento de los eventos
   	double t_cola2;		//vejez de los usuarios de la cola2
   	double alpha;		//alpha
   	double beta;		//beta
	bool disciplina;	//disciplina de gestion de la cola2
   	int k;				//número de recursos
   	Colas* c;			//objeto colas (sin instanciar)
   	Usuario usr;		//objeto usuario genérico

public:

	//constructor de Simulador
	Simulador(int n_recursos, double a, double b, bool tipo_cola);
	//ejecución de evento de salida de usuario
	double eventoSalida(double t);
	//ejecución de evento de cambio de cola
	void eventoCambio(double t);
	//ejecución de evento de entrada de usuario
	void eventoEntrada(double t, double s, double x);
	//devuelve el índice del proximo evento [0 - evA; 1 - evB; 2 - evC]
	int proximoEvento();
	//devuelve el valor de "t" en el momento de cumplirse el evento
	double asignarTiempo(int ind_evento);
	//inicializa el sistema para que tenga lugar la primera llegada
	void inicializarEventoEntrada(double x);
	
	//----------------------------------------------------
	
	//hace una monitorización general de los temporizadores del sistema
	void monitorizarTiempos(double t);
	//hace una monitorización general de todas las colas
	void monitorizarColas();
	//devuelve el instante en el que tendrá lugar la próxima salida
	double calcularProximaSalida(double t, bool disciplina);
	//devuelve el instante en el que tendrá lugar el próximo cambio de cola
	double calcularProximoCambio();
	//imprime el valor del temporizador de evento ya formateado
	void imprimirTemporizador(int ind_evento);

};
#endif
