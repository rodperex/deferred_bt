cmake_minimum_required(VERSION 3.8)
project(deferred_bt)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_CXX_STANDARD 17)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(behaviortree_cpp_v3 REQUIRED)

set(dependencies
  rclcpp
  behaviortree_cpp_v3
)

include_directories(include)

add_library(deferred_bt_node SHARED src/deferred_bt/DeferredBT.cpp)
add_library(setup_test_bt_node SHARED src/test/bt_nodes/SetupTest.cpp)
add_library(after_test_bt_node SHARED src/test/bt_nodes/AfterTest.cpp)
add_library(set_value_bt_node SHARED src/test/bt_nodes/SetValue.cpp)

list(APPEND plugin_libs
  deferred_bt_node
  setup_test_bt_node
  after_test_bt_node
  set_value_bt_node
)

foreach(bt_plugin ${plugin_libs})
  ament_target_dependencies(${bt_plugin} ${dependencies})
  target_compile_definitions(${bt_plugin} PRIVATE BT_PLUGIN_EXPORT)
endforeach()

add_executable(test_defer src/test/test_main.cpp)
ament_target_dependencies(test_defer ${dependencies})

install(TARGETS
  ${plugin_libs}
  test_defer
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  bt_xml_test
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_include_directories(include)
ament_export_dependencies(${dependencies})
ament_package()