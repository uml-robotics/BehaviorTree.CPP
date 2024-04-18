#ifndef INTERACTIONNODE_H
#define INTERACTIONNODE_H

#include "leaf_node.h"
#include "behaviortree_cpp/action_node.h"

namespace BT
{
class InteractionNode : public SyncActionNode
{
public:
  InteractionNode(const std::string& name, const NodeConfig& config);
  ~InteractionNode() override = default;

  /// throws if the derived class return RUNNING.
  virtual NodeStatus executeTick() override;

  virtual NodeType type() const override final
  {
    return NodeType::INTERACTION;
  }
};
}  // namespace BT

#endif
