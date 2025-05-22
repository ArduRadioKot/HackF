#include "task.h"
#include <TFT_eSPI.h>

TaskScheduler scheduler;
TFT_eSPI tft = TFT_eSPI();

uint8_t clk = 0;

void task1() {
  clk++;
}

void task2() {
  tft.setCursor(0,0);
  tft.println(clk);
  for(int i = 0; i <= 3; i++){
    tft.setCursor(0, i*10+10);
    tft.println(scheduler.retTask(i));
  }
}

void task3() {
  if(clk >= 255){
    tft.setCursor(0,0);
    tft.println("    ");
  }
}

void setup() {
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    scheduler.addTask(task1, "add");
    scheduler.addTask(task2, "drw");
    scheduler.addTask(task3, "clr");

}

void loop() {
    scheduler.run(); // запускаем мини-ОС 
}
