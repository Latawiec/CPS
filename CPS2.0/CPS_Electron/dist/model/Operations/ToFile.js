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
var ToFile = /** @class */ (function (_super) {
    __extends(ToFile, _super);
    function ToFile(filepath) {
        var _this = _super.call(this, operationsEnum_1.Operation.ToFile, BlockItem_1.Type.Input, filepath) || this;
        _this.inputsLimit = 1;
        return _this;
    }
    Object.defineProperty(ToFile.prototype, "filepath", {
        //filepath
        get: function () {
            return this.args[0];
        },
        set: function (value) {
            this.args[0] = value;
        },
        enumerable: true,
        configurable: true
    });
    return ToFile;
}(BlockItem_1.BlockItem));
exports.ToFile = ToFile;
//# sourceMappingURL=ToFile.js.map