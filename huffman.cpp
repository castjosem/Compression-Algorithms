#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>
#include <string.h>
#include <sstream>
#include <time.h>
#include <iomanip>
#include <cmath>
using namespace std;

struct Caracter
{
    unsigned char c;
    int frecuencia;
    Caracter *izquierdo;
    Caracter *derecho;
};
vector<Caracter> car (256);
float frecuenciaTotal;

bool compare(Caracter c1, Caracter c2){	return (c1.frecuencia < c2.frecuencia);	}

void leer()
{	
	FILE *leer;	
    frecuenciaTotal = 0;
    int lectura;
    // Inicializando
    leer=fopen("input.in","rb");
	for(int i = 0; i < 256; i++)
    {
        car[i].c = i;
        car[i].frecuencia = 0;
    }	     
	//Leyendo   
	while(!feof(leer))
	{
        lectura = fgetc(leer);
        if(lectura!=-1)
        {
			car[lectura].frecuencia+=1;
            frecuenciaTotal++;
        }
	}
	fclose(leer);
}

void cachifa(Caracter *caracter, string cod,float *nc)
{
	if(caracter->izquierdo!= NULL && caracter->derecho!=NULL)
	{
		cachifa(caracter->izquierdo, cod + "0",*(&nc) );
		cachifa(caracter->derecho  , cod + "1",*(&nc));
	}
	else
	{	
        float aux;
        aux=caracter->frecuencia;
        *nc+=cod.size()*(aux/frecuenciaTotal);
	    cout << "Char:"<<caracter->c << "\tFrec:" << caracter->frecuencia << "\tCod: " << cod <<" \tNum: ";
		printf("%d\n",caracter->c);
	}
}

float bichar_codigos()
{
    float nc=0;		
	cachifa(car[car.size()-1].izquierdo, "0",&nc);
	cachifa(car[car.size()-1].derecho  , "1",&nc);
	
	return nc;
}

int buscar_posicion(int frecuencia, int pos)
{
	if(car[car.size()-1].frecuencia < frecuencia)
		return car.size();		
	for(int i = pos ; i<car.size() ; i++)
	{
		if(car[i].frecuencia>=frecuencia )
		{
			pos=i;
			break;
		}
	}	
	return pos;
}

int huffman(int i, int simbolos)
{
	int nueva_pos;
	for(int p= 0 ; p<simbolos-1 ; p++)
	{
		Caracter padre;	
		padre.frecuencia = car[i].frecuencia + car[i+1].frecuencia;
		
		padre.izquierdo = (struct Caracter * )malloc(sizeof (Caracter));
		padre.izquierdo->c =car[i].c;
		padre.izquierdo->frecuencia =car[i].frecuencia ;
		padre.izquierdo->izquierdo =car[i].izquierdo ;
		padre.izquierdo->derecho =car[i].derecho ;
		
		padre.derecho = (struct Caracter * )malloc(sizeof (Caracter));
		padre.derecho->c =car[i+1].c;
		padre.derecho->frecuencia =car[i+1].frecuencia ;
		padre.derecho->izquierdo =car[i+1].izquierdo ;
		padre.derecho->derecho =car[i+1].derecho ;		
		
		car.erase (car.begin()+i, car.begin()+(i+2));
		nueva_pos = buscar_posicion(padre.frecuencia,i);
		car.insert(car.begin()+nueva_pos, padre);		
	}
}

int main()
{
	clock_t start, ends;	
    int frecuencia_total, simbolos;
    float tc,to,rc;
    start = clock();
    leer();
            
    // ***********  Huffman **********************
    sort(car.begin(),car.end(),compare);  
    
	for(simbolos = 0 ; simbolos<256; simbolos++)
        if(car[simbolos].frecuencia)
            break;
        
    cout << "Simbolos: " << car.size()-simbolos << endl;
        
    huffman(simbolos, car.size()-simbolos);	
    tc = bichar_codigos();
    
    to=log2((256-simbolos));
    
    rc = ((to-tc)/to)*100;
    printf("\n\nRC = %f\n",rc);
    //********************************************
    
    ends = clock();
    
   	cout << endl << "Running Time : "  << (double) (ends - start) / (double)CLOCKS_PER_SEC << endl; 
   	
	system("pause");
    return 0;
}
