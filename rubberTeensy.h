/* rubberTeensy by ohxeighty. 
 * https://ohxeighty.github.io
 * This header file along with the accompanying cpp file should be placed 
 * inside your arduino libraries directory. 
 */

#ifndef rubberTeensy
#define rubberTeensy

#include "Arduino.h"




class RubberTeensy{
    public:
        RubberTeensy(int delayMs=100, int ledPin=13, int initDelay=100);

        void SetDelay(int delay);
        void SetLEDPin(int pin);
        int GetDelay();
        int8_t GetLEDPin();

        /* Helper Functions */
        void OpenCMD(bool admin=0, int8_t method=0); 
        void HideCurWindow(); 
        void RepeatKey(char key, int repeat);  
        void Blink(int duration); 

        /* Evil */ 
        void AddUser(char *username, char *pass, bool admin=0); 
        void Shutdown(); 
    private:
        int _delay; 
        int8_t _LED_Pin; 
};
#endif
