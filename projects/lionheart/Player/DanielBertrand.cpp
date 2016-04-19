#include "DanielBertrand.hpp"
#include "Unit.hpp"



lionheart::Direction lionheart::DanielBertrand::defensiveFace(Unit const &u){
	switch (u.getId()){
		case 1:
		case 2:
		case 3:
		case 7:
		case 8:
		case 30:
		case 31:
			return lionheart::Direction::NORTH;
			break;
		case 4:
		case 5:
		case 6:
		case 13:
		case 14:
		case 32:
		case 33:
			return lionheart::Direction::SOUTH;
			break;
		default:
			break;
	}
	if (westSide)
		return lionheart::Direction::EAST;
	return lionheart::Direction::WEST;
}

lionheart::Action lionheart::DanielBertrand::fillTheGap(Unit const &u, SituationReport &r){
	Map::Location l = u.getLocation();
	int row = l.row;
	int col = l.col;

	switch (u.getId()){
		case 1:
		case 2:
		case 3:
		case 31:
			if (r.things[row - 1][col].type == lionheart::SituationReport::SPACE && !(row - 1 < 10))
				return move(1);
			break;
		case 4:
		case 5:
		case 6:
		case 32:
			if (r.things[row + 1][col].type == lionheart::SituationReport::SPACE && !(row + 1 > 19))
				return move(1);
			break;
		case 10:
		case 11:
		case 34:
		case 35:
		case 36:
		case 37:	
			if (u.getFacing() == lionheart::Direction::EAST){
				if (r.things[row][col + 1].type == lionheart::SituationReport::SPACE && !(col + 1 > 7))
					return move(1);
			}
			else if (u.getFacing() == lionheart::Direction::WEST){
				if (r.things[row][col - 1].type == lionheart::SituationReport::SPACE && !(col - 1 < 22))
					return move(1);
			}
			break;
		default:
			break;
		}
	return wait();
}

bool lionheart::DanielBertrand::wallsBreached(SituationReport &r){
	for (int i = 0; i < 10; ++i){
		if (westSide){
			for (int j = 0; j < 6; ++j){
				if (r.things[(i + 10)][(j + 2)].type == lionheart::SituationReport::ENEMY)
					return true;
			}
		}
		else{
			for (int j = 0; j < 6; ++j){
				if (r.things[(i + 10)][(j + 22)].type == lionheart::SituationReport::ENEMY)
					return true;
			}
		}
	}
	return false;
}

lionheart::Action lionheart::DanielBertrand::recommendAction(Unit const &u, SituationReport r, Plan p){
	//keeping track of turns
	moves++;
	if (moves%30 == 0){
		turns++;
		if (turns > 100)
			charge = true;
	}
	//in the first few turns assume defensive positions
	if (turns < 2){
		lionheart::Direction mydir = defensiveFace(u);
		return turn(mydir);
	}
	
	//if there is an enemy in front of you attack it
	if (p.hasAttack()) return p.attackEnemy();
	
	if (u.getType() == CROWN) return wait();

	if (u.getType() == ARCHER) {
		if (p.movesToEnemy() < 4) return p.attackEnemy();
	}
	if (p.movesToEnemy() < 1){
		return p.attackEnemy();
	}
	if (wallsBreached(r)) return p.attackEnemy();

	
	if (charge == false){
		lionheart::Action a = fillTheGap(u, r);
		return a;
	}
	else{
		switch (u.getId()){
		case 0:
			return wait();
			break;
		default:
			return p.attackEnemy();
			break;
		}
	}

	//if you get all the way down here just wait
	return wait();
}

lionheart::Blazon lionheart::DanielBertrand::getBlazon()
{
	return{ Color::AZURE, Color::ARGENT, Style::FESS, "Daniel Bertrand" };
}

lionheart::Placement lionheart::DanielBertrand::placeUnit(UnitType, StartBox const &box, SituationReport report){
	id++;
	charge = false;
	moves = 0;
	turns = 0;
	westSide = (box.minCol < static_cast<int>(report.things[0].size() / 2));
	if (westSide){
		switch (id){
		// CROWN
		case 1: return{ 15, 2 };
		// KNIGHTS
		case 2: return{ 12, 4 };
		case 3: return{ 13, 4 };
		case 4: return{ 14, 4 };
		case 5: return{ 15, 4 };
		case 6: return{ 16, 4 };
		case 7: return{ 17, 4 };
		// ARCHERS
		case 8: return{ 10, 3 };
		case 9: return{ 10, 5 };
		case 10:return{ 13, 7 };
		case 11:return{ 14, 5 };
		case 12:return{ 15, 5 };
		case 13:return{ 16, 7 };
		case 14:return{ 19, 3 };
		case 15:return{ 19, 5 };
		// INFANTRY
		case 16: return{ 10, 4 };
		case 17: return{ 11, 4 };
		case 18: return{ 18, 4 };
		case 19: return{ 19, 4 };
		case 20: return{ 14, 7 };
		case 21: return{ 15, 7 };
		case 22: return{ 14, 6 };
		case 23: return{ 15, 6 };
		case 24: return{ 14, 2 };
		case 25: return{ 14, 3 };
		case 26: return{ 15, 3 };
		case 27: return{ 16, 3 };
		case 28: return{ 16, 2 };
		case 29: return{ 13, 6 };
		case 30: id = 0; return{ 16, 6 };
		}
	}
	else{
		switch (id){
		// CROWN
		case 1: return{ 15, 27 };
		// KNIGHTS
		case 2: return{ 12, 25 };
		case 3: return{ 13, 25 };
		case 4: return{ 14, 25 };
		case 5: return{ 15, 25 };
		case 6: return{ 16, 25 };
		case 7: return{ 17, 25 };
		// ARCHERS
		case 8: return{ 10, 26 };
		case 9: return{ 10, 24 };
		case 10:return{ 13, 22 };
		case 11:return{ 14, 24 };
		case 12:return{ 15, 24 };
		case 13:return{ 16, 22 };
		case 14:return{ 19, 26 };
		case 15:return{ 19, 24 };
		// INFANTRY
		case 16: return{ 10, 25 };
		case 17: return{ 11, 25 };
		case 18: return{ 18, 25 };
		case 19: return{ 19, 25 };
		case 20: return{ 14, 22 };
		case 21: return{ 15, 22 };
		case 22: return{ 14, 23 };
		case 23: return{ 15, 23 };
		case 24: return{ 14, 27 };
		case 25: return{ 14, 26 };
		case 26: return{ 15, 26 };
		case 27: return{ 16, 26 };
		case 28: return{ 16, 27 };
		case 29: return{ 13, 23 };
		case 30: id = 0; return{ 16, 23 };
		}
	}
	return{ 0, 0 };
}
