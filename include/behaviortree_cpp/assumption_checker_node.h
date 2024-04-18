#ifndef ASSUMPTIONCHECKERNODE_H
#define ASSUMPTIONCHECKERNODE_H

#include "leaf_node.h"
#include "behaviortree_cpp/condition_node.h"

namespace BT
{
class AssumptionCheckerNode : public ConditionNode
{
public:
  AssumptionCheckerNode(const std::string& name, const NodeConfig& config);

  virtual ~AssumptionCheckerNode() override = default;

  virtual NodeType type() const override final
  {
    return NodeType::ASSUMPTIONCHECKER;
  }
};

/**
 * @brief The SimpleAssumptionCheckerNode provides an easy to use AssumptionCheckerNode.
 * The user should simply provide a callback with this signature
 *
 *    BT::NodeStatus functionName(void)
 *
 * This avoids the hassle of inheriting from a ActionNode.
 *
 * Using lambdas or std::bind it is easy to pass a pointer to a method.
 */
class SimpleAssumptionCheckerNode : public AssumptionCheckerNode
{
public:
  using TickFunctor = std::function<NodeStatus(TreeNode&)>;

  // You must provide the function to call when tick() is invoked
  SimpleAssumptionCheckerNode(const std::string& name, TickFunctor tick_functor,
                      const NodeConfig& config);

  ~SimpleAssumptionCheckerNode() override = default;

protected:
  virtual NodeStatus tick() override;

  TickFunctor tick_functor_;
};
}  // namespace BT

#endif
