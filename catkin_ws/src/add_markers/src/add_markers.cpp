#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/Int32.h>


int status;
double pick_up_pos[2] = {-11.4167977918,2.16471197121}; 
    
double drop_off_pos[2] = {-3.51941751582, -2.6};
std_msgs::Int32 success;

 

void goal_msgs_callback(const std_msgs::Int32 send)
{
  status = send.data;
}
  
int main( int argc, char** argv )
  {
     ros::init(argc, argv, "add_markers");
     ros::NodeHandle n;
     ros::Rate r(1);
     ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
     ros::Subscriber sub_mgs = n.subscribe("/goal", 10, goal_msgs_callback);
     ros::Publisher success_pub = n.advertise<std_msgs::Int32>("/message", 10);

     

   
   
     while (ros::ok())
     {
       visualization_msgs::Marker marker;
       // Set the frame ID and timestamp.
       marker.header.frame_id = "map";
       marker.header.stamp = ros::Time::now();
   
       // Set the namespace and id for this marker.  This serves to create a unique ID
       // Any marker sent with the same namespace and id will overwrite the old one
       marker.ns = "cube_marker";
       marker.id = 0;
       // Set the marker type. 
      marker.type = visualization_msgs::Marker::CUBE;
      // Set the pose of the marker.  
      marker.pose.position.x = 0;
      marker.pose.position.y = 0;
      marker.pose.position.z = 0;
      marker.pose.orientation.x = 0.0;
      marker.pose.orientation.y = 0.0;
      marker.pose.orientation.z = 0.0;
      marker.pose.orientation.w = 1.0;

			// Set the scale of the marker -- 1x1x1 here means 1m on a side
			marker.scale.x = 0.2;
			marker.scale.y = 0.2;
			marker.scale.z = 0.2;

			// Set the color -- be sure to set alpha to something non-zero!
			marker.color.r = 1.0f;
			marker.color.g = 1.0f;
			marker.color.b = 1.0f;
			marker.color.a = 1.0;

			marker.lifetime = ros::Duration();

       
       
       switch( status )
       {
         case  0: {
          
					 // Set the marker action.  
					 marker.action = visualization_msgs::Marker::ADD;
					 marker.pose.position.x = pick_up_pos[0];
					 marker.pose.position.y = pick_up_pos[1];
					 marker.pose.position.z = 0.0;
					 marker.lifetime = ros::Duration();
					 ROS_INFO("status 0 reached");
					 break;
         }
         case 1:
         {
           marker.action = visualization_msgs::Marker::DELETE;
           ROS_INFO("status 1: robot reached pickup zone");
           break;
         }
         case 2:
         {

           // Set the marker action.  
					 marker.action = visualization_msgs::Marker::ADD;
					 marker.pose.position.x = drop_off_pos[0];
					 marker.pose.position.y = drop_off_pos[1];
					 marker.pose.position.z = 0.0;
					 marker.lifetime = ros::Duration();
					 ROS_INFO("status 2 reached");
					 success.data = 1;
					 success_pub.publish(success);                            
					 break; 
					 } 
  
       }
  
       // Publish the marker
        while (marker_pub.getNumSubscribers() < 1)
       {
         if (!ros::ok())
         {
           return 0;
         }
         ROS_WARN_ONCE("Please create a subscriber to the marker");
       
       }
      marker_pub.publish(marker);
      ros::spinOnce();
      r.sleep();
    }
  }
