#pragma once

#include <ros/ros.h>
#include <ros/console.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <visualization_msgs/Marker.h>
#include <std_srvs/SetBool.h>
#include <vector>
#include <string>
#include <cmath>

namespace smb_highlevel_controller {

/*!
 * Class containing the Smb Highlevel Controller
 */
class SmbHighlevelController {
public:
	/*!
	 * Constructor.
	 */
	SmbHighlevelController(ros::NodeHandle& nodeHandle);

	/*!
	 * Destructor.
	 */
	virtual ~SmbHighlevelController();

	void setVel(const float &vel, const std::string &dof);

	void DriveSmb();

private:
	ros::NodeHandle nodeHandle_;
	ros::Subscriber subscriber_;
	ros::Publisher vel_pub;
	ros::ServiceServer stop_srv;
	geometry_msgs::Twist msg;

	float control_gain;

	void scanCallback(const sensor_msgs::LaserScan& msg);

	bool start_stop(
        std_srvs::SetBool::Request &request,
        std_srvs::SetBool::Response &response);
};

} /* namespace */
