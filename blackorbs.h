/*
 * Exported with nin10kit v1.1
 * Invocation command was nin10kit -mode4 -palette=16 -start=24 blackorbs blackorb.gif 
 * Time-stamp: Monday 11/09/2015, 22:34:21
 * 
 * Image Information
 * -----------------
 * blackorb.gif (frame 0) 6@6
 * blackorb.gif (frame 1) 6@6
 * blackorb.gif (frame 2) 6@6
 * blackorb.gif (frame 3) 6@6
 * blackorb.gif (frame 4) 6@6
 * blackorb.gif (frame 5) 6@6
 * blackorb.gif (frame 6) 6@6
 * blackorb.gif (frame 7) 6@6
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * 
 * All bug reports / feature requests are to be sent to Brandon (bwhitehead0308@gmail.com)
 */

#ifndef BLACKORBS_H
#define BLACKORBS_H

#define BLACKORBS_PALETTE_OFFSET  24

extern const unsigned short blackorbs_palette[15];
#define BLACKORBS_PALETTE_SIZE 15

extern const unsigned short blackorb0[18];

extern const unsigned short blackorb1[18];

extern const unsigned short blackorb2[18];

extern const unsigned short blackorb3[18];

extern const unsigned short blackorb4[18];

extern const unsigned short blackorb5[18];

extern const unsigned short blackorb6[18];

extern const unsigned short blackorb7[18];

extern const unsigned short* blackorb_frames[8];
#define BLACKORB_FRAMES 8
#define BLACKORB_SIZE 18
#define BLACKORB_WIDTH 6
#define BLACKORB_HEIGHT 6

#endif

