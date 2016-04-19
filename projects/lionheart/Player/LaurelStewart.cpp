
#include "LaurelStewart.hpp"
//NOTE: Borrowed heavily from BrandonSmith and WildBoard
namespace
{
int id  =0;
bool west =true;
}

// checks for enemy archers
  bool check4archer(int r, int c, struct lionheart::SituationReport report)
  {
    if ((report.things[r][c].unit == lionheart::UnitType::ARCHER) &&
        (report.things[r][c].type == lionheart::SituationReport::ENEMY))
    {
      return true;
    }
    else
      return false;
  }
// is there an archer by my back wall
  bool mykingstupid(struct lionheart::SituationReport report) // this function
                                                              // helps if
                                                              // someone else
                                                              // knows how to
                                                              // shoot over
                                                              // walls
  {
    for (auto j = 8; j < 21; ++j)
    {
      if ((west) && (check4archer(j, 0, report)))
      {
        return true;
      }
      if ((!west) && (check4archer(j, 29, report)))
      {
        return true;
      }
    }
    for (auto i = 1; i < 4; ++i)
    {
      if ((west) && (check4archer(8, i, report)))
      {
        return true;
      }
      if ((!west) && (check4archer(8, (i + 25), report)))
      {
        return true;
      }
      if ((west) && (check4archer(21, i, report)))
      {
        return true;
      }
      if ((!west) && (check4archer(21, (i + 25), report)))
      {
        return true;
      }
    }
    return false;
  }
lionheart::Placement lionheart::LaurelStewart::placeUnit(UnitType,
                                                       StartBox const& box,
                                                       SituationReport report)
{
 ++id;
  if (id > 30) id = 1; // resets id for each new game
  auto westSide = (box.minCol < static_cast<int>(report.things[0].size() / 2));
  if (westSide)
  {
    west = true;
    switch (id)
    {
    // CROWN
    case 1:
      return {14, 2};
    // KNIGHTS
    case 2:
      return {11, 4};
    case 3:
      return {14, 6};
    case 4:
      return {18, 4};
    case 5:
      return {15, 6};
    case 6:
      return {12, 4};
    case 7:
      return {17, 4};
    // ARCHERS
    case 8:
      return {11, 3};
    case 9:
      return {11, 5};
    case 10:
      return {13, 7};
    case 11:
      return {12, 7};
    case 12:
      return {17, 7};
    case 13:
      return {16, 7};
    case 14:
      return {18, 3};
    case 15:
      return {18, 5};
    // INFANTRY
    case 16:
      return {10, 3};
    case 17:
      return {10, 5};
    case 18:
      return {10, 4};
    case 19:
      return {19, 3};
    case 20:
      return {19, 5};
    case 21:
      return {19, 4};
    case 22:
      return {12, 3};
    case 23:
      return {12, 5};

    case 24:
      return {13, 6};
    case 25:
      return {14, 7};
    case 26:
      return {15, 7};
    case 27:
      return {16, 6};
    case 28:
      return {17, 5};
    case 29:
      return {17, 3};
    case 30:
      return {13, 3};
    }
  }
  else
  {
    west = false;
    switch (id)
    {
    // CROWN
    case 1:
      return {14, 27};
    // KNIGHTS
    case 2:
      return {11, 25};
    case 3:
      return {14, 22};
    case 4:
      return {18, 25};
    case 5:
      return {15, 22};
    case 6:
      return {12, 25};
    case 7:
      return {17, 25};
    // ARCHERS
    case 8:
      return {11, 24};
    case 9:
      return {11, 26};
    case 10:
      return {13, 22};
    case 11:
      return {12, 22};
    case 12:
      return {17, 22};
    case 13:
      return {16, 22};
    case 14:
      return {18, 26};
    case 15:
      return {18, 24};
    // INFANTRY
    case 16:
      return {10, 24};
    case 17:
      return {10, 26};
    case 18:
      return {10, 25};
    case 19:
      return {19, 24};
    case 20:
      return {19, 26};
    case 21:
      return {19, 25};
    case 22:
      return {12, 26};
    case 23:
      return {12, 24};

    case 24:
      return {13, 23};
    case 25:
      return {14, 23};
    case 26:
      return {15, 23};
    case 27:
      return {16, 23};
    case 28:
      return {17, 26};
    case 29:
      return {17, 24};
    case 30:
      return {13, 26};
    }
  }
  return {0, 0};
}

lionheart::Action lionheart::LaurelStewart::recommendAction(Unit const& u,
                                                          SituationReport report,
                                                          Plan p)
{
  auto loc = u.getLocation();
  auto row = loc.row;
  auto col = loc.col;

  if (u.getType() == CROWN) 
     {
	if (p.hasAttack())
	   {
	      return p.attackEnemy();
	   }
	   if (mykingstupid(report))
	      {
	        if (west)
	           {

	      	     if ((row != 14) || (col != 4))
		        {
		         return p.moveToLocation(14, 4);
		        }
	           }
	       if (!west)
	          {
		  
		   if ((row != 14) || (col != 25))
		      {
		       return p.moveToLocation(14, 25);
		      }
	          }
	      }
        return wait();
      }
      if(u.getType() == KNIGHT)
      {
        if(p.hasAttack())
        {
          return p.attackEnemy();
        }
        return p.moveToEnemyCrown();
      }
      if(p.hasAttack())
	{
	  return p.attackEnemy();
	}
	return p.moveToEnemyCrown();
}
lionheart::Blazon lionheart::LaurelStewart::getBlazon()
{
//Figure out colors
  return {Color::SABLE, Color::AZURE, Style::BEND, "Laurel Stewart"};
}
