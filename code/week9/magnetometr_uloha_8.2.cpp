#include "mbed.h"
#include "SSD1306_mini.h"
#include "MMC5883L.h"

MMC5883L compass(PF_0, PF_1);
Serial pc(PA_2, PA_3); // tx, rx

int main() {

    wait(0.1f);
    compass.init();
    wait(0.1f);
    int16_t data[3] = { 0,0,0 };

    pc.baud(9600);

    while (1) {
        compass.getXYZ_OffsetRemoved_nT(data);

        float const Btot = sqrt(pow((double)data[0], 2) + pow((double)data[1], 2) + pow((double)data[2], 2));

        pc.printf("X=%d Y=%d Z=%d, Btot=%.2f\r\n", data[0], data[1], data[2], Btot);

        wait(0.1f); //100 ms delay
    }
}
