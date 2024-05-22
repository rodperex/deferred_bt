// Copyright 2024 Intelligent Robotics Lab - Gentlebots
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "deferred_bt/DeferredBT.hpp"


namespace deferred_bt
{

DeferredBT::DeferredBT(
  const std::string & xml_tag_name,
  const BT::NodeConfiguration & conf)
: BT::ActionNodeBase(xml_tag_name, conf)
{

}

void
DeferredBT::halt()
{
}

BT::NodeStatus
DeferredBT::tick()
{
  bt_xml_ = getInput<std::string>("xml");
  plugins_ = getInput<std::vector<std::string>>("plugins");

  if (!bt_xml_) {
    throw BT::RuntimeError("Missing required input [xml]");
  }
  // if (!plugins_) {
  //   throw BT::RuntimeError("Missing required input [plugins]");
  // }

  if (status() == BT::NodeStatus::IDLE) {
    BT::BehaviorTreeFactory factory;
    BT::SharedLibrary loader;

    if (plugins_) {
      for (const auto & plugin : plugins_.value()) {
        factory.registerFromPlugin(loader.getOSName(plugin));
      }
    }

    subtree_ = factory.createTreeFromText(bt_xml_.value(), config().blackboard);
  }

  return subtree_.rootNode()->executeTick();

}

}  // namespace deferred_bt

BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<deferred_bt::DeferredBT>("DeferredBT");
}
