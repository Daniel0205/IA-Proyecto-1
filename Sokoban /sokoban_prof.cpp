#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>


using namespace std;




int main(int argc, char **argv){
	
	ifstream tablero("nivel1.txt");
	
	vector<string> datos;
	int endTable=0;
	string texto;
	
	while(!tablero.eof()){
		tablero >> texto;
		if(texto[0]!='W' && texto[0]!='0' && texto[0]!='X' && endTable==0){
			endTable=datos.size();
			
		}		
		datos.push_back(texto);
		
	}
	tablero.close();
	
	for (int i = 0; i <endTable; i++){
		
		cout << datos[i] << endl;
	}
	
	
	
}




