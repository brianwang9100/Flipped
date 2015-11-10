#include "main.h"
#include <stdlib.h>
#include <stdio.h>

#define NUMGOALS 10
#define GROUND 10
#define HEIGHT 150
#define WINSCORE 10

enum {BLACKIDX, WHITEIDX};

static int state = START_SCENE;
static int score = 0;
static int splits = 1;

static unsigned short LAST_A = 0;
static unsigned short LAST_B = 0;
static unsigned short LAST_SELECT = 0;
static unsigned short LAST_START = 0;
//static unsigned short LAST_RIGHT = 0;
//static unsigned short LAST_LEFT = 0;
//static unsigned short LAST_UP = 0;
//static unsigned short LAST_DOWN = 0;
//static unsigned short LAST_R = 0;
//static unsigned short LAST_L = 0;

int main(void) {
	REG_DISPCNT = BG2_EN | MODE_4;
	u16 colors[] = {BLACK, WHITE};
	int numcolors = sizeof(colors)/sizeof(colors[0]);
	for(int i = 0; i < numcolors; i++) {
		PALETTE[i] = colors[i];
	}

	while(1) {  
		switch(state) {
			case START_SCENE:
				state = start();
				break;
			case MAIN_SCENE:
				state = game();
				break;
			case WIN_SCENE:
				state = win();
				break;
			case LOSE_SCENE:
				state = lose();
				break;	
		}
	}
}

int game() {
	int flipped = 0;
	score = 0;
	int goalcounter = 0;
	splits = 1;
	int animationframecounter = 0;

	loadpalette(GROUNDS_PALETTE_OFFSET, GROUNDS_PALETTE_SIZE, grounds_palette);
	loadpalette(BLACKORBS_PALETTE_OFFSET, BLACKORBS_PALETTE_SIZE, blackorbs_palette);
	loadpalette(WHITEORBS_PALETTE_OFFSET, WHITEORBS_PALETTE_SIZE, whiteorbs_palette);
	//mainChar
	MAINCHAR mainChar = {GROUND, 0, 2, 0, 10, WHITEIDX};
	mainChar.col = 240/2 - mainChar.size/2;

	//coin
	ORB orb = {0, 0, 0, 0, 0, 6, 6, WHITEIDX};
	orb.row = HEIGHT - orb.height - 2;
	orb.col = 240/2 - orb.height/2;

	//goals
	GOAL goals[NUMGOALS];
	GOAL *goalpointer = goals;
	for (int i = 0; i < NUMGOALS; i++) {
		goals[i].set = 0;
		goals[i].row = 0;
		goals[i].col = 0;
		goals[i].deltar = 0;
		goals[i].deltac = 0;
		goals[i].width = 0;
		goals[i].height = 0;
		goals[i].color = WHITEIDX;
	}

	//init drawing
	char splitsbuffer[50];
	char scorebuffer[50];
	flip();
	fillScreen4(BLACKIDX);
	drawRect4(0, 0, 240, 10, WHITEIDX);
	drawRect4(HEIGHT, 0, 240, 10, WHITEIDX);
	flip();
	fillScreen4(BLACKIDX);
	drawRect4(0, 0, 240, 10, WHITEIDX);
	drawRect4(HEIGHT, 0, 240, 10, WHITEIDX);

	while(1) {
		if (KEY_DOWN_NOW(BUTTON_SELECT)) {
			return START_SCENE;
		}	
    	//timerframecounter++;
    	goalcounter++;
    	animationframecounter++;
		//timer
    	//if (timerframecounter >= 60) {
		//	timer--;
		//	timerframecounter = 0;
		//}
		//if (timer <= 0) {
		//	return LOSE_SCENE;
		//}
		
		//goal spawning
		if (goalcounter >= 15) {
			if(!goalpointer->set) {
				goalpointer->set = 1;
				goalpointer->width = 4;
				goalpointer->height = 4;
				goalpointer-> row = GROUND + 4 + rand()%(HEIGHT-GROUND - 4 - goalpointer->height);
				if (flipped) {
					goalpointer->color = WHITEIDX;
				} else {
					goalpointer->color = BLACKIDX;
				}
				if (rand()%2) {
					//left
					goalpointer->col = 0;
					goalpointer->deltac = rand()%3 + 1;
				} else {
					//right
					goalpointer->col = 240 - goalpointer->width;	
					goalpointer->deltac = -1*(rand()%3 + 1);

				}
				goalpointer++;
				if(goalpointer == &goals[NUMGOALS]) {
					goalpointer = goals;
				}
			}
			goalcounter = 0;
		}
		//flip control
		if (KEY_DOWN_NOW(BUTTON_A) && !LAST_A) {
			if (flipped) {
				flipped = 0;
				mainChar.color = WHITEIDX;
				mainChar.deltar = -1*mainChar.deltar;
				orb.color = WHITEIDX;
			} else {
				flipped = 1;
				mainChar.color = BLACKIDX;
				mainChar.deltar = -1*mainChar.deltar;
				orb.color = BLACKIDX;
			}
			//for (int i = 0; i < NUMGOALS; i++) {
			//	goals[i].deltac = -1*goals[i].deltac;
			//}
		}
		if (KEY_DOWN_NOW(BUTTON_B) && !LAST_B) {
			if (splits != 0) {
				if (flipped) {
					flipped = 0;
					mainChar.color = WHITEIDX;
					//mainChar.deltar = -1*mainChar.deltar;
					orb.color = WHITEIDX;
				} else {
					flipped = 1;
					mainChar.color = BLACKIDX;
					//mainChar.deltar = -1*mainChar.deltar;
					orb.color = BLACKIDX;
				}
				for (int i = 0; i < NUMGOALS; i++) {
					goals[i].deltac = -1*goals[i].deltac;
				}
				splits--;
			}
		}
		//update objects
		for (int i = 0; i < NUMGOALS; i++) {
			if (goals[i].set) {
				updategoal(&goals[i]);
			}
		}
		//update mainchar
		if (updatemainchar(&mainChar, goals, &orb)) {
			return LOSE_SCENE;
		}
		//checkwinning condition
		if (score >= WINSCORE) {
			return WIN_SCENE;
		}
		//draw objects
		sprintf(scorebuffer, "ORBS LEFT: %i", WINSCORE - score);	
		if (splits) {
			sprintf(splitsbuffer, "SPLITS: %i", splits);
		} else {
			sprintf(splitsbuffer, "NO MORE SPLITS!");
		}
		if (flipped) {
			fillScreen4(WHITEIDX);
			//drawRect4(0, 0, 240, 10, BLACKIDX);
			//drawRect4(HEIGHT, 0, 240, 10, BLACKIDX);	
			drawImage4(0, 0, FLIPGAMEGROUNDBLACK_WIDTH, FLIPGAMEGROUNDBLACK_HEIGHT, FlipGameGroundBlack);
			drawImage4(HEIGHT, 0, FLIPGAMEGROUNDBLACK_WIDTH, FLIPGAMEGROUNDBLACK_HEIGHT, FlipGameGroundBlack);
			drawString4(1, 1, splitsbuffer, WHITEIDX);
			drawString4(HEIGHT + 1, 1, scorebuffer, WHITEIDX);
			drawImage4(orb.row, orb.col, orb.width, orb.height, blackorb_frames[(animationframecounter >> 3) % 8]);
		} else {
			fillScreen4(BLACKIDX);
			//drawRect4(0, 0, 240, 10, WHITEIDX);
			//drawRect4(HEIGHT, 0, 240, 10, WHITEIDX);	
			drawImage4(0, 0, FLIPGAMEGROUNDWHITE_WIDTH, FLIPGAMEGROUNDWHITE_HEIGHT, FlipGameGroundWhite);
			drawImage4(HEIGHT, 0, FLIPGAMEGROUNDWHITE_WIDTH, FLIPGAMEGROUNDWHITE_HEIGHT, FlipGameGroundWhite);
			drawString4(1, 1, splitsbuffer, BLACKIDX);
			drawString4(HEIGHT + 1, 1, scorebuffer, BLACKIDX);
			drawImage4(orb.row, orb.col, orb.width, orb.height, whiteorb_frames[(animationframecounter >> 3) % 8]);
		}
		for(int i = 0; i < NUMGOALS; i++) {
			u8 colorindex = WHITEIDX;
			if (flipped) {
				colorindex = BLACKIDX;
			}
			if (goals[i].set) {
				drawRect4(goals[i].row, goals[i].col, goals[i].width, goals[i].height, colorindex);
			}
		}
		drawRect4(mainChar.row, mainChar.col, mainChar.size, mainChar.size, mainChar.color);

		LAST_A = KEY_DOWN_NOW(BUTTON_A); 
		LAST_B = KEY_DOWN_NOW(BUTTON_B); 
		LAST_SELECT = KEY_DOWN_NOW(BUTTON_SELECT); 
		LAST_START = KEY_DOWN_NOW(BUTTON_START);
		//LAST_RIGHT = KEY_DOWN_NOW(BUTTON_RIGHT);
		//LAST_LEFT = KEY_DOWN_NOW(BUTTON_LEFT);
		//LAST_UP = KEY_DOWN_NOW(BUTTON_UP);
		//LAST_DOWN = KEY_DOWN_NOW(BUTTON_DOWN);
		//LAST_R = KEY_DOWN_NOW(BUTTON_R);
		//LAST_L = KEY_DOWN_NOW(BUTTON_L);
        waitForVblank();
        flip();

	}
}

int start() {
	fillScreen4(BLACKIDX);
	loadpalette(STARTSCENE_PALETTE_OFFSET, STARTSCENE_PALETTE_SIZE, startscene_palette);
	drawImage4(0, 0, FLIPPEDSTARTSCENE_WIDTH, FLIPPEDSTARTSCENE_HEIGHT, flippedstartscene);
	flip();
	loadpalette(STARTSCENE_PALETTE_OFFSET, STARTSCENE_PALETTE_SIZE, startscene_palette);
	drawImage4(0, 0, FLIPPEDSTARTSCENE_WIDTH, FLIPPEDSTARTSCENE_HEIGHT, flippedstartscene);
	flip();
	while(!KEY_DOWN_NOW(BUTTON_START));
	return MAIN_SCENE;// user presses start
}

int win() {
	loadpalette(WINSCENE_PALETTE_OFFSET, WINSCENE_PALETTE_SIZE, winscene_palette );
	drawImage4(0, 0, FLIPPEDWINSCENE_WIDTH, FLIPPEDSTARTSCENE_HEIGHT ,flippedwinscene);
	flip();
	while(!KEY_DOWN_NOW(BUTTON_START) && !KEY_DOWN_NOW(BUTTON_SELECT)) {
		if (KEY_DOWN_NOW(BUTTON_START)) {
			return MAIN_SCENE;
		}
	}
	return START_SCENE;
}

int lose() {
	loadpalette(LOSESCENE_PALETTE_OFFSET, LOSESCENE_PALETTE_SIZE, losescene_palette);
	drawImage4(0, 0, FLIPPEDLOSESCENE_WIDTH, FLIPPEDLOSESCENE_HEIGHT, flippedlosescene);
	flip();
	while(!KEY_DOWN_NOW(BUTTON_START) && !KEY_DOWN_NOW(BUTTON_SELECT)) {
		if (KEY_DOWN_NOW(BUTTON_START)) {
			return MAIN_SCENE;
		}
	}
	return START_SCENE;
}

int updatemainchar(MAINCHAR* mainChar, GOAL* goals, ORB* orb) {
	//check orb collision
	if (mainChar->row + mainChar->size > orb->row && mainChar->row < orb->row) {
		score++;
		orb->row = GROUND + 2;
	}
	if (mainChar->row < orb->row + orb->height && mainChar->row + mainChar->size > orb->row + orb->height) {
		score++;
		splits++;
		orb->row = HEIGHT - orb->height - 2;
	}
	//check goal collision
	GOAL* cur;
	for (int i = 0; i < NUMGOALS; i++) {
		cur = goals + i;
		if (((mainChar->col + mainChar->size) > cur->col && (mainChar->row + mainChar->size) > cur->row && mainChar->col < cur->col && mainChar->row < cur->row)
				|| ((mainChar->col + mainChar->size) > cur-> col && mainChar->row < (cur->row + cur->height) && mainChar->col < cur->col && (mainChar->row + mainChar->size) > (cur->row + cur->height))
				|| (mainChar->col < (cur->col + cur->width) && (mainChar->row + mainChar->size) > cur->row && (mainChar->col + mainChar->size) > (cur->col + cur->width) && mainChar->row < cur->row)
				|| (mainChar->col < (cur->col + cur->width) && mainChar->row < (cur->row + cur->height)&& (mainChar->col + mainChar->size) > (cur->col + cur->width) && (mainChar->row + mainChar->size) > (cur->row + cur->height))
				|| (mainChar->col < cur->col && (mainChar->col+ mainChar->size) > cur->col + cur->width && (((mainChar->row + mainChar->size) > cur->row && mainChar->row < cur->row) || (mainChar->row < (cur->row + cur-> height) && (mainChar->row + mainChar->size) > (cur->row + cur->height))))
				|| (((mainChar->col + mainChar->size >  cur->col && mainChar->col < cur->col) || (mainChar->col + mainChar->size > cur->col + cur->width && mainChar->col < cur->col + cur->width)) && mainChar->row < cur->row && mainChar->row + mainChar->size > cur->row + cur->height)) {
			return 1;
		}
	}

	//update char
	mainChar->row = mainChar->row + mainChar->deltar;
	mainChar->col = mainChar->col + mainChar->deltac;
	if (mainChar->row < GROUND) {
		mainChar->row = GROUND;
		mainChar->deltar = -1*mainChar->deltar;
	}
	if (mainChar->row > HEIGHT - mainChar->size + 1) {
		mainChar->row = HEIGHT - mainChar->size + 1;
		mainChar->deltar = -1*mainChar->deltar;
	}


	return 0;
}

void updategoal(GOAL* goal) {
	if (goal->col < 0 || goal->col > 240 - goal->width) {
		goal->set = 0;
	}
	goal->row = goal->row + goal->deltar;
	goal->col = goal->col + goal->deltac;
}

