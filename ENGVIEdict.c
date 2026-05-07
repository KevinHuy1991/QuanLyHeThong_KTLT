#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "ENGVIEdict.h"

// === CAC HAM GIAO DIEN ===

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void slowPrint(char* str, int delay) {
    int i; // Khai bao i 
    for (i = 0; str[i] != '\0'; i++) {
        printf("%c", str[i]);
        Sleep(delay);
    }
}
void boxHeader(char* title) {
    int len = strlen(title);
    int i; // Khai bao i o day
    setColor(11); // Mau xanh cyan
    printf("\n\t%c", 201);
    for (i = 0; i < len + 4; i++) printf("%c", 205);
    printf("%c\n", 187);
    
    printf("\t%c  ", 186);
    setColor(14); // Mau vang
    printf("%s", title);
    setColor(11);
    printf("  %c\n", 186);
    
    printf("\t%c", 200);
    for (i = 0; i < len + 4; i++) printf("%c", 205);
    printf("%c\n", 188);
    setColor(7); // Tra ve mau trang
}

void clearScreen() {
    system("cls");
}

// === LOGIC CHUONG TRINH (GIU NGUYEN COMMENT CUA BRO) ===

// Ham xoa ky tu xuong dong (newline) tu chuoi[cite: 1]
void removeNewline(char* str) {
    str[strcspn(str, "\n")] = 0;
}

//  them tu moi vao danh sach[cite: 1]
void addWord(Node** head, char* english, char* vietnamese) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return; // Ktra cap phat bo nho dong[cite: 1]
    strcpy(newNode->word, english);
    strcpy(newNode->meaning, vietnamese);
// them vao dau danh sach[cite: 1]
    newNode->next = *head;
    *head = newNode;
}

// In tu dien ra man hinh[cite: 1]
void dictionaryPrinting(Node* head) {
    clearScreen();
    boxHeader("DANH SACH TU DIEN");
    if (head == NULL) {
        setColor(12);
        printf("\tTu dien dang trong!\n");
        setColor(7);
        getch();
        return;
    }
    Node* temp = head;
    setColor(10); // Xanh la
    printf("\t%-20s | %-20s\n", "TU TIENG ANH", "NGHIA TIENG VIET");
    printf("\t--------------------------------------------------\n");
    setColor(7);
    while (temp != NULL) {
        printf("\t%-20s | %-20s\n", temp->word, temp->meaning);
        temp = temp->next;
    }
    printf("\t--------------------------------------------------\n");
    printf("\n\tNhan phim bat ky de quay lai menu...");
    getch();
}

// Tim kiem tu trong tu dien
void wordSearch(Node* head, char* english) {
    Node* temp = head;
    while (temp != NULL) {
        if (strcasecmp(temp->word, english) == 0) {
            setColor(10);
            printf("\t=> Ket qua: %s nghia la '%s'\n", temp->word, temp->meaning);
            setColor(7);
            return;
        }
        temp = temp->next;
    }
    setColor(12);
    printf("\t=> Khong tim thay tu '%s' trong tu dien.\n", english);
    setColor(7);
}

// Xoa tu trong tu dien
void removeWord(Node** head, char* english) {
    Node* temp = *head;
    Node* prev = NULL;

    while (temp != NULL) {
        if (strcasecmp(temp->word, english) == 0) {
            if (prev == NULL) {
                *head = temp->next; // Xoa node dau
            } else {
                prev->next = temp->next; // Xoa node giua hoac cuoi
            }
            free(temp);
            setColor(10);
            printf("\t=> Da xoa tu '%s' khoi tu dien.\n", english);
            setColor(7);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    setColor(12);
    printf("\t=> Khong tim thay tu '%s' de xoa.\n", english);
    setColor(7);
}

// Cap nhat nghia cua tu trong tu dien
void updateMeaning(Node* head, char* english, char* newMeaning) {
    Node* temp = head;
    while (temp != NULL) {
        if (strcasecmp(temp->word, english) == 0) {
            strcpy(temp->meaning, newMeaning);
            setColor(10);
            printf("\t=> Da cap nhat nghia cua tu '%s' thanh '%s'.\n", english, newMeaning);
            setColor(7);
            return;
        }
        temp = temp->next;
    }
    setColor(12);
    printf("\t=> Khong tim thay tu '%s' de cap nhat.\n", english);
    setColor(7);
}

// doc du lieu tu File
void loadDictionaryFromFile(Node** head, const char* filename) {
    FILE* f = fopen(filename, "r");
    char line[300];
    
// neu file chua ton tai thi tao file new
    if (f == NULL) {
        f = fopen(filename, "w");
        if (f != NULL) {
            fprintf(f, "Hello|Xin chao\n");
            fprintf(f, "Apple|Qua tao\n");
            fprintf(f, "Banana|Qua chuoi\n");
            fprintf(f, "Computer|May tinh\n");
            fprintf(f, "Software|Phan mem\n");
            fprintf(f, "Student|Sinh vien\n");
            fprintf(f, "Teacher|Giao vien\n");
            fprintf(f, "University|Truong dai hoc\n");
            fprintf(f, "Programming|Lap trinh\n");
            fprintf(f, "Algorithm|Thuat toan\n");
            fprintf(f, "Data Structure|Cau truc du lieu\n");
            fprintf(f, "Dictionary|Tu dien\n");
            fprintf(f, "Love|Tinh yeu\n");
            fprintf(f, "Family|Gia dinh\n");
            fprintf(f, "Money|Tien bac\n");
            fclose(f);
        }
        f = fopen(filename, "r");
    }
    
    if (f == NULL) return;

    while (fgets(line, sizeof(line), f)) {
        removeNewline(line); 
        
        char* english = strtok(line, "|");
        char* vietnamese = strtok(NULL, "|");
        
        if (english && vietnamese) {
            addWord(head, english, vietnamese);
        }
    }
    fclose(f);
}

// ghi toan bo du lieu vao file
void saveDictionaryToFile(Node* head, const char* filename) {
    FILE* f = fopen(filename, "w");
    if (f == NULL) {
        printf("Khong the luu file!\n");
        return;
    }
    
    Node* temp = head;
    while (temp != NULL) {
        //Quy uoc: tu va nghia cach nhau boi dau '|'
        fprintf(f, "%s|%s\n", temp->word, temp->meaning);
        temp = temp->next;
    }
    fclose(f);
}

// giai phong bo nho
void freeMemory(Node** head) {
    Node* temp = *head;
    while (temp != NULL) {
        Node* nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }
    *head = NULL;
}
