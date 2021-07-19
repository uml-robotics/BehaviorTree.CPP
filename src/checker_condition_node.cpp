#include "behaviortree_cpp_v3/checker_condition_node.h"

namespace BT
{
CheckerConditionNode::CheckerConditionNode(const std::string& name, const NodeConfiguration& config)
  : LeafNode::LeafNode(name, config)
{
}

SimpleCheckerConditionNode::SimpleCheckerConditionNode(const std::string& name, TickFunctor tick_functor,
                                         const NodeConfiguration& config)
  : CheckerConditionNode(name, config), tick_functor_(std::move(tick_functor))
{
}

NodeStatus SimpleCheckerConditionNode::tick()
{
    NodeStatus prev_status = status();

    if (prev_status == NodeStatus::IDLE)
    {
        setStatus(NodeStatus::RUNNING);
        prev_status = NodeStatus::RUNNING;
    }

    NodeStatus status = tick_functor_(*this);
    if (status != prev_status)
    {
        setStatus(status);
    }
    return status;
}
}
