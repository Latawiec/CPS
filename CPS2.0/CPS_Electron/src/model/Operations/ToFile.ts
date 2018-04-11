import { BlockItem, Type } from '../BlockItem'
import { Operation } from '../operationsEnum';

export class ToFile extends BlockItem {
    constructor(filepath: string){
        super(Operation.ToFile, Type.Input, filepath);
        this.inputsLimit = 1;
    }

    //filepath
    get filepath(): string {
        return this.args[0];
    }
    set filepath(value: string) {
        this.args[0] = value;
    }
}