#include "behaviortree_cpp_v3/controls/checker_sequence_node.h"
#include "behaviortree_cpp_v3/action_node.h"

namespace BT
{

auto ThrowError = [&](const std::string& text) {
        char buffer[256];
        sprintf(buffer, "Error %s", text.c_str());
        throw RuntimeError( buffer );
};

CheckerSequenceNode::CheckerSequenceNode(const std::string& name)
    : SequenceNode::SequenceNode(name)
{
    setRegistrationID("CheckerSequence");
}

void CheckerSequenceNode::addChild(TreeNode* child)
{
    ControlNode::addChild(child);

    if(!hasAction && child->type() == NodeType::ACTION)
        hasAction = true;
    else {
        if(!hasAction && child->type() != NodeType::CONDITION)
            ThrowError("CheckerSequenceNode Expects <Condition> node(s) before an action node.\n"
                          "CheckerSequenceNode format is: <Condition>(s) <Action> <Condition>(s)");
        else if(hasAction && child->type() != NodeType::CONDITION)
            ThrowError("CheckerSequenceNode Expects only one <Action> node.\n"
                          "CheckerSequenceNode format is: <Condition>(s) <Action> <Condition>(s)");
    }
}

} //end namespace
