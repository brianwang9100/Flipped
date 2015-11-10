#include "mylib.h"
#include "grounds.h"
#include "whiteorbs.h"
#include "blackorbs.h"
#include "losescene.h"
#include "winscene.h"
#include "startscene.h"
extern u16 *videoBuffer;

typedef struct {
	int row;
	int col;
	int deltar;
	int deltac;
	int size;
	u16 color;
} MAINCHAR;

typedef struct {
	int set;
	int row;
	int col;
	int deltar;
	int deltac;
	int width;
	int height;
	u16 color;
} ORB;

typedef struct {
	int set;
	int row;
	int col;
	int deltar;
	int deltac;
	int accelr;
	int accelc;
	int width;
	int height;
	u16 color;
} GOAL;

enum GBAState {
	START_SCENE,
	MAIN_SCENE,
	WIN_SCENE,
	LOSE_SCENE,
};

int main(void);
int start();
int game();
int win();
int lose();
int updatemainchar(MAINCHAR* mainChar, GOAL* goals, ORB* orb);
void updategoal(GOAL* goal);
