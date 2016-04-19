#include "ShemHale.hpp"

/******** MOVES *****************************************************

Action attackEnemy() const;
Action moveToEnemy() const;
Action moveToEnemyCrown() const;
Action moveToAllyCrown() const;
Action moveToLocation(int row,int col) const;
int movesTo(int row,int col) const;
int movesToEnemy() const;
int movesToEnemyCrown() const;
int movesToAllyCrown() const;
bool hasAttack() const {return inRange;}

********************************************************************/

/******** IDs *******************************************************
1 = Crown

2-7 = Knights

8-15 = Archers

16-30 = Infantry
********************************************************************/

/******* GLOBALS ***************************************************/
namespace {
auto mapWidth = 30;
auto mapHeight = 30;
auto id = 0;
auto west = false;
lionheart::Map::Location curLoc;
std::vector<lionheart::Placement> lineOfSight;
lionheart::Placement enemyKing;
}


/******* FUNCTIONS *************************************************/
bool lionheart::ShemHale::canArcherBait(lionheart::Map::Location curLoc, lionheart::Direction curDir, lionheart::SituationReport report)
{
  int startRow;
  int startCol;
  int row;
  int col;
  
  if(curDir == lionheart::Direction::NORTH)
  {
    startRow = curLoc.row-3;
    startCol = curLoc.col-1;
    row = curLoc.row;
    col = curLoc.col+2;
  }
  else if(curDir == lionheart::Direction::EAST)
  {
    startRow = curLoc.row-1;
    startCol = curLoc.col+1;
    row = curLoc.row+2;
    col = curLoc.col+4;
  }
  else if(curDir == lionheart::Direction::SOUTH)
  {
    startRow = curLoc.row+1;
    startCol = curLoc.col-1;
    row = curLoc.row+4;
    col = curLoc.col+2;
  }
  else
  {
    startRow = curLoc.row-1;
    startCol = curLoc.col-3;
    row = curLoc.row+2;
    col = curLoc.col;
  }
  

  auto areThereEnemies = false;

  for(auto i=startRow; i<row; ++i)
  {
    for(auto j=startCol; j<col; ++j)
    {
      if(report.things[i][j].type == lionheart::SituationReport::ENEMY)
      {
	areThereEnemies = true;
      }
    }
  }

  if(!areThereEnemies)
  {
    auto enemiesOutOfReach = false;

    for(auto j=startCol; j<col; ++j)
      if(report.things[startRow-1][j].type == lionheart::SituationReport::ENEMY)
        enemiesOutOfReach = true; 

    if(enemiesOutOfReach)
      return true;
  }

  return false;
}


bool lionheart::ShemHale::canHitEnemyLeft(lionheart::Map::Location curLoc, lionheart::Direction curDir, lionheart::SituationReport report)
{
  int i;
  int j;
  
  if(curDir == lionheart::Direction::NORTH)
  {
    i = curLoc.row;
    j = curLoc.col-1;
  }
  else if(curDir == lionheart::Direction::EAST)
  {
    i = curLoc.row-1;
    j = curLoc.col;
  }
  else if(curDir == lionheart::Direction::SOUTH)
  {
    i = curLoc.row;
    j = curLoc.col+1;
  }
  else
  {
    i = curLoc.row+1;
    j = curLoc.col;
  }
  

  if(report.things[i][j].type == lionheart::SituationReport::ENEMY)
    return true;

  return false;
}


bool lionheart::ShemHale::canHitEnemyRight(lionheart::Map::Location curLoc, lionheart::Direction curDir, lionheart::SituationReport report)
{
  int i;
  int j;
  
  if(curDir == lionheart::Direction::NORTH)
  {
    i = curLoc.row;
    j = curLoc.col+1;
  }
  else if(curDir == lionheart::Direction::EAST)
  {
    i = curLoc.row+1;
    j = curLoc.col;
  }
  else if(curDir == lionheart::Direction::SOUTH)
  {
    i = curLoc.row;
    j = curLoc.col-1;
  }
  else
  {
    i = curLoc.row-1;
    j = curLoc.col;
  }
  

  if(report.things[i][j].type == lionheart::SituationReport::ENEMY)
    return true;

  return false;
}




bool lionheart::ShemHale::canFlank(lionheart::Direction curDir, lionheart::SituationReport report)
{
  auto sq2 = report.things[lineOfSight[1].row][lineOfSight[1].col];
  auto sq1 = report.things[lineOfSight[0].row][lineOfSight[0].col];

  if(sq2.type == lionheart::SituationReport::ENEMY && sq1.type == lionheart::SituationReport::SPACE)
  {
    if(curDir == lionheart::Direction::NORTH)
      return (sq2.direction != lionheart::Direction::SOUTH);
    else if(curDir == lionheart::Direction::EAST)
      return (sq2.direction != lionheart::Direction::WEST);
    else if(curDir == lionheart::Direction::SOUTH)
      return (sq2.direction != lionheart::Direction::NORTH);
    else if(curDir == lionheart::Direction::WEST)
      return (sq2.direction != lionheart::Direction::EAST);
  }

  return false;
}

lionheart::Action lionheart::ShemHale::moveForward(lionheart::Map::Location curLoc, lionheart::Direction curDir, lionheart::Plan p)
{
  if(curDir == lionheart::Direction::NORTH)
    return p.moveToLocation(curLoc.row-1,curLoc.col);
  else if(curDir == lionheart::Direction::EAST)
    return p.moveToLocation(curLoc.row,curLoc.col+1);
  else if(curDir == lionheart::Direction::SOUTH)
    return p.moveToLocation(curLoc.row+1,curLoc.col);
  else
    return p.moveToLocation(curLoc.row,curLoc.col-1);
}

bool lionheart::ShemHale::canArcherShootEnemyLeft(lionheart::Map::Location curLoc, lionheart::Direction curDir, lionheart::SituationReport report)
{
  int startRow;
  int startCol;
  int row;
  int col;
  
  if(curDir == lionheart::Direction::NORTH)
  {
    startRow = curLoc.row-1;
    startCol = curLoc.col-3;
    row = curLoc.row+2;
    col = curLoc.col;
  }
  else if(curDir == lionheart::Direction::EAST)
  {
    startRow = curLoc.row-3;
    startCol = curLoc.col-1;
    row = curLoc.row;
    col = curLoc.col+2;
  }
  else if(curDir == lionheart::Direction::SOUTH)
  {
    startRow = curLoc.row-1;
    startCol = curLoc.col+1;
    row = curLoc.row+2;
    col = curLoc.col+4;
  }
  else
  {
    startRow = curLoc.row+1;
    startCol = curLoc.col-1;
    row = curLoc.row+4;
    col = curLoc.col+2;
  }
  

  for(auto i=startRow; i<row; ++i)
  {
    for(auto j=startCol; j<col; ++j)
    {
      if(report.things[i][j].type == lionheart::SituationReport::ENEMY)
	return true;
    }
  }

  return false;
}


bool lionheart::ShemHale::canArcherShootEnemyRight(lionheart::Map::Location curLoc, lionheart::Direction curDir, lionheart::SituationReport report)
{
  int startRow;
  int startCol;
  int row;
  int col;
  
  if(curDir == lionheart::Direction::NORTH)
  {
    startRow = curLoc.row-1;
    startCol = curLoc.col+1;
    row = curLoc.row+2;
    col = curLoc.col+4;
  }
  else if(curDir == lionheart::Direction::EAST)
  {
    startRow = curLoc.row+1;
    startCol = curLoc.col-1;
    row = curLoc.row+4;
    col = curLoc.col+2;
  }
  else if(curDir == lionheart::Direction::SOUTH)
  {
    startRow = curLoc.row-1;
    startCol = curLoc.col-3;
    row = curLoc.row+2;
    col = curLoc.col;
  }
  else
  {
    startRow = curLoc.row-3;
    startCol = curLoc.col-1;
    row = curLoc.row;
    col = curLoc.col+2;
  }
  

  for(auto i=startRow; i<row; ++i)
  {
    for(auto j=startCol; j<col; ++j)
    {
      if(report.things[i][j].type == lionheart::SituationReport::ENEMY)
	return true;
    }
  }

  return false;
}


bool lionheart::ShemHale::canArcherShootKing(lionheart::Map::Location curLoc, lionheart::Direction curDir, lionheart::SituationReport report)
{
  int startRow;
  int startCol;
  int row;
  int col;
  
  if(curDir == lionheart::Direction::NORTH)
  {
    startRow = curLoc.row-3;
    startCol = curLoc.col-1;
    row = curLoc.row;
    col = curLoc.col+2;
  }
  else if(curDir == lionheart::Direction::EAST)
  {
    startRow = curLoc.row-1;
    startCol = curLoc.col+1;
    row = curLoc.row+2;
    col = curLoc.col+4;
  }
  else if(curDir == lionheart::Direction::SOUTH)
  {
    startRow = curLoc.row+1;
    startCol = curLoc.col-1;
    row = curLoc.row+4;
    col = curLoc.col+2;
  }
  else
  {
    startRow = curLoc.row-1;
    startCol = curLoc.col-3;
    row = curLoc.row+2;
    col = curLoc.col;
  }
  

  for(auto i=startRow; i<row; ++i)
  {
    for(auto j=startCol; j<col; ++j)
    {
      if(report.things[i][j].unit == lionheart::UnitType::CROWN
	&& report.things[i][j].type == lionheart::SituationReport::ENEMY)
	return true;
    }
  }

  return false;
}


lionheart::Action lionheart::ShemHale::turnRight(lionheart::Direction curDir)
{
  if(curDir == lionheart::Direction::NORTH)
    return turn(lionheart::Direction::EAST);
  else if(curDir == lionheart::Direction::EAST)
    return turn(lionheart::Direction::SOUTH);
  else if(curDir == lionheart::Direction::SOUTH)
    return turn(lionheart::Direction::WEST);
  else
    return turn(lionheart::Direction::NORTH);
  
}

bool lionheart::ShemHale::canArcherShootKingRight(lionheart::Map::Location curLoc, lionheart::Direction curDir, lionheart::SituationReport report)
{
  int startRow;
  int startCol;
  int row;
  int col;
  
  if(curDir == lionheart::Direction::NORTH)
  {
    startRow = curLoc.row-1;
    startCol = curLoc.col+1;
    row = curLoc.row+2;
    col = curLoc.col+4;
  }
  else if(curDir == lionheart::Direction::EAST)
  {
    startRow = curLoc.row+1;
    startCol = curLoc.col-1;
    row = curLoc.row+4;
    col = curLoc.col+2;
  }
  else if(curDir == lionheart::Direction::SOUTH)
  {
    startRow = curLoc.row-1;
    startCol = curLoc.col-3;
    row = curLoc.row+2;
    col = curLoc.col;
  }
  else
  {
    startRow = curLoc.row-3;
    startCol = curLoc.col-1;
    row = curLoc.row;
    col = curLoc.col+2;
  }
  

  for(auto i=startRow; i<row; ++i)
  {
    for(auto j=startCol; j<col; ++j)
    {
      if(report.things[i][j].unit == lionheart::UnitType::CROWN
	&& report.things[i][j].type == lionheart::SituationReport::ENEMY)
	return true;
    }
  }

  return false;
}


lionheart::Action lionheart::ShemHale::turnLeft(lionheart::Direction curDir)
{
  if(curDir == lionheart::Direction::NORTH)
    return turn(lionheart::Direction::WEST);
  else if(curDir == lionheart::Direction::EAST)
    return turn(lionheart::Direction::NORTH);
  else if(curDir == lionheart::Direction::SOUTH)
    return turn(lionheart::Direction::EAST);
  else
    return turn(lionheart::Direction::SOUTH);
  
}

bool lionheart::ShemHale::canArcherShootKingLeft(lionheart::Map::Location curLoc, lionheart::Direction curDir, lionheart::SituationReport report)
{
  int startRow;
  int startCol;
  int row;
  int col;
  
  if(curDir == lionheart::Direction::NORTH)
  {
    startRow = curLoc.row-1;
    startCol = curLoc.col-3;
    row = curLoc.row+2;
    col = curLoc.col;
  }
  else if(curDir == lionheart::Direction::EAST)
  {
    startRow = curLoc.row-3;
    startCol = curLoc.col-1;
    row = curLoc.row;
    col = curLoc.col+2;
  }
  else if(curDir == lionheart::Direction::SOUTH)
  {
    startRow = curLoc.row-1;
    startCol = curLoc.col+1;
    row = curLoc.row+2;
    col = curLoc.col+4;
  }
  else
  {
    startRow = curLoc.row+1;
    startCol = curLoc.col-1;
    row = curLoc.row+4;
    col = curLoc.col+2;
  }
  

  for(auto i=startRow; i<row; ++i)
  {
    for(auto j=startCol; j<col; ++j)
    {
      if(report.things[i][j].unit == lionheart::UnitType::CROWN
        && report.things[i][j].type == lionheart::SituationReport::ENEMY)
        return true;
    }
  }

  return false;
}

void lionheart::ShemHale::checkLineOfSight(int i, lionheart::Map::Location curLoc, lionheart::Direction curDir)
{
  lionheart::Placement placement;
  
  if(curDir == lionheart::Direction::NORTH)
  {
    placement.row = curLoc.row+i;
    placement.col = curLoc.col;
  }
  else if(curDir == lionheart::Direction::EAST)
  {
    placement.row = curLoc.row;
    placement.col = curLoc.col+i;
  }
  else if(curDir == lionheart::Direction::SOUTH)
  {
    placement.row = curLoc.row-i;
    placement.col = curLoc.col;
  }
  else
  {
    placement.row = curLoc.row;
    placement.col = curLoc.col-i;
  }
  
  lineOfSight.push_back(placement);
}

void lionheart::ShemHale::locateEnemyKing(lionheart::SituationReport report)
{
  for(auto i=0; i<mapWidth; ++i)
  {
    for(auto j=0; j<mapHeight; ++j)
    {
      if((report.things[i][j].unit == lionheart::UnitType::CROWN)
	&& (report.things[i][j].type == lionheart::SituationReport::ENEMY)) 
      {
	enemyKing.row = i;
	enemyKing.col = j;
      }
    }
  }
}

void lionheart::ShemHale::update(lionheart::Map::Location curLoc, lionheart::Direction curDir)
{
  while(!lineOfSight.empty())
    lineOfSight.pop_back();

  for(auto i=0; i<5; ++i)
    checkLineOfSight(i, curLoc, curDir);

}



lionheart::Placement lionheart::ShemHale::placeUnit(UnitType,
                                              StartBox const &box,
                                              SituationReport report)
{
  /*Fill this out with instructions on how to place your initial units.  Without
   * changes your units will fill the starting box from top left to bottom right
   * in the order constructed.*/
  ++id;

  // resets for each game
  if (id > 30)
    id = 1;

  west = (box.minCol < static_cast<int>(report.things[0].size() / 2));

  if (west)
  {
    switch (id)
    {
    // CROWN
    case 1:
      return {14, 2};
    // KNIGHTS
    case 2:
      return {14, 4};
    case 3:
      return {14, 5};
    case 4:
      return {15, 4};
    case 5:
      return {15, 5};
    case 6:
      return {10, 4};
    case 7:
      return {19, 4};
    // ARCHERS
    case 8:
      return {11, 7};
    case 9:
      return {12, 7};
    case 10:
      return {13, 7};
    case 11:
      return {14, 7};
    case 12:
      return {15, 7};
    case 13:
      return {16, 7};
    case 14:
      return {17, 7};
    case 15:
      return {18, 7};
    // INFANTRY
    case 16:
      return {10, 2};
    case 17:
      return {10, 3};
    case 18:
      return {11, 2};
    case 19:
      return {11, 3};
    case 20:
      return {19, 2};
    case 21:
      return {19, 3};
    case 22:
      return {18, 2};
    case 23:
      return {18, 3};

    case 24:
      return {11, 4};
    case 25:
      return {11, 5};
    case 26:
      return {12, 4};
    case 27:
      return {12, 5};
    case 28:
      return {12, 6};
    case 29:
      return {18, 4};
    case 30:
      return {18, 5};
    }
  }
  else
  {
    switch (id)
    {
    // CROWN
    case 1:
      return {14, 27};
    // KNIGHTS
    case 2:
      return {14, 24};
    case 3:
      return {14, 25};
    case 4:
      return {15, 24};
    case 5:
      return {15, 25};
    case 6:
      return {10, 25};
    case 7:
      return {19, 25};
    // ARCHERS
    case 8:
      return {11, 22};
    case 9:
      return {12, 22};
    case 10:
      return {13, 22};
    case 11:
      return {14, 22};
    case 12:
      return {15, 22};
    case 13:
      return {16, 22};
    case 14:
      return {17, 22};
    case 15:
      return {18, 22};
    // INFANTRY
    case 16:
      return {10, 27};
    case 17:
      return {10, 26};
    case 18:
      return {11, 27};
    case 19:
      return {11, 26};
    case 20:
      return {19, 27};
    case 21:
      return {19, 26};
    case 22:
      return {18, 27};
    case 23:
      return {18, 26};

    case 24:
      return {11, 25};
    case 25:
      return {11, 24};
    case 26:
      return {12, 25};
    case 27:
      return {12, 24};
    case 28:
      return {12, 23};
    case 29:
      return {18, 25};
    case 30:
      return {18, 24};
    }
  }
  

  /*for (int r = box.minRow; r < box.maxRow; ++r)
    for (int c = box.minCol; c < box.maxCol; ++c)
      if (report.things[r][c].type == SituationReport::SPACE)
        return { r, c };
  */
  
  return { 0, 0 };
}

  lionheart::Action
lionheart::ShemHale::recommendAction(Unit const &u, SituationReport report, Plan p)
{

  auto curLoc = u.getLocation();
  auto curDir = u.getFacing();

  update(curLoc, curDir);

  // find their king
  locateEnemyKing(report);

  // attack
  if( (u.getType() == lionheart::UnitType::ARCHER) && (p.hasAttack())
    && (canArcherShootKing(curLoc,curDir,report)) )
    return attack(enemyKing);
  
  if(p.hasAttack())
    return p.attackEnemy();

  /*if(canFlank(curDir, report))
    return moveForward(curLoc, curDir, p);

  // bait
  if(report.things[lineOfSight[0].row][lineOfSight[0].col].type == lionheart::SituationReport::SPACE
    && report.things[lineOfSight[1].row][lineOfSight[1].col].type == lionheart::SituationReport::ENEMY
    && report.things[lineOfSight[1].row][lineOfSight[1].col].unit != lionheart::UnitType::ARCHER
    && baitTimer < 1)
  {
    ++baitTimer;
    return wait();
  }
  else
    baitTimer = 0;
  */


  if(u.getType() == CROWN)
  {
    if(p.movesToEnemy() < 5)
      return p.moveToEnemyCrown();
    
    return wait();
  }
  if(u.getType() == KNIGHT)
  {
    /*if(canHitEnemyLeft(curLoc,curDir,report))
      return turnLeft(curDir);
    if(canHitEnemyRight(curLoc,curDir,report))
      return turnRight(curDir);

    if( (report.things[curLoc.row][curLoc.col-1].type == lionheart::SituationReport::ALLY)
      && (report.things[curLoc.row][curLoc.col+1].type == lionheart::SituationReport::ALLY)
      && (report.things[curLoc.row+1][curLoc.col].type == lionheart::SituationReport::SPACE) )
      return p.moveToLocation(curLoc.row+1, curLoc.col);
    
    if(p.movesToEnemy() < 5)
      return p.moveToEnemy();
    */
    if(p.movesToAllyCrown() > 7 && p.movesToEnemy() > 6)
      return p.moveToAllyCrown();
    
    return p.moveToEnemy();
  }
  if(u.getType() == ARCHER)
  {
    /*auto kingLeft = canArcherShootKingLeft(curLoc, curDir, report);
    auto kingRight = canArcherShootKingRight(curLoc, curDir, report);
    auto enemyLeft = canArcherShootEnemyLeft(curLoc, curDir, report);
    auto enemyRight = canArcherShootEnemyRight(curLoc, curDir, report);

    if(kingLeft || enemyLeft)
      return turnLeft(curDir);
    if(kingRight || enemyRight)
      return turnRight(curDir);
    
    if(canArcherBait(curLoc, curDir, report))
      return wait();
    */
      
    return p.moveToEnemyCrown();
  }
  if(u.getType() == INFANTRY)
  {
    /*if(canHitEnemyLeft(curLoc,curDir,report))
      return turnLeft(curDir);
    if(canHitEnemyRight(curLoc,curDir,report))
      return turnRight(curDir);
    
    if( (report.things[curLoc.row][curLoc.col-1].type == lionheart::SituationReport::ALLY)
      && (report.things[curLoc.row][curLoc.col+1].type == lionheart::SituationReport::ALLY)
      && (report.things[curLoc.row-1][curLoc.col].type == lionheart::SituationReport::SPACE) )
      return p.moveToLocation(curLoc.row-1, curLoc.col);

    if( (report.things[curLoc.row][curLoc.col-1].type == lionheart::SituationReport::ALLY)
      && (report.things[curLoc.row][curLoc.col+1].type == lionheart::SituationReport::ALLY)
      && (report.things[curLoc.row+1][curLoc.col].type == lionheart::SituationReport::SPACE) )
      return p.moveToLocation(curLoc.row+1, curLoc.col);
    */
    
    //if(p.movesToEnemyCrown() < 6)
    //  return p.moveToEnemyCrown();

    return p.moveToEnemy();
  }
  
  return wait();
}

lionheart::Blazon lionheart::ShemHale::getBlazon()
{
  /*Return your blazon here.  In case of conflicts preference will be given to
   * the students that have registered their blazons in class.*/
  return { Color::AZURE, Color::SABLE, Style::BEND, "Shem Hale" };
}
