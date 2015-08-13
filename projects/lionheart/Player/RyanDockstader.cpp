#include "RyanDockstader.hpp"
#include <random>
#include <iostream>


lionheart::Action lionheart::RyanDockstader::goodEyeSniper(lionheart::Unit const &unit, lionheart::SituationReport const &report, lionheart::Plan const &plan)
{
	if (plan.hasAttack())
	{
		return plan.attackEnemy();
	}
	else if (report.turns < 62)
	{

		if (westSide)
		{
			if (unit.getId() == 13)
				return plan.moveToLocation(21, 29);
			else
				return plan.moveToLocation(9, 29);
		}
		else
		{
			if (unit.getId() == 13)
				return plan.moveToLocation(21, 0);
			else
				return plan.moveToLocation(9, 0);
		}

	}
	else if (report.turns < 80)
	{

		if (westSide)
			return plan.moveToLocation(enemyCrown.row, 29);
		else
			return plan.moveToLocation(enemyCrown.row, 0);
	}

	else if (report.turns > 100)
	{
		return plan.moveToEnemyCrown();
	}
	else if (checkForCrown(unit, report))
	{

		if (westSide)
		{
			if (unit.getFacing() == Direction::WEST)
			{
				return plan.attackEnemy();
			}
		}
		else
		{
			if (unit.getFacing() == Direction::EAST)
			{
				return plan.attackEnemy();
			}
		}

		if (westSide)
			return turn(Direction::WEST);
		else
			return turn(Direction::EAST);
	}
	else
	{
		return plan.attackEnemy();
	}

	return plan.attackEnemy();
}

bool lionheart::RyanDockstader::checkForCrown(lionheart::Unit const &unit, lionheart::SituationReport )
{//fix this so it will actually check for the crown?
	int rowPlusFive, colPlusFive, r, c;
	r = unit.getLocation().row - 4;
	c = unit.getLocation().col - 4;
	colPlusFive = unit.getLocation().col + 9;
	rowPlusFive = unit.getLocation().row + 9;


	for ( ; r < rowPlusFive; ++r)
	{
		for (; c < colPlusFive; ++c)
		{
			if (unit.getLocation().row == enemyCrown.row)
			{
				return true;
			}
		}
	}
	return false;
}

void lionheart::RyanDockstader::getEnemyCrownLocation(lionheart::SituationReport report)
{
	for (int r = 0; r < 30; ++r)
	{
		for (int c = 0; c < 30; ++c)
		{
			if (report.things[r][c].type == SituationReport::ENEMY && report.things[r][c].unit == CROWN ) enemyCrown = {r, c };
		}
	}
}

lionheart::Placement lionheart::RyanDockstader::placeUnit(UnitType,
                                              StartBox const &box,
                                              SituationReport report)
{
	westSide = (box.minCol < static_cast<int>(report.things[0].size() / 2));
	id++;
	if (westSide)
	{
		switch (id)
		{

			//crown
		case 1: return{ box.minRow + 5, box.minCol };
				//knights
				//royal guard
		case 2: return{ box.minRow + 3, box.minCol + 1 };
		case 3: return{ box.minRow + 7, box.minCol + 1 };
				//defense line
		case 4: return{ box.minRow + 3, box.maxCol - 1 };
		case 5: return{ box.minRow + 7, box.maxCol - 1 };
				//attack group 1
		case 6: return{ box.minRow + 2, box.minCol };
				//attack group 2
		case 7: return{ box.maxRow, box.minCol + 2 };
				//archers
				//royal guard
		case 8: return{ box.minRow + 4, box.minCol };
				//defense line
		case 9: return{ box.minRow + 4, box.maxCol - 1 };
		case 10: return{ box.minRow + 5, box.maxCol - 1 };
		case 11: return{ box.minRow + 6, box.maxCol - 1 };
				 //attack group 1
		case 12: return{ box.minRow, box.minCol };
		case 13: return{ box.minRow + 1, box.minCol };
				 //attack group 2
		case 14: return{ box.maxRow, box.minCol + 1 };
		case 15: return{ box.maxRow - 1, box.minCol };
				 //infintry
				 //royal guard
		case 16: return{ box.minRow + 6, box.minCol };
		case 17: return{ box.minRow + 6, box.minCol + 1 };
		case 18: return{ box.minRow + 5, box.minCol + 1 };
		case 19: return{ box.minRow + 4, box.minCol + 1 };
				 //defense line
		case 20: return{ box.minRow + 3, box.maxCol };
		case 21: return{ box.minRow + 4, box.maxCol };
		case 22: return{ box.minRow + 5, box.maxCol };
		case 23: return{ box.minRow + 6, box.maxCol };
		case 24: return{ box.minRow + 7, box.maxCol };
				 //attack group 1
		case 25: return{ box.minRow, box.minCol + 1 };
		case 26: return{ box.minRow + 1, box.minCol + 1 };
		case 27: return{ box.minRow + 2, box.minCol + 1 };
				 //attack group 2
		case 28: return{ box.maxRow - 1, box.minCol + 2 };
		case 29: return{ box.maxRow - 1, box.minCol + 1 };
		case 30: return{ box.maxRow, box.minCol};
		}
	}
	else
	{
			switch (id)
			{
				//crown
			case 1: return{ box.maxRow - 5, box.maxCol };
					//knights
					//royal guard
			case 2: return{ box.maxRow - 3, box.maxCol - 1 };
			case 3: return{ box.maxRow - 7, box.maxCol - 1 };
					//defense line
			case 4: return{ box.maxRow - 3, box.minCol + 1 };
			case 5: return{ box.maxRow - 7, box.minCol + 1 };
					//attack group 1
			case 6: return{ box.maxRow - 2, box.maxCol };
					//attack group 2
			case 7: return{ box.minRow, box.maxCol - 2 };
					//archers
					//royal guard
			case 8: return{ box.maxRow - 4, box.maxCol };
					//defense line
			case 9: return{ box.maxRow - 4, box.minCol + 1 };
			case 10: return{ box.maxRow - 5, box.minCol + 1 };
			case 11: return{ box.maxRow - 6, box.minCol + 1 };
					 //attack group 1
			case 12: return{ box.maxRow, box.maxCol };
			case 13: return{ box.maxRow - 1, box.maxCol };
					 //attack group 2
			case 14: return{ box.minRow + 1, box.maxCol - 2 };
			case 15: return{ box.minRow + 1, box.maxCol };
					 //infintry
					 //royal guard
			case 16: return{ box.maxRow - 6, box.maxCol };
			case 17: return{ box.maxRow - 6, box.maxCol - 1 };
			case 18: return{ box.maxRow - 5, box.maxCol - 1 };
			case 19: return{ box.maxRow - 4, box.maxCol - 1 };
					 //defense line
			case 20: return{ box.maxRow - 3, box.minCol };
			case 21: return{ box.maxRow - 4, box.minCol };
			case 22: return{ box.maxRow - 5, box.minCol };
			case 23: return{ box.maxRow - 6, box.minCol };
			case 24: return{ box.maxRow - 7, box.minCol };
					 //attack group 1
			case 25: return{ box.maxRow, box.maxCol - 1 };
			case 26: return{ box.maxRow - 1, box.maxCol - 1 };
			case 27: return{ box.maxRow - 2, box.maxCol - 1 };
					 //attack group 2
			case 28: return{ box.minRow, box.maxCol - 1 };
			case 29: return{ box.minRow + 1, box.maxCol - 1 };
			case 30: return{ box.minRow, box.maxCol};
			}		
	}

	return{ 0, 0 };
	//DONE.
}

  lionheart::Action
	  lionheart::RyanDockstader::recommendAction(Unit const & u, SituationReport r, Plan p)
  {
	  id = 0;
	  getEnemyCrownLocation(r);
	  if (u.getId() == 0)
	  {		 
		  if (p.movesToEnemy() < 7)
		  {
			  static std::random_device rd;
			  static std::mt19937 engine(rd());
			  std::uniform_int_distribution<> act(0, 7);
			  switch (act(engine))
			  {
			  case 0:return turn(Direction::NORTH);
			  case 1:return move(5);
			  case 2:return turn(Direction::EAST);
			  case 3:return move(5);
			  case 4:return turn(Direction::SOUTH);
			  case 5:return move(5);
			  case 6:return turn(Direction::WEST);
			  case 7:return move(5);
			  }
		  }
		  else
		  {
			  return wait();
		  }
	  }
	  //wait for openent to storm
	  if (r.turns < 30)
	  {
		  if (p.hasAttack())
			  return p.attackEnemy();
		  else if (p.movesToEnemy() < 3)
			  return  p.moveToEnemy();
		  else
			  return wait();
	  }
	  //boar hunter
	  else if (u.getId() == 6)
	  {
		  
		  if (r.turns < 40 && r.turns >= 30)
		  {
			  switch (r.turns)
			  {
			  case 30: return turn(Direction::SOUTH);
			  case 31: return move(5);
			  case 32: if (westSide)
						{
							return turn(Direction::EAST);
						}
					   else
					   { 
						   return turn(Direction::WEST);
					   };
			  case 33: return move(5);
			  case 34: return move(5);
			  case 35: return move(5);
			  case 36: return move(5);
			  }
		  }
		  else if (p.hasAttack())
		  {
			  return p.attackEnemy();
		  }
		  else
			 return  p.moveToEnemyCrown();
	  }
	  //good eye, sniper.
	  else if (u.getId() == 13)
	  {
		  return goodEyeSniper(u, r, p);
	  }
	  else if (u.getId() == 12)
	  {
		  return goodEyeSniper(u, r, p);
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
  return { Color::AZURE, Color::SABLE, Style::CROSS, "Ryan Dockstader" };
  //DONE
}
