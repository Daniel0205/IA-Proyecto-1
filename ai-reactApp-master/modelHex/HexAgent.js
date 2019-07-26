const Agent = require('ai-agents').Agent;

import Node from "./Node"



class HexAgent extends Agent {
    constructor(value) {
        super(value);
        this.tree=[];
        this.size=0;
        this.board=[];
        
    }

    expandNode(type,father){
        
        for (let i = 0; i < this.size; i++) {
            let auxBoard=this.board.slice(0,this.size);
            for (let j = 0; j < this.size; j++) {
                if(this.board[i][j]==0){
                    auxBoard[i][j]==this.getID();
                    this.tree.unshift(new Node(father,auxBoard,type,father.getDepth()+1));
                    
                }
            }
        }
    }

    miniMax(){
        while(this.tree!=0){
            let actualNode=this.tree.shift();

            if(actualNode.getDepth()==9){
                console.log(this.tree)
                actualNode.calculateHeuristic();        
                actualNode.informFather();
            }
            else{
                if(actualNode.getType()=="Max")this.expandNode("Min",actualNode);
                else this.expandNode("Max",actualNode);
            }
                
        }
    }
    
    /**
     * return a new move. The move is an array of two integers, representing the
     * row and column number of the hex to play. If the given movement is not valid,
     * the Hex controller will perform a random valid movement for the player
     * Example: [1, 1]
     */
    send() {
        this.board = this.perception;
        this.size = this.board.length;

        this.tree.unshift(new Node(null,this.board,"Max",0));
        

        this.miniMax();

        let available = getEmptyHex(this.board);
        let nTurn = this.size * this.size - available.length;

        if (nTurn == 0) { // First move
            return [Math.floor(this.size / 2), Math.floor(this.size / 2) - 1];
        } else if (nTurn == 1){
            return [Math.floor(this.size / 2), Math.floor(this.size / 2)];
        }

        let move = available[Math.round(Math.random() * ( available.length -1 ))];
        return [Math.floor (move / this.board.length), move % this.board.length];
    }

}

module.exports = HexAgent;

/**
 * Return an array containing the id of the empty hex in the board
 * id = row * size + col;
 * @param {Matrix} board 
 */
function getEmptyHex(board) {
    let result = [];
    let size = board.length;
    for (let k = 0; k < size; k++) {
        for (let j = 0; j < size; j++) {
            if (board[k][j] === 0) {
                result.push(k * size + j);
            }
        }
    }
    return result;
}
