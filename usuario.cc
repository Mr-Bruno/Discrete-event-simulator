
#include "usuario.hh"

void Usuario::setTin(double v){
	t_in = v;
}

void Usuario::setTinRecursos(double v){
	t_in_recursos = v;
}

void Usuario::setS(double v){
	s = v;
}

double Usuario::getTin(){
	return(t_in);
}

double Usuario::getTinRecursos(){
	return(t_in_recursos);
}

double Usuario::getS(){
	return(s);
}