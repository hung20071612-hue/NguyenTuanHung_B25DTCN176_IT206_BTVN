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
 * @brief Sắp xếp danh sách sinh viên theo GPA sử dụng thuật toán Bubble Sort
 * 
 * THUẬT TOÁN BUBBLE SORT:
 * ----------------------
 * Bubble Sort là một thuật toán sắp xếp đơn giản hoạt động bằng cách:
 * 
 * 1. SO SÁNH VÀ ĐỔI CHỖ: Duyệt qua danh sách, so sánh từng cặp phần tử liền kề
 *    - Nếu phần tử đứng trước lớn hơn phần tử đứng sau (với sắp xếp tăng dần)
 *    - Thì đổi chỗ hai phần tử đó
 * 
 * 2. LẶP LẠI NHIỀU LẦN: Quá trình này được lặp lại nhiều lần (n-1 lần)
 *    - Mỗi lần lặp, phần tử lớn nhất sẽ "nổi" lên cuối danh sách (như bong bóng)
 *    - Sau mỗi lần lặp, phạm vi so sánh giảm đi 1 phần tử
 * 
 * 3. VÍ DỤ MINH HỌA:
 *    Lần 1: [3.5, 2.0, 4.0, 3.2] -> [2.0, 3.5, 3.2, 4.0] (4.0 nổi lên cuối)
 *    Lần 2: [2.0, 3.5, 3.2, 4.0] -> [2.0, 3.2, 3.5, 4.0] (3.5 nổi lên)
 *    Lần 3: [2.0, 3.2, 3.5, 4.0] -> [2.0, 3.2, 3.5, 4.0] (không đổi, đã sắp xếp)
 * 
 * 4. ĐỘ PHỨC TẠP:
 *    - Thời gian: O(n²) - trong trường hợp xấu nhất
 *    - Không gian: O(1) - chỉ sử dụng biến tạm để đổi chỗ
 * 
 * 5. ƯU ĐIỂM:
 *    - Dễ hiểu và dễ triển khai
 *    - Không cần thêm bộ nhớ
 *    - Ổn định (giữ nguyên thứ tự các phần tử có cùng giá trị)
 * 
 * 6. NHƯỢC ĐIỂM:
 *    - Chậm với danh sách lớn (O(n²))
 *    - Không hiệu quả với danh sách đã sắp xếp một phần
 * 
 * @param students Mảng chứa danh sách sinh viên cần sắp xếp
 * @param n Số lượng sinh viên trong danh sách
 * @param tangDan Nếu = 1: sắp xếp tăng dần (GPA thấp -> cao)
 *                Nếu = 0: sắp xếp giảm dần (GPA cao -> thấp)
 * 
 * @note Hàm thay đổi trực tiếp mảng students (sắp xếp tại chỗ)
 * @note Với danh sách nhỏ (< 20 phần tử), Bubble Sort hoàn toàn phù hợp
 * 
 * @example
 *   struct Student students[] = {
 *       {1, "A", 20, 3.5},
 *       {2, "B", 21, 2.0},
 *       {3, "C", 19, 4.0}
 *   };
 *   sapXepTheoGPA(students, 3, 1);  // Sắp xếp tăng dần
 *   // Kết quả: B(2.0), A(3.5), C(4.0)
 */
void sapXepTheoGPA(struct Student students[], int n, int tangDan) {
    // Kiểm tra danh sách hợp lệ
    if (students == NULL || n <= 1) {
        return;  // Danh sách rỗng hoặc chỉ có 1 phần tử, không cần sắp xếp
    }
    
    struct Student temp;  // Biến tạm để đổi chỗ
    
    // Vòng lặp ngoài: chạy n-1 lần
    // Mỗi lần lặp, một phần tử lớn nhất sẽ "nổi" lên cuối danh sách
    for (int i = 0; i < n - 1; i++) {
        // Vòng lặp trong: so sánh các cặp phần tử liền kề
        // Giảm phạm vi so sánh sau mỗi lần lặp ngoài (n - 1 - i)
        for (int j = 0; j < n - 1 - i; j++) {
            // So sánh GPA của hai sinh viên liền kề
            int canDoiCho = 0;
            
            if (tangDan) {
                // Sắp xếp tăng dần: đổi chỗ nếu phần tử trước > phần tử sau
                canDoiCho = (students[j].gpa > students[j + 1].gpa);
            } else {
                // Sắp xếp giảm dần: đổi chỗ nếu phần tử trước < phần tử sau
                canDoiCho = (students[j].gpa < students[j + 1].gpa);
            }
            
            // Đổi chỗ hai sinh viên nếu cần
            if (canDoiCho) {
                temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

// Hàm sao chép mảng để test (giữ nguyên mảng gốc)
void saoChepMang(struct Student src[], struct Student dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// Hàm kiểm tra danh sách đã được sắp xếp chưa
int kiemTraSapXep(struct Student students[], int n, int tangDan) {
    if (n <= 1) return 1;  // Danh sách rỗng hoặc 1 phần tử coi như đã sắp xếp
    
    for (int i = 0; i < n - 1; i++) {
        if (tangDan) {
            // Kiểm tra tăng dần
            if (students[i].gpa > students[i + 1].gpa) {
                return 0;  // Chưa sắp xếp đúng
            }
        } else {
            // Kiểm tra giảm dần
            if (students[i].gpa < students[i + 1].gpa) {
                return 0;  // Chưa sắp xếp đúng
            }
        }
    }
    return 1;  // Đã sắp xếp đúng
}

// Test case 1: GPA bằng nhau
void testCase_GPABangNhau() {
    printf("\n=== TEST CASE 1: GPA BANG NHAU ===\n");
    
    struct Student students[] = {
        {1, "Nguyen Van A", 20, 3.5},
        {2, "Tran Thi B", 21, 3.5},
        {3, "Le Van C", 19, 3.5},
        {4, "Pham Thi D", 22, 3.5}
    };
    int n = 4;
    
    printf("Danh sach truoc khi sap xep (tat ca GPA = 3.5):\n");
    inDanhSach(students, n);
    
    struct Student studentsCopy[4];
    saoChepMang(students, studentsCopy, n);
    
    sapXepTheoGPA(studentsCopy, n, 1);
    
    printf("Danh sach sau khi sap xep tang dan:\n");
    inDanhSach(studentsCopy, n);
    
    if (kiemTraSapXep(studentsCopy, n, 1)) {
        printf(">>> KET QUA: Thanh cong! Danh sach da duoc sap xep dung. <<<\n");
    } else {
        printf(">>> KET QUA: LOI! Danh sach chua duoc sap xep dung. <<<\n");
    }
}

// Test case 2: GPA tăng dần sẵn
void testCase_GPATangDanSan() {
    printf("\n=== TEST CASE 2: GPA TANG DAN SAN ===\n");
    
    struct Student students[] = {
        {1, "Nguyen Van A", 20, 2.0},
        {2, "Tran Thi B", 21, 2.5},
        {3, "Le Van C", 19, 3.0},
        {4, "Pham Thi D", 22, 3.5},
        {5, "Hoang Van E", 20, 4.0}
    };
    int n = 5;
    
    printf("Danh sach truoc khi sap xep (da tang dan san):\n");
    inDanhSach(students, n);
    
    struct Student studentsCopy[5];
    saoChepMang(students, studentsCopy, n);
    
    sapXepTheoGPA(studentsCopy, n, 1);
    
    printf("Danh sach sau khi sap xep tang dan:\n");
    inDanhSach(studentsCopy, n);
    
    if (kiemTraSapXep(studentsCopy, n, 1)) {
        printf(">>> KET QUA: Thanh cong! Danh sach van duoc sap xep dung. <<<\n");
    } else {
        printf(">>> KET QUA: LOI! Danh sach bi thay doi khong dung. <<<\n");
    }
}

// Test case 3: GPA ngẫu nhiên
void testCase_GPANgauNhien() {
    printf("\n=== TEST CASE 3: GPA NGAU NHIEN ===\n");
    
    struct Student students[] = {
        {1, "Nguyen Van A", 20, 3.8},
        {2, "Tran Thi B", 21, 2.0},
        {3, "Le Van C", 19, 4.0},
        {4, "Pham Thi D", 22, 2.5},
        {5, "Hoang Van E", 20, 3.2},
        {6, "Vu Thi F", 21, 3.9},
        {7, "Dao Van G", 19, 2.8}
    };
    int n = 7;
    
    printf("Danh sach truoc khi sap xep (GPA ngau nhien):\n");
    inDanhSach(students, n);
    
    struct Student studentsCopy[7];
    saoChepMang(students, studentsCopy, n);
    
    sapXepTheoGPA(studentsCopy, n, 1);
    
    printf("Danh sach sau khi sap xep tang dan:\n");
    inDanhSach(studentsCopy, n);
    
    if (kiemTraSapXep(studentsCopy, n, 1)) {
        printf(">>> KET QUA: Thanh cong! Danh sach da duoc sap xep dung. <<<\n");
        
        // In thứ tự GPA để kiểm tra
        printf("Thu tu GPA sau khi sap xep: ");
        for (int i = 0; i < n; i++) {
            printf("%.1f", studentsCopy[i].gpa);
            if (i < n - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        printf(">>> KET QUA: LOI! Danh sach chua duoc sap xep dung. <<<\n");
    }
}

// Test case 4: Sắp xếp giảm dần
void testCase_SapXepGiamDan() {
    printf("\n=== TEST CASE 4: SAP XEP GIAM DAN ===\n");
    
    struct Student students[] = {
        {1, "Nguyen Van A", 20, 2.5},
        {2, "Tran Thi B", 21, 3.8},
        {3, "Le Van C", 19, 3.0},
        {4, "Pham Thi D", 22, 4.0}
    };
    int n = 4;
    
    printf("Danh sach truoc khi sap xep:\n");
    inDanhSach(students, n);
    
    struct Student studentsCopy[4];
    saoChepMang(students, studentsCopy, n);
    
    sapXepTheoGPA(studentsCopy, n, 0);  // Sắp xếp giảm dần
    
    printf("Danh sach sau khi sap xep giam dan:\n");
    inDanhSach(studentsCopy, n);
    
    if (kiemTraSapXep(studentsCopy, n, 0)) {
        printf(">>> KET QUA: Thanh cong! Danh sach da duoc sap xep giam dan dung. <<<\n");
    } else {
        printf(">>> KET QUA: LOI! Danh sach chua duoc sap xep dung. <<<\n");
    }
}

// Hàm chạy tất cả test cases
void chayTatCaTestCases() {
    printf("\n========================================\n");
    printf("    CHAY TAT CA TEST CASES\n");
    printf("========================================\n");
    
    testCase_GPABangNhau();
    testCase_GPATangDanSan();
    testCase_GPANgauNhien();
    testCase_SapXepGiamDan();
    
    printf("\n========================================\n");
    printf("    KET THUC TEST CASES\n");
    printf("========================================\n");
}

int main() {
    struct Student students[10];
    int n = 0;
    int choice;
    
    printf("=== CHUONG TRINH SAP XEP SINH VIEN THEO GPA ===\n");
    
    // Khởi tạo dữ liệu mẫu
    printf("\nKhoi tao du lieu mau...\n");
    students[0] = (struct Student){1, "Nguyen Van A", 20, 3.8};
    students[1] = (struct Student){2, "Tran Thi B", 21, 2.5};
    students[2] = (struct Student){3, "Le Van C", 19, 4.0};
    students[3] = (struct Student){4, "Pham Thi D", 22, 3.2};
    students[4] = (struct Student){5, "Hoang Van E", 20, 2.0};
    n = 5;
    
    printf("Da khoi tao %d sinh vien mau.\n", n);
    
    // In danh sách ban đầu
    printf("\n=== DANH SACH BAN DAU ===\n");
    inDanhSach(students, n);
    
    // Menu
    do {
        printf("\n=== MENU ===\n");
        printf("1. Sap xep tang dan theo GPA\n");
        printf("2. Sap xep giam dan theo GPA\n");
        printf("3. Chay tat ca test cases\n");
        printf("4. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                struct Student studentsCopy[10];
                saoChepMang(students, studentsCopy, n);
                sapXepTheoGPA(studentsCopy, n, 1);
                printf("\n=== DANH SACH SAU KHI SAP XEP TANG DAN ===\n");
                inDanhSach(studentsCopy, n);
                break;
            }
            case 2: {
                struct Student studentsCopy[10];
                saoChepMang(students, studentsCopy, n);
                sapXepTheoGPA(studentsCopy, n, 0);
                printf("\n=== DANH SACH SAU KHI SAP XEP GIAM DAN ===\n");
                inDanhSach(studentsCopy, n);
                break;
            }
            case 3:
                chayTatCaTestCases();
                break;
            case 4:
                printf("Cam on ban da su dung chuong trinh!\n");
                break;
            default:
                printf("Lua chon khong hop le! Vui long chon lai.\n");
        }
    } while (choice != 4);
    
    return 0;
}
