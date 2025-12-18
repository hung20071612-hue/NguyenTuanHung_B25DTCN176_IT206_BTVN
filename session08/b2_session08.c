#include <stdio.h>
#include <string.h>

// Định nghĩa struct Student
struct Student {
    int id;
    char name[50];
    int age;
    float gpa;
};

// Hàm nhập thông tin sinh viên
void nhapSinhVien(struct Student *sv, int stt) {
    printf("\n--- Nhap thong tin sinh vien thu %d ---\n", stt + 1);
    
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

int main() {
    struct Student students[5];
    int n;
    
    printf("=== CHUONG TRINH QUAN LY SINH VIEN ===\n");
    printf("Nhap so luong sinh vien (toi da 5): ");
    scanf("%d", &n);
    
    // Kiểm tra số lượng hợp lệ
    if (n < 1 || n > 5) {
        printf("So luong khong hop le! Chi cho phep nhap tu 1 den 5 sinh vien.\n");
        return 1;
    }
    
    // Nhập thông tin các sinh viên
    for (int i = 0; i < n; i++) {
        nhapSinhVien(&students[i], i);
    }
    
    // In danh sách sinh viên
    printf("\n=== DANH SACH SINH VIEN ===\n");
    inDanhSach(students, n);
    
    printf("Hoan thanh! Da nhap va xuat danh sach thanh cong.\n");
    
    return 0;
}