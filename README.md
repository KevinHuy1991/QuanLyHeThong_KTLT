# BÀI TẬP LỚN : HỆ THỐNG QUẢN LÝ TỪ ĐIỂN ANH - VIỆT (C)

Ứng dụng quản lý từ điển Anh - Việt sử dụng cấu trúc dữ liệu **Danh sách liên kết đơn (Linked List)** để lưu trữ và xử lý dữ liệu vựng trực tiếp trên RAM, hỗ trợ lưu trữ bền vững qua tệp tin văn bản[cite: 1, 2, 3].

---

## PHÂN CÔNG NHIỆM VỤ

Dự án được thực hiện bởi nhóm 4 thành viên, chia thành 2 nhóm chuyên trách để phối hợp làm việc trên GitHub:

### **Nhóm 2: Xử lý Logic & Cấu trúc (ENGVIEdict.h & ENGVIEdict.c)**
*   **Nguyễn Nhật Huy (Nhóm trưởng):**
    *   Thiết kế cấu trúc dữ liệu `Node` cho từ điển.
    *   Viết hàm `removeNewline`: Chuẩn hóa chuỗi nhập từ bàn phím.
    *   Viết hàm `dictionaryPrinting`: Xuất toàn bộ từ điển ra màn hình.
    *   Viết hàm `wordSearch`: Tìm kiếm từ vựng (không phân biệt hoa thường).
    *   Viết hàm `removeWord`: Xóa từ vựng.
    *   Viết hàm `updateMeaning`: Cập nhật lại nghĩa của từ vựng.
    *   Viết hàm `searchByFirstChar`: Liệt kê danh sách từ bắt đầu bằng chữ cái bất kỳ.
    * Nghiên cứu thuật toán khoảng cách Levenshtein (`advancedWordSearch`) hỗ trợ tính năng tự động gợi ý từ nếu gõ sai chính tả.
    * Phụ trách module AI (`gemini.c`, `gemini.h`): Thiết lập kết nối API mạng qua thư viện `libcurl`, viết hàm giải mã phản hồi JSON (`extractTextFromJSON`) và xây dựng các chức năng phân tích nâng cao (`explainWord`, `suggestRelatedWords`).
    *   Xử lý file history và các hàm xử lý `History`: Thống kê và đồng bộ dữ liệu học tập, làm cơ sở cho các hàm ôn tập.
    * Phát triển tính năng ôn tập từ vựng truyền thống (`randomQuizFromHistory`).
    * Xây dựng hệ thống tự động sinh trắc nghiệm thông minh dựa trên lịch sử tra cứu của người dùng (`smartQuizFromHistory`).
*   **Lê Cường Bảo:**
    *   Viết hàm `addWord`: Thêm một từ vựng mới vào danh sách liên kết.
    *   Viết hàm `loadDictionaryFromFile`: Nạp dữ liệu từ file vào chương trình khi khởi động.
    *   Viết hàm `saveDictionaryToFile`: Ghi lại toàn bộ dữ liệu vào file khi thoát.
    *   Viết hàm `freeMemory`: Giải phóng bộ nhớ động để tránh rò rỉ RAM.
    *   Viết hàm `flashcardReview`: Ôn tập bằng thẻ flashcard.
    * Thiết kế giao diện Console đồ họa ký tự có màu sắc trực quan (`setColor`, `slowPrint`).
    * Xây dựng bố cục các khối hộp tiêu đề (`boxHeader`).
### **Nhóm 1: Giao diện & Điều khiển (main.c)**
*   **Nguyễn Thị Ngọc Đẹp:**
    *   Thiết kế menu lựa chọn và cấu trúc vòng lặp điều hướng.
*   **Nguyễn Thanh Huy:**
    *   Xử lý logic `switch-case` và kết nối các hàm logic vào giao diện người dùng.
    *   Xử lý bộ nhớ đệm (buffer) để tránh lỗi nhập liệu.

---

## HƯỚNG DẪN SỬ DỤNG

### **1. Cấu trúc mã nguồn**
* `ENGVIEdict.h`: Chứa khai báo cấu trúc Node, HistoryNode và các nguyên mẫu hàm xử lý logic cơ sở.
* `ENGVIEdict.c`: Chứa nội dung cài đặt chi tiết của các hàm quản lý dữ liệu, sắp xếp và đồ họa giao diện cơ bản.
* `gemini.h`: Khai báo URL kết nối, chứa Struct mạng và quản lý biến hằng số mã khóa truy cập (API Key) của Google Gemini.
* `gemini.c`: Chứa toàn bộ logic giao tiếp mạng, xử lý gói dữ liệu thông qua `libcurl` và chức năng tương tác chuyên sâu với AI.
* `main.c`: Chương trình chính thực thi giao diện Menu và tương tác trực tiếp với người dùng.
* `dictionary.txt`: Cơ sở dữ liệu chính của hệ thống, lưu trữ từ vựng dưới dạng văn bản thuần túy (Format: `Từ Anh|Nghĩa Việt`).
* `history.txt`: Tệp tin lưu trữ dữ liệu các từ vựng đã được tra cứu thành công, làm dữ liệu đầu vào cho các chế độ Quiz.

### **2. Cấu hình bảo mật API Key**
Do mã khóa API không được đẩy trực tiếp lên GitHub để tuân thủ quy tắc bảo mật an toàn:
1. Bạn cần truy cập trang chủ **Google AI Studio** để khởi tạo một API Key (Hoàn toàn miễn phí).
2. Mở file `gemini.h` trong mã nguồn, tìm dòng khai báo API Key.
3. Thay thế biến `#define GEMINI_API_KEY` bằng chuỗi mã khóa của bạn (ví dụ: `"AIzaSy..."`) và lưu lại trước khi biên dịch.

### **3. Cách biên dịch và khởi chạy**
Hệ thống yêu cầu máy tính Windows đã cài đặt sẵn trình biên dịch **GCC** (qua MinGW/MSYS64) và có hỗ trợ thư viện truyền thông mạng **libcurl**.
Mở Terminal (PowerShell / Git Bash / Command Prompt) ngay tại thư mục chứa dự án và lần lượt gõ các lệnh sau:

```bash
# 1. Lệnh biên dịch liên kết gộp các file mã nguồn và thư viện mạng của Windows
gcc main.c ENGVIEdict.c gemini.c -o app -lcurl -lws2_32

# 2. Khởi chạy ứng dụng
./app
