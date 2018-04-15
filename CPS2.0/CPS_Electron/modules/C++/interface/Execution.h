
#include "./OperationNode.h"
#include <map>

class Execution {
public:
    Execution() = default;
    bool ContainsOperation(uint32_t id) const
    {
        return operationNodes.find(id) != operationNodes.end();
    }

    OperationNode* AddOperation(uint32_t id, OperationNode&& aNode)
    {
        auto result = operationNodes.emplace(id, std::move(aNode));
        if(result.second)
        {
            return &operationNodes[id];
        }
        else
        {
            return nullptr;
        }
    }

    OperationNode* GetOperation(uint32_t id)
    {
        if(ContainsOperation(id))
        {
            return &operationNodes[id];
        }
        else
        {
            return nullptr;
        }
    }
    
private:
    std::map<uint32_t, OperationNode> operationNodes;
}