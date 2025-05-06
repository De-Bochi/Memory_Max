#include "st7789\st7789.h"
#include "stdbool.h"
void DrawCard(uint16_t x, uint16_t y, uint16_t color, const uint64_t* card, uint16_t bgcolor){
	for(int j = 0; j<50; j++){
		for(int i = 0; i<50; i++){
			if(card[i] & (1ULL << (49-j))) ST7789_DrawPixel(x+j, y+i, color);
			else ST7789_DrawPixel(x+j, y+i, bgcolor);
		}
	}
}
