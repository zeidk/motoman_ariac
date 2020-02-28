  #include "motoman_control_node.h"


  void MotomanControl::controlGripper(std::string parameter)
  {
    utils ut;
    tcp_client c;
    std::string host = ut.get_gripper_control_host();
    int port = ut.get_gripper_control_port();
    

    // connect to host
    c.conn(host, port);
    c.send_data(parameter);
  }

  std::string MotomanControl::getPose()
  {
    utils ut;
    tcp_client c;
    std::string host = ut.get_vision_system_host();
    int port = ut.get_vision_system_port();
    

    // connect to host
    c.conn(host, port);
    return (c.receive());
  }

  

    int main(int argc, char** argv)
    {
      /*
      ros::init(argc, argv, "motoman_control_node");


      MotomanControl *moto = new MotomanControl();
      std::string param;
      ros::NodeHandle nh("~");
      std::string check;
      nh.getParam("param", check);
      std::cout << check << std::endl;
      ROS_INFO("Got parameter : %s", check.c_str());

      if(check.compare("c") == 0)
          {
            std::cout << "close gripper" << std::endl;
            moto->controlGripper("1");
          }
           else if(check.compare("o") == 0)
          {
            std::cout << "open gripper" << std::endl;
            moto->controlGripper("0");
          }
          else
          {
            std::cout << "Control has come out !!! " << std::endl;
          }  
*/

ros::init(argc, argv, "path_plan");
bool path{false};
    ros::NodeHandle node("~");;
    ROS_INFO("path_plan node started");
    MotomanControl *moto = new MotomanControl();

    std::string param;
    std::string check;
    node.getParam("param", check);
      std::cout << check << std::endl;
      ROS_INFO("Got parameter : %s", check.c_str());

if(check.compare("c") == 0)
          {
            std::cout << "close gripper" << std::endl;
            moto->controlGripper("1");
          }
           else if(check.compare("o") == 0)
          {
            std::cout << "open gripper" << std::endl;
            moto->controlGripper("0");
          }
          else if(check.compare("r") == 0)
          {
            std::cout << "Control has come out !!! " << std::endl;
            path=true;
          }  
if (path){
  
    ros::Publisher pub = node.advertise<trajectory_msgs::JointTrajectory>("trajectory_msgs/JointTrajectory", 1000);
    //ros::Publisher pub = node.advertise<trajectory_msgs::JointTrajectory>("/pickup/goal ", 1000);
    
    ros::Rate rate(10);
    rate.sleep();

    while (ros::ok())
{


trajectory_msgs::JointTrajectory traj;

traj.joint_names.push_back("joint_s");
traj.joint_names.push_back("joint_l");
traj.joint_names.push_back("joint_e");
traj.joint_names.push_back("joint_u");
traj.joint_names.push_back("joint_r");
traj.joint_names.push_back("joint_b");
traj.joint_names.push_back("joint_t");

// trajectory_msgs::JointTrajectoryPoint points; 

traj.points.resize(2);
int ind = 0;

traj.points[ind].positions.resize(7);
traj.points[ind].positions[0] = 0.0;
traj.points[ind].positions[1] = 0.0;
traj.points[ind].positions[2] = 0.0;
traj.points[ind].positions[3] = 0.0;
traj.points[ind].positions[4] = 0.0;
traj.points[ind].positions[5] = 0.0;
traj.points[ind].positions[6] = 0.0;
// Velocities
traj.points[ind].velocities.resize(7);
for (size_t j = 0; j < 7; ++j)
{
traj.points[ind].velocities[j] = 0.1;
}
// To be reached 1 second after starting along the traj
traj.points[ind].time_from_start = ros::Duration(1.0);

// Second trajectory point
// Positions
ind += 1;
traj.points[ind].positions.resize(7);
traj.points[ind].positions[0] = -1.1734442710876465;
traj.points[ind].positions[1] = 0.9648739695549011;
traj.points[ind].positions[2] = 0.7801997065544128;
traj.points[ind].positions[3] = 1.3781284093856812;
traj.points[ind].positions[4] = 0.7441021800041199;
traj.points[ind].positions[5] = -1.0758672952651978;
traj.points[ind].positions[6] = 0.29112550616264343;

// Velocities
traj.points[ind].velocities.resize(7);
for (size_t j = 0; j < 7; ++j)
{
traj.points[ind].velocities[j] = 0.1;
}
// To be reached 2 seconds after starting along the traj
traj.points[ind].time_from_start = ros::Duration(2.0);


traj.header.stamp = ros::Time::now() + ros::Duration();

pub.publish(traj);

rate.sleep();
}
}










  //name: [joint_s, joint_l, joint_e, joint_u, joint_r, joint_b, joint_t]
  //position: [-1.1734442710876465, 0.9648739695549011, 0.7801997065544128, -1.3781284093856812, 0.7441021800041199, -1.0758672952651978, 0.29112550616264343]



      //ros::init(argc, argv, "motoman_control_node");
      //ros::NodeHandle nh;
      //ros::AsyncSpinner spinner(1);
      //spinner.start();

      //ros::WallDuration(1.0).sleep();
      //moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
      //moveit::planning_interface::MoveGroupInterface group("manipulator");
      //group.setPlanningTime(45.0);

      //std::string pose = moto->getPose();
     

      //moto->controlGripper("0");
      //ros::WallDuration(1.0).sleep();
      //moto->controlGripper("1");
      //ros::WallDuration(1.0).sleep();
      //moto->controlGripper("0");



      
         

          
      
      //ros::waitForShutdown();
      return 0;
    }