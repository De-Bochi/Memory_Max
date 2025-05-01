#include "st7789\st7789.h"
#include "stdbool.h"
void DrawCard(uint8_t x, uint8_t y, uint16_t color, const bool* card){
	for(int j = 0; j<50; j++){
		for(int i = 0; i<50; i++){
			if(card[i*50 + j]) ST7789_DrawPixel(x+j, y+i, color);
			else ST7789_DrawPixel(x+j, y+i, WHITE);
		}
	}
}
