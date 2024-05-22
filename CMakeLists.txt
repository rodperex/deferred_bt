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

add_library(${PROJECT_NAME} SHARED
  src/deferred_bt/DeferredBT.cpp
)
ament_target_dependencies(${PROJECT_NAME} ${dependencies})

# add_executable(XX src/...)
# ament_target_dependencies(XX ${dependencies})
# target_link_libraries(XX ${PROJECT_NAME})

install(TARGETS
  ${PROJECT_NAME}
  # XX
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY DESTINATION share/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_dependencies(${dependencies})
ament_package()