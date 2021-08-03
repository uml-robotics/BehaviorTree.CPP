#include "behaviortree_cpp_v3/checker_condition_node.h"

namespace BT
{
CheckerConditionNode::CheckerConditionNode(const std::string& name, const NodeConfiguration& config)
  : LeafNode::LeafNode(name, config), checker_status_description("")
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
        ++execution_count;
        setStatus(NodeStatus::RUNNING);
        prev_status = NodeStatus::RUNNING;
    }
    CheckerStatus checker_status = tick_functor_(*this);
    //CheckerStatus checker_status;
    //NodeStatus status = tick_functor_(*this);
    NodeStatus status;

    switch(checker_status.status){
      case CheckerNodeStatus::IDLE:
          status = NodeStatus::IDLE;
          break;
      case CheckerNodeStatus::RUNNING:
          status = NodeStatus::RUNNING;
          break;
      case CheckerNodeStatus::SUCCESS:
          status = NodeStatus::SUCCESS;
          checker_status_description = "SUCCESS:" + checker_status.description + ":" + std::to_string(execution_count);
          description_history.push_back(checker_status_description);
          break;
      case CheckerNodeStatus::DEGRADED:
          status = NodeStatus::SUCCESS;
          checker_status_description = "DEGRADED:" + checker_status.description + ":" + std::to_string(execution_count);
          description_history.push_back(checker_status_description);
          break;
      case CheckerNodeStatus::FAILURE:
          status = NodeStatus::SUCCESS;
          checker_status_description = "FAILURE:" + checker_status.description + ":" + std::to_string(execution_count);
          description_history.push_back(checker_status_description);
          break;
    }
    if (status != prev_status)
    {
        setStatus(status);
    }
    return status;
}
}
