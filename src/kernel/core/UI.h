#ifndef UI_H
#define UI_H

#include "Arduino.h"
#include <TFT_eSPI.h>
#include "GyverButton.h"
#include "task.h"

#define BT1_PIN 21
#define BT2_PIN 22
#define MenuItem 7
#define setCnt 5

extern TFT_eSPI tft;
extern TaskScheduler scheduler;
GButton bt1(BT1_PIN);
GButton bt2(BT2_PIN);

class UserInterface {

    static void taskManagerWrapper();
    static void userInterfaceWrapper();
    static void settingsWrapper();

private:
    bool bt_state = false;
    int8_t menuPosUI = 0;
    int8_t menuPosTM = 0;
    uint8_t taskCount = 0;
    String settingPar[setCnt] = {"System color"};
    String ico[MenuItem] = {"Task Manager", "IR", "BLE", "WiFi", "Lora", "RFID", "Settings"};
    String currentTask;
public:
    static UserInterface* instance;

    void setStartSetup(){
        bt1.setType(HIGH_PULL);
        bt2.setType(HIGH_PULL);
        bt1.setDirection(NORM_CLOSE);
        bt2.setDirection(NORM_CLOSE);
        bt1.setTimeout(1200);   
        bt2.setTimeout(1200); 
    }

    void drawMenu() {
        bt1.tick();
        bt2.tick();
 
        tft.drawRect(15 + (ico[menuPosUI].length() * 6), menuPosUI * 10 + 2, 5, 5, TFT_WHITE);
            if(bt1.isClick() && menuPosUI > 0){
                tft.drawRect(15 + (ico[menuPosUI].length() * 6), menuPosUI * 10 + 2, 5, 5, TFT_BLACK);
                menuPosUI--;
            }
            if(bt2.isClick() && menuPosUI <= MenuItem - 1){
                tft.drawRect(15 + (ico[menuPosUI].length() * 6), menuPosUI * 10 + 2, 5, 5, TFT_BLACK);
                menuPosUI++;
            }
            if(menuPosUI > MenuItem- 1 ){menuPosUI = MenuItem - 1;}
            if(menuPosUI < 0){menuPosUI = 0;}
        

        if(!bt1.isHolded()){
            for(int i = 0; i <= sizeof(ico) - 1; i++){
                tft.setCursor(0, i * 10);
                tft.print(ico[i]);
            }
        
        } else {
            tft.fillScreen(TFT_BLACK);
            switch(menuPosUI){
                case 0: scheduler.addTask(UserInterface::taskManagerWrapper, "Task Manager");
                        scheduler.endTask(scheduler.findIndexTask("User Interface"));
                        break;
                case 6: scheduler.addTask(UserInterface::settingsWrapper, "Settings");
                        scheduler.endTask(scheduler.findIndexTask("User Interface"));
                        break;
            }
        }
    }

    void taskManager(){  // task manager
        bt1.tick();
        bt2.tick();
        tft.setCursor(0, 0);
        tft.println("Task manager");
        tft.drawFastHLine(0, 10, 240, TFT_WHITE);
        taskCount = scheduler.getActiveTaskCount();
        for(int i = 0; i < taskCount; i++){
            tft.setCursor(0, i*10 + 12);
            tft.print(scheduler.getTaskName(i));
        }
        tft.drawRect(15 + (scheduler.getTaskName(menuPosTM).length() * 6), menuPosTM * 10 + 15, 5, 5, TFT_WHITE);
        if(bt1.isClick() && menuPosTM > 0){
            tft.drawRect(15 + (scheduler.getTaskName(menuPosTM).length() * 6), menuPosTM * 10 + 15, 5, 5, TFT_BLACK);
            menuPosTM--;
        }
        if(bt2.isClick() && menuPosTM <= taskCount){
            tft.drawRect(15 + (scheduler.getTaskName(menuPosTM).length() * 6), menuPosTM * 10 + 15, 5, 5, TFT_BLACK);
            menuPosTM++;
        }
        if(menuPosTM > taskCount - 1){menuPosTM = taskCount - 1;}
        if(menuPosTM < 0){menuPosTM = 0;}

        if(bt2.isHolded()){
            tft.fillRect(0, 12, 200, 180, TFT_BLACK);
            scheduler.endTask(menuPosTM);
        }
        if(bt1.isHolded()){
            tft.fillScreen(TFT_BLACK);
            scheduler.addTask(UserInterface::userInterfaceWrapper, "User Interface");
            scheduler.endTask(scheduler.findIndexTask("Task Manager"));
        }

    }
    void settings(){
        bt1.tick();
        bt2.tick();
        tft.setCursor(0, 0);
        tft.println("Settings");
        tft.drawFastHLine(0, 10, 240, TFT_WHITE);
        if(bt1.isHolded()){
            tft.fillScreen(TFT_BLACK);
            scheduler.addTask(UserInterface::userInterfaceWrapper, "User Interface");
            scheduler.endTask(scheduler.findIndexTask("Settings"));
        }
    }
};

#endif
UserInterface* UserInterface::instance = nullptr;

void UserInterface::taskManagerWrapper() {
    if (instance) instance->taskManager();
}

void UserInterface::userInterfaceWrapper(){
    if (instance) instance->drawMenu();
}

void UserInterface::settingsWrapper(){
    if (instance) instance->settings();
}

//upd