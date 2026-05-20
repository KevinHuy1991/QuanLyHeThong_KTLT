#ifndef GEMINI_H
#define GEMINI_H

// Thay bang API key that cua ban
#define GEMINI_API_KEY "AIzaSyCbzBNTpQmgUXeaBwOVtBqq9JoVSxjEinU"

// Cach noi chuoi dung trong C: De 2 chuoi canh nhau hoac goi ten Macro
#define GEMINI_URL "https://generativelanguage.googleapis.com/v1beta/models/gemini-2.5-flash-lite:generateContent?key=" GEMINI_API_KEY

// Buffer nhan response tu API
typedef struct {
    char* data;
    size_t size;
} ResponseBuffer;

// Ham goi Gemini API, tra ve chuoi ket qua (can free() sau khi dung)
char* callGeminiAPI(const char* prompt);

// === CAC TINH NANG SU DUNG GEMINI ===

// 1. Giai thich tu chi tiet (nghia, cach dung, vi du cau)
void explainWord(const char* englishWord, const char* vietnameseMeaning);

// 2. Goi y tu lien quan
void suggestRelatedWords(const char* englishWord);

// 3. Quiz thong minh dua tren lich su tra cuu
void smartQuizFromHistory(const char* histFilename);

#endif