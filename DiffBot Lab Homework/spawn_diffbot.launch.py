from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from launch.substitutions import Command
from launch_ros.parameter_descriptions import ParameterValue
import os

def generate_launch_description():
    pkg_share = get_package_share_directory("diffbot_description")
    xacro_file = os.path.join(pkg_share, "urdf", "diffbot.urdf.xacro")
    robot_description = ParameterValue(
        Command(["xacro ", xacro_file]),
        value_type=str
    )

    return LaunchDescription([
        Node(
            package="robot_state_publisher",
            executable="robot_state_publisher",
            output="screen",
            parameters=[{
                "use_sim_time": True,
                "robot_description": robot_description
            }]
        ),

        Node(
            package="ros_gz_sim",
            executable="create",
            arguments=[
                "-name", "diffbot",
                "-topic", "robot_description"
            ],
            output="screen"
        ),
    ])
