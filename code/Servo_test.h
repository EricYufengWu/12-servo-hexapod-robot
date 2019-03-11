 /*************************************************** 
Servo code for 12-channel hexapod.
Modified from Adafruit tutorial on 12-channel servo driver
install "Adafruit_PWMServoDriver" library in ArduinoIDE
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(&Wire, 0x40);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define MIN  280
#define MAX  380
#define BASEMIN  310 // this is the 'minimum' pulse length count (out of 4096)
#define BASEMAX  350 // this is the 'maximum' pulse length count (out of 4096)
#define LEGMIN  260
#define LEGMAX  300
#define MID_ALL  330
#define MID_LEG  300
#define MOVEVAL  20
int MID[] = {345,345,355,328,355,320,303,275,305,295,265,290};
/*            0   1   2   3   4   5   6   7   8   9  10  11        */
/*           horn turns clockwise: less value                      */

// our servo # counter
uint8_t servonum = 0;
uint8_t center_pos = 200;

void reset_pos(){
    delay(100);
    for (int i = 0; i < 12; i++) {
        pwm.setPWM(i, 0, MID[i]);
    }
}



//drives hex forward
void forward(int dur){

    for (int i = 0; i < dur; i++){
        for (uint16_t pulselen = BASEMIN; pulselen < MID_ALL; pulselen++) {
            pwm.setPWM(0, 0, pulselen - (MID_ALL - MID[0]) - 60);
            pwm.setPWM(2, 0, pulselen - (MID_ALL - MID[2]) + 60);
            pwm.setPWM(3, 0, pulselen - (MID_ALL - MID[3]) - 60);
            pwm.setPWM(5, 0, pulselen - (MID_ALL - MID[5]) + 60);
            pwm.setPWM(1, 0, BASEMAX - (pulselen + (MID_ALL - MID[1]) - BASEMIN));
            pwm.setPWM(4, 0, BASEMAX - (pulselen + (MID_ALL - MID[4]) - BASEMIN));
            
            
            pwm.setPWM(6, 0, LEGMAX - (pulselen + (MID_ALL - MID[6]) + (pulselen - BASEMIN - 30)*1.2 - BASEMIN) - 150);
            pwm.setPWM(8, 0, BASEMAX - (pulselen + (MID_ALL - MID[8]) + (pulselen - BASEMIN - 30)*1.2 - BASEMIN) - 150);
            pwm.setPWM(10, 0, BASEMAX - (pulselen + (MID_ALL - MID[10]) + (pulselen - BASEMIN - 30)*1.2 - BASEMIN) - 210);              
        }

        for (uint16_t pulselen = MID_ALL; pulselen < BASEMAX; pulselen++) {
            pwm.setPWM(0, 0, pulselen - (MID_ALL - MID[0]) - 60);
            pwm.setPWM(2, 0, pulselen - (MID_ALL - MID[2]) + 60);
            pwm.setPWM(3, 0, pulselen - (MID_ALL - MID[3]) - 60);
            pwm.setPWM(5, 0, pulselen - (MID_ALL - MID[5]) + 60);
            pwm.setPWM(1, 0, BASEMAX - (pulselen + (MID_ALL - MID[1]) - BASEMIN));
            pwm.setPWM(4, 0, BASEMAX - (pulselen + (MID_ALL - MID[4]) - BASEMIN));

            pwm.setPWM(6, 0, pulselen + (MID_ALL - MID[6]) + (pulselen - BASEMIN + 30)*1.2 - 150);
            pwm.setPWM(8, 0, pulselen + (MID_ALL - MID[8]) + (pulselen - BASEMIN + 30)*1.2 - 150);
            pwm.setPWM(10, 0,pulselen + (MID_ALL - MID[10]) + (pulselen - BASEMIN + 30)*1.2 - 210);   
        }

        delay(100);
        for (uint16_t pulselen = BASEMAX; pulselen > MID_ALL; pulselen--) {
            pwm.setPWM(0, 0, pulselen - (MID_ALL - MID[0]) - 60);
            pwm.setPWM(2, 0, pulselen - (MID_ALL - MID[2]) + 60);
            pwm.setPWM(3, 0, pulselen - (MID_ALL - MID[3]) - 60);
            pwm.setPWM(5, 0, pulselen - (MID_ALL - MID[5]) + 60);
            pwm.setPWM(1, 0, BASEMIN + (BASEMAX - (pulselen + (MID_ALL - MID[1]))));
            pwm.setPWM(4, 0, BASEMIN + (BASEMAX - (pulselen + (MID_ALL - MID[4]))));
 
            pwm.setPWM(7, 0, pulselen - (BASEMAX - pulselen - 30)*1.2 - 150);
            pwm.setPWM(9, 0, pulselen - (BASEMAX - pulselen - 30)*1.2 - 135);
            pwm.setPWM(11, 0, pulselen - (BASEMAX - pulselen - 30)*1.2 - 150);  
        }
        for (uint16_t pulselen = MID_ALL; pulselen > BASEMIN; pulselen--) {
            pwm.setPWM(0, 0, pulselen - (MID_ALL - MID[0]) - 60);
            pwm.setPWM(2, 0, pulselen - (MID_ALL - MID[2]) + 60);
            pwm.setPWM(3, 0, pulselen - (MID_ALL - MID[3]) - 60);
            pwm.setPWM(5, 0, pulselen - (MID_ALL - MID[5]) + 60);
            pwm.setPWM(1, 0, BASEMIN + (BASEMAX - (pulselen + (MID_ALL - MID[1]))));
            pwm.setPWM(4, 0, BASEMIN + (BASEMAX - (pulselen + (MID_ALL - MID[4]))));

                
            pwm.setPWM(7, 0, BASEMAX - (pulselen - (BASEMAX - pulselen + 30)*1.2 - BASEMIN) - 150);
            pwm.setPWM(9, 0, BASEMAX - (pulselen - (BASEMAX - pulselen + 30)*1.2 - BASEMIN) - 135);
            pwm.setPWM(11, 0, BASEMAX - (pulselen - (BASEMAX - pulselen + 30)*1.2 - BASEMIN) - 150);      
        }
        delay(100);
    }
}
  
//3 and 5 switched sign b4 60
//legs - 60

//drives hex backward
void backward(int dur){

    for (int i = 0; i < dur; i++){
        for (uint16_t pulselen = BASEMIN; pulselen < MID_ALL; pulselen++) {
            pwm.setPWM(0, 0, BASEMAX - (pulselen + (MID_ALL - MID[0]) - BASEMIN) - 60);
            pwm.setPWM(2, 0, BASEMAX - (pulselen + (MID_ALL - MID[2]) - BASEMIN) + 60);
            pwm.setPWM(3, 0, BASEMAX - (pulselen + (MID_ALL - MID[3]) - BASEMIN) - 60);
            pwm.setPWM(5, 0, BASEMAX - (pulselen + (MID_ALL - MID[5]) - BASEMIN) + 60);
            pwm.setPWM(1, 0, pulselen - (MID_ALL - MID[1]));
            pwm.setPWM(4, 0, pulselen - (MID_ALL - MID[4]));
            
            pwm.setPWM(6, 0, BASEMAX - (pulselen + (MID_ALL - MID[6]) + (pulselen - BASEMIN - 30)*1.2 - BASEMIN) - 150);
            pwm.setPWM(8, 0, BASEMAX - (pulselen + (MID_ALL - MID[8]) + (pulselen - BASEMIN - 30)*1.2 - BASEMIN) - 150);
            pwm.setPWM(10, 0, BASEMAX - (pulselen + (MID_ALL - MID[10]) + (pulselen - BASEMIN - 30)*1.2 - BASEMIN) - 210);          
        }

        for (uint16_t pulselen = MID_ALL; pulselen < BASEMAX; pulselen++) {
            pwm.setPWM(0, 0, BASEMAX - (pulselen + (MID_ALL - MID[0]) - BASEMIN) - 60);
            pwm.setPWM(2, 0, BASEMAX - (pulselen + (MID_ALL - MID[2]) - BASEMIN) + 60);
            pwm.setPWM(3, 0, BASEMAX - (pulselen + (MID_ALL - MID[3]) - BASEMIN) - 60);
            pwm.setPWM(5, 0, BASEMAX - (pulselen + (MID_ALL - MID[5]) - BASEMIN) + 60);
            pwm.setPWM(1, 0, pulselen - (MID_ALL - MID[1]));
            pwm.setPWM(4, 0, pulselen - (MID_ALL - MID[4]));

            pwm.setPWM(6, 0, pulselen + (MID_ALL - MID[6]) + (pulselen - BASEMIN + 30)*1.2 - 150);
            pwm.setPWM(8, 0, pulselen + (MID_ALL - MID[8]) + (pulselen - BASEMIN + 30)*1.2 - 150);
            pwm.setPWM(10, 0,pulselen + (MID_ALL - MID[10]) + (pulselen - BASEMIN + 30)*1.2 - 210);        
        }

        delay(100);
        for (uint16_t pulselen = BASEMAX; pulselen > MID_ALL; pulselen--) {
            pwm.setPWM(0, 0, BASEMIN + (BASEMAX - (pulselen + (MID_ALL - MID[0]))) - 60);
            pwm.setPWM(2, 0, BASEMIN + (BASEMAX - (pulselen + (MID_ALL - MID[2]))) + 60);
            pwm.setPWM(3, 0, BASEMIN + (BASEMAX - (pulselen + (MID_ALL - MID[3]))) - 60);
            pwm.setPWM(5, 0, BASEMIN + (BASEMAX - (pulselen + (MID_ALL - MID[5]))) + 60);
            pwm.setPWM(1, 0, pulselen - (MID_ALL - MID[1]));
            pwm.setPWM(4, 0, pulselen - (MID_ALL - MID[4]));
 
            pwm.setPWM(7, 0, pulselen - (BASEMAX - pulselen - 30)*1.2 - 150);
            pwm.setPWM(9, 0, pulselen - (BASEMAX - pulselen - 30)*1.2 - 150);
            pwm.setPWM(11, 0, pulselen - (BASEMAX - pulselen - 30)*1.2 - 150);
        }
        for (uint16_t pulselen = MID_ALL; pulselen > BASEMIN; pulselen--) {
            pwm.setPWM(0, 0, BASEMIN + (BASEMAX - (pulselen + (MID_ALL - MID[0]))) - 60);
            pwm.setPWM(2, 0, BASEMIN + (BASEMAX - (pulselen + (MID_ALL - MID[2]))) + 60);
            pwm.setPWM(3, 0, BASEMIN + (BASEMAX - (pulselen + (MID_ALL - MID[3]))) - 60);
            pwm.setPWM(5, 0, BASEMIN + (BASEMAX - (pulselen + (MID_ALL - MID[5]))) + 60);
            pwm.setPWM(1, 0, pulselen - (MID_ALL - MID[1]));
            pwm.setPWM(4, 0, pulselen - (MID_ALL - MID[4]));

            pwm.setPWM(7, 0, BASEMAX - (pulselen - (BASEMAX - pulselen + 30)*1.2 - BASEMIN) - 150);
            pwm.setPWM(9, 0, BASEMAX - (pulselen - (BASEMAX - pulselen + 30)*1.2 - BASEMIN) - 150);
            pwm.setPWM(11, 0, BASEMAX - (pulselen - (BASEMAX - pulselen + 30)*1.2 - BASEMIN) - 150);            
        }
        delay(100);
    }
}



void right(int dur){

    for (int i = 0; i < dur; i++){
        for (uint16_t pulselen = BASEMIN; pulselen < MID_ALL; pulselen++) {
            pwm.setPWM(0, 0, pulselen - (MID_ALL - MID[0]));
            pwm.setPWM(2, 0, pulselen - (MID_ALL - MID[2]));
            pwm.setPWM(4, 0, pulselen - (MID_ALL - MID[4]));
            pwm.setPWM(1, 0, BASEMAX - (pulselen + (MID_ALL - MID[1]) - BASEMIN));
            pwm.setPWM(3, 0, BASEMAX - (pulselen + (MID_ALL - MID[3]) - BASEMIN));
            pwm.setPWM(5, 0, BASEMAX - (pulselen + (MID_ALL - MID[5]) - BASEMIN));
            
            pwm.setPWM(6, 0, BASEMAX - (pulselen + (MID_ALL - MID[6]) + (pulselen - BASEMIN - 30)*1.2 - BASEMIN) - 150);
            pwm.setPWM(8, 0, BASEMAX - (pulselen + (MID_ALL - MID[8]) + (pulselen - BASEMIN - 30)*1.2 - BASEMIN) - 150);
            pwm.setPWM(10, 0, BASEMAX - (pulselen + (MID_ALL - MID[10]) + (pulselen - BASEMIN - 30)*1.2 - BASEMIN) - 210);         
        }

        for (uint16_t pulselen = MID_ALL; pulselen < BASEMAX; pulselen++) {
            pwm.setPWM(0, 0, pulselen - (MID_ALL - MID[0]));
            pwm.setPWM(2, 0, pulselen - (MID_ALL - MID[2]));
            pwm.setPWM(4, 0, pulselen - (MID_ALL - MID[4]));
            pwm.setPWM(1, 0, BASEMAX - (pulselen + (MID_ALL - MID[1]) - BASEMIN));
            pwm.setPWM(3, 0, BASEMAX - (pulselen + (MID_ALL - MID[3]) - BASEMIN));
            pwm.setPWM(5, 0, BASEMAX - (pulselen + (MID_ALL - MID[5]) - BASEMIN));
             
            pwm.setPWM(6, 0, pulselen + (MID_ALL - MID[6]) + (pulselen - BASEMIN + 30)*1.2 - 150);
            pwm.setPWM(8, 0, pulselen + (MID_ALL - MID[8]) + (pulselen - BASEMIN + 30)*1.2 - 150);
            pwm.setPWM(10, 0,pulselen + (MID_ALL - MID[10]) + (pulselen - BASEMIN + 30)*1.2 - 210);       
        }

        delay(100);
        for (uint16_t pulselen = BASEMAX; pulselen > MID_ALL; pulselen--) {
            pwm.setPWM(0, 0, pulselen - (MID_ALL - MID[0]));
            pwm.setPWM(2, 0, pulselen - (MID_ALL - MID[2]));
            pwm.setPWM(4, 0, pulselen - (MID_ALL - MID[4]));
            pwm.setPWM(1, 0, BASEMIN + (BASEMAX - (pulselen + (MID_ALL - MID[1]))));
            pwm.setPWM(3, 0, BASEMIN + (BASEMAX - (pulselen + (MID_ALL - MID[3]))));
            pwm.setPWM(5, 0, BASEMIN + (BASEMAX - (pulselen + (MID_ALL - MID[5]))));

            pwm.setPWM(7, 0, pulselen - (BASEMAX - pulselen - 30)*1.2 - 150);
            pwm.setPWM(9, 0, pulselen - (BASEMAX - pulselen - 30)*1.2 - 135);
            pwm.setPWM(11, 0, pulselen - (BASEMAX - pulselen - 30)*1.2 - 150); 
        }
        for (uint16_t pulselen = MID_ALL; pulselen > BASEMIN; pulselen--) {
            pwm.setPWM(0, 0, pulselen - (MID_ALL - MID[0]));
            pwm.setPWM(2, 0, pulselen - (MID_ALL - MID[2]));
            pwm.setPWM(4, 0, pulselen - (MID_ALL - MID[4]));
            pwm.setPWM(1, 0, BASEMIN + (BASEMAX - (pulselen + (MID_ALL - MID[1]))));
            pwm.setPWM(3, 0, BASEMIN + (BASEMAX - (pulselen + (MID_ALL - MID[3]))));
            pwm.setPWM(5, 0, BASEMIN + (BASEMAX - (pulselen + (MID_ALL - MID[5]))));
             
            pwm.setPWM(7, 0, BASEMAX - (pulselen - (BASEMAX - pulselen + 30)*1.2 - BASEMIN) - 150);
            pwm.setPWM(9, 0, BASEMAX - (pulselen - (BASEMAX - pulselen + 30)*1.2 - BASEMIN) - 135);
            pwm.setPWM(11, 0, BASEMAX - (pulselen - (BASEMAX - pulselen + 30)*1.2 - BASEMIN) - 150);           
        }
        delay(100);
    }
}



void left(int dur){

    for (int i = 0; i < dur; i++){
        for (uint16_t pulselen = BASEMIN; pulselen < MID_ALL; pulselen++) {
            pwm.setPWM(1, 0, pulselen - (MID_ALL - MID[1]));
            pwm.setPWM(3, 0, pulselen - (MID_ALL - MID[3]));
            pwm.setPWM(5, 0, pulselen - (MID_ALL - MID[5]));
            pwm.setPWM(0, 0, BASEMAX - (pulselen + (MID_ALL - MID[0]) - BASEMIN));
            pwm.setPWM(2, 0, BASEMAX - (pulselen + (MID_ALL - MID[2]) - BASEMIN));
            pwm.setPWM(4, 0, BASEMAX - (pulselen + (MID_ALL - MID[4]) - BASEMIN));
            
            pwm.setPWM(6, 0, BASEMAX - (pulselen + (MID_ALL - MID[6]) + (pulselen - BASEMIN - 30)*1.2 - BASEMIN) - 150);
            pwm.setPWM(8, 0, BASEMAX - (pulselen + (MID_ALL - MID[8]) + (pulselen - BASEMIN - 30)*1.2 - BASEMIN) - 150);
            pwm.setPWM(10, 0, BASEMAX - (pulselen + (MID_ALL - MID[10]) + (pulselen - BASEMIN - 30)*1.2 - BASEMIN) - 210);         
        }

        for (uint16_t pulselen = MID_ALL; pulselen < BASEMAX; pulselen++) {
            pwm.setPWM(1, 0, pulselen - (MID_ALL - MID[1]));
            pwm.setPWM(3, 0, pulselen - (MID_ALL - MID[3]));
            pwm.setPWM(5, 0, pulselen - (MID_ALL - MID[5]));
            pwm.setPWM(0, 0, BASEMAX - (pulselen + (MID_ALL - MID[0]) - BASEMIN));
            pwm.setPWM(2, 0, BASEMAX - (pulselen + (MID_ALL - MID[2]) - BASEMIN));
            pwm.setPWM(4, 0, BASEMAX - (pulselen + (MID_ALL - MID[4]) - BASEMIN));

             
            pwm.setPWM(6, 0, pulselen + (MID_ALL - MID[6]) + (pulselen - BASEMIN + 30)*1.2 - 150);
            pwm.setPWM(8, 0, pulselen + (MID_ALL - MID[8]) + (pulselen - BASEMIN + 30)*1.2 - 150);
            pwm.setPWM(10, 0,pulselen + (MID_ALL - MID[10]) + (pulselen - BASEMIN + 30)*1.2 - 210);      
        }

        delay(100);
        for (uint16_t pulselen = BASEMAX; pulselen > MID_ALL; pulselen--) {
            pwm.setPWM(1, 0, pulselen - (MID_ALL - MID[1]));
            pwm.setPWM(3, 0, pulselen - (MID_ALL - MID[3]));
            pwm.setPWM(5, 0, pulselen - (MID_ALL - MID[5]));
            pwm.setPWM(0, 0, BASEMIN + (BASEMAX - (pulselen + (MID_ALL - MID[0]))));
            pwm.setPWM(2, 0, BASEMIN + (BASEMAX - (pulselen + (MID_ALL - MID[2]))));
            pwm.setPWM(4, 0, BASEMIN + (BASEMAX - (pulselen + (MID_ALL - MID[4]))));
 
            pwm.setPWM(7, 0, pulselen - (BASEMAX - pulselen - 30)*1.2 - 150);
            pwm.setPWM(9, 0, pulselen - (BASEMAX - pulselen - 30)*1.2 - 135);
            pwm.setPWM(11, 0, pulselen - (BASEMAX - pulselen - 30)*1.2 - 150);    
        }
        for (uint16_t pulselen = MID_ALL; pulselen > BASEMIN; pulselen--) {
            pwm.setPWM(1, 0, pulselen - (MID_ALL - MID[1]));
            pwm.setPWM(3, 0, pulselen - (MID_ALL - MID[3]));
            pwm.setPWM(5, 0, pulselen - (MID_ALL - MID[5]));
            pwm.setPWM(0, 0, BASEMIN + (BASEMAX - (pulselen + (MID_ALL - MID[0]))));
            pwm.setPWM(2, 0, BASEMIN + (BASEMAX - (pulselen + (MID_ALL - MID[2]))));
            pwm.setPWM(4, 0, BASEMIN + (BASEMAX - (pulselen + (MID_ALL - MID[4]))));

            pwm.setPWM(7, 0, BASEMAX - (pulselen - (BASEMAX - pulselen + 30)*1.2 - BASEMIN) - 150);
            pwm.setPWM(9, 0, BASEMAX - (pulselen - (BASEMAX - pulselen + 30)*1.2 - BASEMIN) - 135);
            pwm.setPWM(11, 0, BASEMAX - (pulselen - (BASEMAX - pulselen + 30)*1.2 - BASEMIN) - 150);        
        }
        delay(100);
    }
}
