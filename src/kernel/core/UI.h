#ifndef UI_H
#define UI_H

#include "Arduino.h"
#include <TFT_eSPI.h>
#include "GyverButton.h"
#include "task.h"

#define BT1_PIN 21
#define BT2_PIN 22
#define menuItemCnt 5

extern TFT_eSPI tft;
extern TaskScheduler scheduler;
GButton bt1(BT1_PIN);
GButton bt2(BT2_PIN);

class UserInterface {

    static void taskManagerWrapper();
private:
    bool bt_state = false;
    uint8_t menuPos = 0;
    uint8_t taskCount = 0;

public:
    static UserInterface* instance;

    void setStartSetup(){
        bt1.setType(HIGH_PULL);
        bt2.setType(HIGH_PULL);
        bt1.setDirection(NORM_CLOSE);
        bt2.setDirection(NORM_CLOSE);
        bt1.setTimeout(700);   
        bt2.setTimeout(700); 
    }
    void TaskManagerIco() {
        tft.drawRoundRect(30, 70, 180, 140, 10, TFT_WHITE);
        tft.setCursor(40, 80);
        tft.print("Task Manager  ");
    }

    void BleIco(){
        tft.drawRoundRect(30, 70, 180, 140, 10, TFT_WHITE);
        tft.setCursor(40, 80);
        tft.print("BLE           ");
    }

    void WifiIco(){
        tft.drawRoundRect(30, 70, 180, 140, 10, TFT_WHITE);
        tft.setCursor(40, 80);
        tft.print("WiFi          ");
    }

    void LoraIco(){
        tft.drawRoundRect(30, 70, 180, 140, 10, TFT_WHITE);
        tft.setCursor(40, 80);
        tft.print("Lora          ");
    }

    void ComingSoon(){
        tft.drawRoundRect(30, 70, 180, 140, 10, TFT_WHITE);
        tft.setCursor(40, 80);
        tft.print("Coming soon...");
    }

    void drawMenu() {
        //tft.setCursor(0, 20);
        //tft.print(menuPos);
        bt1.tick();
        bt2.tick();
        if(bt1.isHolded()){
            tft.fillScreen(TFT_BLACK);
            switch(menuPos){
                case 0: scheduler.addTask(UserInterface::taskManagerWrapper, "Task Manager");
                        scheduler.endTask(scheduler.findIndexTask("User Interface"));
                        break;
            }
        } else{
            switch(menuPos){
                case 0: TaskManagerIco();
                        break;
                case 1: BleIco();
                        break;
                case 2: WifiIco();
                        break;
                case 3: LoraIco();
                        break;
                case 4: ComingSoon();
                        break;
                default: ComingSoon();

                    //default: ComingSoon();
            } 
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

    void taskManager(){  // task manager
        tft.setCursor(0, 0);
        tft.println("Task manager");
        tft.drawFastHLine(0, 10, 240, TFT_WHITE);
        taskCount = scheduler.getActiveTaskCount();
        for(int i = 0; i < taskCount; i++){
            tft.setCursor(0, i*10 + 12);
            tft.print(scheduler.getTaskName(i));
        }
    }
};

#endif
UserInterface* UserInterface::instance = nullptr;

void UserInterface::taskManagerWrapper() {
    if (instance) instance->taskManager();
}