#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

// Structure to store patient details
typedef struct {
    int token;
    char name[50];
    int age;
    char condition[100];
} Patient;

// Queue structure
typedef struct {
    Patient patients[MAX];
    int front;
    int rear;
    int count;
} PatientQueue;

// Initialize the queue
void initQueue(PatientQueue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

// Check if queue is full
int isFull(PatientQueue *q) {
    return q->count == MAX;
}

// Check if queue is empty
int isEmpty(PatientQueue *q) {
    return q->count == 0;
}

// Enqueue: Register a new patient
void registerPatient(PatientQueue *q, int token) {
    if (isFull(q)) {
        printf("\n[Alert] Waiting room is at full capacity! Cannot accept more patients.\n");
        return;
    }

    q->rear = (q->rear + 1) % MAX;

    q->patients[q->rear].token = token;
    printf("Enter Patient Name: ");
    scanf(" %[^\n]", q->patients[q->rear].name);
    printf("Enter Age: ");
    scanf("%d", &q->patients[q->rear].age);
    printf("Enter Chief Complaint/Ailment: ");
    scanf(" %[^\n]", q->patients[q->rear].condition);

    q->count++;
    printf("\n[Success] Patient '%s' registered with Token #%d.\n",
           q->patients[q->rear].name, token);
}

// Dequeue: Doctor calls the next patient
void callNextPatient(PatientQueue *q) {
    if (isEmpty(q)) {
        printf("\n[Info] No patients waiting in the queue.\n");
        return;
    }

    Patient current = q->patients[q->front];
    q->front = (q->front + 1) % MAX;
    q->count--;

    printf("\n--- Calling Patient to Doctor's Cabin ---");
    printf("\nToken No  : %d", current.token);
    printf("\nName      : %s", current.name);
    printf("\nAge       : %d", current.age);
    printf("\nAilment   : %s", current.condition);
    printf("\n-----------------------------------------\n");
}

// Peek: View next patient in line
void peekNextPatient(PatientQueue *q) {
    if (isEmpty(q)) {
        printf("\n[Info] Queue is empty.\n");
        return;
    }

    Patient next = q->patients[q->front];
    printf("\n[Next in Line] Token #%d - %s (%d yrs)\n", next.token, next.name, next.age);
}

// Display waiting list
void displayQueue(PatientQueue *q) {
    if (isEmpty(q)) {
        printf("\n[Info] No patients are currently waiting.\n");
        return;
    }

    printf("\n================ WAITING LIST (%d Patients) ================\n", q->count);
    printf("%-8s %-25s %-6s %-20s\n", "Token", "Name", "Age", "Condition");
    printf("------------------------------------------------------------\n");

    int idx = q->front;
    for (int i = 0; i < q->count; i++) {
        printf("%-8d %-25s %-6d %-20s\n",
               q->patients[idx].token,
               q->patients[idx].name,
               q->patients[idx].age,
               q->patients[idx].condition);
        idx = (idx + 1) % MAX;
    }
    printf("============================================================\n");
}

int main() {
    PatientQueue hospitalQueue;
    initQueue(&hospitalQueue);

    int choice;
    int tokenCounter = 101;

    do {
        printf("\n=== HOSPITAL PATIENT MANAGEMENT SYSTEM ===");
        printf("\n1. Register Patient (Enqueue)");
        printf("\n2. Call Next Patient for Consultation (Dequeue)");
        printf("\n3. Peek Next Patient");
        printf("\n4. View Full Waiting List");
        printf("\n5. Exit");
        printf("\nEnter your choice (1-5): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }

        switch (choice) {
            case 1:
                registerPatient(&hospitalQueue, tokenCounter++);
                break;

            case 2:
                callNextPatient(&hospitalQueue);
                break;

            case 3:
                peekNextPatient(&hospitalQueue);
                break;

            case 4:
                displayQueue(&hospitalQueue);
                break;

            case 5:
                printf("\nExiting hospital management system. Goodbye!\n");
                break;

            default:
                printf("\n[Warning] Invalid choice. Please select a value from 1 to 5.\n");
                break;
        }

    } while (choice != 5);

    return 0;
}
