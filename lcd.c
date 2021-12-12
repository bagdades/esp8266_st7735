/*
 * =====================================================================================
 *
 *       Filename:  lcd.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12.12.21 19:14:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "espressif/esp_common.h"
#include "esp/gpio.h"
#include "esp/spi.h"
#include "esp/uart.h"
#include <stdio.h>
#include "espressif/esp_system.h"
#include "font.h"
#include "st7735.h"
#include "FreeRTOS.h"
#include "task.h"
#include "image.h"

void loop(void* pvParameters)
{
	while (1) {
		// Check border
		ST7735_FillScreen(ST7735_BLACK);

		for(int x = 0; x < ST7735_WIDTH; x++) {
			ST7735_DrawPixel(x, 0, ST7735_RED);
			ST7735_DrawPixel(x, ST7735_HEIGHT-1, ST7735_RED);
		}

		for(int y = 0; y < ST7735_HEIGHT; y++) {
			ST7735_DrawPixel(0, y, ST7735_RED);
			ST7735_DrawPixel(ST7735_WIDTH-1, y, ST7735_RED);
		}

		vTaskDelay(3000 / portTICK_PERIOD_MS);

		// Check fonts
		ST7735_FillScreen(ST7735_BLACK);
		ST7735_WriteString(0, 0, "Font_7x10, red on black, lorem ipsum dolor sit amet", Font_7x10, ST7735_RED, ST7735_BLACK);
		ST7735_WriteString(0, 3*10, "Font_11x18, green, lorem ipsum", Font_11x18, ST7735_GREEN, ST7735_BLACK);
		ST7735_WriteString(0, 3*10+3*18, "Font_16x26", Font_16x26, ST7735_BLUE, ST7735_BLACK);
		vTaskDelay(2000 / portTICK_PERIOD_MS);

		// Check colors
		ST7735_FillScreen(ST7735_BLACK);
		ST7735_WriteString(0, 0, "BLACK", Font_11x18, ST7735_WHITE, ST7735_BLACK);
		vTaskDelay(500 / portTICK_PERIOD_MS);

		ST7735_FillScreen(ST7735_BLUE);
		ST7735_WriteString(0, 0, "BLUE", Font_11x18, ST7735_BLACK, ST7735_BLUE);
		vTaskDelay(500 / portTICK_PERIOD_MS);

		ST7735_FillScreen(ST7735_RED);
		ST7735_WriteString(0, 0, "RED", Font_11x18, ST7735_BLACK, ST7735_RED);
		vTaskDelay(500 / portTICK_PERIOD_MS);

		ST7735_FillScreen(ST7735_GREEN);
		ST7735_WriteString(0, 0, "GREEN", Font_11x18, ST7735_BLACK, ST7735_GREEN);
		vTaskDelay(500 / portTICK_PERIOD_MS);

		ST7735_FillScreen(ST7735_CYAN);
		ST7735_WriteString(0, 0, "CYAN", Font_11x18, ST7735_BLACK, ST7735_CYAN);
		vTaskDelay(500 / portTICK_PERIOD_MS);

		ST7735_FillScreen(ST7735_MAGENTA);
		ST7735_WriteString(0, 0, "MAGENTA", Font_11x18, ST7735_BLACK, ST7735_MAGENTA);
		vTaskDelay(500 / portTICK_PERIOD_MS);

		ST7735_FillScreen(ST7735_YELLOW);
		ST7735_WriteString(0, 0, "YELLOW", Font_11x18, ST7735_BLACK, ST7735_YELLOW);
		vTaskDelay(500 / portTICK_PERIOD_MS);

		ST7735_FillScreen(ST7735_WHITE);
		ST7735_WriteString(0, 0, "WHITE", Font_11x18, ST7735_BLACK, ST7735_WHITE);
		vTaskDelay(500 / portTICK_PERIOD_MS);

		ST7735_DrawImage(0, 0, ST7735_WIDTH, ST7735_HEIGHT, (uint16_t*)test_img_160x80);
		vTaskDelay(15000 / portTICK_PERIOD_MS);
	}
}

void user_init(void) {
	uart_set_baud(0, 115200);
	printf("SDK version:%s\r\n", sdk_system_get_sdk_version());
	ST7735_Init();
	xTaskCreate(loop, "loop", 1024, NULL, 2, NULL);
}
