#include <mbed.h>
#include <MLX90363.h>
#include <ros.h>
#include <std_msgs/Int16.h>

// Sensor
SPI spi(A6, A5, A4);
MLX90363 sensor1(D7, &spi);    //PF0
MLX90363 sensor2(D6, &spi);     //PB1
MLX90363 sensor3(A0, &spi);     //PA0
int16_t angle1, angle2, angle3;

// ROS
ros::NodeHandle nh;
std_msgs::Int16 int16_msg;
ros::Publisher pub1("sensor1", &int16_msg);
ros::Publisher pub2("sensor2", &int16_msg);
ros::Publisher pub3("sensor3", &int16_msg);

// Timing
Ticker sensor_tick;
Ticker ros_tick;

void read_sensor() {
    // read sensors
    sensor1.Poll();
    sensor2.Poll();
    sensor3.Poll();
}

void send_ros_msg() {
    int16_msg.data = sensor1.Get_Angel();
    pub1.publish(&int16_msg);
    int16_msg.data = sensor2.Get_Angel();
    pub2.publish(&int16_msg);
    int16_msg.data = sensor3.Get_Angel();
    pub3.publish(&int16_msg);
    nh.spinOnce();
}
 
int main() {
    nh.getHardware() -> setBaud(115200);
    nh.initNode();
    nh.advertise(pub1);
    nh.advertise(pub2);
    nh.advertise(pub3);
    spi.format(8,1);
    spi.frequency(500000);
    sensor_tick.attach(&read_sensor, 0.005);
    ros_tick.attach(&send_ros_msg, 0.01);

    while(1) {
        wait(1);
    }
}