#ifndef ENGVIEDICT_H
#define ENGVIEDICT_H

#include <windows.h> // Thu vien ho tro mau sac va thoi gian
#include <conio.h>   // Thu vien ho tro ham getch()

// Cau truc du lieu cho tu dien[cite: 2]
typedef struct Node {
    char word[100];       // Tu tieng Anh[cite: 2]
    char meaning[200];    // Nghia tieng Viet[cite: 2]
    struct Node* next;
} Node;
// === CAU TRUC LICH SU TRA CUU ===
typedef struct HistoryNode {
    char keyword[100];       // Tu da tra
    char result[200];        // Ket qua (nghia hoac "Khong tim thay")
    char timestamp[30];      // Thoi gian tra
    struct HistoryNode* next;
} HistoryNode;

// --- CAC HAM GIAO DIEN MOI ---
void setColor(int color);
void slowPrint(char* str, int delay);
void boxHeader(char* title);
void clearScreen();

// Ham tao node moi[cite: 2]
void addWord(Node** head, char* tuAnh, char* nghiaViet);
// In ra toan bo tu dien[cite: 2]
void dictionaryPrinting(Node* head);
// Tim kiem tu trong tu dien[cite: 2]
void wordSearch(Node* head, char* english);
// Giai phong bo nho[cite: 2]
void freeMemory(Node** head);
// Doc du lieu tu file[cite: 2]
void loadDictionaryFromFile(Node** head, const char* filename);
// Ghi du lieu vao file[cite: 2]
void saveDictionaryToFile(Node* head, const char* filename);
// Ham xoa ky tu xuong dong (newline) tu chuoi[cite: 2]
void removeNewline(char* str);
// Xoa tu trong tu dien[cite: 2]
void removeWord(Node** head, char* english);
// Cap nhat nghia cua tu trong tu dien[cite: 2]
void updateMeaning(Node* head, char* english, char* newMeaning);
// Ham tim tat ca cac tu bat dau bang mot chu cai cu the[cite: 2]
void searchByFirstChar(Node* head, char ch);
// Ham sap xep tu dien theo thu tu abc[cite: 2]
void sortDictionary(Node** head);

// CAC HAM HO TRO TIM KIEM NANG CAO
int min3(int a, int b, int c);
int levenshtein(const char *s1, const char *s2);
int startsWithIgnoreCase(const char *prefix, const char *str);
void advancedWordSearch(Node* head, char* english);

// CAC HAM LICH SU TRA CUU
void saveSearchHistory(const char* keyword, const char* result, const char* filename);
void cleanHistory(const char* histFilename, Node* dictHead);
void printHistory(const char* filename, Node* dictHead);

void randomQuizFromHistory(const char* histFilename);
void flashcardReview(const char* histFilename);

#endif