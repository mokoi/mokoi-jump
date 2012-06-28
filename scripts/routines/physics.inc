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

stock operator%(Fixed:oper1, Fixed:oper2)
	return fround(oper1*1000)%fround(oper2*1000);

enum {
	NORMAL,
	FALLING,
	JUMPING
}

enum point {
	X,
	Y,
	MASK,
	Fixed:ANGLE
}

new Fixed:_velocity_[2] = {0.0,0.0};
new Fixed:_acceleration_[2] = {5.0, 9.8};
new Fixed:gravity_y = 5.00;
new object_state = 0;

new foot[5][point];

stock Fixed:Dir2Angle(d, offset = 0)
{
	d %= 8;
	return fixed(d*45);
}

stock Angle2Dir(Fixed:a, Fixed:offset = 0.0)
{
	a += offset;
	return (fround(a)%360) / 45;
}

stock PhysicsMoveSideways(Fixed:speed)
{
	_velocity_[0] = speed * _acceleration_[0];
}

stock PhysicsJump(Fixed:speed)
{
	if (!speed)
	{
		object_state = 1;
		return;
	}
	if (0 >= _velocity_[1] > -100 && object_state != 1 )
	{
		_velocity_[1] -= speed * _acceleration_[1];
		object_state = 2;
	}
}

stock PhysicsCheckpoints(width, height)
{
	dw = width;
	dh = height;
}

stock PhysicsCalculateFalling(qx, qy, minmask = 0)
{
	if ( object_state == JUMPING)
	{
		return;
	}
	if ( MaskGetValue( qx, qy+1 ) <= minmask)
	{
		_velocity_[1] += _acceleration_[1] * GameFrame2();
		object_state = 1;
	}
	else
	{
		_velocity_[1] = 0;
		object_state = 0;
	}
}

stock PhysicsCalculateHLine(qx, qy, dir = 0)
{
	new c = 0
	for (new n = 0; n < 3; n++ )
	{
		foot[n][X] = qx + (n*8);
		foot[n][Y] = qy;
		foot[n][MASK] = MaskGetValue( foot[n][X], foot[n][Y] );
		c = 0;
		/*
		if ( foot[n][MASK] )
		{
			while ( c < 8 )
			{
				foot[n][Y]--;
				foot[n][MASK] = MaskGetValue( foot[n][X], foot[n][Y] );
				
				c++;
			}
		}*/
		foot[n][ANGLE] = 0;
		if (n > 0)
		{
			//GraphicsDraw( "", LINE, foot[n-1][X], foot[n-1][Y], 4, foot[n][X], foot[n][Y], (foot[n][MASK] ? 0x00FFFFAA : 0x000000AA) );
			foot[n][ANGLE] = fatan2(foot[n-1][Y] - foot[n][Y], foot[n-1][X] - foot[n][X], degrees);
		}
		//GraphicsDraw( "", RECTANGLE, foot[n][X]-2, foot[n][Y]-2, 4, 4, 4, 0xFF00FFAA );
	}
	if ( foot[0][MASK] && foot[2][MASK] && foot[1][MASK] )
		return true;
	return false;
}

stock PhysicsGravity( Fixed:angle, Fixed:_speed_ )
{
	PhysicsCalculateFalling( dx-8, dy + (dh/2));

	new Fixed:speed_x = _speed_ * _velocity_[0];
	new Fixed:speed_y = _speed_ * _velocity_[1];
	new results = 0;
	if (speed_y > 1.0)
	{
		while ( speed_y > 1.0 )
		{
			PhysicsGravityCode(angle, speed_x, 1.0);
			speed_y -= 1.0;
		}
	}
	PhysicsGravityCode(angle,speed_x,speed_y);
	
	return results;
}

stock PhysicsGravityCode( Fixed:angle, Fixed:speed_x, Fixed:speed_y )
{
	new Fixed:movement_x = 0.00;
	new Fixed:movement_y = 0.00;
	movement_x = speed_x;
	movement_y = speed_y;

	PhysicsCalculateHLine( dx-8, dy + (dh/2) )

	_x_ += movement_x;
	if ( (!foot[0][MASK] && !foot[1][MASK] && !foot[2][MASK]) || object_state == JUMPING )
	{
		_y_ += movement_y;
	}
	UpdateDisplayPosition();
	for (new n = 0; n < 5; n++ )
		DebugText("%d: angle %d, mask: %d", n, foot[n][ANGLE], foot[n][MASK]);
}
