/* rubberTeensy by ohxeighty.
 * https://ohxeighty.github.io
 * This cpp file along with the accompanying header file should be placed
 * inside your arduino libraries directory
 */

#include "Arduino.h"
#include "rubberTeensy.h"

/* Initialise instance of RubberTeensy */
RubberTeensy::RubberTeensy(int delayMs, int ledPin, int initDelay){
    _delay = delayMs;
    _LED_Pin = ledPin;
   // give some time for the usb to stop shitting itself  
    delay(initDelay); 
}

/* Set the base delay which most functions use a multiple of */ 
void RubberTeensy::SetDelay(int delay){
    _delay = delay;
}

/* Set the LED pin
 * https://www.pjrc.com/teensy/pinout.html
 * LED Pin:
 * Teensy 4.0: 13
 * Teensy 3.6: 13
 * Teensy 3.5: 13
 * Teensy 3.2: 13
 * Teensy 3.1: 13
 * Teensy 3.0: 13
 * Teensy LC: 13
 * Teensy 2.0: 11
 * Teensy++ 2.0: 6
 * Teensy 1.0: 6
 * Teensy++ 1.0: 6
 */
void RubberTeensy::SetLEDPin(int pin){
    pinMode(_LED_Pin, INPUT);
    pinMode(pin, OUTPUT); 
    _LED_Pin = pin; 
}

/* Get the current base delay */
int RubberTeensy::GetDelay(){
    return _delay;
}

/* Get the current LED pin */
int8_t RubberTeensy::GetLEDPin(){
    return _LED_Pin;
}

/* Open CMD and run command
 * Bool - Try open as admin if supported by method
 * Modes: 
 * 0 - Press the Windows Key (KEY_LEFT_GUI) to open the context key, 
 * type cmd, then press enter. Then type in command and press enter. 
 */
void RubberTeensy::OpenCMD(bool admin, int8_t method){
	Keyboard.begin(); 
    switch(method) {
	case 0:
		if(admin){
            Keyboard.write(KEY_LEFT_GUI); 
            delay(_delay); 
            Keyboard.print("cmd");
            Keyboard.press(KEY_LEFT_CTRL); 
            Keyboard.press(KEY_LEFT_SHIFT);
            Keyboard.press(KEY_RETURN);
            Keyboard.releaseAll();
            // Defaults to no selection 
            Keyboard.write(KEY_LEFT_ARROW);
            Keyboard.write(KEY_RETURN);
            delay(_delay);
        } else {
            Keyboard.write(KEY_LEFT_GUI);
            delay(_delay);
            Keyboard.println("cmd");
            delay(_delay);
        }
        break;	
	default:
		// no behaviour 
		break; 
    }
    Keyboard.end();
}

/* Hide the current window by dragging it down */ 
void RubberTeensy::HideCurWindow(){
    Keyboard.begin();
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(' ');
    Keyboard.releaseAll();
    Keyboard.write('m'); 
    Mouse.begin();
    Mouse.press();
    // mouse move signed char, -128 - 127 
    Mouse.move(0, 127); 
    Mouse.end(); 
    Keyboard.end();
    delay(_delay);
}

/* Repeat Keypress */
void RubberTeensy::RepeatKey(char key, int repeat){
    for(int i =0; i < repeat; i++){
        Keyboard.write(key); 
        delay(_delay/5); 
    }
}


void RubberTeensy::Blink(int duration){
    digitalWrite(_LED_Pin, HIGH); 
    delay(500); 
    digitalWrite(_LED_Pin, LOW); 
}
/* ==== EVIL ==== */ 

void RubberTeensy::AddUser(char *username, char *pass, bool admin){

}

void RubberTeensy::Shutdown(){

}


