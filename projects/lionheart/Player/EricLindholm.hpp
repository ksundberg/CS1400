#ifndef LIONHEART_ERIC_LINDHOLM
#define LIONHEART_ERIC_LINDHOLM
#include "Player.hpp"

namespace lionheart
{
/*The : public Player bit allows this code to interact with the framework code
 * provided.  If your class file is Name.hpp the class needs to be named Name or
 * the framework code will not be able to find and add the player to
 * tournaments.*/
  class EricLindholm : public Player
  {
  public:
	  EricLindholm() :id(0) {}
	  Placement placeUnit(UnitType, StartBox const& box, SituationReport report)
	  {
		  ++id;
		  westSide = (box.minCol < static_cast<int>(report.things[0].size() / 2));
		  if (westSide)
		  {
			  switch (id)
			  {
				  // CROWN
			  case 1: return{ 14, 2 };
					  // KNIGHTS
			  case 2: return{ 17,3 };
			  case 3: return{ 17,4 };
			  case 4: return{ 17,5 };
			  case 5: return{ 18,3 };
			  case 6: return{ 18,4 };
			  case 7: return{ 18,5 };
					  // ARCHERS
			  case 8: return{ 19,3 };
			  case 9: return{ 19,5 };
			  case 10:return{ 13,6 };
			  case 11:return{ 14,6 };
			  case 12:return{ 15,6 };
			  case 13:return{ 16,6 };
			  case 14: return{ 10,3 };
			  case 15: return{ 10,5 };
					   // INFANTRY
			  case 16: return{ 10,4 };
			  case 17: return{ 12,3 };
			  case 18: return{ 12,4 };
			  case 19: return{ 13,2 };
			  case 20: return{ 13,3 };
			  case 21: return{ 13,7 };
			  case 22: return{ 14,3 };
			  case 23: return{ 14,7 };

			  case 24: return{ 15,2 };
			  case 25: return{ 15,3 };
			  case 26: return{ 15,7 };
			  case 27: return{ 16,3 };
			  case 28: return{ 16,4 };
			  case 29: return{ 16,7 };
			  case 30: return{ 19,4 };
			  }
		  }
		  else
		  {
			  switch (id)
			  {
				  // CROWN
			  case 1: return{ 14, 27 };
					  // KNIGHTS
			  case 2: return{ 17,26 };
			  case 3: return{ 17,25 };
			  case 4: return{ 17,24 };
			  case 5: return{ 18,26 };
			  case 6: return{ 18,25 };
			  case 7: return{ 18,24 };
					  // ARCHERS
			  case 8: return{ 10,26 };
			  case 9: return{ 10,24 };
			  case 10:return{ 13,23 };
			  case 11:return{ 14,23 };
			  case 12:return{ 15,23 };
			  case 13:return{ 16,23 };
			  case 14: return{ 19,26 };
			  case 15: return{ 19,24 };
					   // INFANTRY
			  case 16: return{ 10,25 };
			  case 17: return{ 12,26 };
			  case 18: return{ 12,25 };
			  case 19: return{ 13,27 };
			  case 20: return{ 13,26 };
			  case 21: return{ 13,22 };
			  case 22: return{ 14,26 };
			  case 23: return{ 14,22 };

			  case 24: return{ 15,27 };
			  case 25: return{ 15,26 };
			  case 26: return{ 15,22 };
			  case 27: return{ 16,26 };
			  case 28: return{ 16,25 };
			  case 29: return{ 16,22 };
			  case 30: return{ 19,25 };

			  }
		  }
		  return{ 0,0 };
	  }
	  Action recommendAction(Unit const& u, SituationReport, Plan p)

	  {
		  int n = 0; 
		 
			  n++;
			  if (u.getType() == CROWN)
				  return wait();

			  if (u.getType() == ARCHER && n >= 15)
			  {
				  if (p.hasAttack())
				  {
					  return p.attackEnemy();
				  }
				  return p.moveToEnemyCrown();
			  }
			  return p.attackEnemy();

			  if (u.getType() == ARCHER && n < 15)
				  return wait();

			  if (u.getType() == INFANTRY)
			  {
				  if (p.hasAttack())
				  {
					  return p.attackEnemy();
				  }
				  return p.moveToEnemy();
			  }
			  if (u.getType() == KNIGHT)
			  {
				  if (p.hasAttack())
				  {
					  return p.attackEnemy();
				  }
				  return p.moveToEnemyCrown();
			  }
			  return p.attackEnemy();


			  if (p.hasAttack()) return p.attackEnemy();
			  switch (u.getId())
			  {
			  case 0: return wait();//return wait();
			  case 1: return p.moveToEnemyCrown();
			  case 2: return p.moveToEnemyCrown();
			  case 3: return p.moveToEnemyCrown();
				  //return p.moveToLocation(7, 15);
			  case 4: return p.moveToEnemyCrown();
			  case 5: return p.moveToEnemyCrown();
			  case 6: return p.moveToEnemyCrown();
				  //return p.moveToLocation(22, 15);
			  case 7: return p.moveToEnemyCrown();
			  case 8: return p.moveToLocation(20, 25);
				  //return turn(Direction::NORTH);
			  case 9: return p.moveToLocation(20, 25);
				  //return wait();
			  case 10: return p.moveToLocation(14, 20);
			  case 11: return p.moveToLocation(14, 20);
			  case 12: return p.moveToLocation(15, 20);
				  //if (u.getLocation().col == 5) return move(1);
				  //if (u.getLocation().col == 24) return move(1);
			  case 13: return p.moveToLocation(15, 20);
			  case 14: return turn(Direction::NORTH);
				  //return turn(Direction::SOUTH);
			  case 15: return turn(Direction::NORTH);
			  case 16: return turn(Direction::NORTH);
				  //break;
			  case 17: return wait();
			  case 18: return wait();
			  case 19: return wait();
			  case 20: return wait();
			  case 21: return p.moveToLocation(14, 20);
			  case 22: return wait();
			  case 23: return p.moveToLocation(14, 20);
			  case 24: return wait();
			  case 25: return wait();
			  case 26: return p.moveToLocation(15, 20);
			  case 27: return wait();
			  case 28: return wait();
			  case 29: return p.moveToLocation(15, 20);
			  case 30: return p.moveToLocation(20, 25);
				  //return move(1);
			  default:
				  break;//break;
			  }

			  return p.moveToEnemyCrown();//return p.moveToEnemyCrown();
	
	  }
	  Blazon getBlazon() { return{ Color::OR, Color::SABLE, Style::QUARTERLY, "Battle Bee" }; }
  private:
	  bool westSide;
	  int id;
  };
}
#endif

