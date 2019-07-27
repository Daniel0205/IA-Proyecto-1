


export default class Node{
    constructor(father,state,type,depth,fila, columna){
        this.father=father;
        this.state=state;
        this.type=type;
        this.depth=depth;
        this.fila=fila;
        this.columna=columna;
        
        if(type=="Min")this.utility=Infinity;
        else this.utility=-Infinity;
        
    }


    getBoard(){
        return this.state;
    }

    getDepth(){
        return this.depth;
    }

    getType(){
        return this.type;
    }

    setUtility(value,row,column){
        
        if(this.type=="Min"){
            this.utility=Math.min(value,this.utility);
        }
        else {
            this.utility=Math.max(value,this.utility)
            
        }
        
        if(this.depth!=0){
            if(this.father==null)console.log(this.depth);
            this.informFather();
        }
        else if(this.utility==value ){
            this.fila=row;
            this.columna=column;
        }

    }

    setFC(fila,columna){
        this.fila=fila;
        this.columna=columna;
    }

    informFather(){
    
        this.father.setUtility(this.utility,this.fila,this.columna);
    }

    calculateHeuristic(){
        this.utility=10;
    }

    getUtility(){
        return this.utility;
    }

    getPos(){
        return [this.fila,this.columna];
    }
}