#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <time.h>
#include "eng.h"
#include <stdbool.h>
#include <conio.h>
#include <string.h>




int main(int argc, char** argv)
{
	SystemInitialise("text.txt", argc, argv);
	SystemRelease();
	
	return 0;
}