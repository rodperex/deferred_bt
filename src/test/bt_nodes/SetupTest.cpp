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

#include "test/bt_nodes/SetupTest.hpp"


namespace deferred_bt
{

SetupTest::SetupTest(
  const std::string & xml_tag_name,
  const BT::NodeConfiguration & conf)
: BT::ActionNodeBase(xml_tag_name, conf)
{
}

void
SetupTest::halt()
{
}

BT::NodeStatus
SetupTest::tick()
{
  std::string pkg_path = ament_index_cpp::get_package_share_directory("deferred_bt");
  std::string xml_path = pkg_path + "/bt_xml_test/dummy.xml";
  std::ifstream file(xml_path);
  std::ostringstream contents_stream;
  contents_stream << file.rdbuf();

  setOutput("bt_xml", contents_stream.str());

  std::vector<std::string> plugins;
  plugins.push_back("set_value_bt_node");

  setOutput("plugins", plugins);

  return BT::NodeStatus::SUCCESS;
}

}  // namespace deferred_bt

BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<deferred_bt::SetupTest>("SetupTest");
}
