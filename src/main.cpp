#include <mbed.h>
#include <MLX90363.h>
#include <ros.h>
#include <std_msgs/Int16.h>

SPI spi(D11, D12, D13);
// Serial serial(USBTX, USBRX);
MLX90363 sensor1(D10, &spi);
MLX90363 sensor2(D9, &spi);
MLX90363 sensor3(D8, &spi);

ros::NodeHandle nh;
std_msgs::Int16 int16_msg;
ros::Publisher pub1("sensor1", &int16_msg);
ros::Publisher pub2("sensor2", &int16_msg);
ros::Publisher pub3("sensor3", &int16_msg);

int main() {
    nh.initNode();
    nh.advertise(pub1);
    nh.advertise(pub2);
    nh.advertise(pub3);
    spi.format(8,1);
    spi.frequency(500000);
    // serial.baud(9600);
    wait(1);

    while(1) {
        sensor1.Poll();
        int16_t angle1 = sensor1.Get_Angel();
        sensor2.Poll();
        int16_t angle2 = sensor2.Get_Angel();
        sensor3.Poll();
        int16_t angle3 = sensor3.Get_Angel();
        int16_msg.data = angle1;
        pub1.publish(&int16_msg);
        int16_msg.data = angle2;
        pub2.publish(&int16_msg);
        int16_msg.data = angle3;
        pub3.publish(&int16_msg);
        nh.spinOnce();
        wait_ms(10);
    }
}