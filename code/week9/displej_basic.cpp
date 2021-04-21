#include "mbed.h"
#include "SSD1306_mini.h"
#include "MMC5883L.h"

SSD1306_mini_swspi gOled1(PA_5, PA_7, PA_3, PA_4, PA_2);
//SSD1306_mini_swspi(PinName D0, PinName D1, PinName DC, PinName RST, PinName CS)

MMC5883L compass(PF_0, PF_1);

int main() {

    wait(0.1f);
    compass.init();
    wait(0.1f);
    char axes[] = "XYZ";
    int32_t data[3] = { 0,0,0 };


    while (1) {
        compass.getXYZ_OffsetRemoved_nT(data);
        float const Btot = sqrt(pow((double)data[0], 2) + pow((double)data[1], 2) + pow((double)data[2], 2));

        gOled1.clearDisplay();
        for (int i = 0; i < 3; ++i) {
            gOled1.setTextCursor(0, 10 * i);
            gOled1.printf(" %c  = %8d [nT]\r\n", axes[i], data[i]);
        }
        gOled1.printf("|B| = %8d [nT]", (int)Btot);
        gOled1.display();

        wait(0.1f);
    }
}
