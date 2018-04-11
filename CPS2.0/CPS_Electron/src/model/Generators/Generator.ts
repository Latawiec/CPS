
import { BlockItem, Type } from '../blockItem'
import { Sampler } from './Sampler'
import { Operation } from '../OperationsEnum';

export class Generator extends BlockItem {
    public readonly sampler: Sampler;

    constructor(operation: Operation, sampler: Sampler, ...args: any[] ) {
        super(operation, Type.Output, sampler, ...args);
    }
}