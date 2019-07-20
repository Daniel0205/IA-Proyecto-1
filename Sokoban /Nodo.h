#ifndef NODO_H
#define NODO_H
#include <string>
#include <vector>

using namespace std;

class Nodo{
    private:
        Nodo * padre = NULL ;
        int * posicionJugador = new int[2];
        int ** posBoxes;
        int deep;
        char accion = 0;
        bool esHoja; 
    public:
        Nodo(int * posicionJugadorIn,int ** cajasInitIn, int profundidadIn);
        Nodo(int * posicionJugadorIn,int ** cajasInitIn, int profundidadIn,char accionIn,Nodo *padreIn);
        ~Nodo();
        int getPosPlayer(int i);
        int getPosBoxes(int f, int c);
        int getProf();
        

};

#endif