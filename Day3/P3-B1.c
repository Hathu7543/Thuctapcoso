/*
 * P3-B1.c
 *
 *  Created on: 17 thg 4, 2025
 *      Author: ADMIN
 */
#include <stdio.h>
// Khai báo cấu trúc có tên "addition"
struct addition {
    int num1;
    int num2;
    int sum;
};
int main() {
    struct addition Cong;
    // Nhập dữ liệu từ người dùng
    printf("Nhap so thu nhat: ");
    scanf("%d", &Cong.num1);
    printf("Nhap so thu hai: ");
    scanf("%d", &Cong.num2);
    // Tính tổng và gán vào thành viên sum
    Cong.sum = Cong.num1 + Cong.num2;
    // In kết quả
    printf("Tong cua %d va %d la: %d\n", Cong.num1, Cong.num2, Cong.sum);
    getchar();
    getchar();
    return 0;
}
