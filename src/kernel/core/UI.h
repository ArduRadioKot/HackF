#ifndef UI_H
#define UI_H

#include "Arduino.h"
#include <TFT_eSPI.h>

#define BT1_PIN 21
#define BT2_PIN 22

extern TFT_eSPI tft;

class UserInterface {
private:
    bool bt_state = false;

public:
    void begin() {
        pinMode(BT1_PIN, INPUT);
        pinMode(BT2_PIN, INPUT);
    }

    // Сделаем публичным для доступа извне
    void drawTaskManagerIco() {
        /*tft.drawFastVLine(20, 20, 200, TFT_WHITE);
        tft.drawFastVLine(220, 20, 200, TFT_WHITE);
        tft.drawFastHLine(20, 20, 200, TFT_WHITE);
        tft.drawFastHLine(20, 220, 200, TFT_WHITE);*/
        tft.drawRoundRect(30, 70, 180, 140, 10, TFT_WHITE);
        tft.setCursor(40, 80);
        tft.print("Task Manager");

    }

    void drawMenu() {
        drawTaskManagerIco();
    }
};

#endif