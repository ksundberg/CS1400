#include "DavidSpencer.hpp"

lionheart::Placement lionheart::DavidSpencer::placeUnitByStartPositions(lionheart::SituationReport report, std::vector<std::pair<int, int>> const& positions) {
  for(auto const& p : positions) {
    if(report.things[p.first][p.second].type == lionheart::SituationReport::SPACE) {
      return { p.first, p.second };
    }
  }

  return {0, 0};
}

bool lionheart::DavidSpencer::inEnemyBox(lionheart::Unit const& u) {
  if(isAllyEast) {
    return (((u.getLocation().row >= 19) && (u.getLocation().row <= 10)) && ((u.getLocation().col >= 2) && (u.getLocation().col <= 7)));
  } else {
    return (((u.getLocation().row >= 19) && (u.getLocation().row <= 10)) && ((u.getLocation().col >= 22) && (u.getLocation().col <= 27)));
  }
}

bool lionheart::DavidSpencer::isEnemyInBox(lionheart::SituationReport report) {
  auto jStart = 2;
  auto jEnd = 7;
  if(isAllyEast)  {
    jStart = 22;
    jEnd = 27;
  }
  for(auto i = 10; i <= 19; i++) {
    for(auto j = jStart; j <= jEnd; j++) {
      if(report.things[i][j].type == lionheart::SituationReport::ENEMY) {
        return true;
      }
    }
  }

  return false;
}

bool lionheart::DavidSpencer::isBottomUnit(lionheart::Unit const& u) {
  if(isAllyEast)
    return (((u.getLocation().row >= 17) && (u.getLocation().row <= 19)) && ((u.getLocation().col >= 24) && (u.getLocation().col <= 26)));
  else
    return (((u.getLocation().row >= 17) && (u.getLocation().row <= 19)) && ((u.getLocation().col >= 3) && (u.getLocation().col <= 5)));
}

bool lionheart::DavidSpencer::isTopUnit(lionheart::Unit const& u) {
  if(isAllyEast)
    return (((u.getLocation().row >= 10) && (u.getLocation().row <= 12)) && ((u.getLocation().col >= 24) && (u.getLocation().col <= 26)));
  else
    return (((u.getLocation().row >= 10) && (u.getLocation().row <= 12)) && ((u.getLocation().col >= 3) && (u.getLocation().col <= 5)));
}

lionheart::Placement lionheart::DavidSpencer::placeUnit(UnitType type, StartBox const& box, SituationReport report)
{
  crownMoves = 0;
  isAllyEast = box.minCol > 15 ? 1 : 0;

  if(type == lionheart::UnitType::CROWN) {
    return isAllyEast ? placeUnitByStartPositions(report, EastCrownStartPosition) : placeUnitByStartPositions(report, WestCrownStartPosition);
  } else if(type == lionheart::UnitType::ARCHER) {
    return isAllyEast ? placeUnitByStartPositions(report, EastArcherStartPositions) : placeUnitByStartPositions(report, WestArcherStartPositions);
  } else if(type == lionheart::UnitType::KNIGHT) {
    return isAllyEast ? placeUnitByStartPositions(report, EastKnightStartPositions) : placeUnitByStartPositions(report, WestKnightStartPositions);
  } else {
    return isAllyEast ? placeUnitByStartPositions(report, EastInfantryStartPositions) : placeUnitByStartPositions(report, WestInfantryStartPositions);
  }
}

auto lionheart::DavidSpencer::getClosestEnemy(Plan p, SituationReport report) {
  for(auto i = 0; i < 30; i++) {
    for(auto j = 0; j < 30; j++) {
      if(report.things[i][j].type == SituationReport::ENEMY) {
        if(p.movesTo(i, j) == p.movesToEnemy()) {
          return std::make_pair(i, j);
        }
      }
    }
  }

  return std::make_pair(-1, -1);
}

lionheart::Action lionheart::DavidSpencer::moveToNorthCorner(Plan p) {

  if(isAllyEast) {
    return p.moveToLocation(0, 29);
  }

  return p.moveToLocation(0, 0);
}

lionheart::Action lionheart::DavidSpencer::moveToSouthCorner(Plan p) {

  if(isAllyEast) {
    return p.moveToLocation(29, 29);
  }

  return p.moveToLocation(29, 0);
}

lionheart::Action lionheart::DavidSpencer::runAway(Unit const& u, Plan p, SituationReport report) {
  auto closestEnemyPos = getClosestEnemy(p, report);

  if(closestEnemyPos.first - u.getLocation().row > 0) { //enemy to the south, move north
    return moveToNorthCorner(p);
  } else if(closestEnemyPos.first - u.getLocation().row == 0) { //same row as us, move away by whichever side we're on
    if(closestEnemyPos.second < 15) { //we're north
      return moveToSouthCorner(p);
    }
    return moveToNorthCorner(p);
  } else { //enemy to the north, move south
    return moveToSouthCorner(p);
  }
}

lionheart::Action lionheart::DavidSpencer::runAwayFromRearWall(Unit const& u, Plan p) {
  if(isAllyEast) {
    return p.moveToLocation(u.getLocation().row, u.getLocation().col - 2);
  }

  return p.moveToLocation(u.getLocation().row, u.getLocation().col + 2);
}

bool lionheart::DavidSpencer::isArcherBehindBox(SituationReport report) {
  for(int i = 9; i < 21; i++) {
    if(report.things[i][0 + 29 * isAllyEast].type == SituationReport::ENEMY && report.things[i][0 + 29 * isAllyEast].unit == UnitType::ARCHER) {
      return true;
    }
  }

  return false;
}

lionheart::Action lionheart::DavidSpencer::recommendAction(Unit const& u, SituationReport report, Plan p)
{
  if (u.getType() == CROWN) {
    crownMoves++;
    if(p.movesToEnemy() <= 3) {
      return runAway(u, p, report);
    }
    if(isArcherBehindBox(report)) {
      return runAwayFromRearWall(u, p);
    }
    return wait();
  }

  if(crownMoves < 2) {
    if(isBottomUnit(u)) {
      return turn(lionheart::Direction::SOUTH);
    } else if(isTopUnit(u)) {
      return turn(lionheart::Direction::NORTH);
    }
  }

  if(crownMoves < 50) {
    if(p.hasAttack()) {
      return p.attackEnemy();
    }

    if(isEnemyInBox(report)) {
      return p.attackEnemy();
    }
    return wait();
  }

  if(p.hasAttack())
  {
    return p.attackEnemy();
  }
  if(inEnemyBox(u)) {
    return p.moveToEnemyCrown();
  }

  return p.attackEnemy();
}
lionheart::Blazon lionheart::DavidSpencer::getBlazon() { return {Color::AZURE, Color::ARGENT, Style::BEND_SINISTER, "David Spencer"}; }
