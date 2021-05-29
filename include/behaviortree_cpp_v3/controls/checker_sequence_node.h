#ifndef CHECKERSEQUENCENODE_H
#define CHECKERSEQUENCENODE_H

#include "behaviortree_cpp_v3/controls/sequence_node.h"

namespace BT
{

class CheckerSequenceNode : public SequenceNode
{
  public:
    CheckerSequenceNode(const std::string& name);

    virtual ~CheckerSequenceNode() override = default;

    virtual void addChild(TreeNode* child) override;

  private:
    bool hasAction = false;
};

}

#endif // CHECKERSEQUENCENODE_H
