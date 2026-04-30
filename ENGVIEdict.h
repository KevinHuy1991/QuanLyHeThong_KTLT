#ifndef TUDIEN_H
#define TUDIEN_H
// Cau truc du lieu cho tu dien
typedef struct Node {
    char word[100];       // Tu tieng Anh 
    char meaning[200];    // Nghia tieng Viet 
    struct Node* next;
} Node;
// Ham tao node moi
void addWord(Node** head, char* tuAnh, char* nghiaViet);
// In ra toan bo tu dien
void dictionaryPrinting(Node* head);
// Tim kiem tu trong tu dien
void wordSearch(Node* head, char* english);
// Giai phong bo nho
void freeMemory(Node** head);
// Doc du lieu tu file
void loadDictionaryFromFile(Node** head, const char* filename);
// Ghi du lieu vao file
void saveDictionaryToFile(Node* head, const char* filename);
// Ham xoa ky tu xuong dong (newline) tu chuoi
void removeNewline(char* str);

#endif