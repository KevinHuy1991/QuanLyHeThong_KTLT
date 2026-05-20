#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "ENGVIEdict.h"
#include <time.h>


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
    printf("\033[H\033[J");
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

// Ham tim tat ca cac tu bat dau bang mot chu cai cu the
void searchByFirstChar(Node* head, char ch) {
    Node* temp = head;
    int found = 0;
    
    // Chuyen ve chu thuong de so sanh
    char searchChar = tolower(ch);

    clearScreen();
    boxHeader("KET QUA TIM KIEM");
    
    printf("\tCac tu bat dau bang chu cai '%c':\n", ch);
    printf("\t--------------------------------------------------\n");
    setColor(10);
    printf("\t%-20s | %-20s\n", "TU TIENG ANH", "NGHIA TIENG VIET");
    setColor(7);

    while (temp != NULL) {
        if (tolower(temp->word[0]) == searchChar) {
            printf("\t%-20s | %-20s\n", temp->word, temp->meaning);
            found = 1;
        }
        temp = temp->next;
    }

    if (!found) {
        setColor(12);
        printf("\t=> Khong co tu nao bat dau bang '%c'.\n", ch);
        setColor(7);
    }
    printf("\t--------------------------------------------------\n");
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

// Ham sap xep danh sach lien ket theo thu tu A-Z (Bubble Sort)
void sortDictionary(Node** head) {
    if (*head == NULL || (*head)->next == NULL) return;

    int swapped;
    Node* ptr1;
    Node* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            // So sanh khong phan biet hoa thuong
            if (strcasecmp(ptr1->word, ptr1->next->word) > 0) {
                // Hoan doi du lieu giua 2 node
                char tempWord[100];
                char tempMeaning[200];

                strcpy(tempWord, ptr1->word);
                strcpy(ptr1->word, ptr1->next->word);
                strcpy(ptr1->next->word, tempWord);

                strcpy(tempMeaning, ptr1->meaning);
                strcpy(ptr1->meaning, ptr1->next->meaning);
                strcpy(ptr1->next->meaning, tempMeaning);

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
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

// === THUAT TOAN TIM KIEM NANG CAO (GOI Y & SUA LOI) ===

// Ham ho tro: Tim so nho nhat trong 3 so
int min3(int a, int b, int c) {
    int m = a;
    if (b < m) m = b;
    if (c < m) m = c;
    return m;
}

// Ham ho tro: Tinh khoang cach Levenshtein (Do muc do giong nhau giua 2 chuoi)
int levenshtein(const char *s1, const char *s2) {
    int l1 = strlen(s1);
    int l2 = strlen(s2);
    int matrix[100][100]; // Gioi han do dai tu 100 ky tu

    for (int i = 0; i <= l1; i++) matrix[i][0] = i;
    for (int j = 0; j <= l2; j++) matrix[0][j] = j;

    for (int i = 1; i <= l1; i++) {
        for (int j = 1; j <= l2; j++) {
            int cost = (tolower(s1[i-1]) == tolower(s2[j-1])) ? 0 : 1;
            matrix[i][j] = min3(
                matrix[i-1][j] + 1,        // Xoa
                matrix[i][j-1] + 1,        // Them
                matrix[i-1][j-1] + cost    // Thay the
            );
        }
    }
    return matrix[l1][l2];
}

// Ham ho tro: Kiem tra xem mot tu co bat dau bang chuoi nhap vao khong (Khong phan biet hoa thuong)
int startsWithIgnoreCase(const char *prefix, const char *str) {
    while (*prefix) {
        if (tolower(*prefix) != tolower(*str)) return 0;
        prefix++;
        str++;
    }
    return 1;
}

// HAM TRA TU CHINH (THAY THE CHO wordSearch CU)
void advancedWordSearch(Node* head, char* english) {
    Node* temp = head;
    int foundExact = 0;

    // 1. Tim chinh xac truoc
    while (temp != NULL) {
        if (strcasecmp(temp->word, english) == 0) {
            setColor(10);
            printf("\t=> Ket qua: %s nghia la '%s'\n", temp->word, temp->meaning);
            setColor(7);
            foundExact = 1;
            break;
        }
        temp = temp->next;
    }

    // 2. Neu tim thay roi thi dung lai
    if (foundExact) return;

    // 3. Neu KHONG tim thay, bat dau thuat toan goi y
    setColor(14); // Mau vang hien thi canh bao
    printf("\t=> Khong tim thay tu '%s'. Co the ban muon tim:\n", english);
    setColor(7);

    temp = head;
    int suggestionCount = 0;

    printf("\t--------------------------------------------------\n");
    while (temp != NULL) {
        // Tính toán khoảng cách lỗi cho phép dựa trên độ dài từ bạn nhập
        int allowedError = (strlen(english) <= 3) ? 1 : 2;

        // Truong hop 1: Tu trong tu dien bat dau bang chuoi ban vua go (Goi y tu dien)
        if (startsWithIgnoreCase(english, temp->word)) {
            printf("\t   [Tu dien] %-15s | %-20s\n", temp->word, temp->meaning);
            suggestionCount++;
        }
        // Truong hop 2: Ban go sai chinh ta (Sua loi) theo nguong an toan
        else if (levenshtein(english, temp->word) <= allowedError) {
            // Loại trừ những từ có độ lệch chiều dài quá lớn (vd: gõ 'fam' nhưng gợi ý 'family' ở mục Sửa lỗi)
            if (abs((int)strlen(english) - (int)strlen(temp->word)) <= allowedError) {
                printf("\t   [Sua loi] %-15s | %-20s\n", temp->word, temp->meaning);
                suggestionCount++;
            }
        }

        if (suggestionCount >= 5) break; // Chi hien thi toi da 5 tu de man hinh khong bi roi
        temp = temp->next;
    }

    if (suggestionCount == 0) {
        setColor(12);
        printf("\t   Khong co tu nao gan giong trong he thong.\n");
        setColor(7);
    }
    printf("\t--------------------------------------------------\n");
}


static void getCurrentTime(char* buf, int bufSize) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    strftime(buf, bufSize, "%d/%m/%Y %H:%M:%S", t);
}


/*
 * Format moi dong trong history.txt:
 *   keyword|result|dd/mm/yyyy hh:mm:ss|hit_count
 * Vi du:
 *   Apple|Qua tao|18/05/2025 14:30:00|3
 */

void saveSearchHistory(const char* keyword, const char* result, const char* filename) {
    // --- Buoc 1: Doc toan bo file cu vao RAM ---
    FILE* f = fopen(filename, "r");
    
    // Mang tam luu noi dung cu (toi da 2000 tu lich su)
    char lines[2000][400];
    int lineCount = 0;
    int foundIdx = -1;  // Vi tri dong cua tu nay neu da ton tai

    if (f != NULL) {
        char buf[400];
        while (fgets(buf, sizeof(buf), f) && lineCount < 2000) {
            buf[strcspn(buf, "\n")] = 0;  // Xoa newline
            
            // Tach keyword de kiem tra trung
            char temp[400];
            strcpy(temp, buf);
            char* existingKey = strtok(temp, "|");
            
            if (existingKey != NULL && strcasecmp(existingKey, keyword) == 0) {
                foundIdx = lineCount;  // Danh dau dong nay se bi ghi de
            }
            strcpy(lines[lineCount++], buf);
        }
        fclose(f);
    }

    // --- Buoc 2: Tinh hit_count ---
    int hitCount = 1;
    if (foundIdx != -1) {
        // Parse hit_count tu dong cu: keyword|result|timestamp|hit_count
        char temp[400];
        strcpy(temp, lines[foundIdx]);
        strtok(temp, "|");  // bo qua keyword
        strtok(NULL, "|");  // bo qua result
        strtok(NULL, "|");  // bo qua timestamp
        char* countStr = strtok(NULL, "|");
        if (countStr != NULL) hitCount = atoi(countStr) + 1;
    }

    // --- Buoc 3: Tao dong moi ---
    char timestamp[30];
    getCurrentTime(timestamp, sizeof(timestamp));

    char newLine[400];
    snprintf(newLine, sizeof(newLine), "%s|%s|%s|%d", keyword, result, timestamp, hitCount);

    // --- Buoc 4: Ghi lai file, thay the dong cu (neu co) bang dong moi ---
    f = fopen(filename, "w");
    if (f == NULL) {
        printf("\tKhong the ghi file lich su!\n");
        return;
    }

    int i;
    for (i = 0; i < lineCount; i++) {
        if (i == foundIdx) continue;  // Bo qua dong cu cua tu nay
        fprintf(f, "%s\n", lines[i]);
    }
    fprintf(f, "%s\n", newLine);  // Ghi dong moi vao cuoi

    fclose(f);
}

// Ham cat khoang trang 2 dau chuoi
static void trimStr(char* str) {
    // Cat dau
    int start = 0;
    while (str[start] == ' ' || str[start] == '\t' || str[start] == '\r')
        start++;
    if (start > 0) memmove(str, str + start, strlen(str) - start + 1);

    // Cat duoi
    int end = strlen(str) - 1;
    while (end >= 0 && (str[end] == ' ' || str[end] == '\t' || str[end] == '\r'))
        str[end--] = '\0';
}

/*
 * Ham don dep file lich su:
 *  1. Xoa cac dong bi lap (giu lai dong co hit_count cao nhat)
 *  2. Xoa cac dong co result = "Khong tim thay"
 */
void cleanHistory(const char* histFilename, Node* dictHead) {
    FILE* f = fopen(histFilename, "r");
    if (f == NULL) {
        setColor(12);
        printf("\tKhong co file lich su de don dep.\n");
        setColor(7);
        return;
    }

    // --- Buoc 1: Doc toan bo file vao RAM ---
    char lines[2000][400];
    int lineCount = 0;

    char buf[400];
    while (fgets(buf, sizeof(buf), f) && lineCount < 2000) {
        buf[strcspn(buf, "\n")] = 0;
        if (strlen(buf) == 0) continue;  // Bo qua dong trong
        strcpy(lines[lineCount++], buf);
    }
    fclose(f);

    // --- Buoc 2: Loc tung dong ---
    // Dung mang danh dau dong nao se duoc giu lai
    int keep[2000] = {0};  // 0 = xoa, 1 = giu

    int i, j;
    for (i = 0; i < lineCount; i++) {
        char temp[400];
        strcpy(temp, lines[i]);

        char* kw     = strtok(temp, "|");
        char* res    = strtok(NULL, "|");
        strtok(NULL, "|");               // bo timestamp
        char* hitStr = strtok(NULL, "|");
        
        if (kw == NULL || res == NULL) continue;  // Dong loi dinh dang

        trimStr(kw);   // <-- THEM
        trimStr(res);  // <-- THEM DONG NAY LA CHINH

        // --- Dieu kien 1: Xoa neu result la "Khong tim thay" ---
        if (strcasecmp(res, "Khong tim thay") == 0) continue;

        // --- Dieu kien 2: Kiem tra co trong tu dien khong ---
        // (Phong truong hop tu da bi xoa khoi tu dien sau khi tra)
        int inDict = 0;
        Node* node = dictHead;
        while (node != NULL) {
            if (strcasecmp(node->word, kw) == 0) {
                inDict = 1;
                break;
            }
            node = node->next;
        }
        if (!inDict) continue;

        // --- Dieu kien 3: Xu ly trung lap ---
        // Neu cung keyword xuat hien nhieu lan, giu dong co hit_count cao nhat
        int currentHit = (hitStr != NULL) ? atoi(hitStr) : 1;
        int isDuplicate = 0;

        for (j = 0; j < lineCount; j++) {
            if (i == j) continue;

            char temp2[400];
            strcpy(temp2, lines[j]);
            char* kw2     = strtok(temp2, "|");
            char* res2    = strtok(NULL, "|");
            strtok(NULL, "|");
            char* hitStr2 = strtok(NULL, "|");

            if (kw2 == NULL) continue;
            if (strcasecmp(kw2, kw) != 0) continue;  // Khac tu, bo qua

            // Cung tu -> so sanh hit_count
            int otherHit = (hitStr2 != NULL) ? atoi(hitStr2) : 1;

            if (currentHit < otherHit) {
                // Dong hien tai thua kem -> danh dau xoa
                isDuplicate = 1;
                break;
            } else if (currentHit == otherHit && i < j) {
                // Bang diem -> giu dong co index lon hon (moi hon)
                isDuplicate = 1;
                break;
            }
        }

        if (!isDuplicate) keep[i] = 1;
    }

    // --- Buoc 3: Ghi lai file voi nhung dong duoc giu ---
    f = fopen(histFilename, "w");
    if (f == NULL) {
        printf("\tKhong the ghi lai file lich su!\n");
        return;
    }

    int savedCount = 0;
    int removedCount = 0;
    for (i = 0; i < lineCount; i++) {
        if (keep[i]) {
            fprintf(f, "%s\n", lines[i]);
            savedCount++;
        } else {
            removedCount++;
        }
    }
    fclose(f);

    // --- Buoc 4: Thong bao ket qua ---
    setColor(10);
    printf("\tDon dep hoan tat!\n");
}
// Hàm in lịch sử nâng cao: Tự động dọn rác và hiển thị từ mới nhất lên đầu
void printHistory(const char* filename, Node* dictHead) {
    // 1. Tự động gọi hàm dọn dẹp của bạn để lọc trùng và xóa "Khong tim thay" trước khi in
    cleanHistory(filename, dictHead);
    
    clearScreen();
    boxHeader("LICH SU TRA CUU (MOI NHAT LEN DAU)");

    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        setColor(12);
        printf("\tChua co lich su tra cuu nao.\n");
        setColor(7);
        printf("\n\tBam phim bat ky de quay lai menu...");
        getch();
        return;
    }

    // Mảng tạm để lưu các dòng từ file nhằm mục đích in ngược
    char lines[2000][400];
    int lineCount = 0;
    char buf[400];

    // 2. Đọc toàn bộ dữ liệu đã sạch vào mảng RAM
    while (fgets(buf, sizeof(buf), f) && lineCount < 2000) {
        buf[strcspn(buf, "\n")] = 0; // Xóa ký tự xuống dòng
        if (strlen(buf) > 0) {
            strcpy(lines[lineCount++], buf);
        }
    }
    fclose(f);

    if (lineCount == 0) {
        setColor(12);
        printf("\tChua co lich su tra cuu nao hien tai.\n");
        setColor(7);
        printf("\n\tBam phim bat ky de quay lai menu...");
        getch();
        return;
    }

    // In tiêu đề bảng lịch sử
    setColor(10); // Màu xanh lá
    printf("\t%-3s | %-18s | %-20s | %-20s | %s\n", "STT", "TU DA TRA", "KET QUA", "THOI GIAN TRA", "SO LAN");
    printf("\t-------------------------------------------------------------------------------------\n");
    setColor(7);

    int displayCount = 1;
    
    // 3. Vòng lặp in ngược: Duyệt từ cuối mảng lên đầu mảng (Từ mới tra luôn ở dưới cùng file -> đưa lên đầu)
    for (int i = lineCount - 1; i >= 0; i--) {
        char temp[400];
        strcpy(temp, lines[i]);

        // Bóc tách dữ liệu theo định dạng chuỗi của bạn
        char* kw     = strtok(temp, "|");
        char* res    = strtok(NULL, "|");
        char* ts     = strtok(NULL, "|");
        char* hitStr = strtok(NULL, "|");

        if (kw && res && ts && hitStr) {
            printf("\t%3d | %-18s | %-20s | %-20s | x%s\n",
                   displayCount++, kw, res, ts, hitStr);
        }
    }

    printf("\t-------------------------------------------------------------------------------------\n");
    printf("\n\tBam phim bat ky de quay lai menu...");
    getch();
}

// === CHUC NANG HOC TAP: MINI GAME KIEM TRA TU VUNG (CO VONG LAP) ===
void randomQuizFromHistory(const char* histFilename) {
    FILE* f;
    char lines[2000][400];
    int lineCount = 0;
    char buf[400];
    int randomIndex;
    char temp[400];
    char *kw, *res;
    char userAnswer[200];
    
    // 1. Doc toan bo lich su sach vao mang (Chi doc 1 lan truoc khi vao vong lap de do lag)
    f = fopen(histFilename, "r");
    if (f == NULL) {
        clearScreen();
        boxHeader("MINI GAME: ON TAP TU VUNG");
        setColor(12);
        printf("\tBan chua co lich su tra cuu nao de kiem tra. Hay tra tu truoc nhe!\n");
        setColor(7);
        printf("\n\tBam phim bat ky de quay lai menu...");
        getch();
        return;
    }

    while (fgets(buf, sizeof(buf), f) && lineCount < 2000) {
        buf[strcspn(buf, "\n")] = 0; // Xoa newline
        if (strlen(buf) > 0) {
            strcpy(lines[lineCount++], buf);
        }
    }
    fclose(f);

    if (lineCount == 0) {
        clearScreen();
        boxHeader("MINI GAME: ON TAP TU VUNG");
        setColor(12);
        printf("\tLich su tra cuu dang trong. Hay tra them tu moi nhe!\n");
        setColor(7);
        printf("\n\tBam phim bat ky de quay lai menu...");
        getch();
        return;
    }

    // Khoi tao hat giong random theo thoi gian thuc
    srand((unsigned int)time(NULL)); 

    // === VONG LAP GAME ===
    while (1) {
        clearScreen();
        boxHeader("MINI GAME: ON TAP TU VUNG");

        // 2. Tao so ngau nhien de boc 1 tu
        randomIndex = rand() % lineCount;

        // 3. Tach tu tieng Anh va nghia tieng Viet tu dong duoc chon
        strcpy(temp, lines[randomIndex]);
        kw = strtok(temp, "|");
        res = strtok(NULL, "|");

        if (kw == NULL || res == NULL) {
            printf("\tLoi doc du lieu!\n");
            getch();
            break;
        }

        trimStr(kw);
        trimStr(res);

        // 4. Hien thi cau hoi
        setColor(14); // Mau vang
        printf("\tCau hoi: Nghia cua tu '%s' la gi?\n", kw);
        setColor(11); // Mau xanh ngoc canh bao
        printf("\t(Nhap '0' de ket thuc tro choi)\n");
        setColor(7);
        printf("\tNhap cau tra loi cua ban: ");
        
        // Nhan cau tra loi tu nguoi dung
        fgets(userAnswer, sizeof(userAnswer), stdin);
        removeNewline(userAnswer);
        trimStr(userAnswer);

        // Kiem tra dieu kien THOAT
        if (strcmp(userAnswer, "0") == 0) {
            setColor(10);
            printf("\n\t=> Da thoat che do on tap. Hen gap lai!\n");
            setColor(7);
            break; // THOAT VONG LAP GAME
        }

        printf("\t--------------------------------------------------\n");
        
        // 5. So sanh ket qua
        if (strcasecmp(userAnswer, res) == 0) {
            setColor(10); // Mau xanh la
            printf("\t=> CHINH XAC! Ban that xuat sac!\n");
        } else {
            setColor(12); // Mau do
            printf("\t=> SAI ROI! \n");
            setColor(11); // Mau xanh duong nhat
            printf("\t=> Nghia dung phai la: '%s'\n", res);
        }
        setColor(7);
        printf("\t--------------------------------------------------\n");
        
        printf("\n\tBam phim bat ky de tiep tuc sang cau hoi khac...");
        getch(); // Dung lai xem ket qua truoc khi vong lap reset
    }

    printf("\n\tBam phim bat ky de quay lai menu chinh...");
    getch();
}

// ============================================================
//  FLASHCARD HELPER: Ve khung ASCII bao quanh noi dung the
//  - content: chuoi can hien thi ben trong khung
//  - frameColor: ma mau cua khung vien (Windows console color)
// ============================================================
static void drawFlashCard(const char* content, int frameColor) {
    // Do rong cua khung the (tinh theo ky tu, khong tinh indent tab)
    const int CARD_WIDTH = 50;

    // --- Dong tren cung: +--...--+ ---
    setColor(frameColor);
    printf("\n\t+");
    int i;
    for (i = 0; i < CARD_WIDTH; i++) printf("-");
    printf("+\n");

    // --- Hang trong phia tren ---
    printf("\t|");
    for (i = 0; i < CARD_WIDTH; i++) printf(" ");
    printf("|\n");

    // --- Dong noi dung: can giua trong khung ---
    int contentLen = (int)strlen(content);
    int totalPad   = CARD_WIDTH - contentLen;
    int padLeft    = (totalPad > 0) ? totalPad / 2 : 0;
    int padRight   = (totalPad > 0) ? totalPad - padLeft : 0;

    printf("\t|");
    for (i = 0; i < padLeft;  i++) printf(" ");
    setColor(14);          // Mau vang cho chu
    printf("%s", content);
    setColor(frameColor);  // Tra mau khung
    for (i = 0; i < padRight; i++) printf(" ");
    printf("|\n");

    // --- Hang trong phia duoi ---
    printf("\t|");
    for (i = 0; i < CARD_WIDTH; i++) printf(" ");
    printf("|\n");

    // --- Dong duoi cung: +--...--+ ---
    printf("\t+");
    for (i = 0; i < CARD_WIDTH; i++) printf("-");
    printf("+\n");

    setColor(7); // Reset mau
}

void flashcardReview(const char* histFilename) {
    // --- Cau truc luu thong tin moi the ---
    typedef struct {
        char word[100];    // Tu tieng Anh
        char meaning[200]; // Nghia tieng Viet
    } FlashCard;

    FILE* f;
    char buf[400];

    // 1. Hien thi man hinh gioi thieu
    clearScreen();
    boxHeader("MINI GAME: FLASHCARD LUYEN TU VUNG");

    // 2. Doc lich su tra cuu de lay danh sach tu
    f = fopen(histFilename, "r");
    if (f == NULL) {
        setColor(12);
        printf("\n\tBan chua co lich su tra cuu nao.\n");
        printf("\tHay tra tu o muc [1] truoc khi luyen tap nhe!\n");
        setColor(7);
        printf("\n\tBam phim bat ky de quay lai menu...");
        getch();
        return;
    }

    /*
     * HANG DOI (QUEUE) DONG:
     *   - capacity: so the toi da hien tai (cap phat bang malloc/realloc)
     *   - qSize   : so the dang co trong hang doi (cap nhat lien tuc)
     *   - front   : chi so the dang duoc hoc (tang dan, khong bao gio giam)
     *
     * Khi nguoi dung chon [2] (Kho), the duoc sao chep vao cuoi mang
     * (qSize++) de hoc lai sau. Khi front == qSize thi da hoc het.
     */
    int capacity = 500;
    FlashCard* queue = (FlashCard*)malloc(capacity * sizeof(FlashCard));
    if (queue == NULL) {
        fclose(f);
        printf("\tLoi cap phat bo nho!\n");
        getch();
        return;
    }
    int qSize = 0; // Tong so the trong hang doi (tang khi them the kho)
    int front = 0; // The dang hoc hien tai

    // Doc tung dong file lich su va nap vao hang doi
    while (fgets(buf, sizeof(buf), f) && qSize < capacity) {
        buf[strcspn(buf, "\n")] = 0;
        if (strlen(buf) == 0) continue;

        char temp[400];
        strcpy(temp, buf);
        char* kw  = strtok(temp, "|");
        char* res = strtok(NULL, "|");

        if (kw == NULL || res == NULL) continue;

        trimStr(kw);
        trimStr(res);

        // Loai bo entry "Khong tim thay"
        if (strcasecmp(res, "Khong tim thay") == 0) continue;

        strncpy(queue[qSize].word,    kw,  sizeof(queue[qSize].word)    - 1);
        strncpy(queue[qSize].meaning, res, sizeof(queue[qSize].meaning) - 1);
        queue[qSize].word[sizeof(queue[qSize].word)-1]       = '\0';
        queue[qSize].meaning[sizeof(queue[qSize].meaning)-1] = '\0';
        qSize++;
    }
    fclose(f);

    if (qSize == 0) {
        setColor(12);
        printf("\n\tDanh sach tu hoc trong. Hay tra them tu moi nhe!\n");
        setColor(7);
        printf("\n\tBam phim bat ky de quay lai menu...");
        free(queue);
        getch();
        return;
    }

    // Hien thi huong dan ngan
    int totalOriginal = qSize; // So the goc (truoc khi them the kho)
    setColor(11);
    printf("\n\t  Tong so the: %d tu\n", totalOriginal);
    printf("\t  Enter    = Lat the xem nghia\n");
    printf("\t  [1]      = De / Da thuoc  -> qua the tiep theo\n");
    printf("\t  [2]      = Kho / Chua thuoc -> on lai o cuoi hang doi\n");
    printf("\t  [0]      = Ket thuc phien hoc\n");
    setColor(7);
    printf("\n\tNhan phim bat ky de bat dau...");
    getch();

    // Thong ke phien hoc
    int countEasy = 0;
    int countHard = 0;
    int quitEarly = 0; // Co hieu nguoi dung tu thoat bang [0]

    // ========================
    //   VONG LAP CHINH GAME
    // ========================
    while (front < qSize) {

        // --- Buoc A: Hien thi MAT TRUOC (tieng Anh) ---
        clearScreen();
        boxHeader("MINI GAME: FLASHCARD LUYEN TU VUNG");

        // Tinh so the chua hoc va so the kho con lai
        int remaining   = qSize - front;      // The chua hoc (ke ca the kho)
        int hardPending = qSize - totalOriginal + countHard - /* so the kho da thuoc */
                          (countHard - (qSize - totalOriginal)); 
        // Cach tinh don gian hon: the kho con lai = (qSize - totalOriginal) - (the kho da thuoc)
        // "the kho da thuoc" = nhung the duoc them vao (qSize - totalOriginal) nhung da qua front
        int hardTotal  = qSize - totalOriginal; // Tong the kho da tung them
        int hardDone   = (front > totalOriginal) ? (front - totalOriginal) : 0;
        int hardLeft   = hardTotal - hardDone; // The kho chua on xong
        (void)hardLeft; // Tranh canh bao unused variable

        setColor(11);
        printf("\n\t  The %d/%d  |  Con lai: %d  |  De: %d  |  Kho : %d\n",
               front + 1, qSize, remaining, countEasy, hardTotal - hardDone);
        setColor(7);

        printf("\n");
        setColor(14);
        printf("\t  *** MAT TRUOC - TU TIENG ANH ***\n");
        setColor(7);
        drawFlashCard(queue[front].word, 11); // Khung xanh cyan

        setColor(11);
        printf("\n\t  [Nhan Enter de lat the xem nghia]");
        printf("   [0 + Enter = Thoat]\n");
        setColor(7);

        // Cho nguoi dung nhan Enter (hoac go '0' de thoat)
        {
            char inputBuf[10];
            fgets(inputBuf, sizeof(inputBuf), stdin);
            removeNewline(inputBuf);
            trimStr(inputBuf);
            if (strcmp(inputBuf, "0") == 0) {
                quitEarly = 1;
                break;
            }
        }

        // --- Buoc B: LAT THE - Hien thi MAT SAU (nghia tieng Viet) ---
        clearScreen();
        boxHeader("MINI GAME: FLASHCARD LUYEN TU VUNG");

        setColor(11);
        printf("\n\t  The %d/%d  |  Con lai: %d  |  De: %d  |  Kho (hang doi): %d\n",
               front + 1, qSize, remaining, countEasy, hardTotal - hardDone);
        setColor(7);

        printf("\n");
        setColor(7);
        printf("\t  Tu: ");
        setColor(14);
        printf("%s\n", queue[front].word);
        setColor(7);

        printf("\n");
        setColor(10);
        printf("\t  *** MAT SAU - NGHIA TIENG VIET ***\n");
        setColor(7);
        drawFlashCard(queue[front].meaning, 10); // Khung xanh la

        // --- Buoc C: Danh gia ---
        setColor(14);
        printf("\n\t  Tu danh gia:\n");
        setColor(10);  printf("\t  [1] De / Da thuoc\n");
        setColor(12);  printf("\t  [2] Kho / Chua thuoc \n");
        setColor(7);   printf("\t  Lua chon cua ban: ");

        char evalBuf[10];
        int evalKey = 0;
        while (evalKey != 1 && evalKey != 2) {
            fgets(evalBuf, sizeof(evalBuf), stdin);
            removeNewline(evalBuf);
            trimStr(evalBuf);
            if (strcmp(evalBuf, "0") == 0) {
                evalKey = -1;
                break;
            }
            evalKey = atoi(evalBuf);
            if (evalKey != 1 && evalKey != 2) {
                setColor(12);
                printf("\t  Vui long nhan [1] hoac [2]: ");
                setColor(7);
            }
        }

        if (evalKey == -1) {
            quitEarly = 1;
            break;
        }

        if (evalKey == 1) {
            // De / Da thuoc: bo qua the nay, chuyen sang the ke tiep
            countEasy++;
            setColor(10);
            printf("\n\t  Tuyet voi! Tiep tuc nao!\n");
            setColor(7);
        } else {
            // Kho / Chua thuoc: SAO CHEP the nay vao CUOI hang doi
            countHard++;

            // Mo rong mang neu can (realloc khi sap het cho)
            if (qSize >= capacity) {
                capacity += 200;
                FlashCard* newQueue = (FlashCard*)realloc(queue, capacity * sizeof(FlashCard));
                if (newQueue == NULL) {
                    // Neu realloc that bai, bo qua buoc them the kho (van tiep tuc)
                    setColor(12);
                    printf("\n\t  Canh bao: Khong du bo nho de them the kho vao hang doi!\n");
                    setColor(7);
                    front++;
                    Sleep(700);
                    continue;
                }
                queue = newQueue;
            }

            // Sao chep the hien tai vao cuoi hang doi
            strncpy(queue[qSize].word,    queue[front].word,    sizeof(queue[qSize].word)    - 1);
            strncpy(queue[qSize].meaning, queue[front].meaning, sizeof(queue[qSize].meaning) - 1);
            queue[qSize].word[sizeof(queue[qSize].word)-1]       = '\0';
            queue[qSize].meaning[sizeof(queue[qSize].meaning)-1] = '\0';
            qSize++; // Hang doi dai them 1

            setColor(12);
            printf("\n\t  Khong sao! The nay se duoc on lai o cuoi hang doi.\n");
            setColor(7);
        }

        front++; // Luon chuyen sang the tiep theo sau khi danh gia
        Sleep(700);
    }

    // =====================================================
    //   KET THUC: Hoc het hoac nguoi dung tu thoat [0]
    // =====================================================
    clearScreen();

    if (!quitEarly) {
        // --- Truong hop 1: HOC HET TAT CA TU VUNG ---
        boxHeader("HOAN THANH PHIEN HOC");
        setColor(10);
        printf("\n\t  ***********************************************\n");
        printf("\t  *                                             *\n");
        printf("\t  *  Ban da hoc het tu vung co trong flashcard! *\n");
        printf("\t  *                                             *\n");
        printf("\t  ***********************************************\n\n");
        setColor(11);
        printf("\t  Tong so the goc    : %d\n", totalOriginal);
        printf("\t  Luot on lai (Kho)  : %d\n", qSize - totalOriginal);
        setColor(10);
        printf("\t  Lan thuoc cuoi cung: %d\n", countEasy);
        setColor(7);
    } else {
        // --- Truong hop 2: Nguoi dung tu thoat som ---
        boxHeader("TONG KET PHIEN HOC");
        int totalSeen = front; // So the da di qua
        setColor(11);
        printf("\n\t  The da xem         : %d / %d\n", totalSeen, qSize);
        setColor(10);
        printf("\t  De / Da thuoc      : %d\n", countEasy);
        setColor(12);
        printf("\t  Kho / Chua thuoc   : %d\n", countHard);
        setColor(7);

        if (totalSeen > 0) {
            int percent = (countEasy * 100) / totalSeen;
            printf("\n\t  Ti le thuoc bai    : %d%%\n", percent);
            if (percent >= 80) {
                setColor(10);
                printf("\t  Xuat sac! Ban hoc rat tot hom nay!\n");
            } else if (percent >= 50) {
                setColor(14);
                printf("\t  Kha day! Co gang them mot chut nua nhe!\n");
            } else {
                setColor(12);
                printf("\t  Hay on tap them nhung tu kho ban nhe!\n");
            }
            setColor(7);
        }
    }

    free(queue);
    printf("\n\tBam phim bat ky de quay lai menu chinh...");
    getch();
}
