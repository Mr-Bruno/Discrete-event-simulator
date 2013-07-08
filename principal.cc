
#include "simulador.hh"
#include "varaleat.hh"
#include "Promedio.hh"

#include <fstream>
#include <iostream>
#include <list>
#include <iomanip>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main (int argc, char *argv[]){
	
  ifstream f1;
  ofstream f2;
  double t_transitorio,alpha,beta,t,t_estancia,x_inicial;
  long semilla;
  float calidad,tolerancia;
  char disciplina[2],round[2]="R",fifo[2]="F";
  bool disciplina_bool;
  int k,ind_evento;
  VarAleat x,s;

  //fichero salida
  double estimacion,inferior,superior;
  float calidad_final;
  unsigned long numero_muestras;

	
  //Parametros de entrada por linea de comandos y fichero fich.cfg
  f1.open(argv[1], ifstream::in);
  semilla = strtol (argv[2],NULL,10);
  t_transitorio=atof(argv[3]);
  f1>>tolerancia;
  f1>>calidad;
  f1>>alpha;
  f1>>beta;
  f1>>disciplina;
  f1>>k;
  f1>>x;
  f1>>s;
  
  alpha = (alpha < beta)? beta : alpha;

  //Indicar tipo de disciplina e inicializar las variables restantes
  if (strcmp(disciplina,round)==0) {
    disciplina_bool=RR;
  }else if (strcmp(disciplina,fifo)==0){
    disciplina_bool=FCFS;
  }else {
    cout<<"DISCIPLINA INCORRECTA"<<endl;
    exit(-1);
  }

  Promedio prom(calidad,tolerancia);
  x.gen.semilla(semilla);
  Simulador sim(k,alpha,beta,disciplina_bool);
  
  //Inicializar la primera entrada en el simulador
  x_inicial=++x;
  sim.inicializarEventoEntrada(x_inicial);
  ind_evento=sim.proximoEvento();
  t=sim.asignarTiempo(ind_evento);
  sim.eventoEntrada(t,++s,x_inicial);


  //Cuando prom.num_promedios=0 requisitos alcanzados
  while(prom.numero_promedios()!=0){
    ind_evento=sim.proximoEvento();
    t=sim.asignarTiempo(ind_evento);
    switch(ind_evento){
    case 2:
      t_estancia=sim.eventoSalida(t);
      if (t>t_transitorio) {
	prom.computa(t_estancia);
      }
      break;
    case 1:
      sim.eventoCambio(t);
      break;
    case 0:
      sim.eventoEntrada(t,++s,++x);
      break;
    }
  }


  //Escribir resultados en el fichero de salida
  estimacion=prom.estimacion();
  calidad_final=prom.calidad();
  inferior = estimacion-estimacion*tolerancia; 
  superior = estimacion+estimacion*tolerancia; 
  numero_muestras=prom.num_muestras();
  f2.open("fich.out", ofstream::out);
  f2<<estimacion<<endl;
  f2<<"("<<inferior<<","<<superior<<")"<<endl;
  f2<<calidad_final<<endl;
  f2<<numero_muestras<<endl;
  f2.close();
	
  return 0;
}
