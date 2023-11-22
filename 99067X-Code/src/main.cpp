#include "main.h"
using namespace pros;
using namespace std;

// pros::Task* task = nullptr;
// void initializeCata();

void drive(int left, int right);
// Motors
// fl - front left
// fr - front right
// bl - back left
// br - back right
// Motor {motor_name}({port_number},E_MOTOR_GEARSET_{motor_type},{1_or_0}, E_MOTOR_ENCODER_COUNTS);
Motor fl_drive(15,E_MOTOR_GEARSET_06,1, E_MOTOR_ENCODER_COUNTS);
Motor bl_drive(18,E_MOTOR_GEARSET_06,1, E_MOTOR_ENCODER_COUNTS);
Motor fr_drive(16,E_MOTOR_GEARSET_06,0, E_MOTOR_ENCODER_COUNTS);
Motor br_drive(19,E_MOTOR_GEARSET_06,0, E_MOTOR_ENCODER_COUNTS);

Motor cata(5,E_MOTOR_GEARSET_18,0, E_MOTOR_ENCODER_COUNTS);
Motor cata2(3,E_MOTOR_GEARSET_18,1, E_MOTOR_ENCODER_COUNTS);
// Inertial sensor
Imu imu_sensor(18);
// Adding a piston:
ADIDigitalIn CataLimit('A');
// Detects presses on the start button
void on_center_button() {
    static bool pressed = false;
    pressed = !pressed;
    if (pressed) {
        lcd::set_text(2, "I was pressed!");
    } else {
        lcd::clear_line(2);
    }
}
// The first steps, gets the rest of the program ready
void initialize() {
    lcd::initialize();
    lcd::set_text(1, "\"I KNOW WORDS, I JUST DON'T KNOW HOW TO USE THEM\" - K Y L E R");
    lcd::register_btn1_cb(on_center_button);
}
// Main loop, code runs while the program is running on the controller
void opcontrol() {
    Controller master(E_CONTROLLER_MASTER);
    // Main loop
    while (true) {
        // Back buttons controls template
        // R1 R2 L1 L2
        
        if (CataLimit.get_value() == false){
            cata.move(80);
            cata2.move(80);
        }
        else if (master.get_digital(DIGITAL_R1)){
            cata.move(80);
            cata2.move(80);
        } else {
            cata.move(0);
            cata2.move(0);
        }
        if (master.get_digital(DIGITAL_R2)){
            drive(-15,-15);
        }
    else{
         // Gets the x and y values L2 or the joystick on the controller
        int yval = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
        int xval = master.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
        
        // Drives the robot with the amount choose on the controller joystick
        drive(yval+xval, yval-xval);
    }

        
        // Arrow keys controls template
        // RIGHT LEFT UP DOWN
        // if(master.get_digital_new_press(DIGITAL_RIGHT)){
		
        // }
		
       
    }
    delay(15);
}

// The drive function, moves the 4 motors on the drive train
void drive(int left, int right){
    // Left side
    fl_drive.move(left);
    bl_drive.move(left);
    // Right side
    fr_drive.move(right);
    br_drive.move(right);
}

// Autonomous for first 15 seconds of a match, match - 15 seconds autonomous and 1:45 second driver control
// Volts - Between 0 and 127 
// Examples - motor.move(0-127) or drive(0-127, 0-127)
// 1000 milliseconds == 1 second   
// delay(milliseconds) so delay(500) delays for .5 seconds and delay(2000) delays for 2 seconds
void autonomous() { 
    // cata.move(80);
    // delay(500);
    // cata.move(0);
    // or
    // drive(80,80);
    // delay(500);
    // drive(0,0);
    drive(40,40);
    delay(1850);
    drive(-40,40);
    delay(410);
    drive(90,90);
    delay(500);
    drive(-40,0);
    delay(500);
    drive(0,0);
}

// void initializeCata(){
//     if(task == nullptr){
//         pros::Task task{[=] {
//             Controller master(E_CONTROLLER_MASTER);
            
    
//     }};}

// }
