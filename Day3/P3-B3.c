/*
 * P3-B3.c
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
// Hàm tính diện tích – nhận struct qua con trỏ
void tinh_dien_tich(struct Rectangle *s) {
    s->dien_tich = s->chieu_dai * s->chieu_rong;
}
int main() {
    struct Rectangle hcn;
    // Nhập dữ liệu từ người dùng
    printf("Nhap chieu dai: ");
    scanf("%f", &hcn.chieu_dai);
    printf("Nhap chieu rong: ");
    scanf("%f", &hcn.chieu_rong);
    // Gọi hàm tính diện tích
    tinh_dien_tich(&hcn);
    // In kết quả
    printf("Dien tich hinh chu nhat: %.2f\n", hcn.dien_tich);
    getchar();
    getchar();
    return 0;
}
