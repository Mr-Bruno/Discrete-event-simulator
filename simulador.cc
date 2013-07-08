
#include "simulador.hh"
#include <limits>
#include <algorithm>

Simulador::Simulador(int n_recursos, double a, double b, bool tipo_cola){
	for(int i=0;i<3;i++){
	  t_event[i] =  numeric_limits<double>::max();
	}
	t_cola2 = 0;
   	alpha = a;
   	beta = b;	
	disciplina = tipo_cola;
	k = n_recursos;
   	c = new Colas(n_recursos);
}

double Simulador::eventoSalida(double t){
	double t_estancia;
	//Se saca al usuario de la cola2
	if (disciplina == RR){
		t_estancia = c->sacarUsrCola2RR(t);
	}else{
		t_estancia = c->sacarUsrCola2FCFS(t);
	}
	//Se calcula el próximo cambio de cola [t1]
	if (!c->empty(1)){
		if (c->size(2) < k){
			t_event[1] = t;
		}
	}
	//Se calcula la próxima salida [t2]
	if (c->empty(2)){
		t_event[2] = numeric_limits<double>::max(); //no puede tener lugar
	}else{
		t_event[2] = calcularProximaSalida(t,disciplina);
	}
	return(t_estancia);
}

void Simulador::eventoCambio(double t){
	//Se fija el valor de t_cola2
	if (c->empty(2)){
		usr = c->proximoSalirCola1();
		t_cola2 = t + (alpha/beta) * (usr.getTin() - t);
	}
	//Se pasa al usuario de la cola1 a la cola2
	if (disciplina == RR){
		c->pasarUsrCola2RR(t);
	}else{
		c->pasarUsrCola2FCFS(t);
	}
	//Se calcula el próximo cambio de cola [t1]
	if (!c->empty(1)){
		if (c->size(2) < k){
			t_event[1] = t;
		}else{
			if (beta == 0){
				t_event[1] = t;
 			}else{
				t_event[1] = calcularProximoCambio();
			}
		}
	}else{
		t_event[1] = numeric_limits<double>::max(); //no puede tener lugar
	}
	//Se calcula la próxima salida [t2]
	t_event[2] = calcularProximaSalida(t,disciplina);
}

void Simulador::eventoEntrada(double t, double s, double x){
	//Se mete un usuario nuevo en la cola1
	c->meterUsrCola1(t,s);
	//Se calcula el próximo cambio de cola [t1]
	if (c->size(2) < k){
		t_event[1] = t;
	}else{
		if (beta == 0){
			t_event[1] = t;
 		}else{
			t_event[1] = calcularProximoCambio();
		}		
	}
	//Se calcula la próxima llegada [t0]
	t_event[0] = t + x;
}

int Simulador::proximoEvento(){
	return(min_element(t_event,t_event+3) - t_event);
}

double Simulador::asignarTiempo(int ind_evento){
	return(t_event[ind_evento]);
}

void Simulador::inicializarEventoEntrada(double x){
	t_event[0] = x;
}

//----------------------------------------------------

void Simulador::monitorizarTiempos(double t){
	static int turno = 1;
	
	double aux = turno;
	int digits = 0;
	do{
		aux /= 10;
		digits++;
	}while(aux >= 1);
	cout << "|" << turno++ << "º|";
	for (int i=0;i<30-digits;i++){
		cout << "¬";
	}
	cout << endl;
	cout << "t:      |" << t << "|\n";
	cout << "t0:     |";
	imprimirTemporizador(0);
	cout << "|\n";
	cout << "t1:     |";
	imprimirTemporizador(1);
	cout << "|\n";
	cout << "t2:     |";
	imprimirTemporizador(2);
	cout << "|\n";
	cout << "tcola2: |" << t_cola2 << "|\n";
	cout << "¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬\n";   
}

void Simulador::monitorizarColas(){
	c->monitorizarColas();
}

double Simulador::calcularProximaSalida(double t, bool disciplina){
	if (disciplina == RR){
		//mira el usuario marcado como próximo y calcula
		usr = c->proximoSalirRR();
		return(t + (usr.getS() * ((double) c->size(2))/min(k,c->size(2))));
	}else{ //FCFS
		//mira el usuario marcado como próximo y calcula
		usr = c->proximoSalirFCFS();
		return(usr.getTinRecursos() + usr.getS());
	}
}

double Simulador::calcularProximoCambio(){
	usr = c->proximoSalirCola1();
	double t_fin = t_cola2 + (usr.getTin() - t_cola2) * (alpha/(alpha - beta));
	return(t_fin);
}

void Simulador::imprimirTemporizador(int ind_evento){
	if (t_event[ind_evento] == numeric_limits<double>::max()){
		cout << "None";
	}else{
		cout << t_event[ind_evento];
	}

}
