#include "Calvin_Makelky.hpp"
#include "Player.hpp"


lionheart::Placement lionheart::Calvin_Makelky::placeUnit(UnitType, StartBox const &box, SituationReport report)
{
	++id;
	westSide = (box.minCol < static_cast<int>(report.things[0].size() / 2));
	if (westSide)
	{
		switch (id)
		{
			// CROWN
		case 1: return{ 16, 2};
				// KNIGHTS
		case 2: return{ 15,3};
		case 3: return{ 17,3};
		case 4: return{ 16,3};
		case 5: return{ 14,3 };
		case 6: return{ 17,2 };
		case 7: return{ 15,2 };
				// ARCHERS
		case 8: return{ 12,4 };
		case 9: return{ 12,5 };
		case 10:return{ 12,7 };
		case 11:return{ 16, 4};
		case 12:return{ 15,4 };
		case 13:return{ 18, 6 };
		case 14: return{ 17, 3 };
		case 15: return{ 18,2 };
				 // INFANTRY
		case 16: return{ 10, 4 };
		case 17: return{ 11, 4 };
		case 18: return{ 15,5 };
		case 19: return{ 10,3};
		case 20: return{ 13,4 };
		case 21: return{ 14,4 };
		case 22: return{ 18,3 };
		case 23: return{ 19,4 };

		case 24: return{ 13,2 };
		case 25: return{ 13, 7 };
		case 26: return{ 13,3 };
		case 27: return{ 14,2 };
		case 28: return{ 18,4 };
		case 29: return{ 18,5 };
		case 30: id = 0; return{ 16,5 };
		}
	}
	else
	{
		switch (id)
		{
			// CROWN
		case 1: return{ 15, 27 };
				// KNIGHTS
		case 2: return{ 15,26 };
		case 3: return{ 14,27 };
		case 4: return{ 16,27};
		case 5: return{ 15,25 };
		case 6: return{ 13,27 };
		case 7: return{ 17,27 };
				// ARCHERS
		case 8: return{ 10,26 };
		case 9: return{ 10,24 };
		case 10:return{ 13,22 };
		case 11:return{ 14,24 };
		case 12:return{ 15,24 };
		case 13:return{ 16,22 };
		case 14: return{ 19,26 };
		case 15: return{ 19,24 };
				 // INFANTRY
		case 16: return{ 19,25 };
		case 17: return{ 18,25 };
		case 18: return{ 17,25 };
		case 19: return{ 11,25 };
		case 20: return{ 10,25 };
		case 21: return{ 14,25 };
		case 22: return{ 13,25 };
		case 23: return{ 12,25 };

		case 24: return{ 11,27 };
		case 25: return{ 16,26 };
		case 26: return{ 16,23 };
		case 27: return{ 13,26 };
		case 28: return{ 15,28 };
		case 29: return{ 13,24 };
		case 30:id = 0; return{ 16, 24 };
		}
	}
	return{ 0,0 };
}
	

	lionheart::Action
		lionheart::Calvin_Makelky::recommendAction(Unit const &u, SituationReport s, Plan p)
	{
		{
			if (u.getType() == CROWN) {
				if (s.turns > 68)
					return p.moveToLocation(29, 0);
				else
				{
					return wait();
				}
			}
		}
		if (u.getType() == INFANTRY)
		{
			if (s.turns < 40)
				if (p.hasAttack())
				{
					return p.attackEnemy();
				}
				else {
					return wait();
				}
			else {
				if (p.hasAttack())
				{
					return p.attackEnemy();
				}
				return p.moveToEnemyCrown();
			}
		}
	    if (u.getType() == ARCHER)
      {
			if (s.turns < 40)
				if (p.hasAttack())
				{
					return p.attackEnemy();
				}
				else {
					return wait();
				}
			else {
				if (p.hasAttack())
				{
					return p.attackEnemy();
				}
				else {
					return p.moveToEnemyCrown();
				}
			}
      }
		if (u.getType() == KNIGHT)
		{
			if (s.turns < 65)
				if (p.hasAttack())
				{
					return p.attackEnemy();
				}
				else {
					return wait();
				}
			else {
				if (p.hasAttack())
				{
					return p.attackEnemy();
				}
				return p.moveToEnemyCrown();
			}
			return p.attackEnemy();
		}
	return Action();
}

lionheart::Blazon lionheart::Calvin_Makelky::getBlazon()
{
  return { Color::AZURE, Color::GULES, Style::QUARTERLY, "Calvin Makelky" };
}
