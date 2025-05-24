#include "task.h"
#include "UI.h"
#include <TFT_eSPI.h>

TaskScheduler scheduler;
TFT_eSPI tft = TFT_eSPI();
UserInterface ui;

uint8_t clk = 0;
uint32_t fps_time = 0;

void task1() {  //FPS
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

void task2() {  //test Button
  tft.setCursor(200, 0);
  tft.print(digitalRead(21));
  tft.println(digitalRead(22));
}

void task3() {  //draw UI
  ui.drawMenu();
}

void setup() {
    //pinMode(21, INPUT);
    //pinMode(22, INPUT);
    ui.setStartSetup();
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(1);
    //scheduler.addTask(task1, "Counter");
    //scheduler.addTask(task2, "Button");
    scheduler.addTask(task3, "User Interface");
}

void loop() {
    scheduler.run();
}