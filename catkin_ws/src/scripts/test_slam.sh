#!/bin/sh

export TURTLEBOT_GAZEBO_WORLD_FILE=$(pwd)/src/my_robot/worlds/corridor.world

xterm -e "source devel/setup.bash && roslaunch my_robot world.launch world_file:="$(pwd)/src/my_robot/worlds/my_corridor.world" " &
sleep 3
xterm -e "source devel/setup.bash && roslaunch my_robot gmapping.launch" &
sleep 3
xterm -e "source devel/setup.bash && rosrun teleop_twist_keyboard teleop_twist_keyboard.py"
