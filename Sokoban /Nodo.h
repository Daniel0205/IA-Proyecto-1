#ifndef NODO_H
#define NODO_H
#include <string>
#include <vector>

using namespace std;

class Nodo{
    private:
        int *posicionJugador = new int[2];
        int ** cajasInit;
        int **objetivos;
        bool esHoja; 
        vector<Nodo> children;
    public:
        Nodo();
        ~Nodo();

        bool getEsHoja();
        void setEsHoja(bool newValue);
};

#endif