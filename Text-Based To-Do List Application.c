#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASK_LENGTH 100
#define FILENAME "todo_list.txt"

void displayMenu() {
    printf("\nText-Based To-Do List Application\n");
    printf("1. Add Task\n");
    printf("2. Mark Task as Completed\n");
    printf("3. View To-Do List\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

void addTask(FILE *file) {
    char task[MAX_TASK_LENGTH];
    printf("Enter the task: ");
    scanf(" %[^\n]", task);
    fprintf(file, "%s\n", task);
    printf("Task added successfully!\n");
}

void markCompleted(FILE *file) {
    // Display current tasks
    printf("To-Do List:\n");
    char line[MAX_TASK_LENGTH];
    int lineNumber = 1;
    rewind(file);
    while (fgets(line, sizeof(line), file)) {
        printf("%d. %s", lineNumber, line);
        lineNumber++;
    }

    // Prompt user to mark a task as completed
    int taskNumber;
    printf("Enter the number of the task to mark as completed: ");
    scanf("%d", &taskNumber);

    // Update file to mark task as completed
    FILE *tempFile = fopen("temp.txt", "w");
    rewind(file);
    lineNumber = 1;
    while (fgets(line, sizeof(line), file)) {
        if (lineNumber == taskNumber) {
            fprintf(tempFile, "%s [Completed]\n", line);
        } else {
            fprintf(tempFile, "%s", line);
        }
        lineNumber++;
    }
    fclose(file);
    fclose(tempFile);
    remove(FILENAME);
    rename("temp.txt", FILENAME);
    printf("Task marked as completed!\n");
}

void viewList(FILE *file) {
    printf("To-Do List:\n");
    char line[MAX_TASK_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
}

int main() {
    FILE *file = fopen(FILENAME, "a+");

    if (file == NULL) {
        printf("Error: Unable to open or create file.\n");
        return 1;
    }

    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addTask(file);
                break;
            case 2:
                markCompleted(file);
                break;
            case 3:
                viewList(file);
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 4);

    fclose(file);
    return 0;
}
