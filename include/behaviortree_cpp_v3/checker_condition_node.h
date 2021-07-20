#ifndef CHECKERCONDITIONNODE_H
#define CHECKERCONDITIONNODE_H

#include "leaf_node.h"
#include <string.h>

namespace BT
{

struct CheckerStatus {
  CheckerNodeStatus status;
  std::string description;
};

class CheckerConditionNode : public LeafNode
{
  public:
    CheckerConditionNode(const std::string& name, const NodeConfiguration& config);

    virtual ~CheckerConditionNode() override = default;

    //Do nothing
    virtual void halt() override final
    {
        // just in case, but it should not be needed
        setStatus(NodeStatus::IDLE);
    }

    virtual NodeType type() const override final
    {
        return NodeType::CHECKERCONDITION;
    }

    std::string getCheckerStatus()
    {
	return checker_status_description;
    }

    protected:
      std::string checker_status_description;
};

class SimpleCheckerConditionNode : public CheckerConditionNode
{
  public:
    typedef std::function<CheckerStatus(TreeNode&)> TickFunctor;

    // You must provide the function to call when tick() is invoked
    SimpleCheckerConditionNode(const std::string& name, TickFunctor tick_functor,
                        const NodeConfiguration& config);

    ~SimpleCheckerConditionNode() override = default;

  protected:
    virtual NodeStatus tick() override;

    TickFunctor tick_functor_;
};
}

#endif
