#include "JoshuaOstberg.hpp"
static bool westSide;
namespace {
int id;
}

lionheart::Placement lionheart::JoshuaOstberg::placeUnit(UnitType,
                                              StartBox const &box,
                                              SituationReport report)

	{
		++id;
		if (id > 30)
			id = 1;
		westSide = (box.minCol < static_cast<int>(report.things[0].size() / 2));
		if (westSide)
		{
			switch (id)
			{
				
				// CROWN
			case 1: return{ 14, 4 };
					// KNIGHTS
			case 2: return{ 10, 4 };
			case 3: return{ 11, 4 };
			case 4: return{ 18, 4 };
			case 5: return{ 19, 4 };
			case 6: return{ 14, 7 };
			case 7: return{ 15, 7 };
					// ARCHERS	
			case 8: return{ 10, 3 };
			case 9: return{ 13, 3 };
			case 10:return{ 15, 3 };
			case 11:return{ 19, 3 };
			case 12:return{ 19, 5 };
			case 13:return{ 10, 5 };
			case 14:return{ 13, 7 };
			case 15:return{ 16, 7 };
					 // INFANTRY
			case 16: return{ 14, 3 };
			case 17: return{ 12, 4 };
			case 18: return{ 13, 4 };
			case 19: return{ 15, 4 };
			case 20: return{ 16, 4 };
			case 21: return{ 17, 4 };
			case 22: return{ 12, 5 };
			case 23: return{ 13, 5 };

			case 24: return{ 14, 5 };
			case 25: return{ 15, 5 };
			case 26: return{ 16, 5 };
			case 27: return{ 13, 6 };
			case 28: return{ 14, 6 };
			case 29: return{ 15, 6 };
			case 30: return{ 16, 6 };
			}
		}
		else
		{
			switch (id)
			{
			
				// CROWN
			case 1: return{ 14, 25 };
					// KNIGHTS
			case 2: return{ 14, 22 };
			case 3: return{ 15, 22 };
			case 4: return{ 10, 25 };
			case 5: return{ 11, 25 };
			case 6: return{ 18, 25 };
			case 7: return{ 19, 25 };
					// ARCHERS
			case 8: return{ 13, 22 };
			case 9: return{ 16, 22 };
			case 10:return{ 10, 24 };
			case 11:return{ 10, 26 };
			case 12:return{ 19, 24 };
			case 13:return{ 19, 26 };
			case 14: return{ 13, 26 };
			case 15: return{ 15, 26 };
					 // INFANTRY
			case 16: return{ 13, 23 };
			case 17: return{ 14, 23 };
			case 18: return{ 15, 23 };
			case 19: return{ 16, 23 };
			case 20: return{ 14, 24 };
			case 21: return{ 15, 24 };
			case 22: return{ 16, 24 };
			case 23: return{ 17, 24 };
								  
			case 24: return{ 18, 24 };
			case 25: return{ 14, 25 };
			case 26: return{ 15, 25 };
			case 27: return{ 17, 25 };
			case 28: return{ 18, 25 };
			case 29: return{ 19, 25 };
			case 30: return{ 16, 26 };
			}
		}
		return{ 0, 0 };
		id = 0;
	
}

  lionheart::Action
	  lionheart::JoshuaOstberg::recommendAction(Unit const& u, SituationReport report, Plan p)
  {
	  if (westSide)
	  {
		  if (p.hasAttack())
		  {
			  return p.attackEnemy();
		  }

		  switch (u.getId())
		  {
			  //crown
		  case 0: return wait();
			  break;
		  case 1:case 2:
			  if (report.turns <2)
			  {
				  return turn(Direction::NORTH);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 3://
			  if (report.turns <2)
			  {
				  return turn(Direction::SOUTH);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 4://
			  if (report.turns < 5)
			  {
				  return p.moveToLocation(22, 7);
			  }
			  if (report.turns > 5 && report.turns < 20)
			  {
				  return p.moveToLocation(26, 17);
			  }
			  if (report.turns > 21 && report.turns < 40)
			  {
				  return p.moveToLocation(29, 28);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 5://
			  if (report.turns <2)
			  {
				  return turn(Direction::EAST);
			  }
			  else
			  {
				  return wait();
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  break;
		  case 6://
			  if (report.turns <2)
			  {
				  return turn(Direction::EAST);
			  }
			  else
			  {
				  return wait();
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  break;
			  
		  case 7:
			  if (report.turns < 5)
			  {
				  return p.moveToLocation(10, 2);
			  }
			  if (report.turns <8 && report.turns >5)
			  {
				  return turn(Direction::EAST);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 8://
			  if (report.turns <2)
			  {
				  return turn(Direction::EAST);

			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  break;
		  case 9://
			
			  if (report.turns <2)
			  {
				  return turn(Direction::EAST);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  break;
		  case 10: //
			  if (report.turns <2)
			  {
				  return turn(Direction::EAST);
			  }
			 
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;

		  case 11: //
			  if (report.turns < 5)
			  {
				  return p.moveToLocation(19, 6);
			  }
			  if (report.turns <8 && report.turns >5)
			  {
				  return turn(Direction::WEST);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 12://
			  if (report.turns < 5)
			  {
				  return p.moveToLocation(10, 6);
			  }
			  if (report.turns <8 && report.turns >5)
			  {
				  return turn(Direction::WEST);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 13://
			  if (report.turns < 5)
			  {
				  return p.moveToLocation(12, 7);//12,3

			  }
			 if (report.turns < 8 && report.turns>5)
			  {
				  return turn(Direction::SOUTH);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  break;
		  case 14://
			  if (report.turns < 5)
			  {
				  return p.moveToLocation(17, 7);//12,3

			  }
			  if (report.turns < 8 && report.turns>5)
			  {
				  return turn(Direction::NORTH);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  break;
		  case 30://///
			  return wait();
			  break;
		  case 31:
			  if (report.turns <2)
			  {
				  return turn(Direction::NORTH);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			 
			  break;
		  case 32://////////
			  if (report.turns <2)
			  {
				  return turn(Direction::NORTH);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			
			  break;
		  case 33: //////
			  if (report.turns <2)
			  {
				  return turn(Direction::SOUTH);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 34:
			  if (report.turns <2)
			  {
				  return turn(Direction::SOUTH);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 35:
			  if (report.turns <2)
			  {
				  return turn(Direction::SOUTH);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 36:
			  if (report.turns <2)
			  {
				  return turn(Direction::WEST);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 37:
			  if (report.turns <2)
			  {
				  return turn(Direction::SOUTH);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 38:////
			  if (report.turns <2)
			  {
				  return turn(Direction::EAST);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 39:
			  if (report.turns <2)
			  {
				  return turn(Direction::EAST);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 40:
			  if (report.turns <2)
			  {
				  return turn(Direction::NORTH);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 41:
			  if (report.turns <2)
			  {
				  return turn(Direction::SOUTH);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			
			  else
			  {
				  return wait();
			  }
			  break;
		  case 42:
			  if (report.turns <2)
			  {
				  return turn(Direction::EAST);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 43:
			  if (report.turns <2)
			  {
				  return turn(Direction::EAST);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 44:
			  if (report.turns <2)
			  {
				  return turn(Direction::NORTH);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
		  default:
			  break;
		  }
		  
	  }
	  else
	  {
		  if (p.hasAttack())
		  {
			  return p.attackEnemy();
		  }

		  switch (u.getId())
		  {
			  //crown
		  case 0: return wait();
			  break;
		  case 1:case 2:
			  if (report.turns < 5)
			  {
				  return turn(Direction::WEST);
			  }
			  if (report.turns > 55)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 3://
			  if (report.turns < 5)
			  {
				  return turn(Direction::NORTH);
			  }
			  if (report.turns > 55)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 4://
			  if (report.turns < 5)
			  {
				  return turn(Direction::NORTH);
			  }
			  
			  if (report.turns > 55)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 5://
			  if (report.turns < 5)
			  {
				  return turn(Direction::SOUTH);
			  }
			  else
			  {
				  return wait();
			  }
			  if (report.turns > 55)
			  {
				  return p.moveToEnemyCrown();
			  }
			  break;
		  case 6://
			  if (report.turns < 5)
			  {
				  return turn(Direction::SOUTH);
			  }
			  else
			  {
				  return wait();
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  break;

		  case 7:
			  if (report.turns < 5)
			  {
				  return p.moveToLocation(12, 22);
			  }
			  if (report.turns <10 && report.turns >5)
			  {
				  return turn(Direction::SOUTH);
			  }
			  if (report.turns > 55)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 8://
			  if (report.turns < 5)
			  {
				  return p.moveToLocation(17, 22);
			  }
			  if (report.turns <10 && report.turns >5)
			  {
				  return turn(Direction::NORTH);

			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  break;
		  case 9://
			  if (report.turns < 2)
			  {
				  return p.moveToLocation(10, 23);
			  }
			  if (report.turns <10 && report.turns >5)
			  {
				  return turn(Direction::EAST);
			  }
			  if (report.turns > 55)
			  {
				  return p.moveToEnemyCrown();
			  }
			  break;
		  case 10: //
			  if (report.turns < 2)
			  {
				  return turn(Direction::EAST);
			  }
			 
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  break;
		  case 11: //
			  if (report.turns < 5)
			  {
				  return p.moveToLocation(19, 23);
			  }
			  if (report.turns <10 && report.turns >5)
			  {
				  return turn(Direction::EAST);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 12://
			  if (report.turns < 5)
			  {
				  return p.moveToLocation(10, 6);
			  }
			  if (report.turns <10 && report.turns >5)
			  {
				  return turn(Direction::WEST);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 13://
			 
			  if (report.turns < 3)
			  {
				  return turn(Direction::NORTH);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  break;
		  case 14://
			  
			  if (report.turns < 3)
			  {
				  return turn(Direction::SOUTH);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  break;
		  case 30://///
			  return wait();
			  break;
		  case 31:
			  if (report.turns < 5)
			  {
				  return turn(Direction::WEST);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }

			  break;
		  case 32://////////
			  if (report.turns < 5)
			  {
				  return turn(Direction::NORTH);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }

			  break;
		  case 33: //////
			  if (report.turns < 5)
			  {
				  return turn(Direction::SOUTH);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 34:
			  if (report.turns < 5)
			  {
				  return turn(Direction::SOUTH);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 35:
			  if (report.turns < 5)
			  {
				  return turn(Direction::SOUTH);
			  }
			  if (report.turns < 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 36:
			  if (report.turns < 5)
			  {
				  return turn(Direction::WEST);
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 37:
			  if (report.turns < 5)
			  {
				  return turn(Direction::SOUTH);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 38:////
			  if (report.turns < 5)
			  {
				  return turn(Direction::EAST);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 39:
			  if (report.turns < 5)
			  {
				  return turn(Direction::EAST);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 40:
			  if (report.turns < 5)
			  {
				  return turn(Direction::NORTH);
			  }
			 
			  else
			  {
				  return wait();
			  }
			  break;
		  case 41:
			 
			  if (report.turns < 5)
			  {
				  return turn(Direction::SOUTH);
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 42:
			  if (report.turns < 5)
			  {
				  return turn(Direction::EAST);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 43:
			  if (report.turns < 5)
			  {
				  return turn(Direction::EAST);
			  }
			  if (report.turns > 70)
			  {
				  return p.moveToEnemyCrown();
			  }
			  else
			  {
				  return wait();
			  }
			  break;
		  case 44:
			  if (report.turns < 5)
			  {
				  return turn(Direction::EAST);
			  }
			  else
			  {
				  return wait();
			  }
			  
		  default:
			  break;
		  }

	  }

	  return wait();
  }
		 

		


	  //if (u.getType() == CROWN && report.turns < 10) 
	  //{
	  //	if (p.hasAttack())
	  //	{
	  //		return p.attackEnemy();
	  //	}
	  //	return wait();
	  //}
	  //if (u.getType() == CROWN && report.turns > 11)
	  //{
	  //	if (p.hasAttack())
	  //	{
	  //		return p.attackEnemy();
	  //	}
	  //	
	  //}
	  //
	  //if (u.getType() == KNIGHT && report.turns < 10)
	  //{
	  //	if (p.hasAttack())
	  //	{
	  //		return p.attackEnemy();
	  //	}
	  //	return wait();
	  //	
	  //}
	  //if (u.getType() == KNIGHT && report.turns > 11)
	  //{
	  //	if (p.hasAttack())
	  //	{
	  //		return p.attackEnemy();
	  //	}
	  //	return p.moveToEnemyCrown();
	  //
	  //}
	  //return p.attackEnemy();
	  //if (u.getType() == ARCHER)
	  //{
	  //	if (p.hasAttack())
	  //	{
	  //		return p.attackEnemy();
	  //	}
	  //	return p.moveToEnemyCrown();
	  //}
	  //return p.attackEnemy();
	  //if (u.getType() == INFANTRY)
	  //{
	  //	if (p.hasAttack())
	  //	{
	  //		return p.attackEnemy();
	  //	}
	  //	return p.moveToEnemyCrown();
	  //}
	  //return p.attackEnemy();
	  //
	  //return Action();



  lionheart::Blazon lionheart::JoshuaOstberg::getBlazon()
{
  /*Return your blazon here.  In case of conflicts preference will be given to
   * the students that have registered their blazons in class.*/
	return{ Color::ARGENT, Color::SABLE, Style::INVERTED_CHEVERON, "Joshua Ostberg" };
}
