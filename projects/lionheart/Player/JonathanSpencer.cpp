#include "JonathanSpencer.hpp"
namespace {
int id;
}
static bool westSide;

lionheart::Placement lionheart::JonathanSpencer::placeUnit(UnitType,StartBox const &box,SituationReport report)
{
  /*Fill this out with instructions on how to place your initial units.  Without
   * changes your units will fill the starting box from top left to bottom right
   * in the order constructed.*/
	
	++id;
	if (id > 30) 
		id = 1;
	
	westSide = (box.minCol < static_cast<int>(report.things[0].size() / 2));
	if (westSide)
	{
		switch (id)
		{
			// CROWN
		case 1: return{ 19, 4 };

				// KNIGHTS
		case 2: return{ 10,4 };
		case 3: return{ 19,5 };
		case 4: return{ 18,3 };
		case 5: return{ 17,3 };

		case 6: return{ 14,6 };
		case 7: return{ 15,6 };

				// ARCHERS
		case 8: return{ 18,4 };
		case 9: return{ 17,2 };
		case 10:return{ 18,2 };

		case 11:return{ 16,7 };
		case 12:return{ 15,7 };
		case 13:return{ 14,7 };
		case 14:return{ 10,3 };

		case 15:return{ 19,3 };

				 // INFANTRY
		case 16: return{ 19,2 };
		case 17: return{ 18,5 };
		case 18: return{ 17,5 };
		case 19: return{ 17,4 };

		case 20: return{ 16,5 };
		case 21: return{ 15,5 };
		case 22: return{ 14,5 };
		case 23: return{ 16,6 };
		case 24: return{ 13,6 };

		case 25: return{ 12,4 };
		case 26: return{ 11,3 };
		case 27: return{ 13,7 };
		case 28: return{ 11,4 };
		case 29: return{ 11,5 };
		case 30: return{ 10,5 };
		}
	}
	else
	{
		switch (id)
		{
			// CROWN
		case 1: return{ 19,25 };

				// KNIGHTS
		case 2: return{ 10,25 };

		case 3: return{ 19,24 };
		case 4: return{ 18,26 };
		case 5: return{ 17,26 };

		case 6: return{ 14,23 };
		case 7: return{ 15,23 };

				// ARCHERS
		case 8: return{ 18,25 };
		case 9: return{ 17,27 };
		case 10:return{ 18,27 };

		case 11:return{ 16,22 };
		case 12:return{ 15,22 };
		case 13:return{ 14,22 };
		case 14:return{ 10,26 };

		case 15:return{ 19,26 };

				 // INFANTRY
		case 16: return{ 19,27 };
		case 17: return{ 18,24 };
		case 18: return{ 17,24 };
		case 19: return{ 17,25 };

		case 20: return{ 16,24 };
		case 21: return{ 15,24 };
		case 22: return{ 14,24 };
		case 23: return{ 16,23 };
		case 24: return{ 13,23 };

		case 25: return{ 12,25 };
		case 26: return{ 11,26 };
		case 27: return{ 13,22 };
		case 28: return{ 11,25 };
		case 29: return{ 11,24 };
		case 30: return{ 10,24 };
		}
	}

	return { 0, 0 };
	id = 0;
}


  lionheart::Action
lionheart::JonathanSpencer::recommendAction(Unit const & u, SituationReport report, Plan p)
{
  /*Fill this out with the behavior you want for your units.  Without changes
   * your units will just wait to be defeated.  Feel free to look at the other provided players for ideas on how to get certain behavior*/
	
	
	if (westSide)
	{
		switch (u.getId())
		{
			//Crown Group	
		case 0: 
			{ 
				return p.moveToLocation(18, 0);
			}
			break;
		case 1:
			if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			if (p.movesToEnemy() < 2)
			{
				return p.attackEnemy();
			}
			else
			{
				return p.moveToLocation(17, 0);
			}
			break;
			
		case 2:
			//if (u.getLocation().row == 19)
			//{
			//	return p.moveToLocation(19, 0);
			//}
			if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			if (p.movesToEnemy() < 2)
			{
				return p.attackEnemy();
			}
			else
			{
				return p.moveToLocation(19, 0);
			}
			break;

		case 3: case 4:
			if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			if (p.movesToEnemy() < 2)
			{
				return p.attackEnemy();
			}
			else
			{
				return wait();
			}
			break;
		
		case 7:
			if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			if (p.movesToEnemy() < 3)
			{
				return p.attackEnemy();
			}
			if (report.turns < 10)
			{
				return wait();
			}
			else
			{
				return p.moveToLocation(20, 0);
			}
			break;
			
		case 14:
			if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			if (p.movesToEnemy() < 3)
			{
				return p.attackEnemy();
			}
			if (report.turns < 20)
			{
				return wait();
			}
			else
			{
				return p.moveToLocation(21, 0);
			}
			break;
			

		case 8:case 9:
			if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			if (p.movesToEnemy() < 3)
			{
				return p.attackEnemy();
			}
			else
			{
				return wait();
			}
			break;
			

		case 31: case 32: case 33:
			if (p.movesToEnemy() < 3)
			{
				return p.attackEnemy();
			}
			if (report.turns < 120)
			{
				return wait();
			}
			else
			{
				return p.moveToEnemyCrown();
			}
			break;

		case 30:
			if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			if (report.turns < 40)
			{
				return wait();
			}
			else
			{
				return p.moveToAllyCrown();
			}
			break;
			

			//Attack Group 1 
		case 5:case 6:
			if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			if (report.turns < 40)
			{
				return wait();
			}
			else
			{
				return p.moveToEnemyCrown();
			}
			break;
			

		case 34:case 35:case 36:case 37:case 38:case 41:
			if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			if (report.turns < 50)
			{
				return wait();
			}
			else
			{
				return p.moveToEnemyCrown();
			}
			break;


			//Attack  Group 1 Archerys
		case 10:case 11:case 12:
			if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			if (report.turns <= 40)
			{
				return wait();
			}
			else
			{
				return p.moveToEnemyCrown();
			}
			break;
			

			// Attack Group 2
		case 39:case 42:case 43:case 44:
			if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			if (report.turns < 50)
			{
				return p.moveToEnemyCrown();
			}
			if (report.turns > 180)
			{
				return p.moveToAllyCrown();
			}
			else
			{
				return p.moveToEnemyCrown();
			}
			break;

		case 40:
			if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			if (p.movesToEnemy() < 2)
			{
				return p.attackEnemy();
			}
			else
			{
				return p.moveToLocation(15, 0);
			}
			break;

		case 13:
			if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			if (p.movesToEnemy() < 3)
			{
				return p.attackEnemy();
			}
			else
			{
				return p.moveToLocation(16, 0);
			}
			break;
		}
	}
	else
	{
		switch (u.getId())
		{
			//Crown Group	
		case 0:
		{
			return p.moveToLocation(18, 29);
		}
		break;
		case 1:
			if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			if (p.movesToEnemy() < 2)
			{
				return p.attackEnemy();
			}
			else
			{
				return p.moveToLocation(17, 29);
			}
			break;

		case 2:
			//if (u.getLocation().row == 19)
			//{
			//	return p.moveToLocation(19, 0);
			//}
			if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			if (p.movesToEnemy() < 2)
			{
				return p.attackEnemy();
			}
			else
			{
				return p.moveToLocation(19, 29);
			}
			break;

		case 3: case 4:
			if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			if (p.movesToEnemy() < 2)
			{
				return p.attackEnemy();
			}
			else
			{
				return wait();
			}
			break;

		case 7:
			if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			if (p.movesToEnemy() < 3)
			{
				return p.attackEnemy();
			}
			if (report.turns < 10)
			{
				return wait();
			}
			else
			{
				return p.moveToLocation(20, 29);
			}
			break;

		case 14:
			if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			if (p.movesToEnemy() < 3)
			{
				return p.attackEnemy();
			}
			if (report.turns < 20)
			{
				return wait();
			}
			else
			{
				return p.moveToLocation(21, 30);
			}
			break;


		case 8:case 9:
			if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			if (p.movesToEnemy() < 3)
			{
				return p.attackEnemy();
			}
			else
			{
				return wait();
			}
			break;


		case 31: case 32: case 33:
			if (p.movesToEnemy() < 3)
			{
				return p.attackEnemy();
			}
			if (report.turns < 120)
			{
				return wait();
			}
			else
			{
				return p.moveToEnemyCrown();
			}
			break;

		case 30:
			if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			if (report.turns < 40)
			{
				return wait();
			}
			else
			{
				return p.moveToAllyCrown();
			}
			break;


			//Attack Group 1 
		case 5:case 6:
			if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			if (report.turns < 40)
			{
				return wait();
			}
			else
			{
				return p.moveToEnemyCrown();
			}
			break;

		case 34:case 35:case 36:case 37:case 38:case 41:
			if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			if (report.turns < 40)
			{
				return wait();
			}
			else
			{
				return p.moveToEnemyCrown();
			}
			break;


			//Attack  Group 1 Archerys
		case 10:case 11:case 12:
			if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			if (report.turns <= 40)
			{
				return wait();
			}
			else
			{
				return p.moveToEnemyCrown();
			}
			break;

		case 40:
			if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			if (p.movesToEnemy() < 2)
			{
				return p.attackEnemy();
			}
			else
			{
				return p.moveToLocation(15, 29);
			}
			break;


			// Attack Group 2
		case 39:case 42:case 43:case 44:
			if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			if (report.turns < 50)
			{
				return p.moveToEnemyCrown();
			}
			if (report.turns > 180)
			{
				return p.moveToAllyCrown();
			}
			else
			{
				return p.moveToEnemyCrown();
			}
			break;

		case 13:
			if (p.hasAttack())
			{
				return p.attackEnemy();
			}
			if (p.movesToEnemy() < 3)
			{
				return p.attackEnemy();
			}
			else
			{
				return p.moveToLocation(16, 29);
			}
			break;
		}
	}
	return wait();
}


lionheart::Blazon lionheart::JonathanSpencer::getBlazon()
{
  /*Return your blazon here.  In case of conflicts preference will be given to
   * the students that have registered their blazons in class.*/
  return { Color::VERT, Color::SABLE, Style::CHIEF, "Jonathan Spencer" };
}
