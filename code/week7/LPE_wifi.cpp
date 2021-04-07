#include "mbed.h"
#include <algorithm>
Serial device(PA_2, PA_3); // tx, rx
AnalogIn ain1(PA_5);
AnalogIn ain2(PA_6);
DigitalOut LEDgreen(PA_4);

bool ntc_active = false, foto_active = false;

int main()
{
    device.baud(115200);// nastavení „baudrate“ - pøenosové rychlosti 115200 Baud

    device.printf("\e]27;2;5\n\e\\"); //five buttons
    //confugre their label
    device.printf("\e]28;1;LED on\n\e\\");
    device.printf("\e]28;2;LED off\n\e\\");
    device.printf("\e]28;3;NTC\n\e\\");
    device.printf("\e]28;4;foto\n\e\\");
    device.printf("\e]28;5;light\n\e\\");

    //and initialize colors for buttons 1-4. Button 5 is update regularly
    device.printf("\e]30;1;#00ff00\n\e\\");
    device.printf("\e]30;2;#ff0000\n\e\\");
    device.printf("\e]30;3;#ff0000\n\e\\");
    device.printf("\e]30;4;#ff0000\n\e\\");
    while (1) {
        unsigned const sense1 = ain1.read_u16() / 20; // pøeètení jednoho vstupu 0...65535 odpovídá 0...3300 mV
        wait(0.05); // ms
        unsigned const sense2 = ain2.read_u16() / 20; // pøeètení druhého vstupu
        device.printf("                          \r"); //"clear line" in the terminal
        //If a measurement is activated, print the result to terminal
        if (ntc_active)
            device.printf("NTC: %04u mV ", sense1);
        if (foto_active)
            device.printf("foto: %04u mV", sense2);
        device.printf("\r");
        char buffer[16] = { 0 };
        //Construct escape sequence for illumination indication color.
        sprintf(buffer, "%02x%02x00", 0xff - (int)(sense2 / 3300.0 * 0xff), (int)(sense2 / 3300.0 * 0xff));
        //Nibbles in red, green and blue component are swapped (the least significant nibble is first and the most significant second)
        std::swap(buffer[0], buffer[1]);
        std::swap(buffer[2], buffer[3]);

        //update the displayed color of button 5 (illumination indicator)
        device.printf("\e]30;5;#%s\n\e\\", buffer);


        //odeslání dvou èárkou oddìlených hodnot, napøíklad „2000,0099+zaèátek øádku“
        wait(0.05); // ms
        if (device.readable()) { //je k dispozici novy prikaz?
            char const comIN = device.getc(); //je, tak ho nacti
            switch (comIN) { //a podle toho co prislo, proved danou akci
            case 1:
                LEDgreen = 1;
                break;
            case 2:
                LEDgreen = 0;
                break;
            case 3: //button 3 .. (de)activation of NTC measurements
                ntc_active = !ntc_active;
                device.printf(ntc_active ? "\e]30;3;#00ff00\n\e\\" : "\e]30;3;#ff0000\n\e\\");
                break;
            case 4: //button 4 .. (de)activation of phototransistor measurements
                foto_active = !foto_active;
                device.printf(foto_active ? "\e]30;4;#00ff00\n\e\\" : "\e]30;4;#ff0000\n\e\\");
                break;
            default: //kdyz prijde neznamy znak, provede se „default“ cast kodu
                break;
            };//switch
        };//if
    };// while(1)
};//int main
