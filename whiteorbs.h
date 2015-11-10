/*
 * Exported with nin10kit v1.1
 * Invocation command was nin10kit -mode4 -palette=16 -start=40 whiteorbs whiteorb.gif 
 * Time-stamp: Monday 11/09/2015, 22:34:39
 * 
 * Image Information
 * -----------------
 * whiteorb.gif (frame 0) 6@6
 * whiteorb.gif (frame 1) 6@6
 * whiteorb.gif (frame 2) 6@6
 * whiteorb.gif (frame 3) 6@6
 * whiteorb.gif (frame 4) 6@6
 * whiteorb.gif (frame 5) 6@6
 * whiteorb.gif (frame 6) 6@6
 * whiteorb.gif (frame 7) 6@6
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * 
 * All bug reports / feature requests are to be sent to Brandon (bwhitehead0308@gmail.com)
 */

#ifndef WHITEORBS_H
#define WHITEORBS_H

#define WHITEORBS_PALETTE_OFFSET  40

extern const unsigned short whiteorbs_palette[16];
#define WHITEORBS_PALETTE_SIZE 16

extern const unsigned short whiteorb0[18];

extern const unsigned short whiteorb1[18];

extern const unsigned short whiteorb2[18];

extern const unsigned short whiteorb3[18];

extern const unsigned short whiteorb4[18];

extern const unsigned short whiteorb5[18];

extern const unsigned short whiteorb6[18];

extern const unsigned short whiteorb7[18];

extern const unsigned short* whiteorb_frames[8];
#define WHITEORB_FRAMES 8
#define WHITEORB_SIZE 18
#define WHITEORB_WIDTH 6
#define WHITEORB_HEIGHT 6

#endif

