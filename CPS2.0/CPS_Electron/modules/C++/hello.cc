#include <node.h>
#include <string>
#include "./model/CPSModels.hpp"
#include "./interface/OperationNode.h"
#include "./interface/Execution.h"

namespace demo {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Array;
using v8::Object;
using v8::Number;
using v8::String;
using v8::Value;
using v8::Function;
using v8::Handle;


void Method(const FunctionCallbackInfo<Value>& args) {
  Numeric::Number a(1);
  
  std::string val = "Value is: " + std::to_string(double(a));

  Isolate* isolate = args.GetIsolate();

  Local<Object> wtf = Object::New(isolate);
  Local<Object> inner = Object::New(isolate);

  args[0]->ToObject(isolate);

  inner->Set(String::NewFromUtf8(isolate, "val"), Number::New(isolate, 15));
  wtf->Set(String::NewFromUtf8(isolate, "innerObj"), inner);
  wtf->Set(String::NewFromUtf8(isolate, "outVal"), String::NewFromUtf8(isolate, "xDDD"));

  //args.GetReturnValue().Set(String::NewFromUtf8(isolate, [&](){ return val.c_str(); }()));
  args.GetReturnValue().Set(wtf);
}

void Resolver(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if(args.Length() > 1 || !args[0]->IsObject()){
    isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, "Wrong function args.")));
    return;
  }

  Execution executionContext{};
  OperationNode* mainNode = Resolve(Handle<Object>::Cast(args[0]), isolate, executionContext);
  //mainNode->Execute();
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "I'm fucking alive!"));
}

OperationNode* Resolve(Handle<Object>& aObject, Isolate* aIsolate, Execution& aContext){
  Handle<Value> id = aObject->Get(String::NewFromUtf8(aIsolate, "id"));
  uint32_t idValue = id->NumberValue();

  OperationNode* result = nullptr;

  if(!aContext.ContainsOperation(idValue))
  {
    Handle<Value> operation = aObject->Get(String::NewFromUtf8(aIsolate, "operation"));
    String::Utf8Value utfOperation(operation);
    Handle<Value> args = aObject->Get(String::NewFromUtf8(aIsolate, "args"));
    Handle<Value> callback = aObject->Get(String::NewFromUtf8(aIsolate, "dataCallback"));
    if(!callback->IsNullOrUndefined())
    {
      Handle<Function> callbackFunction = Handle<Function>::Cast(callback);
      //TODO
    }

    result = aContext.AddOperation(idValue, OperationNode(std::string(*utfOperation), args, aIsolate));
  }
  else
  {
    result = aContext.GetOperation(idValue);
  }
  
  //Resolving all previous nodes
  Handle<Array> previousNodes = aObject->Get(String::NewFromUtf8(aIsolate, "previous"));
  for(uint32_t i = 0; i < previousNodes->Length(); ++i)
  {
    result->AddPrevious(Resolve(previousNodes->Get(i)->ToObject(), aIsolate, aContext));
  }
  //Resolving all 
  Handle<Array> nextNodes = aObject->Get(String::NewFromUtf8(aIsolate, "previous"));
  for(uint32_t i = 0; i < previousNodes->Length(); ++i)
  {
    result->AddPrevious(Resolve(nextNodes->Get(i)->ToObject(), aIsolate, aContext));
  }

  return result;
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Method);
  NODE_SET_METHOD(exports, "Resolver", Resolver);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, init)

}  // namespace demo