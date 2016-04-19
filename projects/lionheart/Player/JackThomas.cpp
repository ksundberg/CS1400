#include "JackThomas.hpp"
//Checks 3 spaces west of the unit to make sure the position is on the gameboard
//Returns the number of spaces it can check without error
int lionheart::JackThomas::checkWest(int currCol){
  int i = 0;
  while(currCol < 29 && i < 4){
    i++;
    currCol++;
  }
  return i;
}
//Checks 3 spaces east of the unit to make sure the position is on the gameboard
//Returns the number of spaces it can check without error
int lionheart::JackThomas::checkEast(int currCol){
  int i = 0;
  while(currCol > 0 && i < 3){
    i++;
    currCol--;
  }
  return i;
}
//Checks 3 spaces north of the unit to make sure the position is on the gameboard
//Returns the number of spaces it can check without error
int lionheart::JackThomas::checkNorth(int currRow){
  int i = 0;
  while(currRow > 0 && i < 3){
    i++;
    currRow--;
  }
  return i;
}
//Checks 3 spaces south of the unit to make sure the position is on the gameboard
//Returns the number of spaces it can check without error
int lionheart::JackThomas::checkSouth(int currRow){
  int i = 0;
  while(currRow < 29 && i < 3){
    i++;
    currRow++;
  }
  return i;
}
//Checks for an enemy in the north direction up to 3 spaces away
bool lionheart::JackThomas::enemyToTheNorth(int temp, int row, int col, SituationReport report){
  for(int i = 0; i < temp; i++){
    if(report.things[row][col].type == lionheart::SituationReport::ENEMY){
      return true;
    }
    row++;
  }
  return false;
}
bool lionheart::JackThomas::enemyToTheSouth(int temp, int row, int col, SituationReport report){
  for(int i = 0; i < temp; i++){
    if(report.things[row][col].type == lionheart::SituationReport::ENEMY){
      return true;
    }
    row--;
  }
  return false;
}
bool lionheart::JackThomas::enemyToTheWest(int temp, int row, int col, SituationReport report){
  for(int i = 0; i < temp; i++){
    if(report.things[row][col].type == lionheart::SituationReport::ENEMY){
      return true;
    }
    col--;
  }
  return false;
}
bool lionheart::JackThomas::enemyToTheEast(int temp, int row, int col, SituationReport report){
  for(int i = 0; i < temp; i++){
    if(report.things[row][col].type == lionheart::SituationReport::ENEMY){
      return true;
    }
    col++;
  }
  return false;
}
bool lionheart::JackThomas::isValidLocation(int row, int col){
  if(row < 30 && row >= 0){
    if(col < 30 && col >= 0){
      return true;
    }
  }
  return false;
}
//checks 3x3 block from unit. West first, then south, then north and East last
lionheart::JackThomas::archerLocation lionheart::JackThomas::checkSurroundingsForArcherWestFirst(int tempRow, int tempCol, SituationReport report){
  //Checking West
  int row = tempRow + 1;
  int col = tempCol - 3;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      if(isValidLocation(row, col) && report.things[row][col].type == lionheart::SituationReport::ENEMY){
        if(report.things[row][col].unit == lionheart::UnitType::ARCHER){
          archerLocation al(row, col);
          return al;
        }
      }
      col++;
    }
    row--;
  }
  //Checking South
  row = tempRow + 1;
  col = tempCol - 1;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      if(isValidLocation(row, col) && report.things[row][col].type == lionheart::SituationReport::ENEMY){
        if(report.things[row][col].unit == lionheart::UnitType::ARCHER){
          archerLocation al(row, col);
          return al;
        }
      }
      col++;
    }
    row--;
  }
  //Checking North
  row = tempRow - 1;
  col = tempCol - 1;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      if(isValidLocation(row, col) && report.things[row][col].type == lionheart::SituationReport::ENEMY){
        if(report.things[row][col].unit == lionheart::UnitType::ARCHER){
          archerLocation al(row, col);
          return al;
        }
      }
      col++;
    }
    row++;
  }
  //Checking East
  row = tempRow + 1;
  col = tempCol + 1;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      if(isValidLocation(row, col) && report.things[row][col].type == lionheart::SituationReport::ENEMY){
        if(report.things[row][col].unit == lionheart::UnitType::ARCHER){
          archerLocation al(row, col);
          return al;
        }
      }
      col++;
    }
    row--;
  }
  archerLocation al(-1, -1);
  return al;
}

//checks 3x3 block from unit. East first, then south, then north and west last
lionheart::JackThomas::archerLocation lionheart::JackThomas::checkSurroundingsForArcherEastFirst(int tempRow, int tempCol, SituationReport report){
  //Checking East
  int row = tempRow + 1;
  int col = tempCol + 1;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      if(isValidLocation(row, col) && report.things[row][col].type == lionheart::SituationReport::ENEMY){
        if(report.things[row][col].unit == lionheart::UnitType::ARCHER){
          archerLocation al(row, col);
          return al;
        }
      }
      col++;
    }
    row--;
  }
  //Checking South
  row = tempRow + 1;
  col = tempCol - 1;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      if(isValidLocation(row, col) && report.things[row][col].type == lionheart::SituationReport::ENEMY){
        if(report.things[row][col].unit == lionheart::UnitType::ARCHER){
          archerLocation al(row, col);
          return al;
        }
      }
      col++;
    }
    row--;
  }
  //Checking North
  row = tempRow - 1;
  col = tempCol - 1;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      if(isValidLocation(row, col) && report.things[row][col].type == lionheart::SituationReport::ENEMY){
        if(report.things[row][col].unit == lionheart::UnitType::ARCHER){
          archerLocation al(row, col);
          return al;
        }
      }
      col++;
    }
    row++;
  }
  //Checking West
  row = tempRow + 1;
  col = tempCol - 3;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      if(isValidLocation(row, col) && report.things[row][col].type == lionheart::SituationReport::ENEMY){
        if(report.things[row][col].unit == lionheart::UnitType::ARCHER){
          archerLocation al(row, col);
          return al;
        }
      }
      col++;
    }
    row--;
  }
  archerLocation al(-1, -1);
  return al;
}

lionheart::Placement lionheart::JackThomas::placeUnit(UnitType, StartBox const &box, SituationReport report){
  /*Fill this out with instructions on how to place your initial units.  Without
   * changes your units will fill the starting box from top left to bottom right
   * in the order constructed.*/
     ++id;
     startOnWestSide = (box.minCol < static_cast<int>(report.things[0].size() / 2));
     if(startOnWestSide){
       switch(id){
     // CROWN
     case 1: return {19, 4};
     // KNIGHTS
     case 2: return {18,3};
     case 3: return {14,6};
     case 4: return {12,4};
     case 5: return {14,7};
     case 6: return {16,6};
     case 7: return {19,7};
     // ARCHERS
     case 8: return {10,4};
     case 9: return {18,4};
     case 10:return {10,3};
     case 11:return {19,3};
     case 12:return {11,2};
     case 13:return {18,2};
     case 14:return {10,2};
     case 15:return {19,2};
     // INFANTRY
     case 16: return {11,4};
     case 17: return {17,4};
     case 18: return {15,6};
     case 19: return {15,7};
     case 20: return {13,4};
     case 21: return {14,4};
     case 22: return {15,4};
     case 23: return {16,4};

     case 24: return {14,2};
     case 25: return {15,3};
     case 26: return {14,3};
     case 27: return {13,3};
     case 28: return {16,3};
     case 29: return {13,5};
     case 30: id=0;return {16,5};
    }
  }
  else{
    switch(id){
    // CROWN
    case 1: return {19,25};
    // KNIGHTS
    case 2: return {18,2};
    case 3: return {14,23};
    case 4: return {12,25};
    case 5: return {14,22};
    case 6: return {16,23};
    case 7: return {19,22};
    // ARCHERS
    case 8: return {10,25};
    case 9: return {18,25};
    case 10:return {10,26};
    case 11:return {19,26};
    case 12:return {11,27};
    case 13:return {18,27};
    case 14:return {10,27};
    case 15:return {19,27};
    // INFANTRY
    case 16: return {11,25};
    case 17: return {17,25};
    case 18: return {15,23};
    case 19: return {15,23};
    case 20: return {13,25};
    case 21: return {14,25};
    case 22: return {15,25};
    case 23: return {16,25};

    case 24: return {14,27};
    case 25: return {15,26};
    case 26: return {14,26};
    case 27: return {13,26};
    case 28: return {16,26};
    case 29: return {13,24};
    case 30: id=0;return {19,23};
    }
  }
  return {0, 0};
}
lionheart::Action lionheart::JackThomas::recommendAction(Unit const& u, SituationReport report, Plan p){
  int rowPosition = u.getLocation().row;
  int colPosition = u.getLocation().col;
  int northSpaces = checkNorth(rowPosition);
  int eastSpaces = checkEast(colPosition);
  int westSpaces = checkWest(colPosition);
  int southSpaces = checkSouth(rowPosition);
  if(startOnWestSide){
    if(u.getType() == ARCHER){
      if(p.hasAttack()){
        return p.attackEnemy();
      }
      if(p.movesToEnemy() < 4){
        return p.attackEnemy();
      }
    }

    archerLocation al = checkSurroundingsForArcherEastFirst(u.getLocation().row, u.getLocation().col, report);
    if(al.row != -1){
      return p.moveToLocation(u.getLocation().row, al.col - 3);
    }
    if(p.hasAttack())return p.attackEnemy();
    if(p.movesToEnemy() < 2)return p.attackEnemy();
    if(u.getType() != CROWN){
      if(u.getId() == 7){ //Archer protecting crown north side
        if(u.getLocation().row == 14 && u.getLocation().col == 0)return turn(Direction::NORTH);
        return p.moveToLocation(14, 0);
      }
      if(u.getId() == 8){//Archer protecting crown south side
        if(u.getLocation().row == 16 && u.getLocation().col == 0)return turn(Direction::SOUTH);
        return p.moveToLocation(16, 0);
      }
      if(u.getId() == 30){//Infantry protecting crown north side
        if(u.getLocation().row == 13 && u.getLocation().col == 0)return turn(Direction::NORTH);
        return p.moveToLocation(13, 0);
      }
      if(u.getId() == 31){//Infantry protecting crown south side
        if(u.getLocation().row == 17 && u.getLocation().col == 0)return turn(Direction::SOUTH);
        return p.moveToLocation(17, 0);
      }
      if(u.getId() == 32){//Ifanctry protecting archer behind wall north side
        if(u.getLocation().row == 6 && u.getLocation().col == 4)return turn(Direction::EAST);
        return p.moveToLocation(6, 4);
      }
      if(u.getId() == 33){//Infantry protecting archer behind wall south side
        if(u.getLocation().row == 23 && u.getLocation().col == 4)return turn(Direction::EAST);
        return p.moveToLocation(23, 4);
      }
      if(u.getId() == 9){ //Archer in the top corner
        if(u.getFacing() == Direction::NORTH)return wait();
        return turn(Direction::NORTH);
      }
      if(u.getId() == 10){ //Archer in the lower corner
        if(u.getFacing() == Direction::SOUTH)return wait();
        return turn(Direction::SOUTH);
      }
      if(u.getId() == 11){ //Archer top behind wall
        if(u.getLocation().row == 6 && u.getLocation().col == 3){
          if(u.getFacing() == Direction:: SOUTH)return wait();
          return turn(Direction::SOUTH);
        }
        return p.moveToLocation(6, 3);
      }
      if(u.getId() == 12){ //Archer lower behind wall
        if(u.getLocation().row == 23 && u.getLocation().col == 3){
          if(u.getFacing() == Direction:: NORTH)return wait();
          return turn(Direction::NORTH);
        }
        return p.moveToLocation(23, 3);
      }
      if(u.getId() == 13){//Archer in fort facing back wall north
        if(u.getFacing() == Direction::WEST)return wait();
        return turn(Direction::WEST);
      }
      if(u.getId() == 14){//Archer in fort facing back wall south
        if(u.getFacing() == Direction::WEST)return wait();
        return turn(Direction::WEST);
      }
      if(enemyToTheEast(eastSpaces, rowPosition, colPosition, report))return turn(Direction::EAST);
      if(enemyToTheNorth(northSpaces, rowPosition, colPosition, report))return turn(Direction::NORTH);
      if(enemyToTheSouth(southSpaces, rowPosition, colPosition, report))return turn(Direction::SOUTH);
      if(enemyToTheWest(westSpaces, rowPosition, colPosition, report))return turn(Direction::WEST);
      return p.moveToEnemyCrown();
    }
    if(u.getType() == CROWN){
      return p.moveToLocation(15, 0);
    }
  }
  /*Else if I start on the East Side*/
  else{
    if(u.getType() == ARCHER){
      if(p.hasAttack())return p.attackEnemy();
      if(p.movesToEnemy() < 4)return p.attackEnemy();
    }

    archerLocation al = checkSurroundingsForArcherWestFirst(u.getLocation().row, u.getLocation().col, report);
    if(al.row != -1)return p.moveToLocation(u.getLocation().row, al.col - 3);
    if(p.hasAttack())return p.attackEnemy();
    if(p.movesToEnemy() < 2)return p.attackEnemy();
    if(u.getType() != CROWN){
      if(u.getId() == 7){ //Archer protecting crown north side
        if(u.getLocation().row == 14 && u.getLocation().col == 29)return turn(Direction::NORTH);
        return p.moveToLocation(14, 29);
      }
      if(u.getId() == 8){//Archer protecting crown south side
        if(u.getLocation().row == 16 && u.getLocation().col == 29)return turn(Direction::SOUTH);
        return p.moveToLocation(16, 29);
      }
      if(u.getId() == 30){//Infantry protecting crown north side
        if(u.getLocation().row == 13 && u.getLocation().col == 29)return turn(Direction::NORTH);
        return p.moveToLocation(13, 29);
      }
      if(u.getId() == 31){//Infantry protecting crown south side
        if(u.getLocation().row == 17 && u.getLocation().col == 29)return turn(Direction::SOUTH);
        return p.moveToLocation(17, 29);
      }
      if(u.getId() == 32){
        if(u.getLocation().row == 6 && u.getLocation().col == 25)return turn(Direction::WEST);
        return p.moveToLocation(6, 25);
      }
      if(u.getId() == 33){
        if(u.getLocation().row == 23 && u.getLocation().col == 25)return turn(Direction::WEST);
        return p.moveToLocation(23, 25);
      }
      if(u.getId() == 9){ //Archer in the top corner
        if(u.getFacing() == Direction::NORTH)return wait();
        return turn(Direction::NORTH);
      }
      if(u.getId() == 10){ //Archer in the lower corner
        if(u.getFacing() == Direction::SOUTH)return wait();
        return turn(Direction::SOUTH);
      }
      if(u.getId() == 11){ //Archer top behind wall
        if(u.getLocation().row == 6 && u.getLocation().col == 26){
          if(u.getFacing() == Direction:: SOUTH)return wait();
          return turn(Direction::SOUTH);
        }
        return p.moveToLocation(6, 26);
      }
      if(u.getId() == 12){ //Archer lower behind wall
        if(u.getLocation().row == 23 && u.getLocation().col == 26){
          if(u.getFacing() == Direction:: NORTH)return wait();
          return turn(Direction::NORTH);
        }
        return p.moveToLocation(23, 26);
      }
      if(u.getId() == 13){
        if(u.getFacing() == Direction::EAST)return wait();
        return turn(Direction::EAST);
      }
      if(u.getId() == 14){
        if(u.getFacing() == Direction::EAST)return wait();
        return turn(Direction::EAST);
      }
      if(enemyToTheEast(eastSpaces, rowPosition, colPosition, report))return turn(Direction::EAST);
      if(enemyToTheNorth(northSpaces, rowPosition, colPosition, report))return turn(Direction::NORTH);
      if(enemyToTheSouth(southSpaces, rowPosition, colPosition, report))return turn(Direction::SOUTH);
      if(enemyToTheWest(westSpaces, rowPosition, colPosition, report))return turn(Direction::WEST);
      return p.moveToEnemyCrown();
    }
    if(u.getType() == CROWN){
      return p.moveToLocation(15, 29);
    }
  }
  return Action();
}

lionheart::Blazon lionheart::JackThomas::getBlazon(){
  /*Return your blazon here.  In case of conflicts preference will be given to
   * the students that have registered their blazons in class.*/
  return { Color::AZURE, Color::ARGENT, Style::CROSS, "Jack Thomas" };
}
