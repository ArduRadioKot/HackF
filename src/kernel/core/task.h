#pragma once

#define MAX_TASKS 8  

typedef void (*TaskFunc)();

class TaskScheduler {
private:
    struct Task {
        TaskFunc function;
        String name;
        bool active;
    };
    
    Task tasks[MAX_TASKS];
    int taskCount;
    int currentTask;

public:
    TaskScheduler() : taskCount(0), currentTask(0) {
        for (int i = 0; i < MAX_TASKS; i++) {
            tasks[i].active = false;
        }
    }


    void addTask(TaskFunc task, const String& name) {
        if (taskCount < MAX_TASKS) {
            tasks[taskCount].function = task;
            tasks[taskCount].name = name;
            tasks[taskCount].active = true;
            taskCount++;
        }
    }


    String getTaskName(int index) {
        if (index >= 0 && index < taskCount) {
            return tasks[index].name;
        }
        return "Invalid";
    }


    void endTask(int index) {
    if (index >= 0 && index < taskCount) {
        for (int i = index; i < taskCount - 1; i++) {
            tasks[i] = tasks[i + 1];
        }
        taskCount--;
        // Обнуляем последний элемент (по желанию)
        tasks[taskCount].function = nullptr;
        tasks[taskCount].name = "";
        tasks[taskCount].active = false;
        
        // Убедимся, что currentTask всё ещё валиден
        if (currentTask >= taskCount) {
            currentTask = 0;
        }
    }
}



    void run() {
        if (taskCount == 0) return;
        

        do {
            currentTask = (currentTask + 1) % taskCount;
        } while (!tasks[currentTask].active && taskCount > 0);
        if (tasks[currentTask].active) {
            tasks[currentTask].function();
        }
    }


    int getActiveTaskCount() {
        int count = 0;
        for (int i = 0; i < taskCount; i++) {
            if (tasks[i].active) count++;
        }
        return count;
    }

    int findIndexTask(String taskName) {
        for (int i = 0; i < taskCount; i++) {
            if (tasks[i].name == taskName) {
                return i;
            }
        }
        return -1;
    }

};