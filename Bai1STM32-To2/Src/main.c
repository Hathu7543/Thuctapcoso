/*
 * main.c
 *
 *  Created on: Apr 5, 2025
 *      Author: ADMIN
 */
#include <stdint.h>
#include <timer.h>
#include <Ucglib.h>

static ucg_t ucg;

int main(void)
{
	SystemCoreClockUpdate();
	TimerInit();

	// Khởi tạo LCD
	Ucglib4WireSWSPI_begin(&ucg, UCG_FONT_MODE_SOLID);
	ucg_ClearScreen(&ucg);

	ucg_SetFont(&ucg, ucg_font_helvR08_tf); // lựa chon font chữ và cỡ chữ
	ucg_SetColor(&ucg, 0, 255, 255, 255);
	ucg_SetColor(&ucg, 1, 0, 0, 0);
	ucg_SetRotate180(&ucg);
	ucg_DrawString (&ucg, 0 , 12 , 0, "Ha Trung Thu"); // in dòng chữ ra LCD
	ucg_DrawString (&ucg, 0, 26, 0, "N22DCVT096");

	/* Loop forever */
	while(1)
	{
		processTimerScheduler();
	}
}