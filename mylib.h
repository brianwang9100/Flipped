typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u16 *videoBuffer;
extern const unsigned char fontdata_6x8[122288];

#define REG_DISPCNT *(u16*) 0x4000000
#define BG2_EN (1 << 10)
#define MODE_3 3
#define SCANLINECOUNTER *(volatile unsigned short *)0x4000006

//MODE4 SETUP
#define MODE_4 4
#define BUFFER0 (unsigned short *)0x6000000
#define BUFFER1 (unsigned short *)0x600A000
#define BUFFER1FLAG 0x10
#define PALETTE ((unsigned short *)0x5000000)

//COLORS
#define RGB(R,G,B) (((R) & 0x1F) | (((G) & 0x1F) << 5) | (((B) & 0x1F) << 10))
#define BLACK   RGB(0 , 0 , 0 )
#define WHITE   RGB(31, 31, 31)
#define RED     RGB(31, 0 , 0 )
#define GREEN   RGB(0 , 31, 0 )
#define BLUE    RGB(0 , 0 , 31)
#define YELLOW  RGB(31, 31, 0 )
#define MAGENTA RGB(31, 0 , 31)
#define CYAN    RGB(0 , 31, 31)
#define ORANGE  RGB(31, 15, 0 )
#define BROWN   RGB(18, 9 , 0 )
#define PURPLE  RGB(15, 0 , 15)
#define TEAL    RGB(0 , 15, 15)
#define MAROON  RGB(15, 0 , 0 )
#define GRAY    RGB(15, 15, 15)
#define PINK    RGB(31, 18, 19)
#define LTGRAY	RGB(22, 22, 22)
#define OFFSET(r, c, rowlen) ((r)*(rowlen)+(c))

//BUTTONS
#define BUTTONS *(volatile unsigned int *)0x4000130
#define BUTTON_A			(1<<0)
#define BUTTON_B			(1<<1)
#define BUTTON_SELECT		(1<<2)
#define BUTTON_START		(1<<3)
#define BUTTON_RIGHT		(1<<4)
#define BUTTON_LEFT			(1<<5)
#define BUTTON_UP			(1<<6)
#define BUTTON_DOWN			(1<<7)
#define BUTTON_R			(1<<8)
#define BUTTON_L			(1<<9)

#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)

//DMAAAA
// DMA channel 0 register definitions
#define REG_DMA0SAD         *(const volatile u32*)0x40000B0 // source address
#define REG_DMA0DAD         *(volatile u32*)0x40000B4       // destination address
#define REG_DMA0CNT         *(volatile u32*)0x40000B8       // control register

// DMA channel 1 register definitions
#define REG_DMA1SAD         *(const volatile u32*)0x40000BC // source address
#define REG_DMA1DAD         *(volatile u32*)0x40000C0       // destination address
#define REG_DMA1CNT         *(volatile u32*)0x40000C4       // control register

// DMA channel 2 register definitions
#define REG_DMA2SAD         *(const volatile u32*)0x40000C8 // source address
#define REG_DMA2DAD         *(volatile u32*)0x40000CC       // destination address
#define REG_DMA2CNT         *(volatile u32*)0x40000D0       // control register

// DMA channel 3 register definitions
#define REG_DMA3SAD         *(const volatile u32*)0x40000D4 // source address
#define REG_DMA3DAD         *(volatile u32*)0x40000D8       // destination address
#define REG_DMA3CNT         *(volatile u32*)0x40000DC       // control register

typedef struct
{
	const volatile void *src;
	const volatile void *dst;
	u32                  cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER *) 0x040000B0)

#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)
//pixel
void setPixel(int r, int c, u16 color);
void setPixel4(int r, int c, u8 index);
//rect
void drawRect(int r, int c, int width, int height, u16 color);
void drawRect4(int r, int c, int width, int height, u8 index);
void drawHollowRect(int r, int c, int width, int height, u16 color);
//fill
void fillScreen(volatile u16 color);
void fillScreen4(unsigned char index);
void fillScreenWithPicture(const u16 *image);
//other
void waitForVblank();
void drawImage4(int r, int c, int width, int height, const u16* image);
//text
void drawChar(int r, int c, char ch, u16 color);
void drawString(int r, int c, char *str, u16 color);
void drawChar4(int r, int c, char ch, u8 index);
void drawString4(int r, int c, char *str, u8 index);
//flip
void flip();
//palette
void loadpalette(int offset, int size, const u16* palette); 
