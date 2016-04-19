#include "ChrisWagner.hpp"

#include <vector>
#include <iostream>

lionheart::Placement lionheart::ChrisWagner::placeUnit(UnitType type, StartBox const &box, SituationReport report)
{	
	leftSide = box.minCol < (int)(report.things[0].size()/2);
	fortress = box;
	currentState = HOLD;
	shiftingArchers.clear();
	
	if(type == NONE) return {0, 0};
	if(type == INFANTRY) return placeInfantry(box, report);
	if(type == ARCHER) return placeArcher(box, report);
	if(type == KNIGHT) return placeKnight(box, report);
	return {15, leftSide ? 4 : reflectToR(4, report)}; // CROWN
}

lionheart::Action lionheart::ChrisWagner::recommendAction(Unit const & unit, SituationReport report, Plan plan)
{
	if(unit.getType() == CROWN)
	{
		if(report.turns > 60 && currentState == HOLD && !enemiesComing(unit, report)) currentState = ATTACK;
		lionheart::Map::Location loc = unit.getLocation();
		if(inImmediateDanger(loc.row, loc.col, report))
		{
			currentState = LOCKDOWN;
			defcon = 2;
		}
		else if(inDangerSoon(loc.row, loc.col, report))
		{
			currentState = LOCKDOWN;
			defcon = 3;
		}
		else if(currentState == LOCKDOWN) currentState = ATTACK;
		
		if(currentState == LOCKDOWN)
		{
			lionheart::Direction evade = bestEvasionDirection(unit, report);
			if(unit.getFacing() != evade) return turn(evade);
			int spaces = spacesToMove(unit.getFacing(), loc.row, loc.col, report, 5 - defcon);
			for(int i = spaces; i >= 1; --i)
			{
				lionheart::Placement moveTo = projectMovement(spaces, unit);
				if(isInBounds(moveTo.row, moveTo.col, report) && !inImmediateDanger(moveTo.row, moveTo.col, report))
				return move(spaces);			
			}
		}
		return wait();
	}
	
	lionheart::Map::Location loc = unit.getLocation();
	//default actions
	if(unit.getType() == ARCHER)
	{
		lionheart::Placement toAtk = bestArcherAttack(unit, report);
		if(!(toAtk.row == loc.row && toAtk.col == loc.col)) return attack(toAtk);
	}
	else if (plan.hasAttack()) return plan.attackEnemy(); // don't waste the opportunity
	
	if(currentState == ATTACK) 
	{
		if(report.turns > 170) return plan.moveToEnemyCrown(); // last push
		if(unit.getType() != ARCHER){
			if(inImmediateDanger(loc.row, loc.col, report)) return plan.attackEnemy(); // cornered - don't go down without a fight
			int distanceToKeep = 3;
			if(report.turns > 125) --distanceToKeep;
			if(report.turns > 150) --distanceToKeep;
			if(unit.getType() == KNIGHT) --distanceToKeep;
			if(plan.movesToEnemy() > distanceToKeep || plan.movesToEnemyCrown() < 2) return plan.moveToEnemyCrown();
			return wait(); // let the enemy close the distance
		}
		//1 - see if you can get a hit by turning - like in the fortress
		lionheart::Direction best = bestArcherDirection(unit, report); 
		if(unit.getFacing() != best) return turn(best);
		
		if(shiftingArchers.find(&unit) != shiftingArchers.end())
		{
			shiftingArchers.erase(&unit);
			return move(1);
		}
		best = turnToMow(unit, report);
		if(unit.getFacing() != best)
		{
			shiftingArchers.insert({&unit, 0});
			return turn(best);
		}
		//head for the back if it's worth doing
		int targetCol = leftSide ? reflectToR(0, report) : 0;
		if(enemyBackOpening(report)) 
		{
			if(loc.col == targetCol)
				return plan.moveToLocation((fortress.maxRow + fortress.minRow)/2, targetCol);
			
			//this is a hacky way around a glitch in the pathing code.
			//archer was returning moveToLocation for the same spot over and over, and just turning back and forth as it prioritized different paths
			if(unit.getFacing() == lionheart::Direction::SOUTH 
			&& loc.row == fortress.maxRow + 2 
			&& report.things[loc.row+1][loc.col].type == SituationReport::SPACE) return move(1);
			
			return plan.moveToLocation(report.things.size() * ((loc.row <= (fortress.maxRow + fortress.minRow)/2) ? 0.2 : 0.77), targetCol);
		}
		return plan.moveToEnemyCrown();
	}
	if(currentState == HOLD) 
	{
		if(unit.getType() == ARCHER)
		{
			lionheart::Direction best = bestArcherDirection(unit, report); 
			if(unit.getFacing() != best) return turn(best);
		}
		lionheart::Direction def = defaultDirection(unit); 	
		if(unit.getFacing() != def) return turn(def);	
		return wait();
	}
	//mode must equal LOCKDOWN - only thing left
	if(plan.movesToEnemy() <= 2) return plan.attackEnemy(); // don't just let the enemy attack you while you're crowding the crown
	if(plan.movesToEnemyCrown() <= 4 && unit.getType() != KNIGHT) return plan.moveToEnemyCrown(); // don't bring the infantry back if they're too far away
	if(plan.movesToAllyCrown() > defcon + 1 && !inTheCrownsCourt(unit, report)) return plan.moveToAllyCrown();
	return plan.attackEnemy();
	
	return Action();
}

lionheart::Blazon lionheart::ChrisWagner::getBlazon()
{
  return { Color::ARGENT, Color::GULES, Style::CROSS, "Poe's Consumption" };
}
//placement helpers
lionheart::Placement lionheart::ChrisWagner::placeInfantry(StartBox const &box, SituationReport report)
{
	int col = leftSide ? box.minCol + 2 : box.maxCol - 2;
	for(auto i = box.minRow; i <= box.maxRow; i+=((box.maxRow - box.minRow)-2))
		for(int j = 0; j < 3; ++j)
			if(report.things[i+j][col].type == SituationReport::SPACE) return {i+j, col};
		
	col = leftSide ? box.maxCol: box.minCol;
	int row;
	for(auto i = 3; i <= 6; ++i)
	{
		row = box.minRow + i;
		if(report.things[row][col].type == SituationReport::SPACE) return {row, col};			
	}
	
	row = box.minRow + 4;
	col = leftSide ? box.maxCol - 1 : box.minCol + 1;
	for(int i = 0; i <=1; ++i)
		if(report.things[row+i][col].type == SituationReport::SPACE) return {row+i, col};
	
	row = box.maxRow;
	col = leftSide ? box.minCol + 1 : box.maxCol - 3;
	for(int i = 0; i < 3; i+=2)
		if(report.things[row][col+i].type == SituationReport::SPACE) return {row, col+i};

	row = box.minRow;
	col = leftSide ? box.minCol + 3 : box.maxCol - 3;
	if(report.things[row][col].type == SituationReport::SPACE) return {row, col};
	return {0, 0};
}
lionheart::Placement lionheart::ChrisWagner::placeArcher(StartBox const &box, SituationReport report)
{
	for(int i = box.minRow + 1; i <= box.maxRow - 1; i += ((box.maxRow - box.minRow)- 2)) // this might be offset wrong to put things out of the box
		for(int j = 3; j <= 7; j +=2)
			if(report.things[i][leftSide ? j : reflectToR(j, report)].type == SituationReport::SPACE)
				return {i, leftSide ? j : reflectToR(j, report)};
	
	int col = leftSide ? box.maxCol-1 : box.minCol+1;
	for(int i = box.minRow+3; i <= box.maxRow-3; i+=3)
		if(report.things[i][col].type == SituationReport::SPACE) return {i, col};
	
	return {0, 0};
}
lionheart::Placement lionheart::ChrisWagner::placeKnight(StartBox const &box, SituationReport report)
{
	int col = leftSide ? box.minCol + 1 : box.maxCol - 1;
	int row = box.minRow;
	if(report.things[row][col].type == SituationReport::SPACE) return {row, col};	
	
	col += leftSide ? 1 : -1;
	for(int i = 3; i <= 6; i+=3)
		if(report.things[row+i][col].type == SituationReport::SPACE) return {row+i, col};
	
	if(report.things[row+4][col].type == SituationReport::SPACE) return {row+4, col};
	
	col += leftSide ? 1 : -1;
	for(int i = 4; i <= 5; ++i)
		if(report.things[row+i][col].type == SituationReport::SPACE) return {row+i, col};
	
	return {0, 0};
	
}
int lionheart::ChrisWagner::reflectToR(int col, SituationReport report)
{
	return report.things[0].size() - (col + 1);
}

//intelligence
bool lionheart::ChrisWagner::inImmediateDanger(int row, int col, SituationReport report)
{
	if(isInBounds(row-1, col, report) && report.things[row-1][col].type == SituationReport::ENEMY) return true;
	if(isInBounds(row+1, col, report) && report.things[row+1][col].type == SituationReport::ENEMY) return true;
	if(isInBounds(row, col-1, report) && report.things[row][col-1].type == SituationReport::ENEMY) return true;
	if(isInBounds(row, col+1, report) && report.things[row][col+1].type == SituationReport::ENEMY) return true;
	for(int i = -3; i <=3; ++i)
		for(int j = -1; j <=1; ++j)
		{
			if(isInBounds(row+i, col+j, report) && report.things[row+i][col+j].type == SituationReport::ENEMY && report.things[row+i][col+j].unit == ARCHER) return true;
			if(isInBounds(row+j, col+i, report) && report.things[row+j][col+i].type == SituationReport::ENEMY && report.things[row+j][col+i].unit == ARCHER) return true;
		}
	return false;
}
bool lionheart::ChrisWagner::inDangerSoon(int row, int col, SituationReport report)
{
	for(int i = row - 1; i < row + 1; i += 2)
		for(int j = col - 1; j < col + 1; j += 2)
			if(isInBounds(i, j, report) && report.things[i][j].type == SituationReport::ENEMY) return true;		
	for(int i = -2; i <= 2; i += 4)
	{
		if(isInBounds(row+i, col, report) && report.things[row + i][col].type == SituationReport::ENEMY) return true;
		if(isInBounds(row, col+i, report) && report.things[row][col + i].type == SituationReport::ENEMY) return true;		
	}
	
	for(int i = -4; i <= 4; i += 8)
		for(int j = -1; j <= 1; ++j)
		{			
			if(isInBounds(row+i, col+j, report) && report.things[row+i][col+j].type == SituationReport::ENEMY && report.things[row+i][col+j].unit == ARCHER) return true;
			if(isInBounds(row+j, col+i, report) && report.things[row+j][col+i].type == SituationReport::ENEMY && report.things[row+j][col+i].unit == ARCHER) return true;
		}
	return false;	
}

//functions for HOLD mode
bool lionheart::ChrisWagner::enemiesComing(Unit const & commander, SituationReport report)
{
	int rows = report.things.size();
	int cols = report.things[0].size();
	int offset = commander.getLocation().col > cols/2 ? cols/2 : 0;
	for(int i = 0; i < rows; ++i)
		for(int j = 0; j < cols/2; ++j)
			if(isInBounds(i, offset+j, report) && report.things[i][offset + j].type == SituationReport::ENEMY) return true;
	return false;
}

lionheart::Direction lionheart::ChrisWagner::bestArcherDirection(Unit const & unit, SituationReport report)
{
	lionheart::Direction dir = unit.getFacing();
	lionheart::Map::Location loc = unit.getLocation();
	for(int i = 1; i <=3; ++i)
		for(int j = -1; j <=1; ++j)
		{
			if(isInBounds(loc.row+i, loc.col+j, report) && report.things[loc.row + i][loc.col + j].type == SituationReport::ENEMY) return lionheart::Direction::SOUTH;	
			if(isInBounds(loc.row-i, loc.col+j, report) && report.things[loc.row - i][loc.col + j].type == SituationReport::ENEMY) return lionheart::Direction::NORTH;
			if(isInBounds(loc.row+j, loc.col+i, report) && report.things[loc.row + j][loc.col + i].type == SituationReport::ENEMY) return lionheart::Direction::EAST;
			if(isInBounds(loc.row+j, loc.col-i, report) && report.things[loc.row + j][loc.col - i].type == SituationReport::ENEMY) return lionheart::Direction::WEST;
		}
	return dir;
}

lionheart::Direction lionheart::ChrisWagner::defaultDirection(Unit const & unit)
{
	lionheart::Map::Location loc = unit.getLocation();
	
	if(loc.col != (leftSide ? fortress.maxCol : fortress.minCol))
	{
		if(loc.row == fortress.minRow + 1) return lionheart::Direction::NORTH;
		if(loc.row == fortress.maxRow - 1) return lionheart::Direction::SOUTH;		
	}
	
	if(loc.row == fortress.minRow + 4 
	|| loc.row == fortress.maxRow - 4 
	|| loc.col == fortress.minCol + 1 
	|| loc.col == fortress.maxCol - 1) 
		return leftSide ? lionheart::Direction::EAST : lionheart::Direction::WEST;
	
	if(loc.col == (leftSide ? fortress.minCol + 3 : fortress.maxCol - 3)) 
		return leftSide ? lionheart::Direction::WEST : lionheart::Direction::EAST;
	
	if(loc.col == (leftSide ? fortress.maxCol : fortress.minCol)
	&& loc.row == fortress.minRow + 3) 
		return lionheart::Direction::SOUTH;
	if(loc.col == (leftSide ? fortress.maxCol : fortress.minCol)
	&& loc.row == fortress.maxRow - 3) 
		return lionheart::Direction::NORTH;
		
	if(loc.col == (leftSide ? fortress.maxCol : fortress.minCol))
		return leftSide ? lionheart::Direction::EAST : lionheart::Direction::WEST;
		
	if(loc.row <= ((fortress.minRow + fortress.maxRow) / 2) - 1) return lionheart::Direction::NORTH;
	return lionheart::Direction::SOUTH;
}

// TODO - what the king does in lockdown (stays as far away from enemies as possible)
lionheart::Direction lionheart::ChrisWagner::bestEvasionDirection(Unit const & unit, SituationReport report)
{
	lionheart::Direction currDir = unit.getFacing();
	lionheart::Direction whereEnemyIs;
	bool enemyStraightline = false;
	
	lionheart::Map::Location loc = unit.getLocation();
	
	for(int i = 1; i <= 4; ++i)
	{
		if(isInBounds(loc.row+i, loc.col, report) && report.things[loc.row + i][loc.col].type == SituationReport::ENEMY)
		{
			whereEnemyIs = lionheart::Direction::NORTH;
			enemyStraightline = true;
			break;
		}
		if(isInBounds(loc.row-i, loc.col, report) && report.things[loc.row - i][loc.col].type == SituationReport::ENEMY)
		{
			whereEnemyIs = lionheart::Direction::SOUTH;
			enemyStraightline = true;
			break;
		}
		if(isInBounds(loc.row, loc.col+i, report) && report.things[loc.row][loc.col + i].type == SituationReport::ENEMY)
		{
			whereEnemyIs = lionheart::Direction::EAST;
			enemyStraightline = true;
			break;
		}
		if(isInBounds(loc.row, loc.col-i, report) && report.things[loc.row][loc.col - i].type == SituationReport::ENEMY)
		{
			whereEnemyIs = lionheart::Direction::WEST;
			enemyStraightline = true;
			break;
		}
	}
	if(!enemyStraightline && spacesToMove(currDir, loc.row, loc.col, report, 5 - defcon) > 0) return currDir; // make sure this doesn't put us in immediate danger (also write an isvalidspace function for error checking)
	std::vector<lionheart::Direction> dirs;
	lionheart::Direction dirToSwitchOn = enemyStraightline ? whereEnemyIs : currDir;
	switch(dirToSwitchOn)
	{
		case lionheart::Direction::NORTH:
			dirs.push_back(lionheart::Direction::EAST); dirs.push_back(lionheart::Direction::WEST); dirs.push_back(lionheart::Direction::SOUTH);
			break;
		case lionheart::Direction::SOUTH:
			dirs.push_back(lionheart::Direction::EAST); dirs.push_back(lionheart::Direction::WEST); dirs.push_back(lionheart::Direction::NORTH);
			break;
		case lionheart::Direction::EAST:
			dirs.push_back(lionheart::Direction::SOUTH); dirs.push_back(lionheart::Direction::NORTH); dirs.push_back(lionheart::Direction::WEST);
			break;
		case lionheart::Direction::WEST:
			dirs.push_back(lionheart::Direction::SOUTH); dirs.push_back(lionheart::Direction::NORTH); dirs.push_back(lionheart::Direction::EAST);
			break;
	}
	dirs.push_back(currDir);
	for(auto i = 0u; i < dirs.size(); ++i)
		if(spacesToMove(dirs[i], loc.row, loc.col, report, 5 - defcon) > 0) return dirs[i];
	return currDir;
}

int lionheart::ChrisWagner::spacesToMove(lionheart::Direction dir, int row, int col, SituationReport report, int maxSpaces)
{
	int toMove = 0;
	switch(dir)
	{
		case lionheart::Direction::NORTH:
			for(int i = 1; i <=maxSpaces; ++i)
			{
				if(isInBounds(row-i, col, report) && report.things[row-i][col].type == SituationReport::SPACE)
				{
					if(!inImmediateDanger(row-i, col, report)) toMove = i;					
				}
				else return toMove;							
			}
			break;
		case lionheart::Direction::SOUTH:
			for(int i = 1; i <=maxSpaces; ++i)
			{
				if(isInBounds(row+i, col, report) && report.things[row+i][col].type == SituationReport::SPACE)
				{
					if(!inImmediateDanger(row+i, col, report)) toMove = i;					
				}
				else return toMove;							
			}
			break;
		case lionheart::Direction::EAST:
			for(int i = 1; i <=maxSpaces; ++i)
			{
				if(isInBounds(row, col+i, report) && report.things[row][col+i].type == SituationReport::SPACE)
				{
					if(!inImmediateDanger(row, col+i, report)) toMove = i;					
				}
				else return toMove;							
			}
			break;
		case lionheart::Direction::WEST:
			for(int i = 1; i <=maxSpaces; ++i)
			{
				if(isInBounds(row, col-i, report) && report.things[row][col-i].type == SituationReport::SPACE)
				{
					if(!inImmediateDanger(row, col-i, report)) toMove = i;					
				}
				else return toMove;						
			}
			break;
	}
	return toMove;
}

lionheart::Direction lionheart::ChrisWagner::turnToMow(Unit const & unit, SituationReport report)
{
	lionheart::Direction currDir = unit.getFacing();	
	lionheart::Map::Location loc = unit.getLocation();
	
	for(int i = 1; i <= 3; ++i)
	{
		switch(currDir)
		{
			case lionheart::Direction::NORTH:
				if(isInBounds(loc.row - i, loc.col+2, report) 
					&& report.things[loc.row - i][loc.col+2].type == SituationReport::ENEMY
					&& report.things[loc.row][loc.col+1].type == SituationReport::SPACE) return lionheart::Direction::EAST;
				if(isInBounds(loc.row - i, loc.col-2, report) 
					&& report.things[loc.row - i][loc.col-2].type == SituationReport::ENEMY
					&& report.things[loc.row][loc.col-1].type == SituationReport::SPACE) return lionheart::Direction::WEST;
				break;
			case lionheart::Direction::SOUTH:
				if(isInBounds(loc.row + i, loc.col+2, report) 
					&& report.things[loc.row + i][loc.col+2].type == SituationReport::ENEMY
					&& report.things[loc.row][loc.col+1].type == SituationReport::SPACE) return lionheart::Direction::EAST;
				if(isInBounds(loc.row + i, loc.col-2, report) 
					&& report.things[loc.row + i][loc.col-2].type == SituationReport::ENEMY
					&& report.things[loc.row][loc.col-1].type == SituationReport::SPACE) return lionheart::Direction::WEST;
				break;
			case lionheart::Direction::EAST:
				if(isInBounds(loc.row - 2, loc.col+i, report) 
					&& report.things[loc.row - 2][loc.col+i].type == SituationReport::ENEMY
					&& report.things[loc.row-1][loc.col].type == SituationReport::SPACE) return lionheart::Direction::NORTH;
				if(isInBounds(loc.row + 2, loc.col+i, report) 
					&& report.things[loc.row + 2][loc.col+i].type == SituationReport::ENEMY
					&& report.things[loc.row+1][loc.col].type == SituationReport::SPACE) return lionheart::Direction::SOUTH;
				break;
			case lionheart::Direction::WEST:
				if(isInBounds(loc.row - 2, loc.col-i, report) 
					&& report.things[loc.row - 2][loc.col-i].type == SituationReport::ENEMY
					&& report.things[loc.row-1][loc.col].type == SituationReport::SPACE) return lionheart::Direction::NORTH;
				if(isInBounds(loc.row + 2, loc.col-i, report) 
					&& report.things[loc.row + 2][loc.col-i].type == SituationReport::ENEMY
					&& report.things[loc.row+1][loc.col].type == SituationReport::SPACE) return lionheart::Direction::SOUTH;
				break;			
		}
	}
	return currDir;
}

bool lionheart::ChrisWagner::isInBounds(int row, int col, SituationReport report)
{
	return (row >=0 && col >= 0 && row < (int)(report.things.size()) && col < (int)(report.things[row].size()));
}

bool lionheart::ChrisWagner::enemyBackOpening(SituationReport report)
{
	int col = leftSide ? reflectToR(0, report) : 0;
	for(int i = 0; isInBounds(i, col, report); ++i)
		if(report.things[i][col].type != SituationReport::SPACE
		&& report.things[i][col].type != SituationReport::ALLY) return false;
	col += leftSide ? -3 : 2;
	for(int i = fortress.minRow; i <= fortress.maxRow; ++i)
		for(int j = 0; j < 2; ++j)
			if(report.things[i][col+j].type == SituationReport::ENEMY) return true;
	return false;
}

bool lionheart::ChrisWagner::inTheCrownsCourt(Unit const & unit, SituationReport report)
{
	bool crownIsIn = false;
	for(int i = fortress.minRow; i <= fortress.maxRow && !crownIsIn; ++i)
		for(int j = fortress.minCol; j <= fortress.maxCol && !crownIsIn; ++j)
			if(report.things[i][j].type == SituationReport::ALLY && report.things[i][j].unit == CROWN) crownIsIn = true;
	if(!crownIsIn) return false;
	
	lionheart::Map::Location loc = unit.getLocation();
	if(loc.row > fortress.maxRow) return false;
	if(loc.row < fortress.minRow) return false;
	if(loc.col > fortress.maxCol) return false;
	if(loc.col < fortress.minCol) return false;
	return true;
}

lionheart::Placement lionheart::ChrisWagner::bestArcherAttack(Unit const & unit, SituationReport report)
{
	lionheart::Direction currDir = unit.getFacing();	
	lionheart::Map::Location loc = unit.getLocation();
	
	int row = loc.row-1;
	int col = loc.col-1;
	
	if(currDir == lionheart::Direction::NORTH) row -=2;
	else if(currDir == lionheart::Direction::SOUTH) row +=2;
	else if(currDir == lionheart::Direction::EAST) col +=2;
	else col -=2;
	
	std::vector<UnitType> attackPriorities;
	attackPriorities.push_back(CROWN);
	attackPriorities.push_back(ARCHER);
	attackPriorities.push_back(KNIGHT);
	attackPriorities.push_back(INFANTRY);
	
	for(auto k = 0u; k < attackPriorities.size(); ++k)
		for(int i = 0; i < 3; ++i)
			for(int j = 0; j < 3; ++j)
				if(isInBounds(row+i, col+j, report) 
					&& report.things[row+i][col+j].type == SituationReport::ENEMY
					&& report.things[row+i][col+j].unit == attackPriorities[k]) return {row+i, col+j};
	return {loc.row, loc.col};
}

lionheart::Placement lionheart::ChrisWagner::projectMovement(int moveSpaces, Unit const & unit)
{
	lionheart::Map::Location loc = unit.getLocation();	
	
	switch(unit.getFacing())
	{
		case lionheart::Direction::NORTH:return {loc.row - moveSpaces, loc.col};
		case lionheart::Direction::SOUTH:return {loc.row + moveSpaces, loc.col};
		case lionheart::Direction::EAST:return {loc.row, loc.col + moveSpaces};
		default: return {loc.row, loc.col - moveSpaces};
	}
}