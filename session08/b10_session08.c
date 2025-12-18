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

// ============================================
// CÁC HÀM HỖ TRỢ
// ============================================

/**
 * Chức năng: In danh sách sinh viên ra màn hình dưới dạng bảng
 * Input: Mảng students và số lượng n
 * Output: In bảng ra màn hình
 */
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
 * Chức năng: Nhập thông tin một sinh viên từ bàn phím
 * Input: Con trỏ đến struct Student
 * Output: Cập nhật thông tin vào struct Student
 */
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

// ============================================
// CHỨC NĂNG 1: NHẬP SINH VIÊN
// ============================================

/**
 * Chức năng: Nhập nhiều sinh viên từ bàn phím
 * - Yêu cầu người dùng nhập số lượng sinh viên
 * - Nhập thông tin từng sinh viên
 * - Lưu vào mảng students
 * Input: Mảng students, con trỏ n, maxSize
 * Output: Cập nhật mảng students và biến n
 */
void nhapDanhSachSinhVien(struct Student students[], int *n, int maxSize) {
    int soLuong;
    printf("\n=== NHAP DANH SACH SINH VIEN ===\n");
    printf("Nhap so luong sinh vien (toi da %d): ", maxSize);
    scanf("%d", &soLuong);
    
    // Kiểm tra số lượng hợp lệ
    if (soLuong < 1 || soLuong > maxSize) {
        printf("So luong khong hop le! Chi cho phep nhap tu 1 den %d sinh vien.\n", maxSize);
        return;
    }
    
    // Kiểm tra không vượt quá giới hạn
    if (*n + soLuong > maxSize) {
        printf("Danh sach hien tai co %d sinh vien. Khong the them %d sinh vien nua!\n", *n, soLuong);
        return;
    }
    
    // Nhập thông tin từng sinh viên
    for (int i = 0; i < soLuong; i++) {
        printf("\n--- Nhap thong tin sinh vien thu %d ---\n", i + 1);
        nhapSinhVien(&students[*n + i]);
    }
    
    // Cập nhật số lượng
    *n += soLuong;
    printf("\n>>> Da nhap thanh cong %d sinh vien! <<<\n", soLuong);
}

// ============================================
// CHỨC NĂNG 2: IN DANH SÁCH
// ============================================

/**
 * Chức năng: Hiển thị danh sách sinh viên ra màn hình
 * - Kiểm tra danh sách có rỗng không
 * - In danh sách dưới dạng bảng
 * - Hiển thị tổng số sinh viên
 * Input: Mảng students và số lượng n
 * Output: In bảng ra màn hình
 */
void hienThiDanhSach(struct Student students[], int n) {
    printf("\n=== DANH SACH SINH VIEN ===\n");
    
    if (n == 0) {
        printf("Danh sach rong!\n");
        return;
    }
    
    inDanhSach(students, n);
    printf("Tong so: %d sinh vien\n", n);
}

// ============================================
// CHỨC NĂNG 3: GHI FILE
// ============================================

/**
 * Chức năng: Lưu danh sách sinh viên vào file
 * - Yêu cầu người dùng nhập tên file
 * - Mở file để ghi
 * - Ghi dữ liệu dưới dạng bảng
 * - Đóng file
 * Input: Mảng students, số lượng n
 * Output: Tạo file chứa dữ liệu sinh viên
 */
void ghiFile(struct Student students[], int n) {
    if (n == 0) {
        printf("\nDanh sach rong! Khong co du lieu de ghi.\n");
        return;
    }
    
    char filename[100];
    printf("\n=== GHI FILE ===\n");
    printf("Nhap ten file (vi du: students.txt): ");
    
    // Xóa bộ đệm
    while (getchar() != '\n');
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;
    
    // Mở file để ghi
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Loi: Khong the tao file %s!\n", filename);
        return;
    }
    
    // Ghi tiêu đề bảng
    fprintf(file, "+----+------------------+------+-------+\n");
    fprintf(file, "| ID |      Name        | Age  |  GPA  |\n");
    fprintf(file, "+----+------------------+------+-------+\n");
    
    // Ghi dữ liệu từng sinh viên
    for (int i = 0; i < n; i++) {
        fprintf(file, "| %-2d | %-16s | %-4d | %5.2f |\n", 
                students[i].id, 
                students[i].name, 
                students[i].age, 
                students[i].gpa);
    }
    
    // Ghi dòng kết thúc
    fprintf(file, "+----+------------------+------+-------+\n");
    fprintf(file, "\nTong so sinh vien: %d\n", n);
    
    fclose(file);
    printf(">>> Da luu danh sach vao file %s thanh cong! <<<\n", filename);
}

// ============================================
// CHỨC NĂNG 4: ĐỌC FILE
// ============================================

/**
 * Chức năng: Đọc danh sách sinh viên từ file
 * - Yêu cầu người dùng nhập tên file
 * - Mở file để đọc
 * - Parse dữ liệu từ file
 * - Lưu vào mảng students
 * Input: Mảng students, con trỏ n, maxSize
 * Output: Cập nhật mảng students và biến n
 */
void docFile(struct Student students[], int *n, int maxSize) {
    char filename[100];
    printf("\n=== DOC FILE ===\n");
    printf("Nhap ten file can doc (vi du: students.txt): ");
    
    // Xóa bộ đệm
    while (getchar() != '\n');
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;
    
    // Mở file để đọc
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Loi: Khong the mo file %s!\n", filename);
        return;
    }
    
    char line[200];
    int count = 0;
    int skipHeader = 1;
    int skipCount = 0;
    
    // Đọc từng dòng trong file
    while (fgets(line, sizeof(line), file) != NULL && count < maxSize) {
        // Bỏ qua các dòng phân cách và tiêu đề
        if (line[0] == '+') continue;
        
        if (skipHeader && skipCount < 3) {
            skipCount++;
            if (skipCount >= 3) skipHeader = 0;
            continue;
        }
        
        if (strstr(line, "Tong so sinh vien") != NULL) continue;
        
        // Parse dữ liệu từ dòng
        if (line[0] == '|') {
            struct Student sv;
            if (sscanf(line, "| %d | %49[^|] | %d | %f |", 
                      &sv.id, sv.name, &sv.age, &sv.gpa) == 4) {
                // Trim tên
                char *start = sv.name;
                while (*start == ' ') start++;
                char *end = start + strlen(start) - 1;
                while (end > start && *end == ' ') end--;
                *(end + 1) = '\0';
                strcpy(sv.name, start);
                
                students[count] = sv;
                count++;
            }
        }
    }
    
    fclose(file);
    *n = count;
    
    if (count > 0) {
        printf(">>> Da doc thanh cong %d sinh vien tu file %s! <<<\n", count, filename);
    } else {
        printf("File rong hoac khong co du lieu hop le!\n");
    }
}

// ============================================
// CHỨC NĂNG 5: TÌM KIẾM
// ============================================

/**
 * Chức năng: Tìm kiếm sinh viên theo ID
 * - Yêu cầu người dùng nhập ID cần tìm
 * - Duyệt qua danh sách để tìm ID trùng khớp
 * - Hiển thị thông tin nếu tìm thấy
 * - Báo "Khong tim thay" nếu không tìm thấy
 * Input: Mảng students, số lượng n
 * Output: In thông tin sinh viên tìm được hoặc thông báo không tìm thấy
 */
void timKiemSinhVien(struct Student students[], int n) {
    if (n == 0) {
        printf("\nDanh sach rong! Khong co du lieu de tim kiem.\n");
        return;
    }
    
    int id;
    printf("\n=== TIM KIEM SINH VIEN ===\n");
    printf("Nhap ID sinh vien can tim: ");
    scanf("%d", &id);
    
    // Tìm kiếm trong danh sách
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (students[i].id == id) {
            printf("\n>>> Tim thay sinh vien co ID = %d <<<\n", id);
            printf("ID: %d\n", students[i].id);
            printf("Ten: %s\n", students[i].name);
            printf("Tuoi: %d\n", students[i].age);
            printf("GPA: %.2f\n", students[i].gpa);
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("\n>>> Khong tim thay sinh vien co ID = %d <<<\n", id);
    }
}

// ============================================
// CHỨC NĂNG 6: SẮP XẾP
// ============================================

/**
 * Chức năng: Sắp xếp danh sách sinh viên theo GPA
 * - Sử dụng thuật toán Bubble Sort
 * - Cho phép chọn sắp xếp tăng dần hoặc giảm dần
 * - Sắp xếp tại chỗ (in-place)
 * Input: Mảng students, số lượng n
 * Output: Mảng students đã được sắp xếp
 */
void sapXepTheoGPA(struct Student students[], int n) {
    if (n <= 1) {
        printf("\nDanh sach co it hon 2 sinh vien, khong can sap xep.\n");
        return;
    }
    
    int choice;
    printf("\n=== SAP XEP THEO GPA ===\n");
    printf("1. Tang dan (GPA thap -> cao)\n");
    printf("2. Giam dan (GPA cao -> thap)\n");
    printf("Lua chon: ");
    scanf("%d", &choice);
    
    struct Student temp;
    int tangDan = (choice == 1);
    
    // Bubble Sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            int canDoiCho = 0;
            if (tangDan) {
                canDoiCho = (students[j].gpa > students[j + 1].gpa);
            } else {
                canDoiCho = (students[j].gpa < students[j + 1].gpa);
            }
            
            if (canDoiCho) {
                temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    
    printf(">>> Da sap xep thanh cong! <<<\n");
    inDanhSach(students, n);
}

// ============================================
// CHỨC NĂNG 7: THÊM SINH VIÊN
// ============================================

/**
 * Chức năng: Thêm một sinh viên mới vào danh sách
 * - Nhập thông tin sinh viên mới
 * - Kiểm tra ID không trùng
 * - Kiểm tra danh sách chưa đầy
 * - Thêm vào cuối danh sách
 * Input: Mảng students, con trỏ n, maxSize
 * Output: Cập nhật mảng students và biến n
 */
void themSinhVien(struct Student students[], int *n, int maxSize) {
    if (*n >= maxSize) {
        printf("\nDanh sach da day! Khong the them sinh vien moi.\n");
        return;
    }
    
    printf("\n=== THEM SINH VIEN MOI ===\n");
    struct Student newStudent;
    nhapSinhVien(&newStudent);
    
    // Kiểm tra ID trùng
    for (int i = 0; i < *n; i++) {
        if (students[i].id == newStudent.id) {
            printf(">>> Loi: ID %d da ton tai! Khong the them. <<<\n", newStudent.id);
            return;
        }
    }
    
    // Thêm vào danh sách
    students[*n] = newStudent;
    (*n)++;
    printf(">>> Them sinh vien thanh cong! <<<\n");
}

// ============================================
// CHỨC NĂNG 8: XÓA SINH VIÊN
// ============================================

/**
 * Chức năng: Xóa một sinh viên khỏi danh sách theo ID
 * - Yêu cầu người dùng nhập ID cần xóa
 * - Tìm vị trí sinh viên trong danh sách
 * - Dịch chuyển các phần tử phía sau lên
 * - Giảm số lượng sinh viên
 * Input: Mảng students, con trỏ n
 * Output: Cập nhật mảng students và biến n
 */
void xoaSinhVien(struct Student students[], int *n) {
    if (*n == 0) {
        printf("\nDanh sach rong! Khong co sinh vien nao de xoa.\n");
        return;
    }
    
    int id;
    printf("\n=== XOA SINH VIEN ===\n");
    printf("Nhap ID sinh vien can xoa: ");
    scanf("%d", &id);
    
    // Tìm vị trí sinh viên
    int viTri = -1;
    for (int i = 0; i < *n; i++) {
        if (students[i].id == id) {
            viTri = i;
            break;
        }
    }
    
    if (viTri == -1) {
        printf(">>> Loi: ID %d khong ton tai! <<<\n", id);
        return;
    }
    
    // Dịch chuyển các phần tử
    for (int i = viTri; i < *n - 1; i++) {
        students[i] = students[i + 1];
    }
    
    (*n)--;
    printf(">>> Xoa sinh vien thanh cong! <<<\n");
}

// ============================================
// HÀM KHỞI TẠO DỮ LIỆU MẪU
// ============================================

/**
 * Chức năng: Khởi tạo 10 sinh viên giả lập để test
 * - Tạo 10 sinh viên với thông tin khác nhau
 * - ID từ 1 đến 10
 * - GPA từ 2.0 đến 4.0
 * Input: Mảng students, con trỏ n
 * Output: Cập nhật mảng students với 10 sinh viên mẫu
 */
void khoiTaoDuLieuMau(struct Student students[], int *n) {
    *n = 10;
    
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
    
    printf("\n>>> Da khoi tao 10 sinh vien mau! <<<\n");
}

// ============================================
// HÀM HIỂN THỊ MENU
// ============================================

/**
 * Chức năng: Hiển thị menu chính của chương trình
 * - In ra các tùy chọn chức năng
 * - Định dạng đẹp với dấu = để phân cách
 * Input: Không
 * Output: In menu ra màn hình
 */
void hienThiMenu() {
    printf("\n");
    printf("===== Student Manager =====\n");
    printf("1. Nhap sinh vien\n");
    printf("2. In danh sach\n");
    printf("3. Ghi file\n");
    printf("4. Doc file\n");
    printf("5. Tim kiem\n");
    printf("6. Sap xep\n");
    printf("7. Them sinh vien\n");
    printf("8. Xoa sinh vien\n");
    printf("9. Khoi tao du lieu mau (10 sinh vien)\n");
    printf("0. Thoat\n");
    printf("===========================\n");
    printf("Chon chuc nang: ");
}

// ============================================
// HÀM MAIN - LUỒNG CHẠY CHƯƠNG TRÌNH
// ============================================

/**
 * LUỒNG CHẠY CHƯƠNG TRÌNH:
 * ------------------------
 * 
 * BƯỚC 1: KHỞI TẠO
 * - Khai báo mảng students với kích thước tối đa 100
 * - Khởi tạo biến n = 0 (số lượng sinh viên hiện tại)
 * - In thông báo chào mừng
 * 
 * BƯỚC 2: VÒNG LẶP MENU CHÍNH
 * - Hiển thị menu các chức năng
 * - Đọc lựa chọn từ người dùng
 * - Xử lý từng chức năng dựa trên lựa chọn:
 * 
 *   + Chức năng 1: Nhập sinh viên
 *     * Gọi hàm nhapDanhSachSinhVien()
 *     * Người dùng nhập số lượng và thông tin từng sinh viên
 *     * Dữ liệu được lưu vào mảng students
 * 
 *   + Chức năng 2: In danh sách
 *     * Gọi hàm hienThiDanhSach()
 *     * Hiển thị tất cả sinh viên dưới dạng bảng
 * 
 *   + Chức năng 3: Ghi file
 *     * Gọi hàm ghiFile()
 *     * Người dùng nhập tên file
 *     * Dữ liệu được ghi vào file dưới dạng bảng
 * 
 *   + Chức năng 4: Đọc file
 *     * Gọi hàm docFile()
 *     * Người dùng nhập tên file
 *     * Dữ liệu được đọc từ file và lưu vào mảng
 * 
 *   + Chức năng 5: Tìm kiếm
 *     * Gọi hàm timKiemSinhVien()
 *     * Người dùng nhập ID cần tìm
 *     * Hiển thị thông tin nếu tìm thấy
 * 
 *   + Chức năng 6: Sắp xếp
 *     * Gọi hàm sapXepTheoGPA()
 *     * Người dùng chọn tăng dần hoặc giảm dần
 *     * Danh sách được sắp xếp theo GPA
 * 
 *   + Chức năng 7: Thêm sinh viên
 *     * Gọi hàm themSinhVien()
 *     * Người dùng nhập thông tin sinh viên mới
 *     * Kiểm tra ID trùng và thêm vào danh sách
 * 
 *   + Chức năng 8: Xóa sinh viên
 *     * Gọi hàm xoaSinhVien()
 *     * Người dùng nhập ID cần xóa
 *     * Xóa sinh viên và dịch chuyển các phần tử
 * 
 *   + Chức năng 9: Khởi tạo dữ liệu mẫu
 *     * Gọi hàm khoiTaoDuLieuMau()
 *     * Tạo 10 sinh viên mẫu để test
 * 
 *   + Chức năng 0: Thoát
 *     * In thông báo cảm ơn
 *     * Thoát khỏi vòng lặp và kết thúc chương trình
 * 
 * BƯỚC 3: KẾT THÚC
 * - Return 0 để báo hiệu chương trình chạy thành công
 * 
 * ĐẶC ĐIỂM:
 * - Menu lặp lại cho đến khi người dùng chọn 0 (Thoát)
 * - Mỗi chức năng độc lập, có thể gọi bất kỳ lúc nào
 * - Dữ liệu được lưu trong mảng students trong suốt phiên làm việc
 * - Có thể lưu/đọc dữ liệu từ file để lưu trữ lâu dài
 */
int main() {
    struct Student students[100];  // Mảng lưu tối đa 100 sinh viên
    int n = 0;  // Số lượng sinh viên hiện tại
    int choice;  // Lựa chọn của người dùng
    
    printf("===== Student Manager =====\n");
    printf("Chao mung den voi chuong trinh quan ly sinh vien!\n");
    
    // Vòng lặp menu chính
    do {
        hienThiMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                // Chức năng 1: Nhập sinh viên
                nhapDanhSachSinhVien(students, &n, 100);
                break;
                
            case 2:
                // Chức năng 2: In danh sách
                hienThiDanhSach(students, n);
                break;
                
            case 3:
                // Chức năng 3: Ghi file
                ghiFile(students, n);
                break;
                
            case 4:
                // Chức năng 4: Đọc file
                docFile(students, &n, 100);
                break;
                
            case 5:
                // Chức năng 5: Tìm kiếm
                timKiemSinhVien(students, n);
                break;
                
            case 6:
                // Chức năng 6: Sắp xếp
                sapXepTheoGPA(students, n);
                break;
                
            case 7:
                // Chức năng 7: Thêm sinh viên
                themSinhVien(students, &n, 100);
                break;
                
            case 8:
                // Chức năng 8: Xóa sinh viên
                xoaSinhVien(students, &n);
                break;
                
            case 9:
                // Chức năng 9: Khởi tạo dữ liệu mẫu
                khoiTaoDuLieuMau(students, &n);
                break;
                
            case 0:
                // Chức năng 0: Thoát
                printf("\nCam on ban da su dung chuong trinh!\n");
                printf("Hen gap lai!\n");
                break;
                
            default:
                // Lựa chọn không hợp lệ
                printf("\nLua chon khong hop le! Vui long chon lai.\n");
        }
    } while (choice != 0);  // Lặp lại cho đến khi chọn 0 (Thoát)
    
    return 0;
}
