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
#include <plumbers>

new obj = -1;

public Init( ... )
{
	obj = EntityGetNumber("object-id");
	EntityGetPosition( _x_, _y_, _z_);
	_x_ += 8;
	_y_ += 16;
	UpdateDisplayPosition();

	PhysicsCheckpoints(16,32);
}

main()
{
	PhysicsMoveSideways( Fixed:(10*InputAxis(0)) );
	if ( InputAxis(1) < 0 )
	{
		PhysicsJump( 1.0 );
	}
	PhysicsGravity( 0.0, GameFrame2() );

	UpdateDisplayPosition();
	ObjectPosition(object:obj, dx-8 ,dy-16, 3, 16, 32);
}
