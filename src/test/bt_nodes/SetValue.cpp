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

#include "test/bt_nodes/SetValue.hpp"


namespace deferred_bt
{

SetValue::SetValue(
  const std::string & xml_tag_name,
  const BT::NodeConfiguration & conf)
: BT::ActionNodeBase(xml_tag_name, conf)
{
}

void
SetValue::halt()
{
}

BT::NodeStatus
SetValue::tick()
{
  int val = 42;
  std::cout << "SetValue: setting output - " << val << std::endl;
  setOutput("value", val);

  return BT::NodeStatus::SUCCESS;
}

}  // namespace deferred_bt

BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<deferred_bt::SetValue>("SetValue");
}
