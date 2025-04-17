/*
 * P3-B2.c
 *
 *  Created on: 17 thg 4, 2025
 *      Author: ADMIN
 */
#include <stdio.h>

// Khai báo cấu trúc
struct Rectangle {
    float chieu_dai;
    float chieu_rong;
    float dien_tich;
};
int main() {
    struct Rectangle hcn;
    // Nhập dữ liệu từ người dùng
    printf("Nhap chieu dai: ");
    scanf("%f", &hcn.chieu_dai);
    printf("Nhap chieu rong: ");
    scanf("%f", &hcn.chieu_rong);
    // Tính diện tích
    hcn.dien_tich = hcn.chieu_dai * hcn.chieu_rong;
    // In kết quả
    printf("Dien tich hinh chu nhat la: %.2f\n", hcn.dien_tich);
    getchar();
    getchar();
    return 0;
}
