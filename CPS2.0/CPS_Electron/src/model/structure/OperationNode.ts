import { Operation } from "../OperationsEnum";

class OperationNode {
    public readonly operation: Operation;
    public readonly id: number;
    public readonly args: any = {};
    public readonly previous: OperationNode[] = [];
    public readonly next: OperationNode[] = [];
    public readonly dataCallback: (data?:any) => void;

    constructor(operation: Operation, id: number, args: any, dataCallback: (data?:any) => void){
        this.operation = operation;
        this.id = id;
        this.dataCallback = dataCallback;
    }

    public AddPrevious(node: OperationNode) {
        this.previous.push(node);
    }

    public AddNext(node: OperationNode) {
        this.next.push(node);
    }
}