#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/Int32.h>



typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int robot_status = 0; // 0 for starting point, 1 pickup point, 2 dropoff point

std_msgs::Int32 msgs;
double pick_up[2] = {-11.4167977918,2.16471197121};  
    
double drop_off[2] = {-3.51941751582, -2.80676723183};
int message_returned;
bool value_returned;

bool move_to_goal(float x,float y)
{
	//tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);
  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }
 
  
  move_base_msgs::MoveBaseGoal goal;
  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = x;
  goal.target_pose.pose.position.y = y;
  goal.target_pose.pose.orientation.x = 0.0;
	goal.target_pose.pose.orientation.y = 0.0;
	goal.target_pose.pose.orientation.z = 0.0;
	goal.target_pose.pose.orientation.w = 1.0;


   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
     
     ROS_INFO("Successful, the robot has moved");
     return true; // for success of an operation.
    
       
  }
  
  else{
    ROS_INFO("The robot failed to move");
    return false; // for failure of an operation.
    
    }
    
}

void success_callback(const std_msgs::Int32 value)
{
  message_returned = value.data;
}

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");  
  
  // publish goal reach message
  ros::NodeHandle n;
  ros::Publisher pub_msgs = n.advertise<std_msgs::Int32>("/goal",10);
  ros::Subscriber success_msgs = n.subscribe<std_msgs::Int32>("/message", 10, success_callback);
  
  
  msgs.data = robot_status;
  pub_msgs.publish(msgs);
  value_returned = move_to_goal(pick_up[0], pick_up[1]);
  
  if(value_returned)
  {
 
     ROS_INFO("value_returned  is set to true");
     value_returned = false;
     ros::Duration(0.5).sleep(); // sleep for 0.5 seconds before moving to the next destination.
     robot_status = 1; // to delete the marker in add_markers.cpp. 
     msgs.data = robot_status;
     pub_msgs.publish(msgs);
     value_returned = move_to_goal(drop_off[0], drop_off[1]);

     if(value_returned)
     {
       ROS_INFO("value_returned is set to  true");
       robot_status = 2;
       msgs.data = robot_status;
       pub_msgs.publish(msgs);
       while(message_returned != 1)
       {
         continue;
       }
       
       
     }
  }

 	

  return 0;
}

