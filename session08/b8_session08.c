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

/**
 * @brief Tạo file dữ liệu mẫu cho một lớp
 * 
 * BƯỚC 1: MỞ FILE ĐỂ GHI
 * ----------------------
 * - Sử dụng fopen() với mode "w" để tạo file mới hoặc ghi đè file cũ
 * - Kiểm tra file pointer != NULL để đảm bảo mở file thành công
 * - Nếu thất bại, in thông báo lỗi và return
 * 
 * BƯỚC 2: GHI TIÊU ĐỀ BẢNG
 * ------------------------
 * - Ghi các dòng phân cách và tiêu đề cột vào file
 * - Format giống như khi in ra màn hình để dễ đọc và nhất quán
 * 
 * BƯỚC 3: GHI DỮ LIỆU SINH VIÊN
 * ------------------------------
 * - Duyệt qua mảng students và ghi từng sinh viên vào file
 * - Sử dụng fprintf() để format dữ liệu giống như bảng
 * - Mỗi dòng chứa thông tin một sinh viên
 * 
 * BƯỚC 4: GHI THÔNG TIN TỔNG KẾT
 * -------------------------------
 * - Ghi dòng phân cách cuối cùng
 * - Ghi tổng số sinh viên trong lớp
 * - Có thể thêm thông tin khác như GPA trung bình nếu cần
 * 
 * BƯỚC 5: ĐÓNG FILE
 * ------------------
 * - Luôn đóng file bằng fclose() sau khi ghi xong
 * - Đảm bảo dữ liệu được flush vào đĩa
 * - Giải phóng tài nguyên hệ thống
 * 
 * @param students Mảng chứa danh sách sinh viên của lớp
 * @param n Số lượng sinh viên trong lớp
 * @param filename Tên file cần tạo (ví dụ: "classA.txt")
 * 
 * @return 1 nếu thành công, 0 nếu thất bại
 */
int taoFileDuLieu(struct Student students[], int n, const char *filename) {
    // BƯỚC 1: MỞ FILE ĐỂ GHI
    // -----------------------
    // Mở file với mode "w" (write) - tạo mới hoặc ghi đè
    FILE *file = fopen(filename, "w");
    
    // Kiểm tra xem file có mở thành công không
    if (file == NULL) {
        printf("Loi: Khong the tao file %s!\n", filename);
        return 0;  // Trả về 0 để báo hiệu lỗi
    }
    
    // BƯỚC 2: GHI TIÊU ĐỀ BẢNG
    // -------------------------
    // Ghi dòng phân cách đầu tiên
    fprintf(file, "+----+------------------+------+-------+\n");
    // Ghi dòng tiêu đề các cột
    fprintf(file, "| ID |      Name        | Age  |  GPA  |\n");
    // Ghi dòng phân cách sau tiêu đề
    fprintf(file, "+----+------------------+------+-------+\n");
    
    // BƯỚC 3: GHI DỮ LIỆU SINH VIÊN
    // ------------------------------
    // Duyệt qua từng sinh viên trong mảng
    for (int i = 0; i < n; i++) {
        // Ghi thông tin sinh viên vào file với format bảng
        // Format: | ID | Name | Age | GPA |
        fprintf(file, "| %-2d | %-16s | %-4d | %5.2f |\n", 
                students[i].id, 
                students[i].name, 
                students[i].age, 
                students[i].gpa);
    }
    
    // BƯỚC 4: GHI THÔNG TIN TỔNG KẾT
    // -------------------------------
    // Ghi dòng phân cách cuối cùng
    fprintf(file, "+----+------------------+------+-------+\n");
    // Ghi tổng số sinh viên trong lớp
    fprintf(file, "\nTong so sinh vien: %d\n", n);
    
    // BƯỚC 5: ĐÓNG FILE
    // -----------------
    // Đóng file để đảm bảo dữ liệu được ghi vào đĩa
    fclose(file);
    
    return 1;  // Trả về 1 để báo hiệu thành công
}

/**
 * @brief Đọc dữ liệu sinh viên từ file
 * 
 * BƯỚC 1: MỞ FILE ĐỂ ĐỌC
 * ----------------------
 * - Sử dụng fopen() với mode "r" (read) để mở file chỉ đọc
 * - Kiểm tra file pointer != NULL để đảm bảo file tồn tại
 * - Nếu file không tồn tại, in thông báo lỗi và return
 * 
 * BƯỚC 2: KHỞI TẠO BIẾN
 * ----------------------
 * - Khởi tạo biến đếm số lượng sinh viên (*n = 0)
 * - Tạo buffer để đọc từng dòng từ file (char line[200])
 * - Đặt cờ để bỏ qua các dòng tiêu đề (skipHeader, skipCount)
 * 
 * BƯỚC 3: ĐỌC TỪNG DÒNG TRONG FILE
 * ---------------------------------
 * - Sử dụng vòng lặp while với fgets() để đọc từng dòng
 * - fgets() đọc đến khi gặp ký tự xuống dòng hoặc hết buffer
 * - Kiểm tra điều kiện dừng: fgets() trả về NULL hoặc đã đọc đủ số lượng tối đa
 * 
 * BƯỚC 4: LỌC CÁC DÒNG KHÔNG PHẢI DỮ LIỆU
 * ---------------------------------------
 * - Bỏ qua các dòng phân cách (bắt đầu bằng '+')
 * - Bỏ qua 3 dòng đầu tiên (tiêu đề bảng)
 * - Bỏ qua dòng "Tong so sinh vien"
 * - Chỉ xử lý các dòng bắt đầu bằng '|' (dòng dữ liệu)
 * 
 * BƯỚC 5: PARSE DỮ LIỆU TỪ DÒNG
 * ------------------------------
 * - Sử dụng sscanf() để trích xuất dữ liệu từ dòng
 * - Format: "| %d | %49[^|] | %d | %f |"
 *   + %d: đọc ID (số nguyên)
 *   + %49[^|]: đọc tên (tối đa 49 ký tự, dừng khi gặp '|')
 *   + %d: đọc tuổi (số nguyên)
 *   + %f: đọc GPA (số thực)
 * - Kiểm tra sscanf() trả về 4 để đảm bảo đọc đủ 4 trường
 * 
 * BƯỚC 6: XỬ LÝ TÊN SINH VIÊN
 * ----------------------------
 * - Loại bỏ khoảng trắng thừa ở đầu và cuối tên
 * - Tìm vị trí bắt đầu (bỏ qua khoảng trắng đầu)
 * - Tìm vị trí kết thúc (bỏ qua khoảng trắng cuối)
 * - Copy tên đã được trim vào struct
 * 
 * BƯỚC 7: LƯU SINH VIÊN VÀO MẢNG
 * -------------------------------
 * - Gán sinh viên đã parse vào mảng students[*n]
 * - Tăng biến đếm (*n)++
 * - Kiểm tra không vượt quá giới hạn mảng (tối đa 10)
 * 
 * BƯỚC 8: ĐÓNG FILE
 * ------------------
 * - Đóng file bằng fclose() sau khi đọc xong
 * - Giải phóng tài nguyên hệ thống
 * 
 * @param students Mảng để lưu danh sách sinh viên đọc được
 * @param n Con trỏ đến biến lưu số lượng sinh viên (sẽ được cập nhật)
 * @param filename Tên file cần đọc (ví dụ: "classA.txt")
 * 
 * @return 1 nếu thành công, 0 nếu thất bại
 */
int docFileDuLieu(struct Student students[], int *n, const char *filename) {
    // BƯỚC 1: MỞ FILE ĐỂ ĐỌC
    // ------------------------
    // Mở file với mode "r" (read) - chỉ đọc
    FILE *file = fopen(filename, "r");
    
    // Kiểm tra xem file có mở thành công không
    if (file == NULL) {
        printf("Loi: Khong the mo file %s!\n", filename);
        printf("Kiem tra lai ten file hoac duong dan file.\n");
        return 0;  // Trả về 0 để báo hiệu lỗi
    }
    
    // BƯỚC 2: KHỞI TẠO BIẾN
    // ----------------------
    // Khởi tạo số lượng sinh viên = 0
    *n = 0;
    // Buffer để đọc từng dòng từ file (tối đa 200 ký tự)
    char line[200];
    // Cờ để bỏ qua các dòng tiêu đề (3 dòng đầu)
    int skipHeader = 1;
    int skipCount = 0;
    
    // BƯỚC 3: ĐỌC TỪNG DÒNG TRONG FILE
    // ---------------------------------
    // Đọc từng dòng cho đến khi hết file hoặc đã đọc đủ 10 sinh viên
    while (fgets(line, sizeof(line), file) != NULL && *n < 10) {
        
        // BƯỚC 4: LỌC CÁC DÒNG KHÔNG PHẢI DỮ LIỆU
        // ---------------------------------------
        // Bỏ qua các dòng phân cách (bắt đầu bằng '+')
        if (line[0] == '+') {
            continue;  // Bỏ qua dòng này, đọc dòng tiếp theo
        }
        
        // Bỏ qua 3 dòng đầu tiên (tiêu đề bảng)
        if (skipHeader && skipCount < 3) {
            skipCount++;
            if (skipCount >= 3) {
                skipHeader = 0;  // Đã bỏ qua đủ 3 dòng, tắt cờ
            }
            continue;  // Bỏ qua dòng này, đọc dòng tiếp theo
        }
        
        // Bỏ qua dòng "Tong so sinh vien"
        if (strstr(line, "Tong so sinh vien") != NULL) {
            continue;  // Bỏ qua dòng này, đọc dòng tiếp theo
        }
        
        // BƯỚC 5: PARSE DỮ LIỆU TỪ DÒNG
        // ------------------------------
        // Chỉ xử lý các dòng bắt đầu bằng '|' (dòng dữ liệu)
        if (line[0] == '|') {
            struct Student sv;  // Biến tạm để lưu sinh viên
            
            // Sử dụng sscanf() để trích xuất dữ liệu từ dòng
            // Format: "| ID | Name | Age | GPA |"
            // %49[^|] nghĩa là đọc tối đa 49 ký tự, dừng khi gặp ký tự '|'
            if (sscanf(line, "| %d | %49[^|] | %d | %f |", 
                      &sv.id, sv.name, &sv.age, &sv.gpa) == 4) {
                
                // BƯỚC 6: XỬ LÝ TÊN SINH VIÊN
                // ----------------------------
                // Loại bỏ khoảng trắng thừa ở đầu tên
                char *start = sv.name;
                while (*start == ' ') {
                    start++;  // Di chuyển con trỏ đến ký tự đầu tiên không phải khoảng trắng
                }
                
                // Loại bỏ khoảng trắng thừa ở cuối tên
                char *end = start + strlen(start) - 1;
                while (end > start && *end == ' ') {
                    end--;  // Di chuyển con trỏ về trước đến ký tự cuối cùng không phải khoảng trắng
                }
                *(end + 1) = '\0';  // Đặt ký tự kết thúc chuỗi
                
                // Copy tên đã được trim vào struct
                strcpy(sv.name, start);
                
                // BƯỚC 7: LƯU SINH VIÊN VÀO MẢNG
                // -------------------------------
                // Gán sinh viên đã parse vào mảng
                students[*n] = sv;
                // Tăng biến đếm số lượng sinh viên
                (*n)++;
            }
        }
    }
    
    // BƯỚC 8: ĐÓNG FILE
    // ------------------
    // Đóng file sau khi đọc xong
    fclose(file);
    
    return 1;  // Trả về 1 để báo hiệu thành công
}

/**
 * @brief Tạo dữ liệu mẫu cho 3 lớp (classA.txt, classB.txt, classC.txt)
 * 
 * BƯỚC 1: TẠO DỮ LIỆU CHO LỚP A
 * ------------------------------
 * - Khởi tạo mảng students với 5 sinh viên mẫu
 * - Gọi hàm taoFileDuLieu() để ghi vào classA.txt
 * - Kiểm tra kết quả và in thông báo
 * 
 * BƯỚC 2: TẠO DỮ LIỆU CHO LỚP B
 * ------------------------------
 * - Khởi tạo mảng students với 4 sinh viên mẫu (khác lớp A)
 * - Gọi hàm taoFileDuLieu() để ghi vào classB.txt
 * - Kiểm tra kết quả và in thông báo
 * 
 * BƯỚC 3: TẠO DỮ LIỆU CHO LỚP C
 * ------------------------------
 * - Khởi tạo mảng students với 6 sinh viên mẫu (khác lớp A, B)
 * - Gọi hàm taoFileDuLieu() để ghi vào classC.txt
 * - Kiểm tra kết quả và in thông báo
 * 
 * @note Mỗi lớp có số lượng và dữ liệu sinh viên khác nhau để test đầy đủ
 */
void taoDuLieuMauCho3Lop() {
    printf("\n=== TAO DU LIEU MAU CHO 3 LOP ===\n");
    
    // BƯỚC 1: TẠO DỮ LIỆU CHO LỚP A
    // ------------------------------
    printf("\n1. Tao du lieu cho classA.txt...\n");
    struct Student classA[5] = {
        {1, "Nguyen Van A", 20, 3.5},
        {2, "Tran Thi B", 21, 3.8},
        {3, "Le Van C", 19, 3.2},
        {4, "Pham Thi D", 22, 3.9},
        {5, "Hoang Van E", 20, 3.6}
    };
    
    if (taoFileDuLieu(classA, 5, "classA.txt")) {
        printf("   -> Thanh cong! Da tao file classA.txt voi 5 sinh vien.\n");
    } else {
        printf("   -> That bai! Khong the tao file classA.txt.\n");
    }
    
    // BƯỚC 2: TẠO DỮ LIỆU CHO LỚP B
    // ------------------------------
    printf("\n2. Tao du lieu cho classB.txt...\n");
    struct Student classB[4] = {
        {1, "Vu Thi F", 21, 2.8},
        {2, "Dao Van G", 20, 3.0},
        {3, "Bui Thi H", 19, 3.4},
        {4, "Dang Van I", 22, 2.9}
    };
    
    if (taoFileDuLieu(classB, 4, "classB.txt")) {
        printf("   -> Thanh cong! Da tao file classB.txt voi 4 sinh vien.\n");
    } else {
        printf("   -> That bai! Khong the tao file classB.txt.\n");
    }
    
    // BƯỚC 3: TẠO DỮ LIỆU CHO LỚP C
    // ------------------------------
    printf("\n3. Tao du lieu cho classC.txt...\n");
    struct Student classC[6] = {
        {1, "Ly Thi K", 20, 4.0},
        {2, "Ngo Van L", 21, 3.7},
        {3, "Do Thi M", 19, 3.1},
        {4, "Truong Van N", 22, 3.3},
        {5, "Le Thi O", 20, 2.5},
        {6, "Phan Van P", 21, 3.8}
    };
    
    if (taoFileDuLieu(classC, 6, "classC.txt")) {
        printf("   -> Thanh cong! Da tao file classC.txt voi 6 sinh vien.\n");
    } else {
        printf("   -> That bai! Khong the tao file classC.txt.\n");
    }
    
    printf("\n=== HOAN THANH TAO DU LIEU MAU ===\n");
}

int main() {
    struct Student students[10];
    int n = 0;
    int choice;
    char filename[100];  // Buffer để lưu tên file người dùng nhập
    
    printf("=== CHUONG TRINH QUAN LY NHIEU FILE LOP ===\n");
    
    // Menu chính
    do {
        printf("\n=== MENU ===\n");
        printf("1. Tao du lieu mau cho 3 lop (classA.txt, classB.txt, classC.txt)\n");
        printf("2. Doc du lieu tu file (nhap ten file)\n");
        printf("3. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        
        // Xóa bộ đệm để tránh lỗi khi nhập chuỗi sau scanf
        while (getchar() != '\n');
        
        switch (choice) {
            case 1:
                // Tạo dữ liệu mẫu cho 3 lớp
                taoDuLieuMauCho3Lop();
                break;
                
            case 2:
                // Đọc dữ liệu từ file
                printf("\nNhap ten file can doc (vi du: classA.txt): ");
                fgets(filename, sizeof(filename), stdin);
                // Xóa ký tự xuống dòng ở cuối
                filename[strcspn(filename, "\n")] = 0;
                
                printf("\nDang doc du lieu tu file: %s\n", filename);
                
                if (docFileDuLieu(students, &n, filename)) {
                    if (n > 0) {
                        printf("Da doc thanh cong %d sinh vien tu file %s\n", n, filename);
                        printf("\n=== DANH SACH SINH VIEN ===\n");
                        inDanhSach(students, n);
                    } else {
                        printf("File rong hoac khong co du lieu sinh vien!\n");
                    }
                } else {
                    printf("Khong the doc file! Vui long kiem tra lai ten file.\n");
                }
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
