
import { Generator } from './Generator';
import { Sampler } from './Sampler';
import { Operation } from '../operationsEnum';

export class Sinus extends Generator {

    constructor(sampler: Sampler, period?: number, amplitude?: number, offset?: number){
        super(Operation.Sinus,
              sampler,
              period || 6.283185307179586,
              amplitude || 1,
              offset || 0);
    }

    //sampler
    get sampler(): Sampler {
        return this.args[0];
    }
    set sampler(value: Sampler) {
        this.args[0] = value;
    }

    //period
    get period(): number {
        return this.args[1];
    }
    set period(value: number) {
        this.args[1] = value;
    }

    //amplitude 
    get amplitude(): number {
        return this.args[2];
    }
    set amplitude(value: number) {
        this.args[2] = value;
    }

    //offset 
    get offset(): number {
        return this.args[3];
    }
    set offset(value: number) {
        this.args[3] = value;
    }
}