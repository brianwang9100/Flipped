#include "mylib.h"

u16 *videoBuffer = (u16*) 0x6000000;

void setPixel(int r, int c, u16 color) {
	videoBuffer[OFFSET(r, c, 240)] = color;
}

void setPixel4(int r, int c, u8 index) {
    int whichPixel = OFFSET(r, c, 240);
    int whichShort = whichPixel/2;
    if(c & 1)
    {
        // Column is odd. We change left byte
        videoBuffer[whichShort] = (videoBuffer[whichShort] & 0x00FF) | (index<<8);
        
    }
    else
    {
        // Column is even. We change right byte
        videoBuffer[whichShort] = (videoBuffer[whichShort] & 0xFF00) | (index);
    }
}

void drawRect(int r, int c, int width, int height, u16 color) {
    for(int row = 0; row < height; row++)
    {
        DMA[3].src = &color;
        DMA[3].dst = &videoBuffer[OFFSET(r + row, c, 240)];
        DMA[3].cnt = width | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED | DMA_ON;
        
    }
}

void drawRect4(int r, int c, int width, int height, u8 index) {
    volatile u16 color = index<<8 | index;
    
    for(int row = 0; row < height; row++)
    {
        DMA[3].src = &color;
        DMA[3].dst = &videoBuffer[OFFSET(r + row, c, 240)/2];
        DMA[3].cnt = (width/2) | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED | DMA_ON;
    }
} 

void drawHollowRect(int r, int c, int width, int height, u16 color) {
	for (int row = 0; row < height; row++) {
		setPixel(row + r, c, color);	
		setPixel(row + r,c + width - 1, color); 
	}
	for (int col = 0; col < width; col++) {
		setPixel(r, col + c, color);
		setPixel(r + height - 1, col  + c, color);
	}	
}

void fillScreen(volatile u16 color) {
	DMA[3].src = &color;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = (240*160) | DMA_SOURCE_FIXED | DMA_ON;
}

void fillScreen4(unsigned char index) {
	volatile unsigned short color = index | (index << 8);
	DMA[3].src = &color;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = 19200 | DMA_SOURCE_FIXED | DMA_ON;
}

void fillScreenWithPicture(const u16 *image) {
	DMA[3].src = image;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = (240*160) | DMA_ON;
}

void waitForVblank() {
    while(SCANLINECOUNTER > 160);
    while(SCANLINECOUNTER < 160);
}

void drawImage4(int r, int c, int width, int height, const u16 *image) {	
	for (int row = 0; row < height; row++) {
		DMA[3].src = &image[OFFSET(row, 0, width)/2];
		DMA[3].dst = &videoBuffer[OFFSET(row+r, c, 240)/2];
		DMA[3].cnt = width/2 | DMA_ON;
	}
	
    //for(int row = 0; row < height; row++)
    //{
    //    DMA[3].src = &image[OFFSET(row, c, width)/2];
    //    DMA[3].dst = &videoBuffer[OFFSET(r + row, c, 240)/2];
    //    DMA[3].cnt = (width/2) | DMA_DESTINATION_INCREMENT | DMA_ON;
    //}
}

void drawChar(int r, int c, char ch, u16 color) {
	for(int row = 0; row < 8; row++) {
		for(int col = 0; col < 6; col++) {
			if(fontdata_6x8[OFFSET(row, col, 6) + ch*48]){
				setPixel(r+row, c+col, color);
			}
		}
	}
}

void drawString(int r, int c, char *str, u16 color) {
	while(*str)	{
		drawChar(r, c, *str++, color);
		c += 6;
	}
}

void drawChar4(int r, int c, char ch, u8 index) {
    
    for(int row = 0; row < 8; row++)
    {
        for(int col = 0; col < 6; col++)
        {
            if(fontdata_6x8[OFFSET(row, col, 6) + ch*48])
            {
                setPixel4(r+row, c+col, index);
            }
        }
    }
}

void drawString4(int r, int c, char *str, u8 index) {
    while(*str)
    {
        drawChar4(r, c, *str++, index);
        c+= 6;
    }
}

void flip() {
    if(REG_DISPCNT & BUFFER1FLAG)
    {
        // we were displaying BUFFER1
        videoBuffer = BUFFER1;
        REG_DISPCNT = REG_DISPCNT & ~BUFFER1FLAG;
    }
    else
    {
        // We were displaying BUFFER0
        videoBuffer = BUFFER0;
        REG_DISPCNT = REG_DISPCNT | BUFFER1FLAG;
    }
}

void loadpalette(int offset, int size, const u16* palette) {
	DMA[3].src = palette;
	DMA[3].dst = &PALETTE[offset];
	DMA[3].cnt = size | DMA_ON;
}

