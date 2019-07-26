


export default class Node{
    constructor(father,state,type,depth){
        this.father=father;
        this.state=state;
        this.type=type;
        this.depth=depth;
        this.utility=Infinity;
        
        
    }

    getDepth(){
        return this.depth;
    }

    getType(){
        return this.type;
    }

    setUtility(value){
        if(this.type=="Min")this.utility=Math.min(value,this.utility);
        else this.utility=Math.max(value,this.utility)
    }

    informFather(){
        this.father.setUtility(this.utility);
    }

    calculateHeuristic(){
        this.utility=10;
    }







}