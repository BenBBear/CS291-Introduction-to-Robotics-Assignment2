#ifndef CONTROLLER_HEADER_FILE
#define CONTROLLER_HEADER_FILE

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

static float TICK = 0.1;
#define RUN(x) run(vel,x);
#define STOP() stop(vel);
#define LEFT(x) left(vel,x);
#define RIGHT(x) right(vel,x);
#define NO_PEN() no_pen(pen);
#define STYLE_PEN() set_pen(pen, 0, 0, 0, 20);


void tick(){
    ros::spinOnce();
    ros::Duration duration(TICK);
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

geometry_msgs::Twist get_twist(float v,float a){
    geometry_msgs::Twist t;
    t.linear.x = v;
    t.linear.y = 0;
    t.linear.z = 0;
    t.angular.x = 0;
    t.angular.y = 0;
    t.angular.z = a;
    return t;
};

void run(ros::Publisher vel,int times = 1,float v = 2.0,float a = 0.0){
    int count = 0;
    while(ros::ok()){
        vel.publish(get_twist(v,a));
        tick();
        count++;
        if(count == times){
            return;
        }
    }
};

void stop(ros::Publisher vel,int times = 1){
    run(vel, times, 0.0, 0.0);
};

void left(ros::Publisher vel,int times = 1,float a = 1){
    run(vel,times,0.0, abs(a));
};

void right(ros::Publisher vel,int times = 1,float a = -1){
    run(vel,times,0.0, -abs(a));
}




#endif /* CONTROLLER_HEADER_FILE */
