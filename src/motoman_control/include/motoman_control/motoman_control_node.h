#ifndef MOTOMAN_CONTROL_H
#define MOTOMAN_CONTROL_H

#include <ros/ros.h>
#include "socket_node.h" //-- activate and deactivate gripper
#include "utils.h" //-- activate and deactivate gripper
// MoveIt!
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/move_group_interface/move_group_interface.h>

// TF2
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <ros/ros.h>
//#include "../../../motoman/motoman_driver/include/motoman_driver/industrial_robot_client/joint_trajectory_action.h"
#include <motoman_driver/industrial_robot_client/joint_trajectory_action.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/server/action_server.h>

#include <trajectory_msgs/JointTrajectory.h>
#include <control_msgs/FollowJointTrajectoryAction.h>
#include <control_msgs/FollowJointTrajectoryFeedback.h>
#include <industrial_msgs/RobotStatus.h>
#include <motoman_driver/industrial_robot_client/robot_group.h>
#include <motoman_msgs/DynamicJointTrajectory.h>



/**
MotomanControl class
*/
class MotomanControl
{
private:

public:
	//! Initialize the action client and wait for action server to come up
    MotomanControl(){

    };
    ~MotomanControl(){

    };
	void controlGripper(std::string);
	
	std::string getPose();
};

#endif /* MOTOMAN_CONTROL_H */