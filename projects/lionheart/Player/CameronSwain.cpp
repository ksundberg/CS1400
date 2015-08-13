#include "CameronSwain.hpp"
#include <map>
lionheart::Placement lionheart::CameronSwain::placeUnit(UnitType,
                                              StartBox const &box,
                                              SituationReport report)
{
  /*Fill this out with instructions on how to place your initial units.  Without
   * changes your units will fill the starting box from top left to bottom right
   * in the order constructed.*/
	++id;
	westSide = (box.minCol < static_cast<int>(report.things[0].size() / 2));
	if (westSide)
	{
		switch (id)
		{
			// CROWN
		case 1: return{ 13, 6 };
				// KNIGHTS
		case 2: return{ 10, 4 };
		case 3: return{ 14, 4 };
		case 4: return{ 15, 4 };
		case 5: return{ 19, 4 };
		case 6: return{ 14, 7 };
		case 7: return{ 15, 7 };
				// ARCHERS
		case 8: return{ 11, 6 };
		case 9: return{ 11, 4 };
		case 10:return{ 11, 5 };
		case 11:return{ 13, 7 };
		case 12:return{ 14, 6 };
		case 13:return{ 16, 7 };
		case 14: return{ 18, 6 };
		case 15: return{ 15, 6 };
				 // INFANTRY
		case 16: return{ 10, 3 };
		case 17: return{ 11, 3 };
		case 18: return{ 12, 3 };
		case 19: return{ 10, 5 };
		case 20: return{ 15, 3 };
		case 21: return{ 16, 3 };
		case 22: return{ 17, 3 };
		case 23: return{ 18, 3 };

		case 24: return{ 13, 2 };
		case 25: return{ 11, 2 };
		case 26: return{ 12, 2 };
		case 27: return{ 18, 4 };
		case 28: return{ 12, 5 };
		case 29: return{ 10, 2 };
		case 30: id = 0; return{ 19, 3 };
		}
	}
	else
	{
		switch (id)
		{
			// CROWN
		case 1: return{ 13, 23 };
				// KNIGHTS
		case 2: return{ 10, 25 };
		case 3: return{ 14, 25 };
		case 4: return{ 15, 25 };
		case 5: return{ 19, 25 };
		case 6: return{ 14, 22 };
		case 7: return{ 15, 22 };
				// ARCHERS
		case 8: return{ 11, 23 };
		case 9: return{ 11, 25 };
		case 10:return{ 11, 24 };
		case 11:return{ 13, 22 };
		case 12:return{ 14, 23 };
		case 13:return{ 16, 22 };
		case 14: return{ 18, 23 };
		case 15: return{ 15, 23 };
				 // INFANTRY
		case 16: return{ 10, 26 };
		case 17: return{ 11, 26 };
		case 18: return{ 12, 26 };
		case 19: return{ 10, 24 };
		case 20: return{ 15, 26 };
		case 21: return{ 16, 26 };
		case 22: return{ 17, 26 };
		case 23: return{ 18, 26 };

		case 24: return{ 13, 27 };
		case 25: return{ 11, 27 };
		case 26: return{ 12, 27 };
		case 27: return{ 18, 25 };
		case 28: return{ 12, 24 };
		case 29: return{ 10, 27 };
		case 30: id = 0; return{ 19, 26 };
		}
	}
	return{ 0, 0 };
}

bool lionheart::CameronSwain::west(Unit const& , SituationReport s)
{
	for (int i = 10; i < 20; ++i)//rows
	{
		for (int j = 2; j < 8; ++j)//cols
		{
			if (s.things[i][j].unit == UnitType::CROWN && s.things[i][j].type == lionheart::SituationReport::ThingType::ALLY) return true;//return the row that the king is in
		}
	}
	return false;

}

/*lionheart::Action lionheart::CameronSwain::protectBase(Unit const& u, SituationReport s, Plan p)
{
	if (west(u, s))
	{
		for (int i = 10; i < 20; ++i)//rows
		{
			for (int j = 2; j < 8; ++j)//cols
			{
				if (u.getLocation().col<8 &&s.things[i][j].type == lionheart::SituationReport::ThingType::ENEMY) return p.attackEnemy();//return the row that the king is in
			}
		}
		
	}
	else
	{
		for (int i = 10; i < 20; ++i)//rows
		{
			for (int j = 22; j < 28; ++j)//cols
			{
				if (u.getLocation().col> 21 && s.things[i][j].type == lionheart::SituationReport::ThingType::ENEMY) return p.attackEnemy();
			}
		}
		
	}
	return;
}*/

int lionheart::CameronSwain::KingInFront(Unit const & u, SituationReport s)//this will give me the row that the king is in
{
	if (west(u,s))
	{
	for (int i = 10; i < 20; ++i)//rows
			{
				for (int j = 0; j < 2; ++j)//cols
				{
					if (s.things[i][j + 22].unit == UnitType::CROWN) return i;//return the row that the king is in
				}
			}
			return 0;
		
	}
	else
	{
		for (int i = 10; i < 20; ++i)//rows
		{
			for (int j = 0; j < 2; ++j)//cols
			{
				if (s.things[i][j + 6].unit == UnitType::CROWN) return i;
			}
		}
		return 0;
	}
}

int lionheart::CameronSwain::KingInBack(Unit const & u, SituationReport s)//this will give me the row that the king is in
{
	if (west(u,s))
	{
		
		for (int i = 10; i < 20; ++i)//rows
		{
			for (int j = 0; j < 2; ++j)//cols
			{
				if (s.things[i][j + 26].unit == UnitType::CROWN) return i;//return the row that the king is in
			}
		}
		
	}
	else
	{
		for (int i = 10; i < 20; ++i)//rows
		{
			for (int j = 0; j < 2; ++j)//cols
			{
				if (s.things[i][j + 2].unit == UnitType::CROWN) return i;
			}
		}
		
	}
	return 0;
}

lionheart::Action lionheart::CameronSwain::Destination(Unit const& u, SituationReport s,Plan p, lionheart::CameronSwain::Location l)
{
	int n=29;
	
	if (KingInBack(u, s) != 0)
	{
		int row = KingInBack(u, s);
		n = 29;
		if (p.movesTo(row, n) < 1)
		{
			if (s.things[row][u.getLocation().col - 3].type == lionheart::SituationReport::ThingType::ENEMY){
				attack({ row, u.getLocation().col - 3 });
			}
			else attack({ row, u.getLocation().col - 2 });
			if (west(u,s)) return turn(Direction::WEST);
			else return turn(Direction::EAST);
		}
	}
	if (KingInBack(u, s) == 0)//Getting archers to turn once they reach the king's spot
	{
		int row = KingInFront(u, s);
		n = 20;
		if (p.movesTo(row, n) < 1)
		{
			if (s.things[row][u.getLocation().col +3].type == lionheart::SituationReport::ThingType::ENEMY){
				attack({ row, u.getLocation().col + 3 });
			}
			else attack({ row, u.getLocation().col+2 });
			if (west(u,s)) return turn(Direction::EAST);
			else return turn(Direction::WEST);
		}
	}
	if (west(u, s))//since I can't use my protectBase function as I wanted to, i'm just sticking it here.
	{
		for (int i = 10; i < 20; ++i)//rows
		{
			for (int j = 2; j < 8; ++j)//cols
			{
				if (u.getLocation().col<8 && s.things[i][j].type == lionheart::SituationReport::ThingType::ENEMY) return p.attackEnemy();
			}
		}

	}
	else
	{
		for (int i = 10; i < 20; ++i)//rows
		{
			for (int j = 22; j < 28; ++j)//cols
			{
				if (u.getLocation().col> 21 && s.things[i][j].type == lionheart::SituationReport::ThingType::ENEMY) return p.attackEnemy();
			}
		}

	}//end of protect base function
	
	if (l == TOP && u.getType() == KNIGHT && u.getLocation().col>22) { Act[u.getId()] = p.moveToEnemyCrown(); return Act[u.getId()]; }
	if (l == TOP && u.getType() == INFANTRY && u.getLocation().col>22) { Act[u.getId()] = p.attackEnemy(); return Act[u.getId()]; }
	if (l == TOP && u.getType() == ARCHER && u.getLocation().col>23) { Act[u.getId()] = p.attackEnemy()/*p.moveToLocation(row, n)*/; return Act[u.getId()]; }
	if (l == TOP && u.getLocation().col<15&&u.getLocation().col>=9) Act[u.getId()] = p.moveToLocation(6, 25);
	if (l == TOP && u.getLocation().col < 9) Act[u.getId()] = p.attackEnemy();
	 
	if (l == BOTTOM && u.getType() == KNIGHT && u.getLocation().col>22){ Act[u.getId()] = p.moveToEnemyCrown(); return Act[u.getId()]; }
	if (l == BOTTOM && u.getType() == INFANTRY && u.getLocation().col>22){ Act[u.getId()] = p.attackEnemy(); return Act[u.getId()]; }
	if (l == BOTTOM && u.getType() == ARCHER && u.getLocation().col>23) { Act[u.getId()] = p.attackEnemy()/*p.moveToLocation(row, n)*/; return Act[u.getId()]; }
	if (l == BOTTOM && u.getLocation().col<15&&u.getLocation().col>=9) Act[u.getId()] = p.moveToLocation(23, 25);
	if (l == BOTTOM && u.getLocation().col < 9) Act[u.getId()] = p.attackEnemy();
	//TODO create an "if westside" statement for these locations, in case you're put on the east side
	return Act[u.getId()];
	
	
}
int
lionheart::CameronSwain::EnemyNear(Unit const & u, SituationReport s, int row, int col, Direction enemyFacing)//checking for infantry in a given direction
{
	if ((s.things[u.getLocation().row+row][u.getLocation().col+col].type == lionheart::SituationReport::ThingType::ENEMY) && (s.things[u.getLocation().row+row][u.getLocation().col + col].direction == enemyFacing)) return 1;
	else return 0;
	
}

int
lionheart::CameronSwain::ArcherNear(Unit const & u, SituationReport s,int row, int col)
{
	if ((s.things[u.getLocation().row+row][u.getLocation().col +col].type == lionheart::SituationReport::ThingType::ENEMY) && (s.things[u.getLocation().row+row][u.getLocation().col +col].direction == Direction::WEST)) return 1;
	if ((s.things[u.getLocation().row + row][u.getLocation().col + col].type == lionheart::SituationReport::ThingType::ENEMY) && (s.things[u.getLocation().row + row][u.getLocation().col + col].direction == Direction::EAST)) return 2;
	if ((s.things[u.getLocation().row + row][u.getLocation().col + col].type == lionheart::SituationReport::ThingType::ENEMY) && (s.things[u.getLocation().row + row][u.getLocation().col + col].direction == Direction::NORTH)) return 3;
	if ((s.things[u.getLocation().row + row][u.getLocation().col + col].type == lionheart::SituationReport::ThingType::ENEMY) && (s.things[u.getLocation().row + row][u.getLocation().col + col].direction == Direction::SOUTH)) return 4;
	else return 0;


}
  lionheart::Action
	  lionheart::CameronSwain::recommendAction(Unit const & u, SituationReport s, Plan p)
  {
	  /*Fill this out with the behavior you want for your units.  Without changes
	   * your units will just wait to be defeated.  Feel free to look at the other provided players for ideas on how to get certain behavior*/
	  /*enum dest
	  {
		  TOP,
		  BOTTOM,
		  BACKSIDE,
	  };
	  auto movement = Act[u.getId()];
	  if (Act == TOP)
	  {
		  Act[u.getId()]
	  }
	 */


	  if (p.hasAttack()) return p.attackEnemy();
	  switch (u.getId())
	  {
	  case 0: //the crown evading different types of units
	  {if (s.turns == 1){
		  if (west(u,s)) return turn(Direction::WEST);
		  else  
		  return turn(Direction::EAST);
	  }
	  if (s.turns == 10)return move(1);
	  if (s.turns == 11) return turn(Direction::SOUTH);
	  if (s.turns == 12) return move(3);
	  if (s.turns == 40) return wait();
	  if (s.turns < 50) return p.moveToLocation(15, 2);
		/*  if ((ArcherNear(u, s, 0, 3) == 1) || (ArcherNear(u, s, 1, 3) == 1) || (ArcherNear(u, s, -1, 3) == 1) || (ArcherNear(u, s, 0, 4) == 1) || (ArcherNear(u, s, 1, 4) == 1) || (ArcherNear(u, s, -1, 4) == 1))
		  {
			  if (u.getFacing() == Direction::EAST)
			  {
				  if (std::rand() % 2 == 1)
					  return turn(Direction::NORTH);
				  else return turn(Direction::SOUTH);
			  }
			  return move(5);
		  }
		  if ((ArcherNear(u, s, 0, -3) == 1) || (ArcherNear(u, s, 1, -3) == 1) || (ArcherNear(u, s, -1, -3) == 1) || (ArcherNear(u, s, 0, -4) == 1) || (ArcherNear(u, s, 1, -4) == 1) || (ArcherNear(u, s, -1, -4) == 1))
		  {
			  if (u.getFacing() == Direction::WEST)
			  {
				  if (std::rand() % 2 == 1)
					  return turn(Direction::NORTH);
				  else return turn(Direction::SOUTH);
			  }
			  return move(5);
		  }
		  if ((ArcherNear(u, s, 3, 0) == 1) || (ArcherNear(u, s, 3, 1) == 1) || (ArcherNear(u, s, 3, -1) == 1) || (ArcherNear(u, s, 4, 0) == 1) || (ArcherNear(u, s, 4, 1) == 1) || (ArcherNear(u, s, 4, -1) == 1))
		  {
			  if (u.getFacing() == Direction::SOUTH)
			  {
				  if (std::rand() % 2 == 1)
					  return turn(Direction::EAST);
				  else return turn(Direction::WEST);
			  }
			  return move(5);
		  }
		  if ((ArcherNear(u, s, -3, 0) == 1) || (ArcherNear(u, s, -3, 1) == 1) || (ArcherNear(u, s, -3, -1) == 1) || (ArcherNear(u, s, -4, 0) == 1) || (ArcherNear(u, s, -4, 1) == 1) || (ArcherNear(u, s, -4, -1) == 1))
		  {
			  if (u.getFacing() == Direction::NORTH)
			  {
				  if (std::rand() % 2 == 1)
					  return turn(Direction::EAST);
				  else return turn(Direction::WEST);
			  }
			  return move(5);
		  }
		  if (EnemyNear(u, s,0,2,Direction::WEST) == 1)//if enemy is in the east facing west, and you're facing east(facing them), then turn , and get ready to run!
		  {
			  if (u.getFacing() == Direction::EAST)
			  {
				  if (std::rand() % 2 == 1)
					  return turn(Direction::NORTH);
				  else return turn(Direction::SOUTH);
			  }
			  return move(2);
		  }
		  if (EnemyNear(u, s,0,-2,Direction::EAST) == 1)
		  {
			  if (u.getFacing() == Direction::WEST)
			  {
				  if (std::rand() % 2 == 1)
					  return turn(Direction::NORTH);
				  else return turn(Direction::SOUTH);
			  }
			  return move(2);
		  }
		  if (EnemyNear(u, s,2,0,Direction::NORTH) ==1)
		  {
			  if (u.getFacing() == Direction::SOUTH)
			  {
				  if (std::rand() % 2 == 1)
					  return turn(Direction::EAST);
				  else return turn(Direction::WEST);
			  }
			  return move(2);
		  }
		  if (EnemyNear(u, s,-2,0,Direction::SOUTH) == 1)
		  {
			  if (u.getFacing() == Direction::NORTH)
			  {
				  if (std::rand() % 2 == 1)
					  return turn(Direction::EAST);
				  else return turn(Direction::WEST);
			  }
			  return move(2);
		  }*/
		  
	  

	  else return wait();

	  case 1:{if (s.turns == 1) return turn(Direction::NORTH);//Knight 2
		  if (s.turns < 50) return wait();
		  else return p.attackEnemy(); } //Destination(u,s,p,TOP); }
	  
	  case 2:{if (s.turns == 1) return turn(Direction::NORTH);
		  if (s.turns < 20) return wait();
		  else return p.attackEnemy(); }
	  case 3:{if (s.turns == 1) return turn(Direction::SOUTH);
		  if (s.turns < 20) return wait();
		  else return p.attackEnemy(); }
		 
	  case 4:
	  {
		  if (s.turns == 1) return turn(Direction::SOUTH);
		  if (s.turns < 30) return wait();
		  else return p.moveToEnemyCrown();// Destination(u, s, p, BOTTOM);
		  
	  }

	  case 5: {if (s.turns < 60) return wait();
			  else return p.attackEnemy(); }// Destination(u, s, p, TOP); }
	  case 6:{if (s.turns < 60) return wait();
			 else return p.attackEnemy(); }// Destination(u, s, p, BOTTOM); }
		  
	  case 7:{if (s.turns == 1) return turn(Direction::WEST); //archer 8
		  if (s.turns < 50) return wait();
		  return p.attackEnemy();// Destination(u, s, p, TOP);
	  }
	  case 8:
	  case 9:{if (s.turns == 1) return turn(Direction::NORTH);//archer 10
		  if (s.turns < 50) return wait();
		  return p.attackEnemy();// Destination(u, s, p, TOP);
		 
	  }
	  case 10:{if (s.turns < 60) return wait();//Archer 11
			  else return p.attackEnemy(); }// Destination(u,s,p,TOP); }
	  case 11:{if (s.turns < 50) return wait();//Archer 12
			  else return p.attackEnemy(); }//Destination(u,s,p,TOP); }
	  case 12:{if (s.turns < 60) return wait();//Archer 13
			  else return p.attackEnemy(); }//Destination(u,s,p,BOTTOM); }
	  case 13:{if (s.turns == 1) return turn(Direction::SOUTH);
		  if (s.turns < 60) return wait();
		  else return p.attackEnemy(); }//Destination(u,s,p,BOTTOM); }
	  
	  case 14:{if (s.turns < 50) return wait(); //Archer 15
			  else return p.attackEnemy(); }//Destination(u,s,p,BOTTOM); }
		  
	  case 30:{if (s.turns < 40) return wait();//Infantry 16
			  else return p.attackEnemy(); }  
	  case 31:{if (s.turns < 40) return wait();
			  else return p.attackEnemy(); }//Destination(u, s, p, TOP); }
	  case 32:{if (s.turns < 40) return wait();
			  else return p.attackEnemy(); }//Destination(u, s, p, TOP); }
	  case 33:{if (s.turns == 1) //infantry 19
	  {
		  if (west(u,s)) return turn(Direction::WEST);
		  else return turn(Direction::EAST);
	  }
		  if (s.turns < 40) return wait();
		  else return p.attackEnemy(); }//Destination(u, s, p, TOP); }

	  case 34:
	  case 35:
	  case 36:
	  case 37:{if (s.turns == 1) return turn(Direction::SOUTH);
		  if (s.turns < 30) return wait();
		  else return p.attackEnemy(); }//Destination(u, s, p, BOTTOM); }

	  case 38:{if (s.turns == 1) return turn(Direction::NORTH);//infantry 24
		  if (s.turns < 15) return wait();
		  else return p.attackEnemy(); }//Destination(u, s, p, TOP); }

	  case 39:{//infantry 25
		  if (s.turns < 30) return wait();
		  else return p.attackEnemy(); }
	  case 40:{
		  //infantry 26
		  if (s.turns < 30) return wait();
		  else return p.attackEnemy(); }
	  case 41:{if (s.turns == 1) return turn(Direction::SOUTH);//infantry 27
		  if (s.turns < 30) return wait();
		  else return p.attackEnemy(); }//Destination(u, s, p, BOTTOM); }

	  case 42:{if (s.turns == 1) return turn(Direction::NORTH);
		  if (s.turns < 20) return wait();
			  else return p.attackEnemy(); }
	  case 43:{if (s.turns < 10) return wait();
		  else return p.attackEnemy(); }

	  case 44:{if (s.turns < 30) return wait();
		  else return p.moveToEnemyCrown(); }
	

	  default:
		  break;
	  }
		  return p.moveToEnemyCrown();
	  }
		  return p.attackEnemy();
	  }
	  
	  lionheart::Blazon lionheart::CameronSwain::getBlazon()
{
  /*Return your blazon here.  In case of conflicts preference will be given to
   * the students that have registered their blazons in class.*/
  return { Color::AZURE, Color::VERT, Style::PER_BEND, "mmMMMmmm Broccoli" };
}
