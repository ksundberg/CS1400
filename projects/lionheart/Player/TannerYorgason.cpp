#include "TannerYorgason.hpp"

lionheart::Placement lionheart::TannerYorgason::placeUnit(UnitType,
	StartBox const &box,
	SituationReport report)
{
	++id;
	westSide = (box.minCol < static_cast<int>(report.things[0].size() / 2));
	if (westSide)
	{
		switch (id)
		{
			// CROWN
		case 1: return{ 15, 2 };
				// KNIGHTS
		case 2: return{ 10, 4 };
		case 3: return{ 11, 4 };
		case 4: return{ 12, 4 };
		case 5: return{ 17, 4 };
		case 6: return{ 18, 4 };
		case 7: return{ 19, 4 };
				// ARCHERS
		case 8: return{ 10, 3 };
		case 9: return{ 10, 5 };
		case 10:return{ 14, 6 };
		case 11:return{ 14, 5 };
		case 12:return{ 15, 5 };
		case 13:return{ 15, 6 };
		case 14: return{ 19, 3 };
		case 15: return{ 19, 5 };
				 // INFANTRY
		case 16: return{ 13, 7 };
		case 17: return{ 14, 7 };
		case 18: return{ 16, 7 };
		case 19: return{ 15, 7 };
		case 20: return{ 13, 4 };
		case 21: return{ 14, 4 };
		case 22: return{ 15, 4 };
		case 23: return{ 16, 4 };

		case 24: return{ 14, 2 };
		case 25: return{ 15, 3 };
		case 26: return{ 14, 3 };
		case 27: return{ 13, 3 };
		case 28: return{ 16, 3 };
		case 29: return{ 13, 5 };
		case 30: id = 0; return{ 16, 2 };
		}
	}
	else
	{
		switch (id)
		{
			// CROWN
		case 1: return{ 15, 27 };
				// KNIGHTS
		case 2: return{ 10, 25 };
		case 3: return{ 11, 25 };
		case 4: return{ 12, 25 };
		case 5: return{ 17, 25 };
		case 6: return{ 18, 25 };
		case 7: return{ 19, 25 };
				// ARCHERS
		case 8: return{ 10, 26 };
		case 9: return{ 10, 24 };
		case 10:return{ 14, 23 };
		case 11:return{ 14, 24 };
		case 12:return{ 15, 24 };
		case 13:return{ 15, 23 };
		case 14: return{ 19, 26 };
		case 15: return{ 19, 24 };
				 // INFANTRY
		case 16: return{ 13, 22 };
		case 17: return{ 14, 22 };
		case 18: return{ 16, 22 };
		case 19: return{ 15, 22 };
		case 20: return{ 13, 25 };
		case 21: return{ 14, 25 };
		case 22: return{ 15, 25 };
		case 23: return{ 16, 25 };

		case 24: return{ 14, 27 };
		case 25: return{ 15, 26 };
		case 26: return{ 14, 26 };
		case 27: return{ 13, 26 };
		case 28: return{ 16, 26 };
		case 29: return{ 13, 24 };
		case 30: id = 0; return{ 16, 27 };
		}
	}
	return{ 0, 0 };
}

lionheart::Action
lionheart::TannerYorgason::recommendAction(Unit const & u, SituationReport s, Plan p)
{
	if (p.hasAttack())
		return p.attackEnemy();
	else
	{
		switch (u.getId())
		{
		case 0:
			return wait();
		case 3:
			if (s.turns > 50)
				return p.moveToEnemyCrown();
			else
				return turn(Direction::NORTH);
		case 1:
		case 2:
			if (s.turns > 50)
				return p.moveToEnemyCrown();
			else
				return turn(Direction::NORTH);
		case 4:
			if (s.turns > 50)
				return p.moveToEnemyCrown();
			else
				return turn(Direction::SOUTH);
		case 5:
		case 6:
			if (s.turns > 50)
				return p.moveToEnemyCrown();
			else
				return turn(Direction::SOUTH);
		case 7:
		case 8:
			if (s.turns > 100)
				return p.moveToEnemyCrown();
			else
				return turn(Direction::NORTH);
		case 9:
		case 12:
		case 10:
		case 11:
			if (s.turns > 100)
				return p.moveToEnemyCrown();
			else
				return wait();
			//if (u.getLocation().col == 5) return move(1);
			//if (u.getLocation().col == 24) return move(1);
		case 13:
		case 14:
			if (s.turns > 100)
				return p.moveToEnemyCrown();
			else
				return turn(Direction::SOUTH);
		case 28:
		case 19:
		case 26:
			return turn(Direction::NORTH);
		case 22:
		case 27:
		case 29:
			return turn(Direction::SOUTH);
		case 15:
		case 16:
		case 17:
		case 18:
			return p.moveToEnemyCrown();
		case 20:
		case 21:
		case 23:
		case 24:
		case 25:
			if (s.turns > 100)
				return p.moveToEnemyCrown();
			else
				return wait();
		default:
			break;
		}
		if (s.turns > 75)
			return p.moveToEnemyCrown();
		else
			return wait();
	}
}


lionheart::Blazon lionheart::TannerYorgason::getBlazon()
{
	return{ Color::VERT, Color::OR, Style::SALTIRE, "Trogdor the Burninator" };
}

//maybe something like while has attack == false, turn until has attack, then attack...
//use unittype to find out what the thing is, use facing to find out what direction it is facing, 

/*if (id == 28 || id == 19 || id == 26)
return turn(Direction::NORTH);
if (id == 22 || id == 27 || id == 29)
return turn(Direction::SOUTH);
if (id == 15 || id == 16 || id == 17 || id == 18)
return p.moveToEnemyCrown();
if (id == 20 || id == 21 || id == 23 || id == 24 || id == 25)
{
if (s.turns > 100)
return p.moveToEnemyCrown();
else
return wait();
}*/

/*if (id == 43 || id == 34 || id == 41)
{
if (s.turns > 5)
return p.moveToEnemyCrown();
else
return wait();
}
if (id == 37 || id == 42 || id == 44)
{
if (s.turns > 10)
return p.moveToEnemyCrown();
else
return wait();
}
if (id == 30 || id == 31 || id == 32 || id == 33)
{
if (s.turns > 15)
return p.moveToEnemyCrown();
else
return wait();
}
if (id == 35 || id == 36 || id == 38 || id == 39 || id == 40)
{
if (s.turns > 25)
return p.moveToEnemyCrown();
else
return wait();
}*/
