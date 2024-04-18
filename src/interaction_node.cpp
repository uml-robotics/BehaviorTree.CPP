#include "behaviortree_cpp/interaction_node.h"

namespace BT
{
InteractionNode::InteractionNode(const std::string& name, const NodeConfig& config)
  : ActionNodeBase(name, config)
{}

}