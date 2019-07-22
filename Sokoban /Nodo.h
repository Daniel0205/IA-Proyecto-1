#ifndef NODO_H
#define NODO_H
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Nodo{
    private:
        int * posicionJugador = new int[2];
        int ** posBoxes;
        int deep;
        string path = "";
        bool esHoja; 
    public:
        Nodo(int * posicionJugadorIn,int ** cajasInitIn, int profundidadIn);
        Nodo(int * posicionJugadorIn,int ** cajasInitIn, int profundidadIn,string camino);
        ~Nodo();

        int getPosPlayer(int i);
        int getPosBoxes(int f, int c);
        int getProf();
        string getPath(); 
        void borrar();       

};

#endif