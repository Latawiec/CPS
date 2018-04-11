import { BlockItem, Type } from '../BlockItem'
import { Operation } from '../operationsEnum';

export class Sum extends BlockItem {
    constructor(){
        super(Operation.Sum, Type.InputOutput);
    }
}