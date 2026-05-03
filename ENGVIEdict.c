#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ENGVIEdict.h"

// Ham xoa ky tu xuong dong (newline) tu chuoi
void removeNewline(char* str) {
    str[strcspn(str, "\n")] = 0;
}

//  them tu moi vao danh sach
void addWord(Node** head, char* english, char* vietnamese) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return; // Ktra cap phat bo nho dong
    strcpy(newNode->word, english);
    strcpy(newNode->meaning, vietnamese);
// them vao dau danh sach
    newNode->next = *head;
    *head = newNode;
}

// In tu dien ra man hinh
void dictionaryPrinting(Node* head) {
    if (head == NULL) {
        printf("Tu dien dang trong!\n");
        return;
    }
    Node* temp = head;
    printf("\n%-20s | %s\n", "TU TIENG ANH", "NGHIA TIENG VIET");
    printf("--------------------------------------------------\n");
    while (temp != NULL) {
        printf("%-20s | %s\n", temp->word, temp->meaning);
        temp = temp->next;
    }
    printf("--------------------------------------------------\n");
}

// Tim kiem tu trong tu dien
void wordSearch(Node* head, char* english) {
    Node* temp = head;
    while (temp != NULL) {
        // Hàm strcasecmp giúp so sánh không phân biệt hoa thường (Apple = apple)
        if (strcasecmp(temp->word, english) == 0) {
            printf("=> Ket qua: %s nghia la '%s'\n", temp->word, temp->meaning);
            return;
        }
        temp = temp->next;
    }
    printf("=> Khong tim thay tu '%s' trong tu dien.\n", english);
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
            printf("=> Da xoa tu '%s' khoi tu dien.\n", english);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("=> Khong tim thay tu '%s' de xoa.\n", english);
}

// Cap nhat nghia cua tu trong tu dien
void updateMeaning(Node* head, char* english, char* newMeaning) {
    Node* temp = head;
    while (temp != NULL) {
        if (strcasecmp(temp->word, english) == 0) {
            strcpy(temp->meaning, newMeaning);
            printf("=> Da cap nhat nghia cua tu '%s' thanh '%s'.\n", english, newMeaning);
            return;
        }
        temp = temp->next;
    }
    printf("=> Khong tim thay tu '%s' de cap nhat.\n", english);
}

// doc du lieu tu File
void loadDictionaryFromFile(Node** head, const char* filename) {
    FILE* f = fopen(filename, "r");
    char line[300];
    
// neu file chua ton tai thi tao file new
    if (f == NULL) {
        f = fopen(filename, "w");
        if (f != NULL) {
            printf("Khong co tu trong tu dien. Da tao file moi: %s\n", filename);
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
