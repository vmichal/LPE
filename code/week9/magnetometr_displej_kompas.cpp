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


    while (1) {
        int16_t _[3];
        double const heading = compass.getHeadingXY(_);


        int16_t compassRadius = gOled1.height() / 2 - 1;
        int16_t compassCenterX = gOled1.width() / 2;
        int16_t compassCenterY = gOled1.height() / 2;

        gOled1.clearDisplay();
        gOled1.setTextCursor(0, 0);
        gOled1.printf("MMC5883        kompas\r\n");


        gOled1.drawCircle(compassCenterX, compassCenterY, compassRadius, WHITE);
        gOled1.fillCircle(compassCenterX, compassCenterY, 2, WHITE);

        gOled1.drawLine(compassCenterX, compassCenterY + 18, compassCenterX, compassCenterY + 20, WHITE);
        gOled1.drawLine(compassCenterX, compassCenterY - 18, compassCenterX, compassCenterY - 20, WHITE);
        gOled1.drawLine(compassCenterX + 18, compassCenterY, compassCenterX + 20, compassCenterY, WHITE);
        gOled1.drawLine(compassCenterX - 18, compassCenterY, compassCenterX - 20, compassCenterY, WHITE);

        double x_vect = cos(heading) * compassRadius;
        double y_vect = sin(heading) * compassRadius;

        gOled1.drawLine(compassCenterX, compassCenterY, (int16_t)(compassCenterX + x_vect), (int16_t)(compassCenterY - y_vect), WHITE);

        gOled1.setTextCursor(compassCenterX - 2, compassCenterY - compassRadius);
        gOled1.printf("S");
        gOled1.setTextCursor(compassCenterX - 2, compassCenterY + compassRadius - 7);
        gOled1.printf("J");
        gOled1.setTextCursor(compassCenterX - compassRadius - 2, compassCenterY - 3);
        gOled1.printf("Z");
        gOled1.setTextCursor(compassCenterX + compassRadius - 2, compassCenterY - 3);
        gOled1.printf("V");

        gOled1.setTextCursor(0, gOled1.height() - 18);
        gOled1.printf("FEL");
        gOled1.setTextCursor(17 * 6, gOled1.height() - 18);
        gOled1.printf("CVUT");

        gOled1.setTextCursor(0, gOled1.height() - 8);
        gOled1.printf("LPE");
        gOled1.setTextCursor(17 * 6, gOled1.height() - 8);
        gOled1.printf("2021");

        gOled1.display();

        wait(0.1f);
    }
}
