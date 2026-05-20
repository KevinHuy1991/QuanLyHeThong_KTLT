#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <conio.h>
#include <windows.h>
#include "gemini.h"
#include "ENGVIEdict.h"

// ===  HAM HO TRO CURL ===
static size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    ResponseBuffer* buf = (ResponseBuffer*)userp;
    buf->data = realloc(buf->data, buf->size + totalSize + 1);
    if (buf->data == NULL) return 0;
    memcpy(&(buf->data[buf->size]), contents, totalSize);
    buf->size += totalSize;
    buf->data[buf->size] = '\0';
    return totalSize;
}

static char* extractTextFromJSON(const char* json) {
    const char* key = "\"text\": \"";
    char* pos = strstr(json, key);
    if (pos == NULL) return NULL;

    pos += strlen(key);
    char* result = (char*)malloc(4096);
    if (!result) return NULL;

    int i = 0;
    while (*pos != '\0' && i < 4095) {
        if (*pos == '\\' && *(pos + 1) == '"') {
            result[i++] = '"';
            pos += 2;
        } else if (*pos == '\\' && *(pos + 1) == 'n') {
            result[i++] = '\n';
            pos += 2;
        } else if (*pos == '"') {
            break;
        } else {
            result[i++] = *pos++;
        }
    }
    result[i] = '\0';
    return result;
}

// === HAM GOI API CHINH ===
char* callGeminiAPI(const char* prompt) {
    Sleep(1000); // Nghi 1s giua cac lan goi de Google khong block vi spam
    
    CURL* curl = curl_easy_init();
    if (!curl) return NULL;

    ResponseBuffer buf = {0};
    buf.data = malloc(1);
    buf.size = 0;

    char jsonBody[2048];
    snprintf(jsonBody, sizeof(jsonBody),
        "{\"contents\":[{\"parts\":[{\"text\":\"%s\"}]}]}", prompt);

    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, GEMINI_URL);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonBody);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buf);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); 

    CURLcode res = curl_easy_perform(curl);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        free(buf.data);
        return NULL;
    }

    char* text = extractTextFromJSON(buf.data);
    free(buf.data);
    return text;
}

// === TINH NANG 1: GIAI THICH TU CHI TIET ===
void explainWord(const char* englishWord, const char* vietnameseMeaning) {
    UINT oldCP = GetConsoleOutputCP();
    SetConsoleOutputCP(65001);

    setColor(11);
    printf("\n\t[AI] Dang tra cuu chi tiet...\n");
    setColor(7);

    char prompt[512];
    snprintf(prompt, sizeof(prompt),
        "Explain the English word '%s' (Vietnamese meaning: %s). "
        "Give: 1) Detailed meaning in Vietnamese, 2) Word type (noun/verb/adj), "
        "3) Two example sentences with Vietnamese translation. "
        "Keep it concise, use plain text no markdown.",
        englishWord, vietnameseMeaning);

    char* result = callGeminiAPI(prompt);
    if (result) {
        setColor(14);
        printf("\n\t=== CHI TIET TU '%s' ===\n", englishWord);
        setColor(7);
        char* line = strtok(result, "\n");
        while (line != NULL) {
            printf("\t%s\n", line);
            line = strtok(NULL, "\n");
        }
        free(result);
    } else {
        setColor(12);
        printf("\t[LOI] Khong the ket noi API. Kiem tra internet hoac API key.\n");
        setColor(7);
    }
    SetConsoleOutputCP(oldCP);
}

// === TINH NANG 2: GOI Y TU LIEN QUAN ===
void suggestRelatedWords(const char* englishWord) {
    UINT oldCP = GetConsoleOutputCP();
    SetConsoleOutputCP(65001);

    setColor(11);
    printf("\n\t[AI] Dang tim tu lien quan...\n");
    setColor(7);

    char prompt[512];
    snprintf(prompt, sizeof(prompt),
        "Give 5 English words related to '%s'. "
        "Format each line as: EnglishWord - VietNameseMeaning. "
        "Plain text only, no markdown, no numbering.",
        englishWord);

    char* result = callGeminiAPI(prompt);
    if (result) {
        setColor(14);
        printf("\n\t=== TU LIEN QUAN DEN '%s' ===\n", englishWord);
        setColor(7);
        char* line = strtok(result, "\n");
        while (line != NULL) {
            if (strlen(line) > 1)
                printf("\t  + %s\n", line);
            line = strtok(NULL, "\n");
        }
        free(result);
    } else {
        setColor(12);
        printf("\t[LOI] Khong the ket noi API.\n");
        setColor(7);
    }
    SetConsoleOutputCP(oldCP);
}

// === TINH NANG 3: QUIZ THONG MINH TU LICH SU ===
void smartQuizFromHistory(const char* histFilename) {
    UINT oldCP = GetConsoleOutputCP();
    SetConsoleOutputCP(65001);

    FILE* f = fopen(histFilename, "r");
    if (f == NULL) {
        setColor(12);
        printf("\tChua co lich su de on tap!\n");
        setColor(7);
        SetConsoleOutputCP(oldCP);
        return;
    }

    char words[200][100];
    char meanings[200][200];
    int count = 0;

    char buf[400];
    while (fgets(buf, sizeof(buf), f) && count < 200) {
        buf[strcspn(buf, "\n")] = 0;
        char temp[400];
        strcpy(temp, buf);
        char* kw  = strtok(temp, "|");
        char* res = strtok(NULL, "|");
        if (kw && res) {
            strncpy(words[count], kw, 99);
            strncpy(meanings[count], res, 199);
            count++;
        }
    }
    fclose(f);

    if (count == 0) {
        setColor(12);
        printf("\tKhong co tu nao trong lich su!\n");
        setColor(7);
        SetConsoleOutputCP(oldCP);
        return;
    }

    srand((unsigned int)time(NULL));
    int idx = rand() % count;

    setColor(11);
    printf("\n\t[AI QUIZ] Dang tao cau hoi...\n");
    setColor(7);

    char prompt[512];
    snprintf(prompt, sizeof(prompt),
        "Create a fill-in-the-blank English sentence using the word '%s'. "
        "Format strictly as:\n"
        "SENTENCE: [sentence with ___ replacing the word]\n"
        "ANSWER: %s\n"
        "HINT: [one short hint in Vietnamese]\n"
        "Plain text only.",
        words[idx], meanings[idx]);

    char* result = callGeminiAPI(prompt);

    setColor(14);
    printf("\n\t=== QUIZ: DIEN VAO CHO TRONG ===\n");
    setColor(7);
    printf("\t(Tu can tim: gom %d chu cai)\n\n", (int)strlen(words[idx]));

    if (result) {
        char* line = strtok(result, "\n");
        char answerLine[300] = "";

        while (line != NULL) {
            if (strncmp(line, "ANSWER:", 7) == 0) {
                strncpy(answerLine, line, sizeof(answerLine) - 1);
            } else if (strlen(line) > 1) {
                printf("\t%s\n", line);
            }
            line = strtok(NULL, "\n");
        }

        SetConsoleOutputCP(oldCP);
        char userAnswer[100];
        printf("\n\tDap an cua ban: ");
        fgets(userAnswer, sizeof(userAnswer), stdin);
        userAnswer[strcspn(userAnswer, "\n")] = 0;

        if (strcasecmp(userAnswer, words[idx]) == 0) {
            setColor(10);
            printf("\tCHINH XAC! Rat gioi!\n");
        } else {
            setColor(12);
            printf("\tSai roi! Dap an dung la: %s (%s)\n", words[idx], meanings[idx]);
        }
        setColor(7);
        free(result);
    } else {
        setColor(12);
        printf("\t[LOI] Khong the ket noi API.\n");
        setColor(7);
        SetConsoleOutputCP(oldCP);
    }
}