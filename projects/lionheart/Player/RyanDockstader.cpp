#include "RyanDockstader.hpp"
#include <random>

lionheart::Placement lionheart::RyanDockstader::placeUnit(UnitType ,
                                              StartBox const &box,
                                              SituationReport report)
{
	westSide = (box.minCol < static_cast<int>(report.things[0].size() / 2));
	id++;
	switch (id)
	{
		
		//crown
	case 1: return{ box.minRow + 5, box.minCol};
		//knights
			//royal guard
	case 2: return{ box.minRow +3, box.minCol +1};
	case 3: return{ box.minRow +7, box.minCol +1};
			//defense line
	case 4: return{ box.minRow +3, box.maxCol -1};
	case 5: return{ box.minRow +7, box.maxCol -1};
			//attack group 1
	case 6: return{ box.minRow +2, box.minCol};
			//attack group 2
	case 7: return{ box.maxRow , box.minCol+2};
		//archers
			//royal guard
	case 8: return{ box.minRow + 4, box.minCol};
			//defense line
	case 9: return{ box.minRow +4, box.maxCol -1};
	case 10: return{ box.minRow +5, box.maxCol -1};
	case 11: return{ box.minRow +6, box.maxCol -1};
			 //attack group 1
	case 12: return{ box.minRow, box.minCol};
	case 13: return{ box.minRow +1, box.minCol};
			 //attack group 2
	case 14: return{ box.maxRow, box.minCol};
	case 15: return{ box.maxRow -1, box.minCol};
		//infintry
			 //royal guard
	case 16: return{ box.minRow +6, box.minCol};
	case 17: return{ box.minRow +6, box.minCol +1};
	case 18: return{ box.minRow +5, box.minCol +1};
	case 19: return{ box.minRow +4, box.minCol +1};
			 //defense line
	case 20: return{ box.minRow +3, box.maxCol};
	case 21: return{ box.minRow +4, box.maxCol};
	case 22: return{ box.minRow +5, box.maxCol};
	case 23: return{ box.minRow +6, box.maxCol};
	case 24: return{ box.minRow +7, box.maxCol};
			 //attack group 1
	case 25: return{ box.minRow, box.minCol +1};
	case 26: return{ box.minRow+1, box.minCol +1};
	case 27: return{ box.minRow+2, box.minCol +1};
			 //attack group 2
	case 28: return{ box.maxRow, box.minCol +1};
	case 29: return{ box.maxRow-1, box.minCol +1};
	case 30: return{ box.maxRow-1, box.minCol +2};
	}

	return{ 0, 0 };
	//DONE.
}

  lionheart::Action
	  lionheart::RyanDockstader::recommendAction(Unit const & u, SituationReport r, Plan p)
  {
	  id = 0;
	  if (u.getId() == 0)
	  {		 
		  if (p.movesToEnemy() < 7)
		  {
			  static std::random_device rd;
			  static std::mt19937 engine(rd());
			  std::uniform_int_distribution<> act(0, 4);
			  switch (act(engine))
			  {
			  case 0:return turn(Direction::NORTH);
			  case 1:return turn(Direction::EAST);
			  case 2:return turn(Direction::SOUTH);
			  case 3:return turn(Direction::WEST);
			  case 4:return move(5);
			  }
		  }
		  else
		  {
			  return wait();
		  }
	  }
	  //wait for openent to storm
	  if (r.turns < 25)
	  {
		  if (p.hasAttack())
			  return p.attackEnemy();
		  else if (p.movesToEnemy() < 3)
			  return  p.moveToEnemy();
		  else
			  return wait();
	  }
	  //take a cautious attack party 
	  else if (r.turns >= 25 && r.turns < 50)
	  {
		  if (u.getId() == 5 || u.getId() == 6 || u.getId() == 3 || u.getId() == 11 || u.getId() == 12 || u.getId() == 13 || u.getId() == 14)
		  {
			  if (p.hasAttack())
			  {
				  return p.attackEnemy();
			  }
			  else if (p.movesToEnemy() < 3)
			  {
				  return p.moveToEnemy();
			  }
			  else
			  {
				 return p.moveToEnemyCrown();
			  }

		  }
		  else if (u.getId() > 23)
		  {
			  if (p.hasAttack())
			  {
				  return p.attackEnemy();
			  }
			  else if (p.movesToEnemy() < 3)
			  {
				  return p.moveToEnemy();
			  }
			  else
			  {
				  return p.moveToEnemyCrown();
			  }
		  }
		  else
		  {
			  if (p.hasAttack())
			  {
				  return p.attackEnemy();
			  }
			  else if (p.movesToEnemy() < 3)
			  {
				  return p.moveToEnemy();
			  }
			  else if (p.movesToAllyCrown() > 7)
			  {
				  return p.moveToAllyCrown();
			  }
			  else
			  {
				  return wait();
			  }
		  }

	  }
	  else 
	  {
		  if (u.getId() != 0 && u.getId() != 1 && u.getId() != 2 && u.getId() != 7 && u.getId() != 15 && u.getId() != 17 && u.getId() != 18)
		  {
			  if (p.hasAttack())
			  {
				  return p.attackEnemy();
			  }
			  else if (p.movesToEnemy() < 3)
			  {
				  return p.moveToEnemy();
			  }
			  else
			  {
				 return p.moveToEnemyCrown();
			  }
		  }
		  else
		  {
			  if (p.hasAttack())
			  {
				  return p.attackEnemy();
			  }
			  else if (p.movesToEnemy() < 3)
			  {
				  return p.moveToEnemy();
			  }
			  else
			  {
				  return p.moveToAllyCrown();
			  }
		  }
	  }

	  return p.attackEnemy();

  }



lionheart::Blazon lionheart::RyanDockstader::getBlazon()
{
  return { Color::AZURE, Color::SABLE, Style::CROSS, "N1GHTSH4D3" };
  //DONE
}
