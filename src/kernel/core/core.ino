#include "task.h"
#include "UI.h"
#include <TFT_eSPI.h>

TaskScheduler scheduler;
TFT_eSPI tft = TFT_eSPI();
UserInterface ui;

uint8_t clk = 0;
uint32_t fps_time = 0;
void task1() {  
  clk++;
  if(millis() >= fps_time + 1000){
    fps_time = millis();
    tft.setCursor(0,0);
    tft.println("    ");
    tft.setCursor(0,0);
    tft.println(clk);
    clk = 0;
  }
}

void task2() {  
  for(int i = 0; i < scheduler.getActiveTaskCount(); i++){
    tft.setCursor(0, i*10+10);
    tft.println(scheduler.getTaskName(i));
  }
}

void task4() {  
  ui.drawTaskManagerIco();
}

void setup() {
    ui.begin();
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(1);
    scheduler.addTask(task1, "Counter");
    //scheduler.addTask(task2, "Display");
    //scheduler.addTask(task3, "Clear");
    scheduler.addTask(task4, "Draw Icon");
}

void loop() {
    scheduler.run();

}