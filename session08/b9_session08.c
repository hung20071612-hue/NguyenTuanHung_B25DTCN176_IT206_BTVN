#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Định nghĩa struct Student
struct Student {
    int id;
    char name[50];
    int age;
    float gpa;
};

// Hàm in danh sách sinh viên
void inDanhSach(struct Student students[], int n) {
    printf("\n");
    printf("+----+------------------+------+-------+\n");
    printf("| ID |      Name        | Age  |  GPA  |\n");
    printf("+----+------------------+------+-------+\n");
    
    for (int i = 0; i < n; i++) {
        printf("| %-2d | %-16s | %-4d | %5.2f |\n", 
               students[i].id, 
               students[i].name, 
               students[i].age, 
               students[i].gpa);
    }
    
    printf("+----+------------------+------+-------+\n");
    printf("\n");
}

// Hàm nhập thông tin sinh viên từ bàn phím
void nhapSinhVien(struct Student *sv) {
    printf("Nhap ID: ");
    scanf("%d", &sv->id);
    
    // Xóa bộ đệm để tránh lỗi khi nhập chuỗi
    while (getchar() != '\n');
    
    printf("Nhap ten: ");
    fgets(sv->name, sizeof(sv->name), stdin);
    // Xóa ký tự xuống dòng ở cuối chuỗi
    sv->name[strcspn(sv->name, "\n")] = 0;
    
    printf("Nhap tuoi: ");
    scanf("%d", &sv->age);
    
    printf("Nhap GPA: ");
    scanf("%f", &sv->gpa);
}

/**
 * @brief Thêm một sinh viên mới vào danh sách
 * 
 * MÔ TẢ CHỨC NĂNG:
 * -----------------
 * Hàm này cho phép thêm một sinh viên mới vào cuối danh sách hiện có.
 * Trước khi thêm, hàm sẽ kiểm tra các điều kiện để đảm bảo tính hợp lệ của dữ liệu.
 * 
 * CÁC BƯỚC XỬ LÝ:
 * ---------------
 * 
 * BƯỚC 1: KIỂM TRA ĐIỀU KIỆN ĐẦU VÀO
 * ----------------------------------
 * - Kiểm tra con trỏ students và newStudent không phải NULL
 * - Kiểm tra danh sách chưa đầy (n < maxSize)
 * - Nếu không thỏa mãn, trả về 0 và báo lỗi
 * 
 * BƯỚC 2: KIỂM TRA TRÙNG ID
 * -------------------------
 * - Duyệt qua toàn bộ danh sách hiện có
 * - So sánh ID của sinh viên mới với ID của từng sinh viên trong danh sách
 * - Nếu tìm thấy ID trùng, trả về -1 và báo lỗi "ID da ton tai"
 * - Điều này đảm bảo tính duy nhất của ID trong danh sách
 * 
 * BƯỚC 3: THÊM SINH VIÊN VÀO DANH SÁCH
 * -------------------------------------
 * - Gán sinh viên mới vào vị trí cuối cùng của mảng (students[*n])
 * - Tăng biến đếm số lượng sinh viên (*n)++
 * - Trả về 1 để báo hiệu thành công
 * 
 * XỬ LÝ CÁC TRƯỜNG HỢP ĐẶC BIỆT:
 * --------------------------------
 * - Trùng ID: Trả về -1, không thêm vào danh sách
 * - Danh sách đầy: Trả về 0, không thêm vào danh sách
 * - Thành công: Trả về 1, sinh viên đã được thêm vào
 * 
 * @param students Mảng chứa danh sách sinh viên (sẽ được cập nhật)
 * @param n Con trỏ đến biến đếm số lượng sinh viên (sẽ được tăng lên nếu thành công)
 * @param maxSize Kích thước tối đa của mảng (giới hạn số lượng sinh viên)
 * @param newStudent Con trỏ đến struct Student chứa thông tin sinh viên cần thêm
 * 
 * @return 1 nếu thêm thành công
 * @return 0 nếu danh sách đầy hoặc tham số không hợp lệ
 * @return -1 nếu ID đã tồn tại trong danh sách
 * 
 * @note Hàm sẽ thay đổi mảng students và biến n
 * @note ID phải là duy nhất trong danh sách
 * 
 * @example
 *   struct Student students[10];
 *   int n = 3;
 *   struct Student newStudent = {4, "Nguyen Van D", 20, 3.5};
 *   int result = themSinhVien(students, &n, 10, &newStudent);
 *   if (result == 1) {
 *       printf("Them thanh cong!\n");
 *   } else if (result == -1) {
 *       printf("ID da ton tai!\n");
 *   }
 */
int themSinhVien(struct Student students[], int *n, int maxSize, struct Student *newStudent) {
    // BƯỚC 1: KIỂM TRA ĐIỀU KIỆN ĐẦU VÀO
    // ----------------------------------
    // Kiểm tra các con trỏ không phải NULL
    if (students == NULL || n == NULL || newStudent == NULL) {
        printf("Loi: Tham so khong hop le!\n");
        return 0;  // Trả về 0 để báo hiệu lỗi tham số
    }
    
    // Kiểm tra danh sách chưa đầy
    if (*n >= maxSize) {
        printf("Loi: Danh sach da day! Khong the them sinh vien moi.\n");
        return 0;  // Trả về 0 để báo hiệu danh sách đầy
    }
    
    // BƯỚC 2: KIỂM TRA TRÙNG ID
    // -------------------------
    // Duyệt qua toàn bộ danh sách hiện có để kiểm tra ID trùng
    for (int i = 0; i < *n; i++) {
        // So sánh ID của sinh viên mới với ID của từng sinh viên trong danh sách
        if (students[i].id == newStudent->id) {
            printf("Loi: ID %d da ton tai trong danh sach! Khong the them.\n", newStudent->id);
            return -1;  // Trả về -1 để báo hiệu ID trùng
        }
    }
    
    // BƯỚC 3: THÊM SINH VIÊN VÀO DANH SÁCH
    // -------------------------------------
    // Gán sinh viên mới vào vị trí cuối cùng của mảng
    students[*n] = *newStudent;
    // Tăng biến đếm số lượng sinh viên
    (*n)++;
    
    return 1;  // Trả về 1 để báo hiệu thành công
}

/**
 * @brief Xóa một sinh viên khỏi danh sách theo ID
 * 
 * MÔ TẢ CHỨC NĂNG:
 * -----------------
 * Hàm này cho phép xóa một sinh viên khỏi danh sách dựa trên ID của sinh viên.
 * Sau khi xóa, các sinh viên phía sau sẽ được dịch chuyển lên để lấp đầy khoảng trống.
 * 
 * CÁC BƯỚC XỬ LÝ:
 * ---------------
 * 
 * BƯỚC 1: KIỂM TRA ĐIỀU KIỆN ĐẦU VÀO
 * ----------------------------------
 * - Kiểm tra con trỏ students và n không phải NULL
 * - Kiểm tra danh sách không rỗng (n > 0)
 * - Nếu không thỏa mãn, trả về 0 và báo lỗi
 * 
 * BƯỚC 2: TÌM VỊ TRÍ SINH VIÊN CẦN XÓA
 * ------------------------------------
 * - Duyệt qua toàn bộ danh sách từ đầu đến cuối
 * - So sánh ID của từng sinh viên với ID cần xóa
 * - Nếu tìm thấy, lưu lại vị trí (index) và thoát khỏi vòng lặp
 * - Nếu không tìm thấy sau khi duyệt hết, trả về -1 và báo lỗi "ID khong ton tai"
 * 
 * BƯỚC 3: XÓA SINH VIÊN VÀ DỊCH CHUYỂN CÁC PHẦN TỬ
 * ------------------------------------------------
 * - Dịch chuyển tất cả các sinh viên phía sau vị trí xóa lên một vị trí
 * - Sử dụng vòng lặp for từ vị trí xóa đến cuối danh sách
 * - Gán students[i] = students[i+1] để dịch chuyển
 * - Giảm biến đếm số lượng sinh viên (*n)--
 * - Trả về 1 để báo hiệu thành công
 * 
 * XỬ LÝ CÁC TRƯỜNG HỢP ĐẶC BIỆT:
 * --------------------------------
 * - ID không tồn tại: Trả về -1, không xóa gì
 * - Danh sách rỗng: Trả về 0, không xóa gì
 * - Thành công: Trả về 1, sinh viên đã được xóa và danh sách đã được cập nhật
 * 
 * @param students Mảng chứa danh sách sinh viên (sẽ được cập nhật sau khi xóa)
 * @param n Con trỏ đến biến đếm số lượng sinh viên (sẽ được giảm đi nếu thành công)
 * @param id ID của sinh viên cần xóa
 * 
 * @return 1 nếu xóa thành công
 * @return 0 nếu danh sách rỗng hoặc tham số không hợp lệ
 * @return -1 nếu ID không tồn tại trong danh sách
 * 
 * @note Hàm sẽ thay đổi mảng students và biến n
 * @note Sau khi xóa, thứ tự các sinh viên còn lại được giữ nguyên (chỉ dịch chuyển)
 * 
 * @example
 *   struct Student students[10];
 *   int n = 5;
 *   int result = xoaSinhVien(students, &n, 3);
 *   if (result == 1) {
 *       printf("Xoa thanh cong! Con lai %d sinh vien.\n", n);
 *   } else if (result == -1) {
 *       printf("ID khong ton tai!\n");
 *   }
 */
int xoaSinhVien(struct Student students[], int *n, int id) {
    // BƯỚC 1: KIỂM TRA ĐIỀU KIỆN ĐẦU VÀO
    // ----------------------------------
    // Kiểm tra các con trỏ không phải NULL
    if (students == NULL || n == NULL) {
        printf("Loi: Tham so khong hop le!\n");
        return 0;  // Trả về 0 để báo hiệu lỗi tham số
    }
    
    // Kiểm tra danh sách không rỗng
    if (*n <= 0) {
        printf("Loi: Danh sach rong! Khong co sinh vien nao de xoa.\n");
        return 0;  // Trả về 0 để báo hiệu danh sách rỗng
    }
    
    // BƯỚC 2: TÌM VỊ TRÍ SINH VIÊN CẦN XÓA
    // ------------------------------------
    int viTri = -1;  // Vị trí của sinh viên cần xóa, -1 nghĩa là chưa tìm thấy
    
    // Duyệt qua toàn bộ danh sách để tìm sinh viên có ID trùng khớp
    for (int i = 0; i < *n; i++) {
        // So sánh ID của sinh viên hiện tại với ID cần xóa
        if (students[i].id == id) {
            viTri = i;  // Lưu lại vị trí tìm thấy
            break;      // Thoát khỏi vòng lặp vì đã tìm thấy
        }
    }
    
    // Kiểm tra xem có tìm thấy sinh viên không
    if (viTri == -1) {
        printf("Loi: ID %d khong ton tai trong danh sach! Khong the xoa.\n", id);
        return -1;  // Trả về -1 để báo hiệu ID không tồn tại
    }
    
    // BƯỚC 3: XÓA SINH VIÊN VÀ DỊCH CHUYỂN CÁC PHẦN TỬ
    // ------------------------------------------------
    // Dịch chuyển tất cả các sinh viên phía sau vị trí xóa lên một vị trí
    // Bắt đầu từ vị trí cần xóa, gán phần tử sau vào phần tử trước
    for (int i = viTri; i < *n - 1; i++) {
        students[i] = students[i + 1];  // Dịch chuyển phần tử lên
    }
    
    // Giảm biến đếm số lượng sinh viên
    (*n)--;
    
    return 1;  // Trả về 1 để báo hiệu thành công
}

// Test case 1: Thêm sinh viên trùng ID
void testCase_ThemTrungID() {
    printf("\n=== TEST CASE 1: THEM SINH VIEN TRUNG ID ===\n");
    
    struct Student students[10] = {
        {1, "Nguyen Van A", 20, 3.5},
        {2, "Tran Thi B", 21, 3.8},
        {3, "Le Van C", 19, 3.2}
    };
    int n = 3;
    
    printf("Danh sach hien tai:\n");
    inDanhSach(students, n);
    
    // Thử thêm sinh viên có ID trùng với ID đã có (ID = 2)
    struct Student newStudent = {2, "Pham Thi D", 22, 3.9};
    printf("Thu them sinh vien moi co ID = 2 (ID da ton tai)...\n");
    
    int result = themSinhVien(students, &n, 10, &newStudent);
    
    if (result == -1) {
        printf(">>> KET QUA: Dung - Ham phat hien ID trung va tu choi them! <<<\n");
        printf("   So luong sinh vien van la: %d (khong thay doi)\n", n);
    } else {
        printf(">>> KET QUA: LOI - Ham khong phat hien ID trung! <<<\n");
        printf("   So luong sinh vien sau khi them: %d\n", n);
    }
}

// Test case 2: Xóa sinh viên không tồn tại
void testCase_XoaKhongTonTai() {
    printf("\n=== TEST CASE 2: XOA SINH VIEN KHONG TON TAI ===\n");
    
    struct Student students[10] = {
        {1, "Nguyen Van A", 20, 3.5},
        {2, "Tran Thi B", 21, 3.8},
        {3, "Le Van C", 19, 3.2}
    };
    int n = 3;
    
    printf("Danh sach hien tai:\n");
    inDanhSach(students, n);
    
    // Thử xóa sinh viên có ID không tồn tại (ID = 999)
    int idXoa = 999;
    printf("Thu xoa sinh vien co ID = %d (ID khong ton tai)...\n", idXoa);
    
    int result = xoaSinhVien(students, &n, idXoa);
    
    if (result == -1) {
        printf(">>> KET QUA: Dung - Ham phat hien ID khong ton tai va tu choi xoa! <<<\n");
        printf("   So luong sinh vien van la: %d (khong thay doi)\n", n);
    } else {
        printf(">>> KET QUA: LOI - Ham khong phat hien ID khong ton tai! <<<\n");
        printf("   So luong sinh vien sau khi xoa: %d\n", n);
    }
}

// Test case 3: Thêm sinh viên thành công
void testCase_ThemThanhCong() {
    printf("\n=== TEST CASE 3: THEM SINH VIEN THANH CONG ===\n");
    
    struct Student students[10] = {
        {1, "Nguyen Van A", 20, 3.5},
        {2, "Tran Thi B", 21, 3.8}
    };
    int n = 2;
    
    printf("Danh sach truoc khi them:\n");
    inDanhSach(students, n);
    
    // Thêm sinh viên mới với ID chưa tồn tại
    struct Student newStudent = {3, "Le Van C", 19, 3.2};
    printf("Them sinh vien moi co ID = 3 (ID chua ton tai)...\n");
    
    int result = themSinhVien(students, &n, 10, &newStudent);
    
    if (result == 1) {
        printf(">>> KET QUA: Thanh cong! <<<\n");
        printf("Danh sach sau khi them:\n");
        inDanhSach(students, n);
        printf("So luong sinh vien: %d\n", n);
    } else {
        printf(">>> KET QUA: LOI - Khong the them sinh vien! <<<\n");
    }
}

// Test case 4: Xóa sinh viên thành công
void testCase_XoaThanhCong() {
    printf("\n=== TEST CASE 4: XOA SINH VIEN THANH CONG ===\n");
    
    struct Student students[10] = {
        {1, "Nguyen Van A", 20, 3.5},
        {2, "Tran Thi B", 21, 3.8},
        {3, "Le Van C", 19, 3.2}
    };
    int n = 3;
    
    printf("Danh sach truoc khi xoa:\n");
    inDanhSach(students, n);
    
    // Xóa sinh viên có ID tồn tại
    int idXoa = 2;
    printf("Xoa sinh vien co ID = %d...\n", idXoa);
    
    int result = xoaSinhVien(students, &n, idXoa);
    
    if (result == 1) {
        printf(">>> KET QUA: Thanh cong! <<<\n");
        printf("Danh sach sau khi xoa:\n");
        inDanhSach(students, n);
        printf("So luong sinh vien: %d\n", n);
    } else {
        printf(">>> KET QUA: LOI - Khong the xoa sinh vien! <<<\n");
    }
}

// Hàm chạy tất cả test cases
void chayTatCaTestCases() {
    printf("\n========================================\n");
    printf("    CHAY TAT CA TEST CASES\n");
    printf("========================================\n");
    
    testCase_ThemTrungID();
    testCase_XoaKhongTonTai();
    testCase_ThemThanhCong();
    testCase_XoaThanhCong();
    
    printf("\n========================================\n");
    printf("    KET THUC TEST CASES\n");
    printf("========================================\n");
}

int main() {
    struct Student students[10];
    int n = 0;
    int choice;
    
    printf("=== CHUONG TRINH QUAN LY SINH VIEN ===\n");
    
    // Khởi tạo dữ liệu mẫu
    printf("\nKhoi tao du lieu mau...\n");
    students[0] = (struct Student){1, "Nguyen Van A", 20, 3.5};
    students[1] = (struct Student){2, "Tran Thi B", 21, 3.8};
    students[2] = (struct Student){3, "Le Van C", 19, 3.2};
    n = 3;
    
    printf("Da khoi tao %d sinh vien mau.\n", n);
    
    // In danh sách ban đầu
    printf("\n=== DANH SACH BAN DAU ===\n");
    inDanhSach(students, n);
    
    // Menu
    do {
        printf("\n=== MENU ===\n");
        printf("1. Them sinh vien moi\n");
        printf("2. Xoa sinh vien theo ID\n");
        printf("3. Hien thi danh sach\n");
        printf("4. Chay tat ca test cases\n");
        printf("5. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                struct Student newStudent;
                printf("\n=== THEM SINH VIEN MOI ===\n");
                nhapSinhVien(&newStudent);
                
                int result = themSinhVien(students, &n, 10, &newStudent);
                if (result == 1) {
                    printf("\n>>> Them sinh vien thanh cong! <<<\n");
                    printf("So luong sinh vien hien tai: %d\n", n);
                } else if (result == -1) {
                    printf("\n>>> Loi: ID da ton tai! <<<\n");
                } else {
                    printf("\n>>> Loi: Khong the them sinh vien! <<<\n");
                }
                break;
            }
            
            case 2: {
                int id;
                printf("\n=== XOA SINH VIEN ===\n");
                printf("Nhap ID sinh vien can xoa: ");
                scanf("%d", &id);
                
                int result = xoaSinhVien(students, &n, id);
                if (result == 1) {
                    printf("\n>>> Xoa sinh vien thanh cong! <<<\n");
                    printf("So luong sinh vien hien tai: %d\n", n);
                } else if (result == -1) {
                    printf("\n>>> Loi: ID khong ton tai! <<<\n");
                } else {
                    printf("\n>>> Loi: Khong the xoa sinh vien! <<<\n");
                }
                break;
            }
            
            case 3:
                printf("\n=== DANH SACH SINH VIEN ===\n");
                if (n > 0) {
                    inDanhSach(students, n);
                    printf("Tong so: %d sinh vien\n", n);
                } else {
                    printf("Danh sach rong!\n");
                }
                break;
                
            case 4:
                chayTatCaTestCases();
                break;
                
            case 5:
                printf("Cam on ban da su dung chuong trinh!\n");
                break;
                
            default:
                printf("Lua chon khong hop le! Vui long chon lai.\n");
        }
    } while (choice != 5);
    
    return 0;
}
