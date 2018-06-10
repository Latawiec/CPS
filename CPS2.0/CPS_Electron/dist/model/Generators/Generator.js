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
var blockItem_1 = require("../blockItem");
var Generator = /** @class */ (function (_super) {
    __extends(Generator, _super);
    function Generator(operation, sampler) {
        var args = [];
        for (var _i = 2; _i < arguments.length; _i++) {
            args[_i - 2] = arguments[_i];
        }
        return _super.apply(this, [operation, blockItem_1.Type.Output, sampler].concat(args)) || this;
    }
    return Generator;
}(blockItem_1.BlockItem));
exports.Generator = Generator;
//# sourceMappingURL=Generator.js.map