"use strict";
var __extends = (this && this.__extends) || (function () {
    var extendStatics = Object.setPrototypeOf ||
        ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
        function (d, b) { for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p]; };
    return function (d, b) {
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
Object.defineProperty(exports, "__esModule", { value: true });
var BlockItem_1 = require("../BlockItem");
var operationsEnum_1 = require("../operationsEnum");
var Sum = /** @class */ (function (_super) {
    __extends(Sum, _super);
    function Sum() {
        return _super.call(this, operationsEnum_1.Operation.Sum, BlockItem_1.Type.InputOutput) || this;
    }
    return Sum;
}(BlockItem_1.BlockItem));
exports.Sum = Sum;
//# sourceMappingURL=Sum.js.map