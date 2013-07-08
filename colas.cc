
#include "colas.hh"
#include <cstdlib>

Colas::Colas(int n_recursos){
	k = n_recursos;
	ind_usr = cola2.end();
	lim_recursos = cola2.end();
	t_ref = 0;
}

void Colas::setTRef(double v){
	t_ref = v;
}

double Colas::getTRef(){
	return(t_ref);	
}

void Colas::meterUsrCola1(double t_in, double s){
	//introduzco nodo
	if (empty(0)){
		Usuario usr;
		cola1.push_back(usr);
	}else{
		cola1.splice(cola1.end(),vacios,vacios.begin());
	}
	//introduzco valores
	cola1.back().setTin(t_in);
	cola1.back().setTinRecursos(0);
	cola1.back().setS(s);
}

Usuario Colas::proximoSalirCola1(){
	if (!empty(1)){
		return(cola1.front());
	}else{
      	cout << "ERROR: LA COLA1 ESTÁ VACÍA" << endl;
      	exit(-1);
	}
}

void Colas::pasarUsrCola2FCFS(double t){
	if (empty(1)){
      	cout << "ERROR: LA COLA1 ESTÁ VACÍA" << endl;
      	exit(-1);		
	}
	if (empty(2)){
		cola1.front().setTinRecursos(t); 
		ind_usr = cola1.begin();
	}else{
		if (size(2) < k){ //se marca el proximo en salir
			cola1.front().setTinRecursos(t);
			double min = (*ind_usr).getTinRecursos() + (*ind_usr).getS();
			if (min > (cola1.front().getTinRecursos() + cola1.front().getS())){
				ind_usr = cola1.begin();
			}
		}else{ 
			if (size(2) == k){ //los recursos estan todos ocupados
				lim_recursos = cola1.begin();
			}
		}
	}
	cola2.splice(cola2.end(),cola1,cola1.begin());
}

void Colas::pasarUsrCola2RR(double t){
	if (empty(1)){
      	cout << "ERROR: LA COLA1 ESTÁ VACÍA" << endl;
      	exit(-1);		
	}
	if (empty(2)){
		cola2.splice(cola2.begin(),cola1,cola1.begin());
	}else{
		reiniciarTiempoProcesado(t);
		ref = cola1.begin();
		//introduzco de menor a mayor servicio demandado (orden de salida)
		if (cola2.back().getS()<(*ref).getS()){
			cola2.splice(cola2.end(),cola1,cola1.begin());
		}else{
			it=cola2.begin();	
			while(it!=cola2.end()){
				if ((*it).getS()>(*ref).getS()) break;	
				it++;
			}
			cola2.splice(it,cola1,cola1.begin());
		}
	}
	setTRef(t);
}

double Colas::sacarUsrCola2FCFS(double t){
	if (empty(2)){
      	cout << "ERROR: LA COLA2 ESTÁ VACÍA" << endl;
      	exit(-1);		
	}
	vacios.splice(vacios.end(),cola2,ind_usr);
	if (size(2) > (k-1)){ //si nos quedamos con menos usuarios que recursos
		meterUsrRecursos(t);
	}
	if (!empty(2)){
		buscaMenor();
	}else{
		ind_usr = cola2.end();	
	}
	return(t - vacios.back().getTin());
}

double Colas::sacarUsrCola2RR(double t){
	if (empty(2)){
      	cout << "ERROR: LA COLA1 ESTÁ VACÍA" << endl;
      	exit(-1);		
	}
	
	reiniciarTiempoProcesado(t);
	setTRef(t);
		
	vacios.splice(vacios.end(),cola2,cola2.begin());
	return(t - vacios.back().getTin());
}

int Colas::size(int id_cola){
	switch(id_cola){
	case 0:
	  return(vacios.size());
	  break;
	case 1:
	  return(cola1.size());  
	  break;
	case 2:
	  return(cola2.size());
	  break;
	default:
      cout << "ERROR: EL 'id' DE LA COLA NO EXISTE" << endl;
      exit(-1);
	};
}

bool Colas::empty(int id_cola){
	switch(id_cola){
	case 0:
	  return(vacios.empty());
	  break;
	case 1:
	  return(cola1.empty());	  
	  break;
	case 2:
	  return(cola2.empty());
	  break;
	default:
      cout << "ERROR: EL 'id' DE LA COLA NO EXISTE" << endl;
      exit(-1);
	};
}

Usuario Colas::buscaMenor(){
	double min = 0;

	if (!empty(2)){
		it=cola2.begin();
		ind_usr = it++; //postincremento
		min = (*ind_usr).getTinRecursos() + (*ind_usr).getS();
		//Comprueba todos los "servicios demandados" y se queda con el menor
		while(it!=lim_recursos){
			if (min > ((*it).getTinRecursos() + (*it).getS())){
				min = (*it).getTinRecursos() + (*it).getS();
				ind_usr = it;
			}
			it++;
		}
		return(*ind_usr);
	}else{
		cout << "ERROR: LA COLA2 ESTÁ VACÍA\n"; 
		exit(-1);
	}
	return(cola2.front());
}

Usuario Colas::proximoSalirFCFS(){
	if (!empty(2)){
		return(*ind_usr);
	}else{
      	cout << "ERROR: LA COLA2 ESTÁ VACÍA" << endl;
      	exit(-1);
	}
}

Usuario Colas::proximoSalirRR(){
	if (!empty(2)){
		return(cola2.front());
	}else{
      	cout << "ERROR: LA COLA2 ESTÁ VACÍA" << endl;
      	exit(-1);
	}
}

void Colas::meterUsrRecursos(double t){
	if (lim_recursos != cola2.end()){
	  	(*lim_recursos).setTinRecursos(t);
  		lim_recursos++;
  	}else{
      	cout << "ERROR: NO HAY USUARIOS PENDIENTES DE ENTRAR EN RECURSOS" << endl;
      	exit(-1);  	  	
  	}
}

void Colas::reiniciarTiempoProcesado(double t){
	if (empty(2)){
      	cout << "ERROR: LA COLA2 ESTÁ VACÍA" << endl;
      	exit(-1);	
	}else{
		double t_procesado = (t-getTRef())*((double) min(k,size(2))/size(2));
		for (it=cola2.begin(); it!=cola2.end(); it++){
			(*it).setS(funCero((*it).getS() - t_procesado)); //redondeamos el valor de la resta
		}
	}
}

double Colas::funCero(double val){
	if (val < 0.000000001){
		return 0;
	}else{
		return val;
	}
}

//----------------------------------------------------

void Colas::monitorizarColas(){
	static int turno = 1;
	
	double aux = turno;
	int digits = 0;
	do{
		aux /= 10;
		digits++;
	}while(aux >= 1);
	cout << "|" << turno++ << "º|";
	for (int i=0;i<30-digits;i++){
		cout << "%";
	}	
	cout << endl;
	imprimirVacios();
	imprimirCola1();
	imprimirCola2();
	cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";  
}

void Colas::imprimirVacios(){
  if (!empty(0)){
    cout << "CONTENIDO DE LA COLA VACÍOS:";
    cout << "\ntin:  |";
    for (it=vacios.begin(); it!=vacios.end(); it++)
      cout << setprecision(PRECISION) << (*it).getTin() << "|";
    cout << "\ntinr: |";
    for (it=vacios.begin(); it!=vacios.end(); it++)
      cout << setprecision(PRECISION) << (*it).getTinRecursos() << "|";
    cout << "\ns:    |";
    for (it=vacios.begin(); it!=vacios.end(); it++)
      cout << setprecision(PRECISION) << (*it).getS() << "|";
    cout << endl;
  }else{
    cout << "---LA COLA V ESTÁ VACÍA---\n";  
  }
}

void Colas::imprimirCola1(){
  if (!empty(1)){
    cout << "CONTENIDO DE LA COLA 1:";
    cout << "\ntin:  |";
    for (it=cola1.begin(); it!=cola1.end(); it++)
      cout << /*setprecision(PRECISION) <<*/ (*it).getTin() << "|";

    cout << "\ntinr: |";
    for (it=cola1.begin(); it!=cola1.end(); it++)
      cout << /*setprecision(PRECISION) <<*/ (*it).getTinRecursos() << "|";
    cout << "\ns:    |";
    for (it=cola1.begin(); it!=cola1.end(); it++)
      cout << /*setprecision(PRECISION) <<*/ (*it).getS() << "|";
    cout << endl;
  }else{
    cout << "---LA COLA 1 ESTÁ VACÍA---\n";  
  }
}

void Colas::imprimirCola2(){	
  if (!empty(2)){
    cout << "CONTENIDO DE LA COLA 2:";
    cout << "\ntin:  |";
    for (it=cola2.begin(); it!=cola2.end(); it++)
      cout << /*setprecision(PRECISION) <<*/ (*it).getTin() << "|";
    cout << "\ntinr: |";
    for (it=cola2.begin(); it!=cola2.end(); it++)
      cout << /*setprecision(PRECISION) <<*/ (*it).getTinRecursos() << "|";
    cout << "\ns:    |";
    for (it=cola2.begin(); it!=cola2.end(); it++)
      cout << /*setprecision(PRECISION) <<*/ (*it).getS() << "|";
    cout << endl;
  }else{
    cout << "---LA COLA 2 ESTÁ VACÍA---\n";  
  }
}

void Colas::llenarVacios(){
	Usuario usr;
	vacios.push_back(usr);
	vacios.back().setTin(0);
	vacios.back().setTinRecursos(0);
	vacios.back().setS(0);
}

Usuario Colas::usrlimiteRecursos(){
	if (lim_recursos == cola2.end()){
		cout << "Usuario límite: No hay usuarios pendientes de entrar en recursos\n";
	}else{
	cout << "Usuario límite: [tin: " << (*lim_recursos).getTin()
		 << "] [tinr: " << (*lim_recursos).getTinRecursos()
	 	 << "] [s: " << (*lim_recursos).getS() << "]\n";
	}
	return(*lim_recursos);
}
