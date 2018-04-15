#pragma once

#include <node.h>
#include <node_object_wrap.h>

#include <vector>
#include <memory>

#include "../model/CPSModels.hpp"
#include "./OperationFactory.hpp"
#include "./Execution.h"

#include <node.h>

#include <memory>
#include <vector>

class OperationNode{
public:
    OperationNode(std::string aOperationName, v8::Local<v8::Object> args, v8::Isolate* isolate)
    : operation(std::move(aOperationName))
    , arguments(args)
    , isolate(isolate)
    {}

    void Execute()
    {
        //Early escape if it's been visited already.
        if(executed) return;

        executed = true;
        //Execute all previous nodes
        for(const auto& previous : previousNodes){
            previous->Execute();
        }

        //Execute current node as we've got all necesarry data.
        output = OperationFactory::Create(operation, arguments, isolate, previousNodes);

        //Execute all following nodes
        for(const auto& next : nextNodes){
            next->Execute();
        }
    }

    void AddNext(OperationNode* aNode)
    {
        nextNodes.push_back(aNode);
    }

    void AddPrevious(OperationNode* aNode)
    {
        previousNodes.push_back(aNode);
    }

    const IOutput& GetOutput()
    {
        return *output;
    }

private:
    v8::Isolate*                                isolate;
    std::vector<OperationNode*>                 previousNodes;
    std::vector<OperationNode*>                 nextNodes;
    std::string                                 operation;
    v8::Local<v8::Object>                       arguments;
    std::unique_ptr<IOutput>                    output = nullptr;
    bool                                        executed = false;
}