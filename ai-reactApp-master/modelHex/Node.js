


export default class Node{
    constructor(father,state,type,depth,fila, columna){
        this.father=father;
        this.state=state;
        this.type=type;
        this.depth=depth;
        this.fila;
        this.columan;
        
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

    setUtility(value){
        console.log(this)
        if(this.type=="Min")this.utility=Math.min(value,this.utility);
        else this.utility=Math.max(value,this.utility)
        if(this.depth!=0)this.father.informFather();
    }

    informFather(){
    
        this.father.setUtility(this.utility);
    }

    calculateHeuristic(){
        this.utility=10;
    }
}