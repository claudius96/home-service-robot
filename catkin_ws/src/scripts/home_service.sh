#!/bin/sh

export TURTLEBOT_GAZEBO_WORLD_FILE=$(pwd)/src/my_robot/worlds/corridor.world

xterm -e "source devel/setup.bash && roslaunch turtlebot_gazebo turtlebot_world.launch world_file:="$(pwd)/src/my_robot/worlds/my_corridor.world" " &
sleep 3
xterm -e "source devel/setup.bash && roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(pwd)/src/my_robot/maps/map.yaml" &
sleep 3
xterm -e "source devel/setup.bash && roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 3
xterm -e "source devel/setup.bash && rosrun add_markers add_markers"&
sleep 3
xterm -e "source devel/setup.bash && rosrun pick_objects pick_objects"



