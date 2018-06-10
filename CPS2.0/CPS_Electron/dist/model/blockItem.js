"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var BlockItem = /** @class */ (function () {
    function BlockItem(operation, type) {
        var args = [];
        for (var _i = 2; _i < arguments.length; _i++) {
            args[_i - 2] = arguments[_i];
        }
        this.inputs = [];
        this.outputs = [];
        this.inputsLimit = -1;
        this.outputsLimit = -1;
        this.operation = operation;
        this.type = type;
        this.args = args || [];
    }
    BlockItem.prototype.InputCount = function () {
        if (this.type === Type.Output) {
            return 0;
        }
        return this.inputs.length;
    };
    BlockItem.prototype.AddInput = function (block) {
        if (this.type === Type.Output) {
            throw new TypeError("This operation does not accept inputs.");
        }
        if (this.InputCount() == this.inputsLimit) {
            throw new TypeError("Inputs count overflow. This object only accepts " + this.inputsLimit + " inputs");
        }
        this.inputs.push(block);
    };
    BlockItem.prototype.RemoveInput = function (block) {
        if (this.type === Type.Output) {
            throw new TypeError("This operation does not accept inputs.");
        }
        var found = this.inputs.indexOf(block);
        if (found !== -1) {
            this.inputs.splice(found, 1);
        }
    };
    BlockItem.prototype.OutputCount = function () {
        if (this.type === Type.Input) {
            return 0;
        }
        return this.outputs.length;
    };
    BlockItem.prototype.AddOutput = function (block) {
        if (this.type === Type.Input) {
            throw new TypeError("This operation does not accept outputs.");
        }
        if (this.OutputCount() == this.inputsLimit) {
            throw new TypeError("Outputs count overflow. This object only accepts " + this.outputsLimit + " outputs");
        }
        this.outputs.push(block);
    };
    BlockItem.prototype.RemoveOutput = function (block) {
        if (this.type === Type.Input) {
            throw new TypeError("This operation does not accept outputs.");
        }
        var found = this.outputs.indexOf(block);
        if (found !== -1) {
            this.outputs.splice(found, 1);
        }
    };
    return BlockItem;
}());
exports.BlockItem = BlockItem;
var Type;
(function (Type) {
    //Use as flags 
    // 0 1 Input
    // 1 0 Output
    Type[Type["Input"] = 1] = "Input";
    Type[Type["Output"] = 2] = "Output";
    Type[Type["InputOutput"] = 3] = "InputOutput";
})(Type = exports.Type || (exports.Type = {}));
//# sourceMappingURL=blockItem.js.map