#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tudien.h"

// 1. Hàm thêm t? m?i vào danh sách liên k?t
void addWord(Node** head, char* english, char* vietnamese) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return; // Ki?m tra c?p phát b? nh?
    
    strcpy(newNode->word, english);
    strcpy(newNode->meaning, vietnamese);
    
    // Thêm vào d?u danh sách (Logic nhanh nh?t cho Linked List)
    newNode->next = *head;
    *head = newNode;
}

// 2. Hàm d?c d? li?u t? File vào RAM
void loadDictionaryFromFile(Node** head, const char* filename) {
    FILE* f = fopen(filename, "r");
    char line[300];
    
    // N?u file chua t?n t?i, t?o file m?i v?i d? li?u m?u
    if (f == NULL) {
        f = fopen(filename, "w");
        if (f != NULL) {
            fprintf(f, "Hello|Xin chao\nApple|Qua tao\nBanana|Qua chuoi\n");
            fclose(f);
        }
        f = fopen(filename, "r");
    }
    
    if (f == NULL) return;

    while (fgets(line, sizeof(line), f)) {
        // G?i hàm ti?n ích c?a Ngu?i 2 d? xóa d?u xu?ng dòng
        removeNewline(line); 
        
        char* english = strtok(line, "|");
        char* vietnamese = strtok(NULL, "|");
        
        if (english && vietnamese) {
            addWord(head, english, vietnamese);
        }
    }
    fclose(f);
}

// 3. Hàm ghi toàn b? d? li?u t? RAM ngu?c l?i vào File
void saveDictionaryToFile(Node* head, const char* filename) {
    FILE* f = fopen(filename, "w");
    if (f == NULL) return;
    
    Node* temp = head;
    while (temp != NULL) {
        fprintf(f, "%s|%s\n", temp->word, temp->meaning);
        temp = temp->next;
    }
    fclose(f);
}

// 4. Hàm gi?i phóng b? nh? (Tránh rò r? RAM)
void freeMemory(Node** head) {
    Node* temp = *head;
    while (temp != NULL) {
        Node* nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }
    *head = NULL;
}
