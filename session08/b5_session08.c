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

// Hàm in thông tin một sinh viên
void inSinhVien(struct Student sv) {
    printf("\n=== THONG TIN SINH VIEN ===\n");
    printf("ID: %d\n", sv.id);
    printf("Ten: %s\n", sv.name);
    printf("Tuoi: %d\n", sv.age);
    printf("GPA: %.2f\n", sv.gpa);
    printf("\n");
}

/**
 * @brief Tìm kiếm sinh viên theo ID trong danh sách
 * 
 * Hàm này thực hiện tìm kiếm tuyến tính trong mảng sinh viên để tìm sinh viên
 * có ID trùng khớp với ID được cung cấp. Hàm sẽ duyệt qua toàn bộ danh sách
 * từ đầu đến cuối và trả về con trỏ đến sinh viên đầu tiên có ID khớp.
 * 
 * @param students Mảng chứa danh sách sinh viên cần tìm kiếm
 * @param n Số lượng sinh viên trong mảng (kích thước thực tế của danh sách)
 * @param id ID của sinh viên cần tìm kiếm (có thể là số dương hoặc số âm)
 * 
 * @return Con trỏ đến struct Student nếu tìm thấy sinh viên có ID khớp,
 *         trả về NULL nếu không tìm thấy hoặc danh sách rỗng
 * 
 * @note Độ phức tạp thời gian: O(n) - duyệt tuyến tính qua toàn bộ danh sách
 * @note Hàm không thay đổi dữ liệu trong mảng, chỉ đọc dữ liệu
 * 
 * @example
 *   struct Student students[] = {{1, "Nguyen Van A", 20, 3.5}, {2, "Tran Thi B", 21, 3.8}};
 *   struct Student *found = timKiemTheoID(students, 2, 1);
 *   if (found != NULL) {
 *       printf("Tim thay: %s\n", found->name);
 *   }
 */
struct Student* timKiemTheoID(struct Student students[], int n, int id) {
    // Kiểm tra danh sách rỗng
    if (students == NULL || n <= 0) {
        return NULL;
    }
    
    // Duyệt qua toàn bộ danh sách để tìm ID khớp
    for (int i = 0; i < n; i++) {
        if (students[i].id == id) {
            return &students[i];  // Trả về con trỏ đến sinh viên tìm thấy
        }
    }
    
    // Không tìm thấy
    return NULL;
}

// Hàm nhập ID cần tìm từ bàn phím
int nhapID() {
    int id;
    printf("Nhap ID sinh vien can tim: ");
    scanf("%d", &id);
    return id;
}

// Hàm tìm kiếm và hiển thị kết quả
void timVaHienThi(struct Student students[], int n) {
    int id = nhapID();
    struct Student *found = timKiemTheoID(students, n, id);
    
    if (found != NULL) {
        printf("\n>>> Tim thay sinh vien co ID = %d <<<\n", id);
        inSinhVien(*found);
    } else {
        printf("\n>>> Khong tim thay sinh vien co ID = %d <<<\n", id);
    }
}

// Hàm test case: ID tồn tại
void testCase_IDTonTai(struct Student students[], int n) {
    printf("\n=== TEST CASE 1: ID TON TAI ===\n");
    if (n > 0) {
        int testID = students[0].id;  // Lấy ID của sinh viên đầu tiên
        printf("Tim kiem ID = %d (ID ton tai trong danh sach)\n", testID);
        struct Student *found = timKiemTheoID(students, n, testID);
        
        if (found != NULL) {
            printf(">>> KET QUA: Tim thay! <<<\n");
            inSinhVien(*found);
        } else {
            printf(">>> KET QUA: LOI - Khong tim thay! <<<\n");
        }
    } else {
        printf("Danh sach rong, khong the test!\n");
    }
}

// Hàm test case: ID không tồn tại
void testCase_IDKhongTonTai(struct Student students[], int n) {
    printf("\n=== TEST CASE 2: ID KHONG TON TAI ===\n");
    int testID = 999;  // ID chắc chắn không tồn tại
    printf("Tim kiem ID = %d (ID khong ton tai trong danh sach)\n", testID);
    struct Student *found = timKiemTheoID(students, n, testID);
    
    if (found == NULL) {
        printf(">>> KET QUA: Dung - Khong tim thay! <<<\n");
    } else {
        printf(">>> KET QUA: LOI - Tim thay (khong dung)! <<<\n");
    }
}

// Hàm test case: ID âm
void testCase_IDAm(struct Student students[], int n) {
    printf("\n=== TEST CASE 3: ID AM ===\n");
    int testID = -1;  // ID âm
    printf("Tim kiem ID = %d (ID am)\n", testID);
    struct Student *found = timKiemTheoID(students, n, testID);
    
    if (found == NULL) {
        printf(">>> KET QUA: Dung - Khong tim thay ID am! <<<\n");
    } else {
        printf(">>> KET QUA: Tim thay ID am (neu co trong danh sach) <<<\n");
        inSinhVien(*found);
    }
}

// Hàm chạy tất cả test cases
void chayTatCaTestCases(struct Student students[], int n) {
    printf("\n========================================\n");
    printf("    CHAY TAT CA TEST CASES\n");
    printf("========================================\n");
    
    testCase_IDTonTai(students, n);
    testCase_IDKhongTonTai(students, n);
    testCase_IDAm(students, n);
    
    printf("\n========================================\n");
    printf("    KET THUC TEST CASES\n");
    printf("========================================\n");
}

int main() {
    struct Student students[5];
    int n = 0;
    int choice;
    
    printf("=== CHUONG TRINH TIM KIEM SINH VIEN THEO ID ===\n");
    
    // Khởi tạo dữ liệu mẫu để test
    printf("\nKhoi tao du lieu mau...\n");
    students[0] = (struct Student){1, "Nguyen Van A", 20, 3.5};
    students[1] = (struct Student){2, "Tran Thi B", 21, 3.8};
    students[2] = (struct Student){3, "Le Van C", 19, 3.2};
    n = 3;
    
    printf("Da khoi tao %d sinh vien mau.\n", n);
    
    // In danh sách sinh viên
    printf("\n=== DANH SACH SINH VIEN ===\n");
    inDanhSach(students, n);
    
    // Menu
    do {
        printf("\n=== MENU ===\n");
        printf("1. Tim kiem sinh vien theo ID (nhap tu ban phim)\n");
        printf("2. Chay tat ca test cases\n");
        printf("3. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                timVaHienThi(students, n);
                break;
            case 2:
                chayTatCaTestCases(students, n);
                break;
            case 3:
                printf("Cam on ban da su dung chuong trinh!\n");
                break;
            default:
                printf("Lua chon khong hop le! Vui long chon lai.\n");
        }
    } while (choice != 3);
    
    return 0;
}
