#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------- STRUCTURE ---------- */

struct Student {
    char name[50];
    char father[50];
    char roll[20];
    char address[100];
    int total;
    int present;
    struct Student *next;
};

struct Student *head = NULL;

/* ---------- CREATE NODE ---------- */

struct Student* createNode() {
    struct Student *newNode =
        (struct Student*)malloc(sizeof(struct Student));
    newNode->next = NULL;
    return newNode;
}

/* ---------- LOAD FROM FILE ---------- */

void loadFromFile() {
    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) return;

    struct Student *temp, *last = NULL;

    while (1) {
        temp = createNode();

        if (fscanf(fp,
            "%[^|]|%[^|]|%[^|]|%[^|]|%d|%d\n",
            temp->name,
            temp->father,
            temp->roll,
            temp->address,
            &temp->total,
            &temp->present) == EOF) {
            free(temp);
            break;
        }

        if (head == NULL)
            head = temp;
        else
            last->next = temp;

        last = temp;
    }
    fclose(fp);
}

/* ---------- SAVE TO FILE ---------- */

void saveToFile() {
    FILE *fp = fopen("students.txt", "w");
    struct Student *temp = head;

    while (temp != NULL) {
        fprintf(fp, "%s|%s|%s|%s|%d|%d\n",
                temp->name,
                temp->father,
                temp->roll,
                temp->address,
                temp->total,
                temp->present);
        temp = temp->next;
    }
    fclose(fp);
}

/* ---------- STUDENT DETAILS ---------- */

void addStudent() {
    struct Student *newNode = createNode();

    printf("\nEnter Student Name: ");
    scanf(" %[^\n]", newNode->name);

    printf("Enter Father Name: ");
    scanf(" %[^\n]", newNode->father);

    printf("Enter Roll No: ");
    scanf("%s", newNode->roll);

    printf("Enter Address: ");
    scanf(" %[^\n]", newNode->address);

    newNode->total = 0;
    newNode->present = 0;

    if (head == NULL)
        head = newNode;
    else {
        struct Student *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }

    saveToFile();
    printf("Student added successfully!\n");
}

void deleteStudent() {
    char roll[20];
    printf("\nEnter Roll No to delete: ");
    scanf("%s", roll);

    struct Student *temp = head, *prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->roll, roll) == 0) {
            if (prev == NULL)
                head = temp->next;
            else
                prev->next = temp->next;

            free(temp);
            saveToFile();
            printf("Student deleted successfully!\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Student not found!\n");
}

void viewStudents() {
    if (head == NULL) {
        printf("\nNo student records found!\n");
        return;
    }

    struct Student *temp = head;
    while (temp != NULL) {
        printf("\nName: %s", temp->name);
        printf("\nFather Name: %s", temp->father);
        printf("\nRoll No: %s", temp->roll);
        printf("\nAddress: %s\n", temp->address);
        temp = temp->next;
    }
}

/* ---------- ATTENDANCE DETAILS ---------- */

void markAttendance() {
    char roll[20];
    int status;

    printf("\nEnter Roll No: ");
    scanf("%s", roll);

    struct Student *temp = head;

    while (temp != NULL) {
        if (strcmp(temp->roll, roll) == 0) {
            printf("Enter Attendance (1 = Present, 0 = Absent): ");
            scanf("%d", &status);

            temp->total++;
            if (status == 1)
                temp->present++;

            saveToFile();
            printf("Attendance marked successfully!\n");
            return;
        }
        temp = temp->next;
    }
    printf("Student not found!\n");
}

void attendanceReport() {
    float percent;
    struct Student *temp = head;

    printf("\n--- Attendance Report ---\n");

    while (temp != NULL) {
        percent = (temp->total == 0) ? 0 :
                  (temp->present * 100.0) / temp->total;

        printf("\nName: %s", temp->name);
        printf("\nRoll No: %s", temp->roll);
        printf("\nTotal Classes: %d", temp->total);
        printf("\nPresent: %d", temp->present);

        if (percent < 75)
            printf("\nStatus: LOW Attendance ⚠️\n");
        else
            printf("\nStatus: Attendance OK\n");

        temp = temp->next;
    }
}

/* ---------- MENUS ---------- */

void studentDetails() {
    int ch;
    do {
        printf("\n--- Student Details Menu ---");
        printf("\n1. Add Student");
        printf("\n2. Delete Student");
        printf("\n3. View Student Details");
        printf("\n4. Back");
        printf("\nEnter choice: ");
        scanf("%d", &ch);

        if (ch == 1) addStudent();
        else if (ch == 2) deleteStudent();
        else if (ch == 3) viewStudents();

    } while (ch != 4);
}

void attendanceDetails() {
    int ch;
    do {
        printf("\n--- Attendance Details Menu ---");
        printf("\n1. Mark Attendance");
        printf("\n2. Attendance Report");
        printf("\n3. Back");
        printf("\nEnter choice: ");
        scanf("%d", &ch);

        if (ch == 1) markAttendance();
        else if (ch == 2) attendanceReport();

    } while (ch != 3);
}

/* ---------- MAIN ---------- */

int main() {
    int choice;
    loadFromFile();

    do {
        printf("\n=== Attendance Management System ===");
        printf("\n1. Student Details");
        printf("\n2. Attendance Details");
        printf("\n3. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1) studentDetails();
        else if (choice == 2) attendanceDetails();

    } while (choice != 3);

    return 0;
}
