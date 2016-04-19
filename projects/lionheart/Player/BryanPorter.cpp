#include "BryanPorter.hpp"

lionheart::Placement lionheart::BryanPorter::placeUnit(UnitType t,
                                              StartBox const &box,
                                              SituationReport report)
{
  leaveFort = true;
  westSide = box.minCol < 15;
  eKingr = -5; eKingc = -5;
  if(t == CROWN && westSide) return {14, 4};
  else if(t == CROWN) return {15, 25};
  runawayKing = -1;
  if(westSide){
    for(int c=box.maxCol; c > box.minCol; c--)
      for(int r= box.maxRow-1; r>box.minRow; r--)
        if(report.things[r][c].type == SituationReport::SPACE && r != 14)
          return {r, c};
  }
  for (int c = box.minCol+1; c < box.maxCol; c++)
    for (int r = box.maxRow-1; r > box.minRow; r--)
      if (r != 15 && report.things[r][c].type == SituationReport::SPACE)
        return { r, c };
  return { 0, 0 };
  }

  lionheart::Action
lionheart::BryanPorter::recommendAction(Unit const &u, SituationReport r, Plan p){
  if(p.hasAttack()) return p.attackEnemy();
  if(facingRock(u, r)) return turn(getTurn(u.getFacing()));
  if(r.turns > 175) return p.moveToEnemyCrown(); //go for loss, not tie

  if(u.getType() == CROWN) return recCrown(u, r, p);
  if(u.getType() == ARCHER) return recArcher(u, r, p);
  if(u.getType() == INFANTRY) return recInfant(u, r, p);
  if(u.getType() == KNIGHT) return recKnight(u, r, p);

  return Action();
}

lionheart::Blazon lionheart::BryanPorter::getBlazon()
{
  return { Color::VERT, Color::GULES, Style::BEND, "Eagle-Eye Bryan" };
}

bool lionheart::BryanPorter::archerRange(
               int r1, int c1, int r2, int c2, Direction d){
  int tr, lc;
  if(d == Direction::NORTH){
    tr = r1-3; lc = c1-1;
  } else if(d == Direction::EAST){
    tr = r1-1; lc = c1 +1;
  } else if(d == Direction::SOUTH){
    tr = r1+1; lc = c1-1;
  } else {
    tr = r1-1; lc = c1-3;
  }

  for(int i=tr; i< tr+3; i++)
    for(int j=lc; j<lc+3; j++)
      if(i == r2 && j== c2) return true;

  return false;
}

//returns potential number of enemies that could attack a location
int lionheart::BryanPorter::checkDanger(
            int r, int c, SituationReport sr){
    int targeted=0;
    if(r < 0 || r > 29 || c > 29 || c < 0) targeted += 100;
    if(sr.things[r][c].type != SituationReport::SPACE) targeted += 20;
    
    //check for surrounding Enemies
    for(int i=r-5; i<r+5; i++)
      for(int j=c-5; j<c+5; j++)
        if(i >=0 && i<30 && j>=0 && j<30)
          if(sr.things[i][j].type == SituationReport::ENEMY){
            if(sr.things[i][j].unit == CROWN){
              eKingr = i; eKingc = j;
            }
            if(sr.things[i][j].unit == ARCHER){
              if(archerRange(i, j, r, c, sr.things[i][j].direction))
                targeted++;
            } else {
              if(i-r == 1 && j-c == 0 && 
                   sr.things[i][j].direction == Direction::SOUTH)
                targeted++;
              else if(r-i == 1 && j == c &&
                   sr.things[i][j].direction == Direction::NORTH)
                targeted++;
              else if(r == i && j-c == 1 &&
                   sr.things[i][j].direction == Direction::EAST)
                targeted++;
              else if(r == i && c-j == 1 &&
                   sr.things[i][j].direction == Direction::WEST)
                targeted++;
            }
          }
   return targeted;
}

bool lionheart::BryanPorter::facingRock(Unit const& u, SituationReport r){
  int row = u.getLocation().row;
  int col = u.getLocation().col;

  if(u.getFacing() == Direction::NORTH){
    if(row-1 >= 0)
      return r.things[row-1][col].type == SituationReport::ThingType::ROCK;
  } else if(u.getFacing() == Direction::EAST){
    if(col+1 <30)
      return r.things[row][col+1].type == SituationReport::ThingType::ROCK;
  } else if(u.getFacing() == Direction::SOUTH){
    if(row+1 <30)
      return r.things[row][col].type == SituationReport::ThingType::ROCK; 
  } else if(u.getFacing() == Direction::WEST){
    if(col-1 >=0)
      return r.things[row][col-1].type == SituationReport::ThingType::ROCK;
  } else return true;
 return false;
}

lionheart::Direction lionheart::BryanPorter::getTurn(lionheart::Direction d){
  if(d == Direction::NORTH) return Direction::WEST;
  if(d == Direction::WEST) return Direction::SOUTH;
  if(d == Direction::SOUTH) return Direction::EAST;
  return Direction::NORTH;
}

lionheart::Action
    lionheart::BryanPorter::recCrown(Unit const&u, SituationReport r, Plan p){
  if(runawayKing <0) checkInvaders(r);
  if(runawayKing <0) return wait();

  auto row = u.getLocation().row;
  if(row <= 3) runawayKing = 8;
  if(row >= 26) runawayKing = 9;
  if(westSide){
    if(runawayKing%4 == 1) return p.moveToLocation(3, 2);
    return p.moveToLocation(26, 2);
  }
  if(runawayKing%4 == 0) return p.moveToLocation(3, 26);
  return p.moveToLocation(28, 28);
}

lionheart::Action 
    lionheart::BryanPorter::recArcher(Unit const &u, SituationReport r, Plan p){

  auto row = u.getLocation().row;
  auto col = u.getLocation().col;

  //shoot king if possible and found
  if(archerRange(row, col, eKingr, eKingc, u.getFacing()))
    return attack({eKingr, eKingc});

  int tr, lc;
  if(u.getFacing() == Direction::NORTH){
    tr = row-3; lc = col-1;
  } else if(u.getFacing() == Direction::EAST){
    tr = row-1; lc = col+1;
  } else if(u.getFacing() == Direction::SOUTH){
    tr = row+1; lc = col-1;
  } else{
    tr = row-1; lc = col-3;
  }
  for(int i=tr; i< tr+3; i++)
    for(int j=lc; j<lc+3; j++)
      if(j >=0 && j < 30 && i >= 0 && i < 30)
        if(r.things[tr][lc].type == SituationReport::ENEMY)
          return attack({i, j});

  int d, d1, r1, c1;
  r1 = row; c1 = col;
  d = checkDanger(row, col, r)-20;
  if(u.getFacing() == Direction::NORTH) r1 -= 1;
  if(u.getFacing() == Direction::EAST) c1 += 1;
  if(u.getFacing() == Direction::SOUTH) r1 += 1;
  if(u.getFacing() == Direction::WEST) c1 -= 1;

  d1 = checkDanger(r1, c1, r);

  if(d1 == 0 && d == 0) return p.moveToEnemyCrown();
  if(d1 == 0) return p.moveToLocation(r1, c1);
  if(d1 >= 20) return p.attackEnemy();
  if(d == 0) return wait();
  return p.attackEnemy();
}

  lionheart::Action
lionheart::BryanPorter::recKnight(Unit const &u, SituationReport r, Plan p){
  
  auto row = u.getLocation().row;
  auto col = u.getLocation().row;
  int d = checkDanger(row, col, r)-20;
  int r1, c1, d1, nr, nc;
  nr = row; nc = col;

  if(u.getFacing() == Direction::NORTH){
    r1 = -1; c1 = 0;
  } else if (u.getFacing() == Direction::EAST){
    r1 = 0; c1 = 1;
  } else if (u.getFacing() == Direction::SOUTH){
    r1 = 1; c1 = 0;
  } else {
    r1 = 0; c1 = -1;
  }

  for(int i=1; i<6; i++){
    d1 = checkDanger(row + (r1*i), col + (c1*i), r);
    if(d1 == 0){
      nr = row + (r1*i); nc = col + (c1*i);
    } else if(d1 >= 20) i =6;
    
  }
  d1 = checkDanger(nr, nc, r);
  if(d1 == 0 && d == 0) return p.moveToEnemyCrown();
  if(d1 == 0) return p.moveToLocation(nr, nc);
  if(d1 >= 20) return p.attackEnemy();
  if(d == 0) return wait();

  return p.moveToEnemyCrown();
}

  lionheart::Action
lionheart::BryanPorter::recInfant(Unit const &u, SituationReport r, Plan p){

  if(runawayKing >=0) return p.attackEnemy();
  auto row = u.getLocation().row;
  auto col = u.getLocation().col;
  int d = checkDanger(row, col, r)-20; 
  int r1 = 0;
  int c1 = 0;

  if(u.getFacing() == Direction::NORTH)r1 = -1;
  if(u.getFacing() == Direction::EAST) c1 = 1;
  if(u.getFacing() == Direction::SOUTH) r1 = 1;
  if(u.getFacing() == Direction::WEST) c1 = -1;
  
  int d1 = checkDanger(row + r1, col + c1, r);
  
  if(d1 == 0 && d == 0) return p.moveToEnemyCrown();
  if(d1 == 0) return p.moveToLocation(r1, c1);
//  if(d1 >= 20 && runawayKing >=0) return p.attackEnemy();
  if(d == 0) return wait();
  return p.attackEnemy();
}

