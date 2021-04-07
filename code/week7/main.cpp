#include "mbed.h"
//Number of dutycycle steps for output wave
#define SINE_STEPS 8
//Frequency of output sine in Hz
#define SINE_OUT_FREQ 2000
//Constants to compute the sine waveform
#define PI 3.141592f
#define SINE_STEPS_RAD (2.0f * PI / (float)SINE_STEPS)
//Table to generate the sine waveform using dutycycles
float sine_duty[SINE_STEPS];


//Frequency of Pulse Width Modulated signal in Hz
#define PWM_FREQ 16000
//Ticker to update the PWM dutycycle
Ticker pwm_ticker;
Ticker data_readout_ticker;
AnalogIn adc_0(PA_5);
AnalogIn adc_1(PA_6);
DigitalOut ledka(PA_4);
PwmOut sound(PB_1);
Serial pc(PA_2, PA_3); // tx, rx

unsigned char status = 0;
float tim = 0;

//Ticker calls this fucntion to update the PWM dutycycle
void pwm_duty_updater()
{
    static int idx = 0;
    sound.write(sine_duty[idx]); // Set the dutycycle % to next value in array
    idx++; // Increment the idx
    if (idx == SINE_STEPS) idx = 0; // Reset the idx when teh end has been reached
}

void measure_and_transmit()
{
    //hrubý pøevod na mV...(65535/3300)
    unsigned const aread0 = adc_0.read_u16() / 20;
    unsigned const aread1 = adc_1.read_u16() / 20;


    float const v1 = aread0 / 1000.0f;
    float const v2 = aread1 / 1000.0f;

    if (status) {
        tim += 0.05;
        // pc.printf("%04u,%04u\r\n",aread0,aread1); //SerialChart
        pc.printf("$$P%.2f,%.3f,%.3f;", tim, v1, v2); //Data Plotter by Jiri Maier
    }
}


char buffer[20];
char comIN;


unsigned char i;
int main()
{
    pc.baud(9600);

    data_readout_ticker.attach(&measure_and_transmit, 1.0 / 20);

    for (i = 0; i < SINE_STEPS; i++) {
        sine_duty[i] = ((sin(i * SINE_STEPS_RAD)) * 0.8f + 1.0f) / 2.0f; // convert sine (-1.0 .. +1.0) into dutycycle (0.0 .. 1.0)
    }

    printf("PWM test & measure!\r\n");

    while (1) {

        if (pc.readable()) { //je k dispozici novy prikaz?
            comIN = pc.getc(); //je, tak ho nacti


            switch (comIN) { //a podle toho co prislo, proved danou akci
            case '0': //not sending data
                status = 0;
                printf("Off\r\n");
                break;
            case '1': //sending data
                status = 1;
                printf("On\r\n");
                break;
            case 'a': //LED off
                ledka = 0;
                printf("LED Off\r\n");
                break;
            case 's': //LED on
                ledka = 1;
                printf("LED On\r\n");
                break;

            case 'q': //generate PWM 2kHz
                printf("2 kHz PWM On\r\n");
                pwm_ticker.detach();
                sound.period(0.0005f);
                sound.write(0.5f);
                break;
            case 'r': //generate PWM 2kHz
                printf("16 kHz PWM On\r\n");
                pwm_ticker.detach();
                sound.period(0.0000625f);
                sound.write(0.5f);
                break;
            case 'w': //stop generating PWM
                pwm_ticker.detach();
                sound.write(0.0f);
                printf("Off\r\n");
                break;
            case 'e':
                pwm_ticker.detach();
                sound.period(0.00008f); // generate burst of 12500 Hz PWM
                sound.write(0.5f);
                wait(0.001); //
                sound.write(0.0f);
                printf("Burst\r\n");
                break;

            case 'n':
                sound.period(1.0f / (float)PWM_FREQ);
                pwm_ticker.attach(&pwm_duty_updater, 1.0f / (float)(SINE_STEPS * SINE_OUT_FREQ));


                printf("2kHz PWM sine On\r\n");
                break;
            case 'm':
                pwm_ticker.detach();
                sound.write(0.0);
                printf("Off\r\n");
                break;
            default: //kdyz prijde neznamy znak, provede se „default“ cast kodu
                break;
            };//switch
        };//if
        wait(0.05); // 50ms wait
    }
}