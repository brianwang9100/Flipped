/*
 * Exported with nin10kit v1.1
 * Invocation command was nin10kit -mode4 -palette=16 -start=8 grounds FlipGameGroundWhite.png FlipGameGroundBlack.png 
 * Time-stamp: Monday 11/09/2015, 22:32:43
 * 
 * Image Information
 * -----------------
 * FlipGameGroundWhite.png 240@10
 * FlipGameGroundBlack.png 240@10
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * 
 * All bug reports / feature requests are to be sent to Brandon (bwhitehead0308@gmail.com)
 */

#ifndef GROUNDS_H
#define GROUNDS_H

#define GROUNDS_PALETTE_OFFSET  8

extern const unsigned short grounds_palette[16];
#define GROUNDS_PALETTE_SIZE 16

extern const unsigned short FlipGameGroundWhite[1200];
#define FLIPGAMEGROUNDWHITE_SIZE 1200
#define FLIPGAMEGROUNDWHITE_WIDTH 240
#define FLIPGAMEGROUNDWHITE_HEIGHT 10

extern const unsigned short FlipGameGroundBlack[1200];
#define FLIPGAMEGROUNDBLACK_SIZE 1200
#define FLIPGAMEGROUNDBLACK_WIDTH 240
#define FLIPGAMEGROUNDBLACK_HEIGHT 10

#endif

