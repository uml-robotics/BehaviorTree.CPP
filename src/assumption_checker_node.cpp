#include "behaviortree_cpp/assumption_checker_node.h"

namespace BT
{
AssumptionCheckerNode::AssumptionCheckerNode(const std::string& name, const NodeConfig& config)
  : ConditionNode::ConditionNode(name, config)
{}

SimpleAssumptionCheckerNode::SimpleAssumptionCheckerNode(const std::string& name,
                                         TickFunctor tick_functor,
                                         const NodeConfig& config)
  : AssumptionCheckerNode(name, config), tick_functor_(std::move(tick_functor))
{}

NodeStatus SimpleAssumptionCheckerNode::tick()
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
}  // namespace BT