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
var Generator_1 = require("./Generator");
var operationsEnum_1 = require("../operationsEnum");
var Sinus = /** @class */ (function (_super) {
    __extends(Sinus, _super);
    function Sinus(sampler, period, amplitude, offset) {
        return _super.call(this, operationsEnum_1.Operation.Sinus, sampler, period || 6.283185307179586, amplitude || 1, offset || 0) || this;
    }
    Object.defineProperty(Sinus.prototype, "sampler", {
        //sampler
        get: function () {
            return this.args[0];
        },
        set: function (value) {
            this.args[0] = value;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Sinus.prototype, "period", {
        //period
        get: function () {
            return this.args[1];
        },
        set: function (value) {
            this.args[1] = value;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Sinus.prototype, "amplitude", {
        //amplitude 
        get: function () {
            return this.args[2];
        },
        set: function (value) {
            this.args[2] = value;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Sinus.prototype, "offset", {
        //offset 
        get: function () {
            return this.args[3];
        },
        set: function (value) {
            this.args[3] = value;
        },
        enumerable: true,
        configurable: true
    });
    return Sinus;
}(Generator_1.Generator));
exports.Sinus = Sinus;
//# sourceMappingURL=Sinus.js.map