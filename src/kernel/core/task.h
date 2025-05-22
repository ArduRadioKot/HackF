// task_scheduler.h
#pragma once

#define MAX_TASKS 4
typedef void (*TaskFunc)();

class TaskScheduler {
private:
    TaskFunc tasks[MAX_TASKS];
    int taskCount;
    int taskNameCnt;
    int currentTask;
    String taskName[MAX_TASKS];

public:
    TaskScheduler() : taskCount(0), currentTask(0) {}

    void addTask(TaskFunc task, String Name) {
        taskNameCnt++;
        if (taskCount < MAX_TASKS) {
            tasks[taskCount++] = task;
            taskName[taskNameCnt] = Name;
        }
    }

    void run() {
        while (true) {
            tasks[currentTask]();
            currentTask = (currentTask + 1) % taskCount;
        }
    }

    String retTask(int lst){
        return taskName[lst];  
    }

    
};

