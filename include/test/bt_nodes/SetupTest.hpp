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

#ifndef SETUP__TEST_HPP_
#define SETUP__TEST_HPP_

#include "rclcpp/rclcpp.hpp"
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "ament_index_cpp/get_package_share_directory.hpp"
#include <iostream>
#include <fstream>


namespace deferred_bt
{

class SetupTest : public BT::ActionNodeBase
{
public:
  explicit SetupTest(
    const std::string & xml_tag_name,
    const BT::NodeConfiguration & conf);

  void halt();
  BT::NodeStatus tick();

  static BT::PortsList providedPorts()
  {
    return BT::PortsList(
      {
        BT::InputPort<int>("bt_type"), // path or content
        BT::OutputPort<std::string>("bt_xml"), // XML corresponding to the BT to be executed
        BT::OutputPort<std::vector<std::string>>("plugins"), // plugins to load
        BT::OutputPort<std::string>("pkg"), // package where the XML is located
        BT::OutputPort<std::string>("rel_path") // relative path to the XML
      });
  }

private:
  std::string transfer_type_, pkg_;

};

}  // namespace deferred_bt

#endif
