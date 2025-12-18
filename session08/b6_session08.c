#include <stdio.h>
#include <string.h>

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

/**
 * @brief Tính điểm GPA trung bình của danh sách sinh viên
 * 
 * Hàm này tính toán điểm GPA trung bình bằng cách cộng tất cả các điểm GPA
 * của sinh viên trong danh sách và chia cho số lượng sinh viên.
 * 
 * @param students Mảng chứa danh sách sinh viên
 * @param n Số lượng sinh viên trong danh sách
 * 
 * @return Điểm GPA trung bình (float). Trả về -1.0 nếu danh sách rỗng (n <= 0)
 *         để báo hiệu lỗi, hoặc trả về 0.0 nếu danh sách NULL
 * 
 * @note Độ phức tạp thời gian: O(n) - duyệt qua toàn bộ danh sách một lần
 * @note Hàm không thay đổi dữ liệu trong mảng, chỉ đọc dữ liệu
 * 
 * @example
 *   struct Student students[] = {
 *       {1, "Nguyen Van A", 20, 3.5},
 *       {2, "Tran Thi B", 21, 3.8},
 *       {3, "Le Van C", 19, 3.2}
 *   };
 *   float avg = tinhGPATrungBinh(students, 3);
 *   printf("GPA trung binh: %.2f\n", avg);  // Kết quả: 3.50
 */
float tinhGPATrungBinh(struct Student students[], int n) {
    // Kiểm tra danh sách rỗng hoặc NULL
    if (students == NULL || n <= 0) {
        return -1.0;  // Trả về -1.0 để báo hiệu lỗi
    }
    
    float tongGPA = 0.0;
    
    // Tính tổng GPA của tất cả sinh viên
    for (int i = 0; i < n; i++) {
        tongGPA += students[i].gpa;
    }
    
    // Tính và trả về GPA trung bình
    return tongGPA / n;
}

// Hàm khởi tạo 10 sinh viên mẫu với GPA khác nhau
void khoiTaoDuLieuMau(struct Student students[], int *n) {
    *n = 10;
    
    // 10 sinh viên với GPA từ 2.0 đến 4.0
    students[0] = (struct Student){1, "Nguyen Van A", 20, 2.0};
    students[1] = (struct Student){2, "Tran Thi B", 21, 2.5};
    students[2] = (struct Student){3, "Le Van C", 19, 3.0};
    students[3] = (struct Student){4, "Pham Thi D", 22, 3.2};
    students[4] = (struct Student){5, "Hoang Van E", 20, 3.5};
    students[5] = (struct Student){6, "Vu Thi F", 21, 3.7};
    students[6] = (struct Student){7, "Dao Van G", 19, 3.8};
    students[7] = (struct Student){8, "Bui Thi H", 20, 3.9};
    students[8] = (struct Student){9, "Dang Van I", 21, 4.0};
    students[9] = (struct Student){10, "Ly Thi K", 22, 2.8};
    
    printf("Da khoi tao %d sinh vien mau.\n", *n);
}

// Test case: Danh sách rỗng
void testCase_DanhSachRong() {
    printf("\n=== TEST CASE: DANH SACH RONG ===\n");
    
    struct Student students[5];
    int n = 0;  // Danh sách rỗng
    
    printf("Test voi danh sach rong (n = 0)...\n");
    float avg = tinhGPATrungBinh(students, n);
    
    if (avg == -1.0) {
        printf(">>> KET QUA: Dung - Ham tra ve -1.0 (bao hieu loi) <<<\n");
        printf("   Ham xu ly dung truong hop danh sach rong!\n");
    } else {
        printf(">>> KET QUA: LOI - Ham khong xu ly dung danh sach rong! <<<\n");
        printf("   Gia tri tra ve: %.2f (khong hop le)\n", avg);
    }
}

// Test case: Danh sách NULL
void testCase_DanhSachNULL() {
    printf("\n=== TEST CASE: DANH SACH NULL ===\n");
    
    printf("Test voi danh sach NULL...\n");
    float avg = tinhGPATrungBinh(NULL, 5);
    
    if (avg == -1.0) {
        printf(">>> KET QUA: Dung - Ham tra ve -1.0 (bao hieu loi) <<<\n");
        printf("   Ham xu ly dung truong hop danh sach NULL!\n");
    } else {
        printf(">>> KET QUA: LOI - Ham khong xu ly dung danh sach NULL! <<<\n");
        printf("   Gia tri tra ve: %.2f (khong hop le)\n", avg);
    }
}

// Test case: Danh sách có dữ liệu
void testCase_DanhSachCoDuLieu(struct Student students[], int n) {
    printf("\n=== TEST CASE: DANH SACH CO DU LIEU ===\n");
    
    printf("Test voi danh sach co %d sinh vien...\n", n);
    
    // In danh sách để kiểm tra
    printf("\nDanh sach sinh vien:\n");
    inDanhSach(students, n);
    
    // Tính GPA trung bình
    float avg = tinhGPATrungBinh(students, n);
    
    if (avg >= 0.0 && avg <= 4.0) {
        printf(">>> KET QUA: Thanh cong! <<<\n");
        printf("   GPA trung binh: %.2f\n", avg);
        
        // Tính thủ công để kiểm tra
        float tong = 0.0;
        for (int i = 0; i < n; i++) {
            tong += students[i].gpa;
        }
        float avgThucTe = tong / n;
        
        if (avg == avgThucTe) {
            printf("   Xac nhan: Ket qua dung (%.2f = %.2f)\n", avg, avgThucTe);
        } else {
            printf("   Canh bao: Ket qua khong khop!\n");
        }
    } else {
        printf(">>> KET QUA: LOI - Gia tri khong hop le! <<<\n");
        printf("   GPA trung binh: %.2f (khong nam trong khoang 0.0-4.0)\n", avg);
    }
}

// Hàm chạy tất cả test cases
void chayTatCaTestCases(struct Student students[], int n) {
    printf("\n========================================\n");
    printf("    CHAY TAT CA TEST CASES\n");
    printf("========================================\n");
    
    testCase_DanhSachRong();
    testCase_DanhSachNULL();
    testCase_DanhSachCoDuLieu(students, n);
    
    printf("\n========================================\n");
    printf("    KET THUC TEST CASES\n");
    printf("========================================\n");
}

int main() {
    struct Student students[10];
    int n = 0;
    int choice;
    
    printf("=== CHUONG TRINH TINH GPA TRUNG BINH ===\n");
    
    // Khởi tạo dữ liệu mẫu
    khoiTaoDuLieuMau(students, &n);
    
    // In danh sách sinh viên
    printf("\n=== DANH SACH SINH VIEN ===\n");
    inDanhSach(students, n);
    
    // Menu
    do {
        printf("\n=== MENU ===\n");
        printf("1. Tinh GPA trung binh\n");
        printf("2. Chay tat ca test cases\n");
        printf("3. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                float avg = tinhGPATrungBinh(students, n);
                if (avg >= 0.0) {
                    printf("\n>>> GPA TRUNG BINH: %.2f <<<\n", avg);
                } else {
                    printf("\n>>> LOI: Danh sach rong hoac khong hop le! <<<\n");
                }
                break;
            }
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
