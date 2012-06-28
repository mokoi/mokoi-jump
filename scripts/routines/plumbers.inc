/***********************************************
 * Copyright © Luke Salisbury
 *
 * You are free to share, to copy, distribute and transmit this work
 * You are free to adapt this work
 * Under the following conditions:
 *  You must attribute the work in the manner specified by the author or licensor (but not in any way that suggests that they endorse you or your use of the work). 
 *  You may not use this work for commercial purposes.
 * Full terms of use: http://creativecommons.org/licenses/by-nc/3.0/
 * Changes:
 *     2010/01/11 [luke]: new file.
 ***********************************************/

#define DEBUG 0
#define JUMP 1
#define SHOOT 2

stock Fixed:_x_, Fixed:_y_, Fixed:_z_;
stock dx, dy, dz;
stock dw = 16, dh = 16;
stock ox = 0, oy = 0;

stock UpdateDisplayPosition()
{
	dx = fround(_x_, round_unbiased);
	dy = fround(_y_, round_unbiased);
	dz = fround(_z_, round_unbiased);
}

#include <physics>