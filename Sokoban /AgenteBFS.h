#ifndef AGENTEBFS_H
#define AGENTEBFS_H
#include <string>
#include <vector>
#include <queue>
#include "Nodo.h"

#include <iostream>

using namespace std;

class AgenteBFS{
    private:
        vector <string> table;
        queue <Nodo *> nodes;
        vector <Nodo *> explored;
        int numBoxes;
        int **targets;


    public:
        AgenteBFS(int numBoxesIn, int* pos, int ** cajasInit,vector <string> * table);
        ~AgenteBFS();
        void identifyTargets();
        bool searchBox(int posF, int posC, Nodo * node);
        bool expand(Nodo * node ,char move);
        int** moveBox(Nodo * node,int * pos,char accion);
        bool checkObstacle(int posF,int posC,Nodo * node);
        bool isSolve();
        void expandNode();
        bool checkExplored(int* pos, int ** boxes);
        bool checkExploredBoxes(Nodo * node, int ** boxes);

        string iniciarBusqueda();
       

};

#endif