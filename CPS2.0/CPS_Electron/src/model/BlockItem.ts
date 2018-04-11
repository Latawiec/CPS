
import { Operation } from './OperationsEnum'

export class BlockItem {
    public readonly operation: Operation;
    public readonly args: any[];
    public readonly inputs: BlockItem[] = [];
    public readonly outputs: BlockItem[] = [];
    public readonly type: Type;
    
    protected inputsLimit: number = -1;
    protected outputsLimit: number = -1;

    constructor(operation: Operation, type: Type, ...args: any[]){
        this.operation = operation;
        this.type = type;
        this.args = args || [];
    }

    public InputCount(): number {
        if(this.type === Type.Output){
            return 0;
        }

        return this.inputs.length;
    }
    
    public AddInput(block: BlockItem) {
        if(this.type === Type.Output){
            throw new TypeError("This operation does not accept inputs.");
        }
        if(this.InputCount() == this.inputsLimit) {
            throw new TypeError(`Inputs count overflow. This object only accepts ${this.inputsLimit} inputs`);
        }

        this.inputs.push(block);
    }
    
    public RemoveInput(block: BlockItem) {
        if(this.type === Type.Output){
            throw new TypeError("This operation does not accept inputs.");
        }

        const found: number = this.inputs.indexOf(block);
        if(found !== -1){
            this.inputs.splice(found, 1);
        }
    }
    
    public OutputCount(): number {
        if(this.type === Type.Input){
            return 0;
        }

        return this.outputs.length;
    }

    public AddOutput(block: BlockItem) {
        if(this.type === Type.Input){
            throw new TypeError("This operation does not accept outputs.");
        }
        if(this.OutputCount() == this.inputsLimit) {
            throw new TypeError(`Outputs count overflow. This object only accepts ${this.outputsLimit} outputs`);
        }

        this.outputs.push(block);
    }

    public RemoveOutput(block: BlockItem) {
        if(this.type === Type.Input){
            throw new TypeError("This operation does not accept outputs.");
        }

        const found: number = this.outputs.indexOf(block);
        if(found !== -1){
            this.outputs.splice(found, 1);
        }
    }

}

export enum Type{
    //Use as flags 
    // 0 1 Input
    // 1 0 Output
    Input       = 1,
    Output      = 2,
    InputOutput = 3
}
