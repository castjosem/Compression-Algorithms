#include <iostream>
#include <fstream>
#include<vector>
using namespace std;

ofstream out("input2.in");

int main()
{
	int tam;
	cout << "Tamanio del archivo en KB: ";
	cin >> tam;
	srand (time(NULL)); 
	
	tam *= 1024;
	for(int i=0 ; i<tam ; i++)
	{
		out << (char)(rand()%256);
	}
	
	system("pause");
    return 0;
}
