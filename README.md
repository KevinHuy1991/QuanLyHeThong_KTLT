# 📘 BÀI TẬP LỚN : HỆ THỐNG QUẢN LÝ TỪ ĐIỂN ANH - VIỆT (C)

Ứng dụng quản lý từ điển Anh - Việt sử dụng cấu trúc dữ liệu **Danh sách liên kết đơn (Linked List)** để lưu trữ và xử lý dữ liệu vựng trực tiếp trên RAM, hỗ trợ lưu trữ bền vững qua tệp tin văn bản[cite: 1, 2, 3].

---

## 👥 PHÂN CÔNG NHIỆM VỤ

Dự án được thực hiện bởi nhóm 4 thành viên, chia thành 2 nhóm chuyên trách để phối hợp làm việc trên GitHub:

### **Nhóm 2: Xử lý Logic & Cấu trúc (ENGVIEdict.h & ENGVIEdict.c)**
*   **Nguyễn Nhật Huy (Nhóm trưởng):**
    *   Thiết kế cấu trúc dữ liệu `Node` cho từ điển.
    *   Viết hàm `removeNewline`: Chuẩn hóa chuỗi nhập từ bàn phím.
    *   Viết hàm `dictionaryPrinting`: Xuất toàn bộ từ điển ra màn hình[cite: 1].
    *   Viết hàm `wordSearch`: Tìm kiếm từ vựng (không phân biệt hoa thường)[cite: 1].
    *   Viết hàm `removeWord`: Xóa từ vựng.[cite 1]
    *   Viết hàm `updateMeaning`: Cập nhật lại nghĩa của từ vựng.[cite 1]
*   **Lê Cường Bảo:**
    *   Viết hàm `addWord`: Thêm một từ vựng mới vào danh sách liên kết[cite: 1].
    *   Viết hàm `loadDictionaryFromFile`: Nạp dữ liệu từ file vào chương trình khi khởi động[cite: 1].
    *   Viết hàm `saveDictionaryToFile`: Ghi lại toàn bộ dữ liệu vào file khi thoát[cite: 1].
    *   Viết hàm `freeMemory`: Giải phóng bộ nhớ động để tránh rò rỉ RAM[cite: 1].

### **Nhóm 1: Giao diện & Điều khiển (main.c)**
*   **Nguyễn Thị Ngọc Đẹp:**
    *   Thiết kế menu lựa chọn và cấu trúc vòng lặp điều hướng.
*   **Nguyễn Thanh Huy:**
    *   Xử lý logic `switch-case` và kết nối các hàm logic vào giao diện người dùng.
    *   Xử lý bộ nhớ đệm (buffer) để tránh lỗi nhập liệu.

---

## 📖 HƯỚNG DẪN SỬ DỤNG

### **1. Cấu trúc mã nguồn**
*   `ENGVIEdict.h`: Chứa khai báo cấu trúc và các nguyên mẫu hàm[cite: 2].
*   `ENGVIEdict.c`: Chứa nội dung cài đặt chi tiết của các hàm chức năng[cite: 1].
*   `main.c`: Chương trình chính thực thi Menu và tương tác người dùng[cite: 3].

### **2. Cách biên dịch và chạy**
Sử dụng trình biên dịch GCC để kết hợp các file nguồn:
```bash
# Biên dịch
gcc main.c ENGVIEdict.c -o dictionary

# Chạy ứng dụng
./dictionary
