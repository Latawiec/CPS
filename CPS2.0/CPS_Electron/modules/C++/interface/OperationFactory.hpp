
#include "../model/CPSModels.hpp"
#include "./OperationNode.h"
#include <node.h>

#include <vector>
#include <memory>

class OperationFactory {
public:
    static std::unique_ptr<IOutput> Create(const std::string& aOperationName,
                                           const v8::Local<v8::Object>& aArgs,
                                           v8::Isolate* aIsolate,
                                           const std::vector<OperationNode*>& aPreviousNodes){
        if(aOperationName == "Average")
        {
            
        }else
        if(aOperationName == "AverageMod")
        {

        }else
        if(aOperationName == "Divide")
        {

        }else
        if(aOperationName == "FromFile")
        {

        }else
        if(aOperationName == "Histogram")
        {

        }else
        if(aOperationName == "Impulse")
        {

        }else
        if(aOperationName == "ImpulseNoise")
        {

        }else
        if(aOperationName == "Linear")
        {

        }else
        if(aOperationName == "Multiply")
        {

        }else
        if(aOperationName == "Power")
        {

        }else
        if(aOperationName == "RandNormal")
        {

        }else
        if(aOperationName == "RandUniform")
        {

        }else
        if(aOperationName == "RMS")
        {

        }else
        if(aOperationName == "Sinus")
        {

        }else
        {
            aIsolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(aIsolate, std::string(aOperationName).append("  is an unknown operation.").c_str())));
            throw std::runtime_error("Uknown operation");
        }
    }
}