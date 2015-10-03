#include "../include/assignment_2/controller.h"



void draw(ros::Publisher vel,ros::ServiceClient pen){

    // FOR "X"
    NO_PEN();        
    LEFT(27);
    RUN(30);
    STOP();
    PEN();
    TURN_AROUND();
    RIGHT(2);
    RUN(30);
    RIGHT(21);
    NO_PEN();
    RUN(15);
    RIGHT(20);
    PEN();
    RUN(29);
    NO_PEN();

    // FOR "Z"
    RIGHT(10);
    RUN(10);
    PEN();
    RUN(16);
    RIGHT(23);
    RUN(30);
    LEFT(22);
    RUN(18);
    STOP();
    
    // FOR Celebration
    NO_PEN();
    // Let's Dance
    int count = 0;
    int move_type;
    float v,a,t;
    int total = rand() % 300;
    while(count < total){
        move_type = rand() % 3 + 1;        
        t = rand() % 5 + 1;
        a = rand() % 20 + 10;
        v = rand() % 20 + 1;
        switch(move_type){
        case 1:            
            right(vel,t,a);
            break;
        case 2:
            left(vel,t,a);
            break;
        default:
            run(vel,t,v);            
        }        
        count++;
    }    
};

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
    
    draw(vel_pub,set_pen);
    return 0;
}
