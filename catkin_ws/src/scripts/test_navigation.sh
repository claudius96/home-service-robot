#!/bin/sh

export TURTLEBOT_GAZEBO_WORLD_FILE=$(pwd)/src/my_robot/worlds/corridor.world
xterm -e "source devel/setup.bash && export ROBOT_INITIAL_POSE -x 0.0122324163965 -y 0.0127243195796 -Y 0   && roslaunch turtlebot_gazebo turtlebot_world.launch world_file:="$(pwd)/src/my_robot/worlds/my_corridor.world" " &
sleep 3
xterm -e "source devel/setup.bash && roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 3
xterm -e "source devel/setup.bash && roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(pwd)/src/my_robot/maps/map.yaml" &


