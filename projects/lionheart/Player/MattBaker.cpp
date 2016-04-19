#include "MattBaker.hpp"

// (Y,X)
// (ROWS, COLS)
lionheart::Placement lionheart::MattBaker::placeUnit(UnitType, StartBox const &box, SituationReport r)
{
  ++id;
  turnNumber = 0;
  westSide = (box.minCol < static_cast<int>(r.things[0].size() / 2));
  if(westSide)
  {
    switch(id)
    {
    // CROWN
    case 1: return {14,2};
    // KNIGHTS
    case 2: return {13,4};
    case 3: return {11,4};
    case 4: return {12,4};
    case 5: return {17,4};
    case 6: return {18,4};
    case 7: return {16,4};
    // ARCHERS
    case 8: return {10,6};
    case 9: return {10,5};
    case 10:return {13,7};
    case 11:return {12,7};
    case 12:return {19,5};
    case 13:return {16,7};
    case 14: return {19,6};
    case 15: return {17,7};
    // INFANTRY
    case 16: return {14,6};
    case 17: return {14,7};
    case 18: return {15,6};
    case 19: return {15,7};
    case 20: return {10,4};
    case 21: return {14,5};
    case 22: return {15,5};
    case 23: return {16,3};
    case 24: return {15,2};
    case 25: return {15,3};
    case 26: return {13,2};
    case 27: return {13,3};
    case 28: return {19,4};
    case 29: return {13,5};
    case 30: id=0; return {16,5};
    }
  }
  else
  {
    switch (id)
    {
    // CROWN
    case 1: return {14, 27};
    // KNIGHTS
    case 2: return {13,25};
    case 3: return {11,25};
    case 4: return {12,25};
    case 5: return {17,25};
    case 6: return {18,25};
    case 7: return {16,25};
    // ARCHERS
    case 8: return {10,23};
    case 9: return {10,24};
    case 10:return {13,22};
    case 11:return {12,22};
    case 12:return {19,23};
    case 13:return {16,22};
    case 14: return {17,22};
    case 15: return {19,24};
    // INFANTRY
    case 16: return {14,23};
    case 17: return {14,22};
    case 18: return {15,23};
    case 19: return {15,22};
    case 20: return {10,25};
    case 21: return {14,24};
    case 22: return {15,25};
    case 23: return {19,25};
    case 24: return {15,27};
    case 25: return {15,26};
    case 26: return {13,27};
    case 27: return {13,26};
    case 28: return {16,26};
    case 29: return {13,24};
    case 30: id=0; return {16,24};
    }
  }
  return {0,0};
}

bool lionheart::MattBaker::checkBehindWall(int x, int y, SituationReport r)
{
  if ((r.things[x][y].unit == lionheart::UnitType::ARCHER) && (r.things[x][y].type == lionheart::SituationReport::ENEMY))
  {
    return true;
  }
  return false;
}

bool lionheart::MattBaker::enemyInMyCastle(SituationReport r)
{
  for (int i = 0; i < 10; ++i)
  {
    if (westSide)
    {
      for (int j = 0; j < 6; ++j)
      {
        if (r.things[i + 10][j + 2].type == lionheart::SituationReport::ENEMY)
          return true;
      }
    }
    else
    {
      for (int j = 0; j < 6; ++j)
      {
        if (r.things[i + 10][j + 22].type == lionheart::SituationReport::ENEMY)
        {
          return true;
        }
      }
    }
  }
  return false;
}

// (Y,X)
// (ROWS, COLS)
lionheart::Action lionheart::MattBaker::recommendAction(Unit const &u, SituationReport r, Plan p)
{
  ++turnNumber;
  if (turnNumber <= 30)
  {
    if (u.getId() == 0)
    {
      return turn(Direction::SOUTH);
    }
    if(u.getLocation().row == 10 || u.getLocation().row == 11)
      return turn(Direction::NORTH);
    else if(u.getLocation().row == 19 || u.getLocation().row == 18)
      return turn(Direction::SOUTH);
  }
  
  if (p.hasAttack())
  {
    return p.attackEnemy();
  }
  if (u.getId() != 0)
  {
    if (enemyInMyCastle(r))
    {
      if (westSide && u.getLocation().col < 10)
        return p.attackEnemy();
      else if (!westSide && u.getLocation().col > 20)
        return p.attackEnemy();
    }
    else if ((turnNumber/30) < 45)
    {
      return wait();
    }
  }
  
  switch(u.getId())
  {
    //CROWN
    case 0:
      //Move away from back archers
      for (int j = 8; j < 21; ++j)
      {
        if (westSide && checkBehindWall(j, 0, r))
        {
          return p.moveToLocation(14, 4);
        }
        if (!westSide && checkBehindWall(j, 29, r))
        {
          return p.moveToLocation(14, 25);
        }
      }
      for (int i = 1; i < 4; ++i)
      {
        if (westSide && checkBehindWall(8, i, r))
        {
          return p.moveToLocation(14, 4);
        }
        if (!westSide && checkBehindWall(8, (i + 25), r))
        {
          return p.moveToLocation(14, 25);
        }
        if (westSide && checkBehindWall(21, i, r))
        {
          return p.moveToLocation(14, 4);
        }
        if (!westSide && checkBehindWall(21, (i + 25), r))
        {
          return p.moveToLocation(14, 25);
        }
      }
      
      // run away from enemies
      if (p.movesToEnemy() <= 2)
      {
        if (westSide)
        {
          if (u.getLocation().row == 19 && u.getLocation().col == 2)
            kingRanAway = true;
          if (!kingRanAway)
            return p.moveToLocation(19, 2);
          else
            return p.moveToLocation(29, 0);
          
        }
        else
        {
          if (u.getLocation().row == 19 && u.getLocation().col == 27)
            kingRanAway = true;
          if (!kingRanAway)
            return p.moveToLocation(19, 27);
          else
            return p.moveToLocation(29, 29);
        }
      }
      
      // Return to back if no archers
      if (u.getLocation().row == 14 && u.getLocation().col == 4)
        return p.moveToLocation(14, 2);
      if (u.getLocation().row == 14 && u.getLocation().col == 25)
        return p.moveToLocation(14, 27);
      
      return wait();
      
    // KNIGHTS
    case 1:
    case 2:
    case 3:
      if(p.movesToEnemy() > 5)
      {
        return p.moveToLocation(9, 15);
      }
      return p.moveToEnemyCrown();
    case 4:
    case 5:
    case 6:
      if(p.movesToEnemy() > 5)
      {
        return p.moveToLocation(18,15);
      }
      return p.moveToEnemyCrown();
      
    // ARCHERS
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
      if (westSide && u.getLocation().col > 16)
        return p.moveToEnemyCrown();
      else if (!westSide && u.getLocation().col < 13)
        return p.moveToEnemyCrown();
      else
        return p.attackEnemy();
      
    // INFANTRY
    case 19: // outer infantry go for crown
    case 22:
      return p.moveToEnemyCrown();
    case 15:
    case 16:
    case 17:
    case 18:
    case 20:
    case 21:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
      if (westSide && u.getLocation().col > 17)
        return p.moveToEnemyCrown();
      else if (!westSide && u.getLocation().col < 12)
        return p.moveToEnemyCrown();
      else
        return p.attackEnemy();
      
    default:
      break;
  }
  return p.attackEnemy();
}

lionheart::Blazon lionheart::MattBaker::getBlazon()
{
  return { Color::GULES, Color::AZURE, Style::QUARTERLY, "MattBaker" };
}
