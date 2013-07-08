
#ifndef USUARIO_HH
#define USUARIO_HH

using namespace std;

class Usuario{

  double t_in;				//tiempo de entrada en el sistema
  double t_in_recursos;		//tiempo de entrada en el recurso
  double s;					//tiempo demandado al recurso

public:

	//asigna valor a la variable 't_in'
	void setTin(double v);
	//asigna valor a la variable 't_in_recursos'
	void setTinRecursos(double v);
	//asigna valor a la variable 's'
	void setS(double v);
	//recupera valor de la variable 't_in'
	double getTin();
	//recupera valor de la variable 't_in_recursos'
	double getTinRecursos();
	//recupera valor de la variable 's'
	double getS();

};
#endif
