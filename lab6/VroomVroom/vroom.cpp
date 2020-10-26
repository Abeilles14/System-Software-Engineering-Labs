#include<iostream>
#include "../../graphics.h"
#include "../../winbgim.h"
#include <dos.h> 
#include <stdio.h> 

int main()
{
	int gd = DETECT, gm;

	initgraph(&gd, &gm, NULL);


	line(0, 300, 640, 300);

	setcolor(4);


	circle(100, 285, 15);
	circle(200, 285, 15);
	circle(100, 285, 5);
	circle(200, 285, 5);

	line(65, 285, 85, 285);
	line(115, 285, 185, 285);
	line(215, 285, 235, 285);
	line(65, 285, 65, 260);
	line(235, 285, 235, 260);

	line(65, 260, 100, 255);
	line(235, 260, 200, 255);

	line(100, 255, 115, 235);
	line(200, 255, 185, 235);

	line(115, 235, 185, 235);


	line(106, 255, 118, 238);
	line(118, 238, 118, 255);
	line(106, 255, 118, 255);

	line(194, 255, 182, 238);
	line(182, 238, 182, 255);
	line(194, 255, 182, 255);

	line(121, 238, 121, 255);
	line(121, 238, 148, 238);
	line(121, 255, 148, 255);
	line(148, 255, 148, 238);


	line(179, 238, 179, 255);
	line(179, 238, 152, 238);
	line(179, 255, 152, 255);
	line(152, 255, 152, 238);
	setcolor(4);
	//floodfill(150,200,4);

	getch();
	closegraph();
}