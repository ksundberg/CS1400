#include "DukePapworth.hpp"

lionheart::Placement lionheart::DukePapworth::placeUnit(UnitType,
                                              StartBox const &box,
                                              SituationReport report)
{
		
  /*Fill this out with instructions on how to place your initial units.  Without
   * changes your units will fill the starting box from top left to bottom right
   * in the order constructed.*/
	
	
	{
		++id;
		westSide = (box.minCol < static_cast<int>(report.things[0].size() / 2));
		if (westSide)
		{
			switch (id)
			{
				// CROWN
			case 1: return{ 12, 4 };
					// KNIGHTS
			case 2: return{ 10, 3 };
			case 3: return{ 10, 4 };
			case 4: return{ 10, 5 };
					//^^^ goes for top battle
			case 5: return{ 10, 6 };
			case 6: return{ 11, 2 };
			case 7: return{ 11, 3 };
					//^^^ goes for bottom battle
					// ARCHERS
			case 8: return{ 10, 2 };
			case 9: return{ 11, 4 };
			case 10:return{ 11, 5 };
			case 11:return{ 11, 6 };
					// ^^ goes for top battle
			case 12:return{ 12, 2 };
			case 13:return{ 12, 3 };
			case 14: return{ 12, 4 };
			case 15: return{ 12, 5 };
					 //^^ goes for bottom battle
					 // INFANTRY
			case 16: return{ 12, 6 };
			case 17: return{ 13, 2 };
			case 18: return{ 13, 3 };
			case 19: return{ 13, 4 };
			case 20: return{ 13, 5 };
			case 21: return{ 13, 6 };
			case 22: return{ 14, 2 };
			case 23: return{ 14, 3 };
					 //^^ goes for top battle

			case 24: return{ 14, 4 };
			case 25: return{ 14, 5 };
			case 26: return{ 14, 6 };
			case 27: return{ 15, 2 };
			case 28: return{ 15, 3 };
			case 29: return{ 15, 4 };
			case 30: id = 0; return{ 15, 5 };
					 // ^^ goes for bottom battle
			}
		}
		else
		{
			switch (id)
			{
				// CROWN
			case 1: return{ 12, 25 };
					// KNIGHTS
			case 2: return{ 10, 23 };
			case 3: return{ 10, 24 };
			case 4: return{ 10, 25 };
					//^^ goes for top battle
			case 5: return{ 10, 27 };
			case 6: return{ 11, 23 };
			case 7: return{ 11, 24 };
					//^^ goes for bottom battle
					// ARCHERS
			case 8: return{ 10, 26 };
			case 9: return{ 11, 25 };
			case 10:return{ 11, 26 };
			case 11:return{ 11, 27 };
					// ^^ goes for top battle
			case 12:return{ 12, 23 };
			case 13:return{ 12, 24 };
			case 14:return{ 12, 25 };
			case 15:return{ 12, 26 };
					 // ^^ goes for bottom battle
					 // INFANTRY
			case 16: return{ 12, 27 };
			case 17: return{ 13, 23 };
			case 18: return{ 13, 24 };
			case 19: return{ 13, 25 };
			case 20: return{ 13, 26 };
			case 21: return{ 13, 27 };
			case 22: return{ 14, 23 };
			case 23: return{ 14, 24 };
					 // ^^ goes for top battle
			case 24: return{ 14, 25 };
			case 25: return{ 14, 26 };
			case 26: return{ 14, 27 };
			case 27: return{ 15, 23 };
			case 28: return{ 15, 24 };
			case 29: return{ 15, 25 };
			case 30: id = 0; return{ 15, 26 };
					 // ^^ goes for bottom battle
			}
		}
		return{ 0, 0 };
	}
}

  

int lionheart::DukePapworth::DetermineDirection(Unit const & u)
{

	if (u.getFacing() == Direction::EAST)
		return 0;
	else if (u.getFacing() == Direction::WEST)
		return 1;
	else if (u.getFacing() == Direction::NORTH)
		return 2;
	else
		return 3;
	
}



lionheart::Action
lionheart::DukePapworth::recommendAction(Unit const & u, SituationReport , Plan p)
{

	{
		if (u.getType() == CROWN) {
			return wait();
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
	}

	/*int d = DetermineDirection(u);
	
	if (p.hasAttack()) return p.attackEnemy();

	// CROWN

		if (u.getType() == CROWN)
		{
			if (DetermineDirection(u) == 0)
			{				
				if (p.movesTo(1, 4) == 0)
				{
					if (DetermineDirection(u) == 3)
					{
						return p.attackEnemy(); // best case scenario
					}							
					return turn(Direction::SOUTH);
				}
				return p.moveToLocation(1, 4); // worst case scenario
			}
			else
			{
				if (p.movesTo(1, 27) == 0)
				{
					if (DetermineDirection(u) == 3)
					{
						return p.attackEnemy(); // p.attackEnemy?? or have to check hasAttack first.  Any person in the 9 squares will get attacked
					}	
					return turn(Direction::SOUTH);
				}
				return p.moveToLocation(1, 27);			
			}
		
		}

		// FIRST and SECOND UPPER KNIGHTs
		if (u.getType() == 1)
		{
			if (DetermineDirection(u) == 0)
			{
				
				if (p.movesTo(10, 13) == 0)
				{
					
					if (DetermineDirection(u) == 0)
					{
						return p.attackEnemy();
					}
					return turn(Direction::EAST);
				}
				return p.moveToLocation(10, 13);
			}
			else
			{
				if (p.movesTo(10, 16) == 0)
				{
					if (DetermineDirection(u) == 1)
						{
							return p.attackEnemy();
						}
						return turn(Direction::WEST);
				}
			}	return p.moveToLocation(10, 16);
		}
		
		if (u.getType() == 2)
		{
			if (DetermineDirection(u) == 0)
			{
				if (p.movesTo(8, 8) == 0)
				{
					if (DetermineDirection(u) == 0)
					{
						return p.attackEnemy();
					}
					return turn(Direction::EAST);
				}	
				return p.moveToLocation(8, 8);
			}	
			
			else
			{
				if (p.movesTo(8, 21) == 0)
					
				if (DetermineDirection(u) == 1)
				{
					return p.attackEnemy();
				}
				return turn(Direction::WEST);
			}
			return p.moveToLocation(8, 21);

		}

		// MIDDLE KNIGHTS
		//if (u.getType() == KNIGHT)
		
		if (u.getId() == 3)
		{
			if (DetermineDirection(u) == 0)
			{
				if (p.movesTo(4, 7) < 1)
				{
					if (p.movesTo(1, 3) == 0)
					{
						if (DetermineDirection(u) == 3)
						{
							return p.attackEnemy();
						}
						return turn(Direction::SOUTH);
					}
					return p.moveToLocation(1, 3);
				}
				return p.moveToLocation(4, 7);
			}
			else
			{
				
				if (p.movesTo(4, 22) < 1)
				{
					
					if (p.movesTo(1, 28) == 0)
						
					if (DetermineDirection(u) == 3)
					{
						return p.attackEnemy();
					}
					return turn(Direction::SOUTH);
				}
				return p.moveToLocation(1, 28);
			}
			return p.moveToLocation(4, 22);
		

		}

		if (u.getId() == 4)
		{
			if (DetermineDirection(u) == 0)
			{
				
				if (p.movesTo(4, 7) < 1)
				{
					

					if (p.movesTo(2, 4) == 0)
					{
						

						if (DetermineDirection(u) == 3)
						{
							return p.attackEnemy();
						}
						return turn(Direction::SOUTH);
					}
					return p.moveToLocation(2, 3);
				}
				return p.moveToLocation(4, 7);
			}
			else
			{
				
				if (p.movesTo(4, 22) < 1)
				{
					 
					if (p.movesTo(1, 28) == 0)
						
					if (DetermineDirection(u) == 3)
					{
						return p.attackEnemy();
					}
					return turn(Direction::SOUTH);
				}
				return p.moveToLocation(2, 28);
			}
			return p.moveToLocation(4, 22);
		}

		

			// TOP BATTLE ARCHERS


			if (u.getId() == 7)
			{ if (DetermineDirection(u) == 3)
				{
					if (p.movesTo(2, 8) == 0)
					{
						if (DetermineDirection(u) == 3)
						{
							return p.attackEnemy();
						}
						return turn(Direction::SOUTH);
					}
					return p.moveToLocation(2, 8);
				}
			}
			else
				if (p.movesTo(2, 23) == 0)
				{
					if (DetermineDirection(u) == 3)
					{
						return p.attackEnemy();
					}
					return turn(Direction::SOUTH);
				}
			return p.moveToLocation(2, 23);


			if (u.getId() == 8)
			{ if(DetermineDirection(u) == 3)
				{
					if (p.movesTo(6, 3) == 0)
					{
						if (DetermineDirection(u) == 0)
						{
							return p.attackEnemy();
						}
						return turn(Direction::EAST);
					}
					return p.moveToLocation(6, 3);
				}
			}
			else
				if (p.movesTo(6, 28) == 0)
				{
					if (DetermineDirection(u) == 1)
					{
						return p.attackEnemy();
					}
					return turn(Direction::WEST);
				}
			return p.moveToLocation(6, 28);
			
			if (u.getId() == 9)
			{
				if (DetermineDirection(u) == 3)
				{
					if (p.movesTo(7, 7) == 0)
					{
						if (DetermineDirection(u) == 0)
						{
							return p.attackEnemy();
						}
						return turn(Direction::EAST);
					}
					return p.moveToLocation(7, 7);
				}
			}
			else
				if (p.movesTo(7, 24) == 0)
				{
					if (DetermineDirection(u) == 1)
					{
						return p.attackEnemy();
					}
					return turn(Direction::WEST);
				}
			return p.moveToLocation(7, 24);
			
			if (u.getId() == 10)
			{
				if (DetermineDirection(u) == 3)
				{
					if (p.movesTo(10, 12) == 0)
					{
						if (DetermineDirection(u) == 2)
						{
							return p.attackEnemy();
						}
						return turn(Direction::NORTH);
					}
					return p.moveToLocation(10, 12);
				}
			}
			else
				if (p.movesTo(10, 17) == 0)
				{
					if (DetermineDirection(u) == 2)
					{
						return p.attackEnemy();
					}
					return turn(Direction::NORTH);
				}
			return p.moveToLocation(10, 17);

			
				
			 // TOP INFANTRY
			if (u.getId() == 30 || u.getId() == 31 || u.getId() == 32 || u.getId() == 33 || u.getId() == 34 || u.getId() == 35 || u.getId() == 36 || u.getId() == 37)
			{
				if (DetermineDirection(u) == 0)
				{

					if (p.movesTo(1, 4) < 3)
					{
						return p.attackEnemy();
					}
					return p.moveToLocation(21, 25);

				}
				else
				{
					if (p.movesTo(1, 27) < 3)
					{
						return p.attackEnemy();
					}
					return p.moveToLocation(21, 4);

				}
			}

			
			if (s.turns > 25)
			{


			//BOTTOM INFANTRY
			if (u.getId() == 38 || u.getId() == 39 || u.getId() == 40 || u.getId() == 41 || u.getId() == 42 || u.getId() == 43 || u.getId() == 44)
			{
				if (DetermineDirection(u) == 0)
				{

					if (p.movesTo(21, 25) < 2)
					{
						return p.attackEnemy();
					}
					return p.moveToLocation(21, 25);

				}
				else
				{
					if (p.movesTo(21, 4) < 2)
					{
						return p.attackEnemy();
					}
					return p.moveToLocation(21, 4);

				}
			}


			// BOTTOM KNIGHTS

			if (u.getId() == 5 || u.getId() == 6)
			{
				if (DetermineDirection(u) == 0)
				{

					if (p.movesTo(21, 25) < 1)
					{
						return p.attackEnemy();
					}
					return p.moveToLocation(21, 25);

				}
				else
				{
					if (p.movesTo(21, 4) < 1)
					{
						return p.attackEnemy();
					}
					return p.moveToLocation(21, 4);


				}
			}

				// BOTTOM BATTLE ARCHERS
				if (u.getId() == 11 || u.getId() == 12 || u.getId() == 13 || u.getId() == 14)
				{
					if (DetermineDirection(u) == 0)
					{

						if (p.movesTo(21, 25) < 1)
						{
							return p.attackEnemy();
						}
						return p.moveToLocation(21, 25);

					}
					else
					{
						if (p.movesTo(21, 4) < 1)
						{
							return p.attackEnemy();
						}
						return p.moveToLocation(21, 4);

					}
				}

			

	}
	
	

	*/

	/*Fill this out with the behavior you want for your units.  Without changes
   * your units will just wait to be defeated.  Feel free to look at the other
   provided players for ideas on how to get certain behavior*/
  return Action();
}

lionheart::Blazon lionheart::DukePapworth::getBlazon()
{
  /*Return your blazon here.  In case of conflicts preference will be given to
   * the students that have registered their blazons in class.*/
  return { Color::OR, Color::VERT, Style::QUARTERLY, "Duke Papworth" };
}
