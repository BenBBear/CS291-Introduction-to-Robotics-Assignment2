#include "ros/ros.h"
#include "std_msgs/String.h"
#include <ros/console.h>

#include "turtlesim/SetPen.h"
#include "turtlesim/TeleportAbsolute.h"
#include "turtlesim/TeleportRelative.h"
#include "turtlesim/Pose.h"
#include "turtlesim/Color.h"
#include "geometry_msgs/Twist.h"

#include <string>
#include <iostream>
#include <sstream>
using namespace std;



void tick(float x){
    ros::spinOnce();
    ros::Duration duration(x);
    duration.sleep();
}


int set_pen(ros::ServiceClient client, int r,int g, int b,int w){
    turtlesim::SetPen p;
    p.request.r = r;
    p.request.g = g;
    p.request.b = b;
    p.request.width = w;
    p.request.off = false;
    ROS_INFO("Ready to call set_pen");
    if (!client.call(p))
    {
        ROS_ERROR("Failed to call service setPen");
        return 1;
    }
    return 0;
}

int no_pen(ros::ServiceClient client){
    turtlesim::SetPen p;   
    p.request.off = true;
    ROS_INFO("Ready to call no_pen");
    if (!client.call(p))
    {
        ROS_ERROR("Failed to call service setPen");
        return 1;
    }
    return 0;
}

int transport(ros::ServiceClient client, float x, float y, float theta = 0.0){
    turtlesim::TeleportAbsolute p;    
    p.request.x = x;
    p.request.y = y;
    p.request.theta = theta;
    if (!client.call(p))
    {
        ROS_ERROR("Failed to call service TeleportAbsolute");
        return 1;
    }
    return 0;
};

geometry_msgs::Twist get_twist(float x, float y,float a){
    geometry_msgs::Twist t;
    t.linear.x = x;
    t.linear.y = y;
    t.linear.z = 0;
    t.angular.x = 0;
    t.angular.y = 0;
    t.angular.z = a;
    return t;
};





//****************************************************************************************************//
// I (Ankur) would be available from 5-6 PM on Monday's and Sakthi would be there from 1-2 PM on Wednesday's.
// Go to the Office Hour

void end(ros::Publisher vel,ros::ServiceClient pen, ros::ServiceClient teleport, ros::ServiceClient relaport){
    while (ros::ok()){}
}



void drawX(ros::Publisher vel,ros::ServiceClient pen, ros::ServiceClient teleport, ros::ServiceClient relaport){
    // set_pen(pen, 100, 100, 100, 30);
    // no_pen(pen);
    
    while (ros::ok()){               
        vel.publish(get_twist(1, 1, 0));
        tick(1.0);        
    }    
};

void drawZ(ros::Publisher vel,ros::ServiceClient pen, ros::ServiceClient teleport, ros::ServiceClient relaport){
    
}

//****************************************************************************************************//

int main(int argc, char **argv)
{
    /* 
       For Configuration
    */    
    string node_name = "controller";
    string vel_topic = "/turtles/turtle1/cmd_vel";
    
    ros::init(argc, argv, node_name);           
    ros::NodeHandle n;
    ros::Publisher vel_pub = n.advertise<geometry_msgs::Twist>(vel_topic, 1000);
    ros::ServiceClient set_pen = n.serviceClient<turtlesim::SetPen>("/turtles/turtle1/set_pen");
    ros::ServiceClient teleport = n.serviceClient<turtlesim::TeleportAbsolute>("/turtles/turtle1/teleport_absolute");
    ros::ServiceClient relaport = n.serviceClient<turtlesim::TeleportRelative>("/turtles/turtle1/teleport_relative");    
    
    drawX(vel_pub,set_pen,teleport,relaport);
    drawZ(vel_pub,set_pen,teleport,relaport);
    end(vel_pub,set_pen,teleport,relaport);    
    return 0;
}
