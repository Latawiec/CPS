"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var OperationNode = /** @class */ (function () {
    function OperationNode(operation, id, args, dataCallback) {
        this.args = {};
        this.previous = [];
        this.next = [];
        this.operation = operation;
        this.id = id;
        this.dataCallback = dataCallback;
    }
    OperationNode.prototype.AddPrevious = function (node) {
        this.previous.push(node);
    };
    OperationNode.prototype.AddNext = function (node) {
        this.next.push(node);
    };
    return OperationNode;
}());
//# sourceMappingURL=OperationNode.js.map