#ifndef INTERACTIONNODE_H
#define INTERACTIONNODE_H

#include "leaf_node.h"
#include "behaviortree_cpp/action_node.h"

namespace BT
{
class InteractionNode : public ActionNodeBase
{
public:
  InteractionNode(const std::string& name, const NodeConfig& config);
  ~InteractionNode() override = default;

  virtual NodeType type() const override final
  {
    return NodeType::INTERACTION;
  }
};
}  // namespace BT

#endif
