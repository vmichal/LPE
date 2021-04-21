#include "mbed.h"
#include "SSD1306_mini.h"
#include "MMC5883L.h"

SSD1306_mini_swspi gOled1(PA_5, PA_7, PA_3, PA_4, PA_2);
//SSD1306_mini_swspi(PinName D0, PinName D1, PinName DC, PinName RST, PinName CS)

MMC5883L compass(PF_0, PF_1);

struct vector {
    float x, y, z;
};

typedef vector matrix[3];

vector operator+(vector a, vector b) {
    return { a.x + b.x, a.y + b.y, a.z + b.z };
}

float operator*(vector a, vector b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

vector operator*(vector a, float coef) {
    return { a.x * coef, a.y * coef, a.z * coef };
}

vector transform(vector v, matrix A) {
    vector result;

    result.x = A[0] * v;
    result.y = A[1] * v;
    result.z = A[2] * v;

    return result;
}

int main() {

    wait(0.1f);
    compass.init();
    wait(0.1f);

    unsigned const centerY = gOled1.height() / 2;
    unsigned const centerX = gOled1.width() / 2;

    vector vertices[8] = {
        {-1, -1, -1},
        {1, -1, -1},
        {1, 1, -1},
        {-1, 1, -1},

        {-1, -1, 1},
        {1, -1, 1},
        {1, 1, 1},
        {-1, 1, 1},
    };

    for (int i = 0; i < 8; ++i) {
        vertices[i] = vertices[i] * (centerY / 2);
    }


    while (1) {
        int16_t data[3];
        compass.getXYZ_OffsetRemoved_RAW(data);
        vector camera = { data[0], data[1], data[2] };
        double const distance = sqrt(pow(camera.x, 2) + pow(camera.y, 2) + pow(camera.z, 2));
        camera = camera * (1000 / distance); //normalize camera's distance
        double const pitch = atan(camera.y / camera.x);
        double const heading = atan(sqrt(camera.y * camera.y + camera.x * camera.x) / camera.z);

        vector transformed[8];

        vector const x_transform = { cos(heading) * cos(pitch), -sin(heading), cos(heading) * sin(pitch) };
        vector const y_transform = { sin(heading), cos(heading), sin(heading) * sin(pitch) };
        vector const z_transform = { -sin(pitch), 0, cos(pitch) };

        matrix rotation = { x_transform, y_transform, z_transform };
        vector translation = { centerX, 0, centerY };



        gOled1.clearDisplay();
        gOled1.setTextCursor(0, 0);
        gOled1.printf("%.2f, %.2f", pitch * RAD_TO_DEG, heading * RAD_TO_DEG);
        gOled1.setTextCursor(0, gOled1.height() - 10);
        gOled1.printf("%d,%d,%d,%d", (int)camera.x, (int)camera.y, (int)camera.z, (int)sqrt(pow(camera.x, 2) + pow(camera.y, 2) + pow(camera.z, 2)));
        for (int i = 0; i < 8; ++i) {

            transformed[i] = transform(vertices[i], rotation) + translation;

        }

        //dolni podstava
        gOled1.drawLine(transformed[0].x, transformed[0].z, transformed[1].x, transformed[1].z, WHITE);
        gOled1.drawLine(transformed[2].x, transformed[2].z, transformed[1].x, transformed[1].z, WHITE);
        gOled1.drawLine(transformed[2].x, transformed[2].z, transformed[3].x, transformed[3].z, WHITE);
        gOled1.drawLine(transformed[0].x, transformed[0].z, transformed[3].x, transformed[3].z, WHITE);

        //horni podstava
        gOled1.drawLine(transformed[4 + 0].x, transformed[4 + 0].z, transformed[4 + 1].x, transformed[4 + 1].z, WHITE);
        gOled1.drawLine(transformed[4 + 2].x, transformed[4 + 2].z, transformed[4 + 1].x, transformed[4 + 1].z, WHITE);
        gOled1.drawLine(transformed[4 + 2].x, transformed[4 + 2].z, transformed[4 + 3].x, transformed[4 + 3].z, WHITE);
        gOled1.drawLine(transformed[4 + 0].x, transformed[4 + 0].z, transformed[4 + 3].x, transformed[4 + 3].z, WHITE);

        //vertical edges
        gOled1.drawLine(transformed[0].x, transformed[0].z, transformed[4 + 0].x, transformed[4 + 0].z, WHITE);
        gOled1.drawLine(transformed[1].x, transformed[1].z, transformed[4 + 1].x, transformed[4 + 1].z, WHITE);
        gOled1.drawLine(transformed[2].x, transformed[2].z, transformed[4 + 2].x, transformed[4 + 2].z, WHITE);
        gOled1.drawLine(transformed[3].x, transformed[3].z, transformed[4 + 3].x, transformed[4 + 3].z, WHITE);

        gOled1.display();

        wait(0.001f);
    }
}
