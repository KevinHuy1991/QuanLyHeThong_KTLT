#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "ENGVIEdict.h"
#include "gemini.h"  //Goi ham tu Gemini API

int main() {
    SetConsoleOutputCP(437);
    Node* dictionary = NULL;
    HistoryNode* history = NULL;
    int choice;
    char english[100], vietnamese[200];
    const char* filename = "dictionary.txt";
    const char* historyFile = "history.txt";
    loadDictionaryFromFile(&dictionary, filename);
    sortDictionary(&dictionary);

    clearScreen();
    setColor(11);
    slowPrint("\n\t[SYSTEM] Dang khoi tao tu dien Anh - Viet...\n", 20);
    slowPrint("\t[SYSTEM] San sang!\n", 20);
    Sleep(500);

    do {
        clearScreen();
        boxHeader("TU DIEN ANH - VIET");
        
        setColor(14); printf("\t1. "); setColor(7); printf("Tra cuu tu vung\n");
        setColor(14); printf("\t2. "); setColor(7); printf("Them tu moi \n");
        setColor(14); printf("\t3. "); setColor(7); printf("In toan bo tu dien\n");
        setColor(14); printf("\t4. "); setColor(7); printf("Thay doi nghia cua tu\n");
        setColor(14); printf("\t5. "); setColor(7); printf("Xoa tu khoi he thong\n");
        setColor(14); printf("\t6. "); setColor(7); printf("Liet ke tu theo chu cai dau\n");
        setColor(14); printf("\t7. "); setColor(7); printf("Xem lich su tra cuu\n");
        setColor(14); printf("\t8. "); setColor(7); printf("On tap tu vung (Mini Game)\n");
        setColor(12); printf("\t0. "); setColor(7); printf("Luu du lieu va Thoat\n");
        
        printf("\t-------------------------------\n");
        printf("\tLua chon cua ban(0-8): ");
        if (scanf("%d", &choice) != 1) {
            choice = -1;
            while(getchar() != '\n');
        }
        getchar(); 

        switch (choice) {
            case 1:
                printf("\tNhap tu tieng Anh can tim: ");
                fgets(english, sizeof(english), stdin);
                removeNewline(english);

                advancedWordSearch(dictionary, english);

                {
                    Node* found = dictionary;
                    int isFound = 0; // Cờ kiểm tra
                    char histResult[200];
                    
                    while (found != NULL) {
                        if (strcasecmp(found->word, english) == 0) {
                            strncpy(histResult, found->meaning, sizeof(histResult) - 1);
                            isFound = 1; // Đánh dấu là đã tìm thấy
                            break;
                        }
                        found = found->next;
                    }
                    
                    // CHỈ GỌI HÀM LƯU VÀO LỊCH SỬ KHI TÌM THẤY TỪ
                    // Sau khi in ket qua advancedWordSearch, them:
                    if (isFound) {
                        saveSearchHistory(english, histResult, historyFile);
                        
                        printf("\n\tBan co muon xem chi tiet tu AI? (1=Co / 0=Khong): ");
                        int aiChoice;
                        scanf("%d", &aiChoice);
                        getchar();
                        if (aiChoice == 1) {
                            explainWord(english, histResult);    // Giai thich chi tiet
                            suggestRelatedWords(english);        // Goi y tu lien quan
                        }
                    }
                }

                printf("\n\tBam phim bat ky de quay lai menu...");
                getch();
                break;

            case 2: {
                /* Tat ca bien khai bao o dau block - tuong thich C89 */
                int inputOK;
                int attempts;
                int addResult;
                int isEmpty;
                int hasDigit;
                int hasSymbol;
                int k;
                const int MAX_ATTEMPTS = 3;

                /* ---------- NHAP TU TIENG ANH ---------- */
                inputOK = 0;
                attempts = 0;

                while (!inputOK && attempts < MAX_ATTEMPTS) {
                    attempts++;
                    printf("\tNhap tu tieng Anh: ");
                    fgets(english, sizeof(english), stdin);
                    removeNewline(english);

                    if (!isValidWord(english)) {
                        setColor(12);

                        /* Phan tich de in thong bao loi cu the hon */
                        isEmpty = 1;
                        for (k = 0; english[k]; k++) {
                            if (english[k] != ' ' && english[k] != '\t') {
                                isEmpty = 0;
                                break;
                            }
                        }

                        if (isEmpty) {
                            printf("\t[LOI] Tu tieng Anh khong duoc de trong.\n");
                        } else {
                            hasDigit = 0;
                            hasSymbol = 0;
                            for (k = 0; english[k]; k++) {
                                if (isdigit((unsigned char)english[k]))
                                    hasDigit = 1;
                                else if (!isalpha((unsigned char)english[k]) && english[k] != ' ')
                                    hasSymbol = 1;
                            }
                            if (hasDigit)
                                printf("\t[LOI] Tu tieng Anh khong duoc chua chu so (0-9).\n");
                            else if (hasSymbol)
                                printf("\t[LOI] Tu tieng Anh khong duoc chua ky tu dac biet.\n");
                            else
                                printf("\t[LOI] Tu tieng Anh khong hop le.\n");
                        }

                        if (attempts < MAX_ATTEMPTS)
                            printf("\tVui long nhap lai (%d lan con lai).\n",
                                   MAX_ATTEMPTS - attempts);
                        setColor(7);
                    } else {
                        inputOK = 1;
                    }
                }

                if (!inputOK) {
                    setColor(12);
                    printf("\n\t=> Da vuot qua so lan nhap toi da. Quay lai menu.\n");
                    setColor(7);
                    printf("\n\tBam phim bat ky de quay lai menu...");
                    getch();
                    break;
                }

                /* ---------- NHAP NGHIA TIENG VIET ---------- */
                inputOK = 0;
                attempts = 0;

                while (!inputOK && attempts < MAX_ATTEMPTS) {
                    attempts++;
                    printf("\tNhap nghia tieng Viet: ");
                    fgets(vietnamese, sizeof(vietnamese), stdin);
                    removeNewline(vietnamese);

                    if (!isValidMeaning(vietnamese)) {
                        setColor(12);
                        printf("\t[LOI] Nghia tieng Viet khong duoc de trong.\n");
                        if (attempts < MAX_ATTEMPTS)
                            printf("\tVui long nhap lai (%d lan con lai).\n",
                                   MAX_ATTEMPTS - attempts);
                        setColor(7);
                    } else {
                        inputOK = 1;
                    }
                }

                if (!inputOK) {
                    setColor(12);
                    printf("\n\t=> Da vuot qua so lan nhap toi da. Quay lai menu.\n");
                    setColor(7);
                    printf("\n\tBam phim bat ky de quay lai menu...");
                    getch();
                    break;
                }

                /* ---------- GHI VAO TU DIEN ---------- */
                addResult = addWord(&dictionary, english, vietnamese);

                if (addResult == 0) {
                    sortDictionary(&dictionary);
                    setColor(10);
                    printf("\t=> Da them tu '%s' vao tu dien thanh cong!\n", english);
                    setColor(7);
                }
                /* addResult == 1: tu trung, addWord() da xu ly va in thong bao roi */
                /* addResult == -1: loi bo nho, addWord() da in thong bao roi       */

                printf("\n\tBam phim bat ky de quay lai menu...");
                getch();
                break;
            }

            case 3: 
                dictionaryPrinting(dictionary);
                printf("\n\tBam phim bat ky de quay lai menu...");
                getch(); 
                break;

            case 4: {
                /* Khai bao bien o dau block - tuong thich C89 */
                int inputOK;
                int attempts;
                int k;
                int isEmpty;
                int hasDigit;
                int hasSymbol;
                const int MAX_ATTEMPTS = 3;

                /* ---------- NHAP TU TIENG ANH CAN SUA ---------- */
                inputOK = 0;
                attempts = 0;

                while (!inputOK && attempts < MAX_ATTEMPTS) {
                    attempts++;
                    printf("\tNhap tu tieng Anh can sua: ");
                    fgets(english, sizeof(english), stdin);
                    removeNewline(english);

                    if (!isValidWord(english)) {
                        setColor(12);

                        /* Phan tich loi cu the */
                        isEmpty = 1;
                        for (k = 0; english[k]; k++) {
                            if (english[k] != ' ' && english[k] != '\t') {
                                isEmpty = 0;
                                break;
                            }
                        }

                        if (isEmpty) {
                            printf("\t[LOI] Tu tieng Anh khong duoc de trong.\n");
                        } else {
                            hasDigit  = 0;
                            hasSymbol = 0;
                            for (k = 0; english[k]; k++) {
                                if (isdigit((unsigned char)english[k]))
                                    hasDigit = 1;
                                else if (!isalpha((unsigned char)english[k]) && english[k] != ' ')
                                    hasSymbol = 1;
                            }
                            if (hasDigit)
                                printf("\t[LOI] Tu tieng Anh khong duoc chua chu so (0-9).\n");
                            else if (hasSymbol)
                                printf("\t[LOI] Tu tieng Anh khong duoc chua ky tu dac biet.\n");
                            else
                                printf("\t[LOI] Tu tieng Anh khong hop le.\n");
                        }

                        if (attempts < MAX_ATTEMPTS)
                            printf("\tVui long nhap lai (%d lan con lai).\n",
                                   MAX_ATTEMPTS - attempts);
                        setColor(7);
                    } else {
                        inputOK = 1;
                    }
                }

                if (!inputOK) {
                    setColor(12);
                    printf("\n\t=> Da vuot qua so lan nhap toi da. Quay lai menu.\n");
                    setColor(7);
                    printf("\n\tBam phim bat ky de quay lai menu...");
                    getch();
                    break;
                }

                /* ---------- NHAP NGHIA TIENG VIET MOI ---------- */
                inputOK = 0;
                attempts = 0;

                while (!inputOK && attempts < MAX_ATTEMPTS) {
                    attempts++;
                    printf("\tNhap nghia tieng Viet moi: ");
                    fgets(vietnamese, sizeof(vietnamese), stdin);
                    removeNewline(vietnamese);

                    if (!isValidMeaning(vietnamese)) {
                        setColor(12);
                        printf("\t[LOI] Nghia tieng Viet khong duoc de trong hoac chi co khoang trang.\n");
                        if (attempts < MAX_ATTEMPTS)
                            printf("\tVui long nhap lai (%d lan con lai).\n",
                                   MAX_ATTEMPTS - attempts);
                        setColor(7);
                    } else {
                        inputOK = 1;
                    }
                }

                if (!inputOK) {
                    setColor(12);
                    printf("\n\t=> Da vuot qua so lan nhap toi da. Quay lai menu.\n");
                    setColor(7);
                    printf("\n\tBam phim bat ky de quay lai menu...");
                    getch();
                    break;
                }

                /* ---------- THUC HIEN CAP NHAT ---------- */
                updateMeaning(dictionary, english, vietnamese);
                printf("\n\tBam phim bat ky de quay lai menu...");
                getch();
                break;
            }

            case 5: 
                printf("\tNhap tu tieng Anh can xoa: ");
                fgets(english, sizeof(english), stdin);
                removeNewline(english);
                
                // Xóa từ khỏi bộ nhớ (Linked List)
                removeWord(&dictionary, english);
                
                // GỌI HÀM DỌN DẸP LỊCH SỬ NGAY SAU KHI XÓA TỪ
                cleanHistory(historyFile, dictionary); 
                
                printf("\n\tBam phim bat ky de quay lai menu...");
                getch(); 
                break;

            case 6:
                printf("\tNhap chu cai dau: ");
                char ch;
                scanf("%c", &ch);
                searchByFirstChar(dictionary, ch);
                printf("\n\tBam phim bat ky de quay lai menu...");
                getch(); 
                break;
            
            case 7:
                printHistory(historyFile, dictionary); 
                break;
            
            case 8:
                {
                    int quizChoice;
                    do {
                        clearScreen();
                        boxHeader("CHON CHE DO ON TAP");
                        setColor(14); printf("\t1. "); setColor(7); printf("On tap truyen thong (He thong tu ra de)\n");
                        setColor(14); printf("\t2. "); setColor(7); printf("On tap bang flashcard\n"); 
                        setColor(14); printf("\t3. "); setColor(11); printf("On tap thong minh cung AI Gemini\n");
                        setColor(12); printf("\t0. "); setColor(7); printf("Quay lai menu chinh\n");
                        printf("\t-------------------------------\n");
                        printf("\tLua chon cua ban: ");
                        
                        if (scanf("%d", &quizChoice) != 1) {
                            quizChoice = -1;
                            while(getchar() != '\n');
                        }
                        getchar();
                        if (quizChoice == 1) {
                            // Goi ham quiz truyen thong (da co san vong lap ben trong)
                            randomQuizFromHistory(historyFile); 
                        } 
                        else if (quizChoice == 2) {
                            // Goi ham flashcardReview voi ten file lich su
                            flashcardReview(historyFile);
                        }
                        else if (quizChoice == 3) {
                            // Goi ham quiz AI va boc vong lap cho no
                            char tiepTuc;
                            do {
                                clearScreen();
                                smartQuizFromHistory(historyFile); 
                                
                                setColor(14);
                                printf("\n\tBan co muon tiep tuc Quiz AI khong? (y/n): ");
                                setColor(7);
                                scanf(" %c", &tiepTuc);
                                getchar(); // Xoa bo dem ban phim
                            } while (tolower(tiepTuc) == 'y');
                        } 
                        else if (quizChoice != 0) {
                            setColor(12);
                            printf("\tLua chon khong hop le. Vui long nhap lai!\n");
                            setColor(7);
                            Sleep(1000);
                        }
                    } while (quizChoice != 0);
                }
                break;
            
            case 0: 
                setColor(11);
                slowPrint("\n\tDang luu file... \n", 30);
                setColor(7);
                break;

            default:
                setColor(12);
                printf("\tLua chon khong hop le. Vui long nhap lai!\n");
                setColor(7); getch();
        }
    } while (choice != 0);

    saveDictionaryToFile(dictionary, filename); 
    cleanHistory("history.txt", dictionary);
    freeMemory(&dictionary);

    return 0;
}