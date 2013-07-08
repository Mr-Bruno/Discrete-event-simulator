
#include <math.h>
#include "varaleat.hh"

//----------------------------------------------------------------------
// Implementación de la clase Aleatorio
//----------------------------------------------------------------------



Aleatorio::Aleatorio(long sem)
{
  //cout<<"Llamada a constructor Aleatorio con semilla "<<sem<<endl;
  z = time(NULL);
}

void Aleatorio::semilla(long sem)
{
  //cout<<"Llamada a metodo Aleatorio::semilla con argumento "<<sem<<endl;
  z = sem;
}

long Aleatorio::max(void)
{
  //cout<<"Llamada a Aleatorio::max"<<endl;
  return(m);
}

long Aleatorio::sig(void)
{
  //cout<<"Llamada a Aleatorio::sig"<<endl;
  
  //-----------------------------------------
  z = a*(z % q) - r*(z / q);
  if (z < 0){
    z = z + m;
  }
  //cout<<"resultado: "<<z<<endl;
  return(z);
}

  Aleatorio VarAleat::gen;

//----------------------------------------------------------------------
// Implementación de la clase VarAleat
//----------------------------------------------------------------------


  VarAleat::VarAleat(const char *tipo_va)
{
  //cout<<"Llamada a constructor VarAleat con parametro "<<tipo_va<<endl;
  stringstream stream;
  stream.str(tipo_va);
  stream >> *this;
}

 double VarAleat::operator++()
 {
   //cout<<"Llamada a VarAleat operador ++"<<endl;
   switch(tipo){
   case 'D':
     return(media);
     break;
   case 'U':
     return ( min + ((max-min) * ((double)gen.sig() / (double)gen.max())) );
     break;
   case 'E':
     return ((- media) * log((double)gen.sig() / (double)gen.max()) );
     break;
   case 'N':
     double suma;
     //-------
     suma = 0;
     for (int i=0;i<12;i++){
       suma += (double)gen.sig() / (double)gen.max();
     }
     return (media + desv * (suma - 6));
     break;
   case 'H':
     int ind;
     double valor;
     //-------
     ind = 0;
     valor = (double)gen.sig() / (double)gen.max();
     while (valor>peso[ind]){
       ind++;
     }
     return ((- vmedio[ind]) * log((double)gen.sig() / (double)gen.max()) );
     break;
   default:
     return -1;
     break;
   }
 }


 istream& operator>>(istream& in, VarAleat &v)
 {
   char dist;
   //-variables auxiliares de la exponencial
   vector<double> med;
   vector<double> pes;
   double valor;
   int ind;
   double acumul;
   double media,peso;
   int max_size;
   int i,j;

   in>>dist;
   v.tipo = toupper(dist);
   switch(v.tipo){
   case 'D':
     //Determinista
     in>>v.media;
     break;
   case 'U':
     //Uniforme
     in>>v.min>>v.max;
     break;
   case 'E':
     //Exponencial
     in>>v.media;
     break;
   case 'N':
     //Normal
     in>>v.media;
     in>>v.desv;
     break;
   case 'H':
     //Hiperexponencial
     
     //CAPTURAMOS VALORES
     in>>v.n_exp;
     for(i=0;i<v.n_exp;i++){
       in>>media>>peso;
       med.push_back(media);
       pes.push_back(peso);
     }
     //ORDENAMOS LOS VALORES DE ENTRADA
     acumul = 0;
     for (j=0;j<v.n_exp;j++){//---REPITELO TANTAS VECES COMO EXPONENCIALES TENGAS
       valor = 0;
       ind = 0;
       if (pes.size()>0){ //---CALCULA EL TAMAÑO ACTUAL DEL VECTOR AUXILIAR
	 max_size= pes.size();
       }else{
	 max_size = 0;
       }
       for(i=0;i<max_size;i++){  //---RECUPERA EL INDICE Y EL PESO DEL MAS PESADO ACTUAL
	 if (valor<pes[i]){
	   valor = pes[i];
	   ind = i;
	 }
       }
       acumul += pes[ind];   //---AÑADE AL VECTOR FINAL LOS PESOS Y MEDIAS ORDENADOS
       v.vmedio.push_back(med[ind]);
       v.peso.push_back(acumul);
       med.erase(med.begin()+ind);
       pes.erase(pes.begin()+ind);
     }
     break;
   default:
     cout<<"Entrada de tipo erronea"<<endl;
     break;
   }   
   return in;
 }
