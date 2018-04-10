#include <node.h>
#include <string>
#include "./model/CPSModels.hpp"

namespace demo {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;


void Method(const FunctionCallbackInfo<Value>& args) {
  Numeric::Number a(1);
  
  std::string val = "Value is: " + std::to_string(double(a));

  Isolate* isolate = args.GetIsolate();
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, [&](){ return val.c_str(); }()));
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Method);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, init)

}  // namespace demo