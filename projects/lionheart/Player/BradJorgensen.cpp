#include "BradJorgensen.hpp"
int side;
lionheart::Placement lionheart::BradJorgensen::placeUnit(UnitType,
	StartBox const &box,
	SituationReport report)
{
	/*Fill this out with instructions on how to place your initial units.  Without
	* changes your units will fill the starting box from top left to bottom right
	* in the order constructed.*/
	++side;
	bool westSide = (box.minCol < static_cast<int>(report.things[0].size() / 2));
	if (westSide)
	{
		switch (side)
		{
			// CROWN
		case 1: return{ 15, 2 };
				// KNIGHTS
		case 2: return{ 15,5 };
		case 3: return{ 19,4 };
		case 4: return{ 10,4 };
		case 5: return{ 11,4 };
		case 6: return{ 19,5 };
		case 7: return{ 19,3 };
				// ARCHERS
		case 8: return{ 17,3 };
		case 9: return{ 13,3 };
		case 10:return{ 16,5 };
		case 11:return{ 14,2 };
		case 12:return{ 10,7 };
		case 13:return{ 19,6 };
		case 14: return{ 19,7 };
		case 15: return{ 18,6 };
				 // INFANTRY
		case 16: return{ 12,2 };
		case 17: return{ 12,3 };
		case 18: return{ 12,4 };
		case 19: return{ 12,5 };
		case 20: return{ 18,2 };
		case 21: return{ 18,3 };
		case 22: return{ 18,4 };
		case 23: return{ 18,5 };

		case 24: return{14 ,5 };
		case 25: return{17 ,5 };
		case 26: return{13 ,5 };
		case 27: return{18 ,7 };
		case 28: return{17,6 };
		case 29: return{17 ,7 };
		case 30: return{16 ,6 };
		}
	}
	else
	{
		switch (side)
		{
			// CROWN
		case 1: return{ 15, 27 };
				// KNIGHTS
		case 2: return{ 10,25 };
		case 3: return{ 11,25 };
		case 4: return{ 15,24 };
		case 5: return{ 19,26 };
		case 6: return{ 19,24 };
		case 7: return{ 19,25 };
				// ARCHERS
		case 8: return{ 10,26 };
		case 9: return{ 10,24 };
		case 10:return{ 13,26 };
		case 11:return{ 17,26 };
		case 12:return{ 19,23 };
		case 13:return{ 16,27 };
		case 14: return{ 19,22 };
		case 15: return{ 14,24 };
				 // INFANTRY
		case 16: return{ 12,27 };
		case 17: return{ 12,26 };
		case 18: return{ 12,25 };
		case 19: return{ 12,24 };
		case 20: return{ 13,24 };
		case 21: return{ 16,24 };
		case 22: return{ 17,24 };
		case 23: return{ 18,24 };

		case 24: return{ 18,25 };
		case 25: return{ 18,26 };
		case 26: return{ 18,27 };
		case 27: return{ 16,23 };
		case 28: return{ 16,22 };
		case 29: return{ 13,23 };
		case 30: return{ 13,22 };
		}
	}
	return{ 0,0 };
}

lionheart::Action
lionheart::BradJorgensen::recommendAction(Unit const &u, SituationReport , Plan p)
{
	/*Fill this out with the behavior you want for your units.  Without changes
	* your units will just wait to be defeated.  Feel free to look at the other provided players for ideas on how to get certain behavior*/

	if (u.getType() == CROWN)
	{
		return p.moveToLocation(15, 2);
	}

	if (u.getType() == ARCHER)
	{
		 if (p.movesToAllyCrown() < 5)
		{
			return turn(Direction::EAST);
			if (p.movesToEnemy() < 4)
			{
				p.attackEnemy();
			}
		}
		 else if (p.movesToEnemy() < 4)
		 {
			 return p.attackEnemy();
		 }
		else if (p.movesToEnemyCrown() >= 4)
		{
			return p.moveToEnemyCrown();
		}
		else if (p.hasAttack())
		{
			return p.attackEnemy();
		}
	}

	if (u.getType() == KNIGHT)
	{
		return p.attackEnemy();
	}
	else if (p.movesToEnemyCrown() == 1)
	{
		return p.attackEnemy();
	}
	else if (p.movesToEnemyCrown() > 1)
	{
		return p.moveToEnemyCrown();
	}
	else if (p.hasAttack())
	{
		return p.attackEnemy();
	}




	if (u.getType() == INFANTRY)
	{
		return p.attackEnemy();
	}
	return p.moveToAllyCrown();
}

lionheart::Blazon lionheart::BradJorgensen::getBlazon()
{
	/*Return your blazon here.  In case of conflicts preference will be given to
	* the students that have registered their blazons in class.*/
	return{ Color::AZURE, Color::ARGENT, Style::CHEVERON, "Brad Jorgensen" };
}
