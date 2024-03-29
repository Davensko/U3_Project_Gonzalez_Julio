/*
 * File:          U3_Project_Gonzalez_Julio.c
 * Date:          July 11
 * Description:   3 wheels Robot Movement
 * Author:
 * Modifications:
 */

#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/keyboard.h>
#include <webots/position_sensor.h>
#include <webots/distance_sensor.h>

#include <stdio.h>

#define TIME_STEP 64

double sn;
double sn_2;
double dis;
double dis_2;
double encoder;
double max_vel = 0.2; 
double resolution = 65535;

int stop_r, stop_l = 0;
int key;
int x= 1;
int y= 0;

float compare = 0;
float angle = 2.61799;

void autoForward(WbDeviceTag *wheels) {
  wb_motor_set_position(wheels[0], INFINITY);
  wb_motor_set_velocity(wheels[0], 0);
  wb_motor_set_position(wheels[1], INFINITY);
  wb_motor_set_velocity(wheels[1], -6.66);
  wb_motor_set_position(wheels[2], INFINITY);
  wb_motor_set_velocity(wheels[2], 6.66);
}

void autoRight(WbDeviceTag *wheels) {
  wb_motor_set_velocity(wheels[0], 0.785398);
  wb_motor_set_velocity(wheels[1], 0.785398);
  wb_motor_set_velocity(wheels[2], 0.785398);
}

void autoLeft(WbDeviceTag *wheels) {
  wb_motor_set_velocity(wheels[0], -0.785398);
  wb_motor_set_velocity(wheels[1], -0.785398);
  wb_motor_set_velocity(wheels[2], -0.785398);
}

void manualForward(WbDeviceTag *wheels) {
  wb_motor_set_velocity(wheels[0], 0);
  wb_motor_set_velocity(wheels[1], -5);
  wb_motor_set_velocity(wheels[2], 5);
}

void manualBackward(WbDeviceTag *wheels) {
  wb_motor_set_velocity(wheels[0], 0);
  wb_motor_set_velocity(wheels[1], 5);
  wb_motor_set_velocity(wheels[2], -5);
}

void manualRight(WbDeviceTag *wheels) {
  wb_motor_set_velocity(wheels[0], -7.7);
  wb_motor_set_velocity(wheels[1], 3.8);
  wb_motor_set_velocity(wheels[2], 3.8);
}

void manualLeft(WbDeviceTag *wheels) {
  wb_motor_set_velocity(wheels[0], 7.7);
  wb_motor_set_velocity(wheels[1], -3.8);
  wb_motor_set_velocity(wheels[2], -3.8);
}

void turnRight(WbDeviceTag *wheels) {
  wb_motor_set_velocity(wheels[0], 0.785398);
  wb_motor_set_velocity(wheels[1], 0.785398);
  wb_motor_set_velocity(wheels[2], 0.785398);
}

void turnLeft(WbDeviceTag *wheels) {
  wb_motor_set_velocity(wheels[0], -0.785398);
  wb_motor_set_velocity(wheels[1], -0.785398);
  wb_motor_set_velocity(wheels[2], -0.785398);
}

void stopMotors(WbDeviceTag *wheels) {
  wb_motor_set_velocity(wheels[0], 0);
  wb_motor_set_velocity(wheels[1], 0);
  wb_motor_set_velocity(wheels[2], 0);
}

int main(int argc, char **argv){

  wb_robot_init();
  wb_keyboard_enable(TIME_STEP);

  WbDeviceTag Wheel_1 = wb_robot_get_device("Wheel_1");
  WbDeviceTag Wheel_2 = wb_robot_get_device("Wheel_2");
  WbDeviceTag Wheel_3 = wb_robot_get_device("Wheel_3");

  WbDeviceTag wheels[3];
  wheels[0] = Wheel_1;
  wheels[1] = Wheel_2;
  wheels[2] = Wheel_3;

  WbDeviceTag sen_1= wb_robot_get_device("sen_1");
  WbDeviceTag sen_2 = wb_robot_get_device("sen_2");

  wb_distance_sensor_enable(sen_1,TIME_STEP);
  wb_distance_sensor_enable(sen_2,TIME_STEP);

  WbDeviceTag enco_1 = wb_robot_get_device("encoder_1");
  WbDeviceTag enco_2 = wb_robot_get_device("encoder_2");
  WbDeviceTag enco_3 = wb_robot_get_device("encoder_3");
  
  wb_position_sensor_enable(enco_1, TIME_STEP);
  wb_position_sensor_enable(enco_2, TIME_STEP);
  wb_position_sensor_enable(enco_3, TIME_STEP);

  void automatic(){

    autoForward(wheels);

    sn = wb_distance_sensor_get_value(sen_1);
    dis = (sn*max_vel)/resolution ;

    sn_2 = wb_distance_sensor_get_value(sen_2);
    dis_2 = (sn_2*max_vel)/resolution;

    encoder = wb_position_sensor_get_value(enco_3);

    if((dis <= 0.17 && dis>dis_2) && stop_r == 0){

      compare = encoder + (angle);   // 2.35619 rad/s = 135 degrees
      stop_r = 1;
    }
    if(stop_r == 1){

      if(encoder <= compare){
        autoRight(wheels);
      }
      else{
        stopMotors(wheels);
        stop_r = 0;
      }
    }

    if((dis_2 <= 0.17 && dis<dis_2) && stop_l == 0){

      compare = encoder - (angle);
      stop_l = 1;
    }
    if(stop_l == 1){

      if(encoder >= compare){
        autoLeft(wheels);
      }
      else{
        stopMotors(wheels);
        stop_l = 0;
      }
    }

  printf("sensor: %f\n", dis);
  printf("sensor2: %f\n", dis_2);
  printf("Encoder: %f\n", encoder);
  printf("flag: %f\n", compare);

  }

  void manual(){

    if(key == WB_KEYBOARD_UP){
      manualForward(wheels);
    }
    else if(key ==WB_KEYBOARD_DOWN){
      manualBackward(wheels);
    }
    else if(key ==WB_KEYBOARD_RIGHT){
      manualRight(wheels);
    }
    else if(key ==WB_KEYBOARD_LEFT){
      manualLeft(wheels);
    }
    else if(key == 'S'){
      turnRight(wheels);
    }
    else if(key =='A'){
      turnLeft(wheels);
    }
    else{
      stopMotors(wheels);
    }
  }

  while (wb_robot_step(TIME_STEP) != -1) {

    key = wb_keyboard_get_key();

    if(key == 'G'){
      x = 1;
      y = 0;
    }
    else if (key == 'W'){
      y = 1;
      x = 0;
    }
    if(y == 1){
      manual();
    }
    if(x == 1){
      automatic();
    }
  };

  wb_robot_cleanup();

  return 0;
}
