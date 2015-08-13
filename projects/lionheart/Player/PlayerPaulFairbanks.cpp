#include "PlayerPaulFairbanks.hpp"

lionheart::Placement lionheart::PlayerPaulFairbanks::placeUnit(UnitType, StartBox const &box, SituationReport report)
{
  /*Fill this out with instructions on how to place your initial units.  Without
   * changes your units will fill the starting box from top left to bottom right
   * in the order constructed.*/
	//sbox = box;

	++id;
	westSide = (box.minCol < static_cast<int>(report.things[0].size() / 2));
	if (westSide)
	{
		switch (id)
		{
			// CROWN
		case 1: return{ 13, 2 };
				// KNIGHTS
		case 2: return{ 10, 4 };
		case 3: return{ 10, 3 };
		case 4: return{ 12, 4 };
		case 5: return{ 17, 4 };
		case 6:;return{ 19, 4 };
		case 7:;return{ 14, 2 };
				// ARCHERS
		case 8: return{ 11, 4 };
		case 9: return{ 13, 4 };
		case 10:return{ 14, 4 };
		case 11:return{ 15, 4 };
		case 12:return{ 16, 4 };
		case 13:return{ 18, 4 };
		case 14: return{ 14, 5 };
		case 15: {id = 0; return{ 15, 5 }; }
				 
				 // INFANTRY
/*		case 16: return{ 14, 7 };
		case 17: { return{ 15, 7 }; }
		case 18: return{ 15, 6 };
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
		case 30: return{ 16, 5 };
	*/	}
	}
	else
	{
		switch (id)
		{
			// CROWN
		case 1: return{ 13, 27 };
				// KNIGHTS
		case 2: return{ 10, 25 };
		case 3: return{ 10, 26 };
		case 4: return{ 11, 25 };
		case 5: return{ 18, 25 };
		case 6: return{ 19, 26 };
		case 7: return{ 19, 25 };
				// ARCHERS
		case 8: return{ 12, 25 };
		case 9: return{ 13, 25 };
		case 10:return{ 14, 25 };
		case 11:return{ 15, 25 };
		case 12:return{ 16, 25 };
		case 13:return{ 17, 25 };
		case 14: return{ 14, 24 };
		case 15: {id = 0; return{ 15, 24 }; }
				 // INFANTRY
	/*	case 16: return{ 15, 22 };
		case 17: { return{ 14, 22 }; }
		case 18: return{ 15, 23 };
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
		case 30: return{ 16, 24 };
		*/}
	}
  return { 0, 0 };
}

  lionheart::Action
lionheart::PlayerPaulFairbanks::recommendAction(Unit const & u, SituationReport , Plan p)
{
  /*Fill this out with the behavior you want for your units.  Without changes
   * your units will just wait to be defeated.  Feel free to look at the other provided players for ideas on how to get certain behavior*/
  //return Action();

	{
		if (u.getType() == CROWN) 
		{
			if ((p.movesToEnemy() < 5))
			{
				return p.moveToEnemy();
			}

			else if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			else
			{
				return p.moveToLocation(14, 0);
			}
		}
		if (u.getType() == KNIGHT)
		{
			if (p.movesToEnemy() < 4)
			{
				return p.moveToEnemy();
			}
			else if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			return p.moveToEnemyCrown();
		}
		if (u.getType() == ARCHER)
		{
			if ((p.movesToEnemy() < 10)&&(p.movesToEnemy()>6))
			{
				return p.moveToEnemy();
			}
			else if ((p.movesToEnemy() < 8) || (p.hasAttack()))
			{
				return p.attackEnemy();
			}
			//else
			//{
			//	return p.moveToEnemyCrown();
		//	}
			/*for (int r = sbox.minRow; r < sbox.maxRow; ++r)
			{
				for (int c = sbox.minCol; c < sbox.maxCol; ++c)
				{
					for (int z = -7; z < 9; ++z)
					{
					if (r = (r + z)	)	
					{
						
						return{ r, c };
					}
				}
			}*/
		}

		return p.attackEnemy();
	}
}

lionheart::Blazon lionheart::PlayerPaulFairbanks::getBlazon()
{
  /*Return your blazon here.  In case of conflicts preference will be given to
   * the students that have registered their blazons in class.*/
  return { Color::ARGENT, Color::AZURE, Style::PALE, "Bull with Horns" };
}



//report.things[row][col].type{space,rocks,enemy,ally}  or  .unitType{None, Crown, Knight, Archer, Infantry}   or   . hp{0-4}   or   .facing{N,S,E,W}
//p.fool()   or   attack(location)   or   move(dist)   or turn(direction)   or wait()


//turn by turn change swiss/gauntlet by changing game.doturn(display) to game.doturn(nullptr) 
