# Home service robot

![](https://github.com/claudius96/home-service-robot/blob/master/catkin_ws/Animation.gif)

### Packages used:
* slam_gmapping
* amcl
* turtlebot_simulator
* turtebot_interactions
* turtlebot
* teleop_twist_keyboard

### Brief explaination of packages
* slam_gmapping package is used for mapping the environment
*  amcl ros package is used for localization of the robot relative the map obtained using the slam_gmapping package.
*  turtlebot_interactions contains the ros package turtlebot_gazebo which contains turtlebot_world.launch file for launching the environment and also spawing turtlebot robot.
* turtlebot_interactions also contatis the ros package turtlebot_rviz_launchers for visualization of robot performing autonomous navigation around the environmeht.
* teleop_twist_keyboard package is for teleoperating the robot around its environment.

### Prerequisites
1. Gazebo
2. ROS(kinetic , Melodic)
3. Ubuntu 14 and above
4. Install xterm `sudo apt-get install xterm`
5. Install dependencies necessary:
```$ sudo apt-get update && sudo apt-get upgrade -y
$ sudo apt-get install ros-${ROS_DISTRO}-map-server
$ sudo apt-get install ros-${ROS_DISTRO}-amcl
$ sudo apt-get install ros-${ROS_DISTRO}-move-base
$ sudo apt-get install ros-${ROS_DISTRO}-slam-gmapping
$ pip install rospkg
$ rosdep -i install gmapping
$ rosdep -i install turtlebot_teleop
$ rosdep -i install turtlebot_rviz_launchers
$ rosdep -i install turtlebot_gazebo
```

### Project goals:
The main goal of this project was to build a robot that is able to map the environment, localize itself in the environment and then be able to navigate itself autonomously to a certain designated area.
We could divide the project task such as:
* building an environment in gazebo
* manually teleoperating the robot
* save map got from slam_gmapping package
* build a **pick_object** node that essential make a robot to move to the pick up position and then to a drop off position
* build a **add_markers** node that sends messages to rviz to display a marker when and before a robot reaches a pick up point and when a robot reaches a drop off point.
* use the ros Navigation stack to sends goals to robot.

### Directory tree structre
![alt text](https://github.com/claudius96/home-service-robot/blob/master/catkin_ws/structure.jpg)

### clone and builing
Have ROS installed in your computer. If ROS is installed in your computer you can perform the follwing commands are cloning this repository.
 ``` 1. git clone https://github.com/claudius96/home-service-robot
     2. catkin_make
     3. install dependencies
     - rosdep -i install gmapping -y
     - rosdep -i install turtlebot_teleop -y
     - rosdep -i install turtlebot_rviz_launchers -y
     - rosdep -i install turtlebot_gazebo -y
  ```
 

### Running

* To see the robot perform autonomous navigation run:
  ```
      $ /src/scripts/home_service.sh
  ```
* to see markers displaying on the pickup and drop off zone in rviz:
  ``` 
      $ /src/scripts/add_markers.sh
  ```
* To perform mapping of the environment use:
  ``` 
      $ /src/scripts/test_slam.sh
      $ rosrun map_server map_saver
  ```
  To map the environment run the `src/scripts/test_slam.sh` first and after you need to use the teleop_twist_keyboard to drive around the environment hence mapping it.
  After driving around you then run `rosrun map_server map_saver` 




