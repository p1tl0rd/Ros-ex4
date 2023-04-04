#include <smb_highlevel_controller/SmbHighlevelController.hpp>

namespace smb_highlevel_controller {

SmbHighlevelController::SmbHighlevelController(ros::NodeHandle& nodeHandle) :
  nodeHandle_(nodeHandle)
{
  std::string topic;
  int queue_size;
  if ( !nodeHandle.getParam("subscriber_topic", topic) 
      || !nodeHandle.getParam("queue_size", queue_size) ) 
  {
      ROS_ERROR("Could not find subscriber params!"); 
      ros::requestShutdown();
  }

  // create subscriber
  subscriber_ = nodeHandle_.subscribe(topic, queue_size, &SmbHighlevelController::scanCallback, this);

  // create publishers
  vel_pub= nodeHandle_.advertise<geometry_msgs::Twist>("/cmd_vel",1);

  // service server
    stop_srv = nodeHandle_.advertiseService("/start_stop",
        &SmbHighlevelController::start_stop, this);

  //setVel(3.0, "forward");
}

SmbHighlevelController::~SmbHighlevelController()
{
}

void SmbHighlevelController::scanCallback(const sensor_msgs::LaserScan& msg)
{
  int size = msg.ranges.size();
  float min = msg.range_max;
  int minIndex = 0;

  // tim khoang cach nho nhat tu vector msg.ranges
  for (int i = 0; i < size; i++) {
    if (msg.ranges.at(i) < min && msg.ranges.at(i) > msg.range_min) {
      min = msg.ranges.at(i);
    }
  }

  ROS_INFO_STREAM("Minimum min: " << min);

  //DriveSmb();
}

void SmbHighlevelController::setVel(const float &vel, const std::string &dof) {
    if (dof == "forward") {
        msg.linear.x = vel;
    }
    else if (dof == "ang") {
        msg.angular.z = vel;
    }
}

void SmbHighlevelController::DriveSmb() {
    vel_pub.publish(msg);
}

bool SmbHighlevelController::start_stop(
    std_srvs::SetBool::Request &request, std_srvs::SetBool::Response &response)
{
    if (request.data) { // start
        response.message = "Start Smb";
        setVel(3.0, "forward");
    }
    else { // stop
        response.message = "Stop Smb";
        setVel(.0, "forward");
    }
    ROS_INFO_STREAM(response.message);
    response.success = true;
    return true;
}
} /* namespace */
