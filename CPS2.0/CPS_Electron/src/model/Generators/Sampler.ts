
export class Sampler {
    public readonly offset: number;
    public readonly interval: number;
    public readonly limit: number;
    
    constructor(offset: number, interval: number, limit: number){
        this.offset = offset;
        this.interval = interval;
        this.limit = limit;
    }
}