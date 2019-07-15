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
//#define pi 3.1416

 
double sn; 
double sn_2; 
double dis;
double dis_2; 
double encoder;
double vel = 2.0;
 
int stop_r, stop_l = 0;

float compare = 0;




/*
void Forward(WbDeviceTag *wheels) {
  wb_motor_set_velocity(wheels[0], 0);
  wb_motor_set_velocity(wheels[1], vel);
  wb_motor_set_velocity(wheels[2], vel);
}

void TurnRight(WbDeviceTag *wheels) {
  wb_motor_set_velocity(wheels[0], vel);
  wb_motor_set_velocity(wheels[1], vel);
  wb_motor_set_velocity(wheels[2], vel);
}

void TurnLeft(WbDeviceTag *wheels) {
  wb_motor_set_velocity(wheels[0], vel);
  wb_motor_set_velocity(wheels[1], vel);
  wb_motor_set_velocity(wheels[2], vel);
}
*/



 
int main(int argc, char **argv){

  int key;
  int x= 1; 
  int y= 0; 

 
  wb_robot_init();
  wb_keyboard_enable(TIME_STEP);
 
  WbDeviceTag wheel_1 = wb_robot_get_device("Wheel_1");
  WbDeviceTag wheel_2 = wb_robot_get_device("Wheel_2");
  WbDeviceTag wheel_3 = wb_robot_get_device("Wheel_3");
     
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
  
    wb_motor_set_position(wheel_1, INFINITY);
    wb_motor_set_velocity(wheel_1, 0);
    wb_motor_set_position(wheel_2, INFINITY);
    wb_motor_set_velocity(wheel_2, -2);
    wb_motor_set_position(wheel_3, INFINITY);
    wb_motor_set_velocity(wheel_3, 2);
     
    sn = wb_distance_sensor_get_value(sen_1);
    dis = (sn*0.2)/65535;
     
    sn_2 = wb_distance_sensor_get_value(sen_2);
    dis_2 = (sn_2*0.2)/65535;
     
    encoder = wb_position_sensor_get_value(enco_3);
     
    if((dis <= 0.17 && dis>dis_2) && stop_r == 0){
    
      compare = encoder + (2.35619);   // 2.35619 rad/s = 135 degrees
      stop_r = 1;
      
    }

    if(stop_r == 1){

      if(encoder <= compare){
      
        wb_motor_set_velocity(wheel_1, 5);
        wb_motor_set_velocity(wheel_2, 5);
        wb_motor_set_velocity(wheel_3, 5);
        
      }
     
      else{
        wb_motor_set_velocity(wheel_1, 0);
        wb_motor_set_velocity(wheel_2, 0);
        wb_motor_set_velocity(wheel_3, 0);
        
        stop_r = 0;
      }
             
    }

    if((dis_2 <= 0.17 && dis<dis_2) && stop_l == 0){
    
      compare = encoder - (2.35619); 
      stop_l = 1;
      
    }

    if(stop_l == 1){

      if(encoder >= compare){
      
        wb_motor_set_velocity(wheel_1, -5);
        wb_motor_set_velocity(wheel_2, -5);
        wb_motor_set_velocity(wheel_3, -5);
      }
      
      else{
      
        wb_motor_set_velocity(wheel_1, 0);
        wb_motor_set_velocity(wheel_2, 0);
        wb_motor_set_velocity(wheel_3, 0);
        
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

       wb_motor_set_velocity(wheel_1, 0);
       wb_motor_set_velocity(wheel_2, -2);
       wb_motor_set_velocity(wheel_3, 2);
  }
  else if(key ==WB_KEYBOARD_DOWN){
       wb_motor_set_velocity(wheel_1, 0);
       wb_motor_set_velocity(wheel_2, 2);
       wb_motor_set_velocity(wheel_3, -2);
  }
  else if(key ==WB_KEYBOARD_RIGHT){
       wb_motor_set_velocity(wheel_1, -4);
       wb_motor_set_velocity(wheel_2, -3);
       wb_motor_set_velocity(wheel_3, 3);
  }
  else if(key ==WB_KEYBOARD_LEFT){
       wb_motor_set_velocity(wheel_1, 4);
       wb_motor_set_velocity(wheel_2, 3);
       wb_motor_set_velocity(wheel_3, -3);
  }
  else if(key == 'S'){
       wb_motor_set_velocity(wheel_1, 2);
       wb_motor_set_velocity(wheel_2, 2);
       wb_motor_set_velocity(wheel_3, 2);
  }
  else if(key =='A'){
       wb_motor_set_velocity(wheel_1, -2);
       wb_motor_set_velocity(wheel_2, -2);
       wb_motor_set_velocity(wheel_3, -2);
  }
  else{
 
  wb_motor_set_velocity(wheel_1, 0);
  wb_motor_set_velocity(wheel_2, 0);
  wb_motor_set_velocity(wheel_3, 0);
  }
  
  }
  
  
  
     
        
   
  while (wb_robot_step(TIME_STEP) != -1) {
  
  key = wb_keyboard_get_key();
  
  
   if(key == 'W'){
    x = 1;
    y = 0;
    //printf("Manual mode \n");
  } 
  
  else if (key == 'G'){
    y = 1;
    x = 0;
   //printf("Automatic mode \n");
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
