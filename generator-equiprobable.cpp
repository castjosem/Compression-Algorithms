#include <iostream>
#include <fstream>
#include<vector>
#include <conio.h>
#include <time.h>

using namespace std;

ofstream out("input1.ini");

bool contains( vector<char> v, char c );
void print( vector<char> v);

int main()
{
	int tam;
	cout << "Tamanio del archivo en KB: ";
	cin >> tam;
	
	cout << "\n\nGenerando el archivo...";
	srand (time(NULL)); 
	
	tam *= 1024;	
	
	int n = (rand()%255);
	int freq;
	int aux = n;
	if (tam%aux == 0)
       freq = tam/aux;
    else {
         while ( aux>0 && (tam%aux != 0) ){
               aux--;
         }
         if (aux == 0){
            aux = n;
            while ( aux<256 && (tam%aux != 0) ){
               aux++;
            }  
         }
         freq = tam/aux;
    }
	 
	char c;
	vector<char> v, txt;
	
	for (int i=0 ; i<n ; i++) {
	    c = (char) (rand()%255);
	    if ( contains(v, c) == false )
           v.push_back(c);
        else{
             while ( contains(v, c) == true){
                 c = (char) (rand()%255);  
             }
             v.push_back(c);
        }
	}
	for (int i=0 ; i<v.size() ; i++)
        for (int j=0 ; j<freq ; j++)
            out << v.at(i);
    
    cout << "\n\nEl archivo se ha generado con exito.";
	getch();
}

bool contains (vector<char> v, char c){
     for (int i=0; i<v.size(); i++){
         if ( v.at(i) == c )
            return true;
     }
     return false;
}


/*void print (vector<char> v){
     for (int i=0; i<v.size(); i++){
         cout << "  ";
         cout << v.at(i);
     }
}*/

