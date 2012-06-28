#include <default> 
#include <graphics> 
#include <entities> 
#include <string> 
 
new player = 0; 
new object:obj1 = -1; 
new object:obj2 = -1; 
new object:obj3 = -1; 
new x = 10, y = 10; 
 
main() 
{ 
	new xaxis = 255; 
	new yaxis = -255; 
	new zaxis = 128; 

	xaxis = InputAxis(0, player)/8;
	yaxis = InputAxis(1, player)/8;
	zaxis = InputAxis(2, player)/8;

	DebugText("%d %d %d", obj1, obj2, obj3);

	if ( xaxis > 0 )
		ObjectPosition(obj1, x, y-5, 3, xaxis, 10); 
	else if ( xaxis < 0 )
		ObjectPosition(obj1, x+xaxis, y-5, 3, 0-xaxis, 10); 
	else
		ObjectPosition(obj1, x-1, y-5, 3, 1, 10); 

	if ( yaxis > 0 )
		ObjectPosition(obj2, x-5, y, 3, 10, yaxis); 
	else if ( yaxis < 0 )
		ObjectPosition(obj2, x-5, y+yaxis, 3, 10, 0-yaxis); 
	else 
		ObjectPosition(obj2, x-5, y-1, 3, 10, 1);

	if ( zaxis > 0 )
		ObjectPosition(obj3, x+44, y, 3, 10, zaxis); 
	else if ( zaxis < 0 )
		ObjectPosition(obj3, x+44, y+zaxis, 3, 10, 0-zaxis); 
	else 
		ObjectPosition(obj3, x+44, y-1, 3, 10, 1); 


	new str[128];
	strformat(str, _,_, "Position %d %d", InputPointer(0, player), InputPointer(1, player) );
	GraphicsDraw(str, TEXT, x+80, y-32, 3, 10, 1); 

} 
 
public Init(...) 
{ 
	new Fixed:fx, Fixed:fy, Fixed:fz;
	EntityGetPosition(fx, fy,fz);
	x = fround(fx)+32;
	y = fround(fy)+32;
 
	player =  EntityGetNumber("player");

	obj1 = ObjectCreate("", RECTANGLE, 11, 10, 5, 16, 64, 0xFF0000FF);
	obj2 = ObjectCreate("", RECTANGLE, 100, 100, 5, 64, 16, 0xFF0000FF);
	obj3 = ObjectCreate("", RECTANGLE, 100, 10, 5, 64, 16, 0xFF0000FF);

} 
 
public Close() 
{ 
	ObjectDelete(obj1); 
	ObjectDelete(obj2); 
	ObjectDelete(obj3); 
} 
