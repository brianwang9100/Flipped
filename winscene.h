/*
 * Exported with nin10kit v1.1
 * Invocation command was nin10kit -mode4 -palette=16 -start=8 winscene flippedwinscene.png 
 * Time-stamp: Monday 11/09/2015, 23:27:05
 * 
 * Image Information
 * -----------------
 * flippedwinscene.png 240@160
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * 
 * All bug reports / feature requests are to be sent to Brandon (bwhitehead0308@gmail.com)
 */

#ifndef WINSCENE_H
#define WINSCENE_H

#define WINSCENE_PALETTE_OFFSET  8

extern const unsigned short winscene_palette[16];
#define WINSCENE_PALETTE_SIZE 16

extern const unsigned short flippedwinscene[19200];
#define FLIPPEDWINSCENE_SIZE 19200
#define FLIPPEDWINSCENE_WIDTH 240
#define FLIPPEDWINSCENE_HEIGHT 160

#endif

