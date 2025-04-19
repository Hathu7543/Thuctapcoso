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

	ucg_SetFont(&ucg, ucg_font_courR12_tf); // lựa chon font chữ và cỡ chữ
	ucg_SetColor(&ucg, 0, 0, 0, 255);
	ucg_SetColor(&ucg, 1, 0, 255, 0);
	ucg_SetRotate180(&ucg);
	ucg_DrawString (&ucg, 60 , 65 , 0, "N4-Day5"); // in dòng chữ ra LCD

	/* Loop forever */
	while(1)
	{
		processTimerScheduler();
	}
}
