#ifndef UI_H
#define UI_H

#include "Arduino.h"
#include <TFT_eSPI.h>
#include "GyverButton.h"

#define BT1_PIN 21
#define BT2_PIN 22
#define menuItemCnt 3
extern TFT_eSPI tft;
GButton bt1(BT1_PIN);
GButton bt2(BT2_PIN);

class UserInterface {
private:
    bool bt_state = false;
    uint8_t menuPos = 0;

public:
    void setStartSetup(){
        bt1.setType(LOW_PULL);
        bt2.setType(LOW_PULL);
        bt1.setDirection(NORM_CLOSE);
        bt2.setDirection(NORM_CLOSE);
    }
    void TaskManagerIco() {
        tft.drawRoundRect(30, 70, 180, 140, 10, TFT_WHITE);
        tft.setCursor(40, 80);
        tft.print("Task Manager  ");
    }

    void ComingSoon(){
        tft.drawRoundRect(30, 70, 180, 140, 10, TFT_WHITE);
        tft.setCursor(40, 80);
        tft.print("Coming soon...");
    }

    void drawMenu() {
        tft.setCursor(0, 20);
        tft.print(menuPos);
        bt1.tick();
        bt2.tick();
        switch(menuPos){
            case 0: TaskManagerIco();
                    break;
            case 1: ComingSoon();
                    break;
            default: ComingSoon();

                //default: ComingSoon();
        } 
            if(bt1.isClick() && menuPos > 0){
                menuPos--;
                //tft.fillScreen(0);
            }
            if(bt2.isClick() && menuPos <= menuItemCnt){
                menuPos++;
                //tft.fillScreen(0);
            }
            if(menuPos > menuItemCnt){menuPos = menuItemCnt;}
            if(menuPos < 0){menuPos = 0;}
    }
};

#endif