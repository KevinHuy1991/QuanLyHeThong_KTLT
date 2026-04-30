#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tudien.h"

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

// doc du lieu tu File
void loadDictionaryFromFile(Node** head, const char* filename) {
    FILE* f = fopen(filename, "r");
    char line[300];
    
// neu file chua ton tai thi tao file new
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
    if (f == NULL) return;
    
    Node* temp = head;
    while (temp != NULL) {
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
