
//Implemented in file MMC5883L.cpp compiled together with the mbed project.
void MMC5883L::getXYZ_OffsetRemoved_RAW(int16_t output[3])
{

    int16_t data_set[3];
    flipSet();
    wait_us(80); //it is suggested to wait for a while, so that the flip set/reset has time to settle
    getXYZ_RAW(data_set);
    flipReset();
    int16_t data_reset[3];
    wait_us(80);
    getXYZ_RAW(data_reset);

    for (int i = 0; i < 3; i++) {
        output[i] = (data_reset[i] - data_set[i]) / 2;
    }
}
