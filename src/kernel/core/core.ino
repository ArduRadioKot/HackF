#include "task.h"
#include "UI.h"
#include <TFT_eSPI.h>

TaskScheduler scheduler;
TFT_eSPI tft = TFT_eSPI();
UserInterface ui;

uint8_t clk = 0;
uint32_t fps_time = 0;

void task1() {  //draw UI
  ui.drawMenu();
}

void task2() {  //FPS
  clk++;
}

void setup() {
    UserInterface::instance = &ui;
    //pinMode(21, INPUT);
    //pinMode(22, INPUT);
    ui.setStartSetup();
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(1);
    scheduler.addTask(task1, "User Interface");
    scheduler.addTask(task2, "Counter");
}

void loop() {
    scheduler.run();
}