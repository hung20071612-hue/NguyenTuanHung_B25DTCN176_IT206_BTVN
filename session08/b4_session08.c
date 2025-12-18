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

// Hàm đọc danh sách sinh viên từ file
int loadFromFile(struct Student students[], int *n, const char *filename) {
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        printf("Loi: Khong the mo file de doc!\n");
        return 0;
    }
    
    char line[200];
    *n = 0;
    int skipHeader = 1; // Bỏ qua 3 dòng đầu (tiêu đề bảng)
    int skipCount = 0;
    
    while (fgets(line, sizeof(line), file) != NULL && *n < 5) {
        // Bỏ qua các dòng phân cách và tiêu đề
        if (line[0] == '+' || (skipHeader && skipCount < 3)) {
            skipCount++;
            if (skipCount >= 3) {
                skipHeader = 0;
            }
            continue;
        }
        
        // Bỏ qua dòng "Tong so sinh vien"
        if (strstr(line, "Tong so sinh vien") != NULL) {
            continue;
        }
        
        // Đọc dòng dữ liệu có format: | ID | Name | Age | GPA |
        if (line[0] == '|') {
            struct Student sv;
            // Parse dữ liệu từ dòng: | %d | %s | %d | %f |
            if (sscanf(line, "| %d | %49[^|] | %d | %f |", 
                      &sv.id, sv.name, &sv.age, &sv.gpa) == 4) {
                // Xóa khoảng trắng thừa ở đầu và cuối tên
                // Trim leading spaces
                char *start = sv.name;
                while (*start == ' ') start++;
                // Trim trailing spaces
                char *end = start + strlen(start) - 1;
                while (end > start && *end == ' ') end--;
                *(end + 1) = '\0';
                
                // Copy tên đã được trim
                strcpy(sv.name, start);
                
                students[*n] = sv;
                (*n)++;
            }
        }
    }
    
    fclose(file);
    return 1;
}

int main() {
    struct Student students[5];
    int n = 0;
    
    printf("=== CHUONG TRINH DOC FILE SINH VIEN ===\n");
    
    // Đọc danh sách từ file
    if (loadFromFile(students, &n, "students.txt")) {
        if (n > 0) {
            printf("Da doc thanh cong %d sinh vien tu file students.txt\n", n);
            
            // In danh sách sinh viên
            printf("\n=== DANH SACH SINH VIEN ===\n");
            inDanhSach(students, n);
            
            printf("Hoan thanh! Da doc va in danh sach thanh cong.\n");
        } else {
            printf("File rong hoac khong co du lieu sinh vien!\n");
        }
    } else {
        printf("Loi khi doc file!\n");
        return 1;
    }
    
    return 0;
}

