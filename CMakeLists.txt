cmake_minimum_required(VERSION 2.8.10)


project(HEAR_ROS C CXX)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_srvs
  hear_msgs
  geometry_msgs
  tf2_geometry_msgs
  tf2
  tf2_ros
)

include_directories(
    include
    ${catkin_INCLUDE_DIRS}
    ${hear_INCLUDE_DIRS}
    ${HEAR_util_INCLUDE_DIRS}    
)

set(${PROJECT_NAME}_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

file(GLOB ${PROJECT_NAME}_SRCs 
${HEAR_ROS_SOURCE_DIR}/Interface_ROS/*.cpp
${HEAR_ROS_SOURCE_DIR}/Interface_motive_natnet/*.cpp
${HEAR_ROS_SOURCE_DIR}/Interface_mavlink/*.cpp
)
##### VCPKG #####
if(VCPKG) 
  file(GLOB VCPKG_cpps ${HEAR_ROS_SOURCE_DIR}/Interface_JSON_wrapper/*.cpp)
  list(APPEND ${PROJECT_NAME}_SRCs ${VCPKG_cpps})
endif() 
##### VCPKG #####
# # add_library(${PROJECT_NAME} ${HEAR_ROS_SRCs} ${HEAR_SRCs})

add_library(${PROJECT_NAME} STATIC ${HEAR_ROS_SRCs})

add_dependencies(${PROJECT_NAME} HEAR_util hear_msgs_generate_messages_cpp hear)

set_target_properties(${PROJECT_NAME}
                      PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_link_libraries(${PROJECT_NAME} PUBLIC hear)

set(${PROJECT_NAME}_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/include CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

message(HEAR_util_INCLUDE_DIRS="${HEAR_util_INCLUDE_DIRS}")


set(${PROJECT_NAME}_LIBS ${catkin_LIBRARIES})