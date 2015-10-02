#include "../include/assignment_2/controller.h";


void end(ros::Publisher vel,ros::ServiceClient pen){
    
}



void drawX(ros::Publisher vel,ros::ServiceClient pen){
    STYLE_PEN();
    NO_PEN();
    
    
    LEFT(60);
    RUN(10);
    STOP();
};

void drawZ(ros::Publisher vel,ros::ServiceClient pen){
    
}



int main(int argc, char **argv)
{
    string node_name = "controller";
    string vel_topic_name = "/turtles/turtle1/cmd_vel";
    string set_pen_service_name = "/turtles/turtle1/set_pen";   
    ros::init(argc, argv, node_name);           
    ros::NodeHandle n;
    ros::Publisher vel_pub = n.advertise<geometry_msgs::Twist>(vel_topic_name, 1000);    
    ros::service::waitForService(set_pen_service_name);    
    ros::ServiceClient set_pen = n.serviceClient<turtlesim::SetPen>(set_pen_service_name);
    
    drawX(vel_pub,set_pen);
    drawZ(vel_pub,set_pen);
    end(vel_pub,set_pen);    
    return 0;
}
