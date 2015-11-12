#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include<iostream>
#include<climits>
#include <algorithm>
#include<cmath>
#include <string>
using namespace std;

struct caracter
{
    char c;
    int frecuencia;
    string codigo;
};
vector<caracter> car (256);

bool compare(caracter c1, caracter c2){	return (c1.frecuencia > c2.frecuencia);	}

int leer()
{	
	FILE *leer;	
    int frecuencia_total = 0,lectura;
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
            frecuencia_total++;
        }
	}
	fclose(leer);
    return frecuencia_total;
}

int shannon_fannon(int index_i, int index_j)
{
    if(index_i!= index_j)
    {
        if(index_j - index_i == 1)
        {
            car[index_i].codigo.append("0");
            car[index_j].codigo.append("1");
        }

        else
        {
            int totalFrecuencia = 0;
            int cont = 0, dif, aux, corte = -1;

            for(int i = index_i; i <= index_j; i++)
                totalFrecuencia += car[i].frecuencia;

            aux = INT_MAX;
            for(int i = index_i; i <= index_j ; i++)
            {
                cont += car[i].frecuencia;
                dif = totalFrecuencia - cont;
                if( abs(dif-cont) < aux )
                {
                    aux = abs(cont - dif);
                    car[i].codigo.append("0");
                }
                else
                {
                    if(corte==-1) corte = i;
                    car[i].codigo.append("1");
                }
            }
            shannon_fannon(index_i,corte-1);
            shannon_fannon(corte,index_j);
        }
    }
}

int main()
{
	clock_t start, ends;	
    int frecuencia_total, simbolos;
    
    start = clock();
    frecuencia_total = leer();
        
    // ***********  Shannon Fanon **********************
    
    sort(car.begin(),car.end(),compare);    
	for(simbolos = 0 ; simbolos < car.size() ; simbolos++)
    {
        if(car[simbolos].frecuencia==0)
        {
            break;
        }
    }
    shannon_fannon(0,simbolos-1);
    
    //***************************************************
    
    
    //Imprimiendo resultados    
    float rc,nc=0,no,aux,aux2;
    for(int i = 0; i < simbolos ; i++)
    {
		cout << "Char:"<< car[i].c << "\tFrec:" << car[i].frecuencia << "\tCod: " << car[i].codigo <<" \tNum: ";
		printf("%d\n",car[i].c);
        aux=car[i].frecuencia;
        aux2=frecuencia_total;
		nc+=car[i].codigo.size()*(aux/aux2);
    }
    
    no=log2(simbolos);
    rc=((no-nc)/no)*100;
    
    printf("\n\nRC = %f\n",rc);
    ends = clock();
    
   	cout << endl << "Running Time : "  << (double) (ends - start) / (double)CLOCKS_PER_SEC << endl; 
    
	system("pause");
    return 0;
}
