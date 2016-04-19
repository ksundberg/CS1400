#include "PaulRoylance.hpp"

lionheart::Placement lionheart::PaulRoylance::placeUnit(UnitType,
	StartBox const &box,
	SituationReport report)
{
	++unitID;
	left = (box.minCol < static_cast<int>(report.things[0].size() / 2));
	if (left)
	{
		switch (unitID)
		{
			// CROWN
		case 1: return{ 15, 2 };
				// KNIGHTS
		case 2: return{ 11, 4 };
		case 3: return{ 12, 4 };
		case 4: return{ 13, 4 };
		case 5: return{ 16, 4 };
		case 6: return{ 17, 4 };
		case 7: return{ 18, 4 };
				// ARCHERS
		case 8: return{ 10, 3 };
		case 9: return{ 10, 5 };
		case 10:return{ 13, 7 };
		case 11:return{ 14, 5 };
		case 12:return{ 15, 5 };
		case 13:return{ 16, 7 };
		case 14: return{ 19, 3 };
		case 15: return{ 19, 5 };
				 // INFANTRY
		case 16: return{ 14, 6 };
		case 17: return{ 14, 7 };
		case 18: return{ 15, 6 };
		case 19: return{ 15, 7 };
		case 20: return{ 13, 2 };
		case 21: return{ 14, 4 };
		case 22: return{ 15, 4 };
		case 23: return{ 16, 2 };

		case 24: return{ 14, 2 };
		case 25: return{ 15, 3 };
		case 26: return{ 14, 3 };
		case 27: return{ 13, 3 };
		case 28: return{ 16, 3 };
		case 29: return{ 13, 5 };
		case 30: unitID = 0; return{ 16, 5 };
		}
	}
	else
	{
		switch (unitID)
		{
			// CROWN
		case 1: return{ 15, 27 };
				// KNIGHTS
		case 2: return{ 11, 25 };
		case 3: return{ 12, 25 };
		case 4: return{ 13, 25 };
		case 5: return{ 16, 25 };
		case 6: return{ 17, 25 };
		case 7: return{ 18, 25 };
				// ARCHERS
		case 8: return{ 10, 26 };
		case 9: return{ 10, 24 };
		case 10:return{ 13, 22 };
		case 11:return{ 14, 24 };
		case 12:return{ 15, 24 };
		case 13:return{ 16, 22 };
		case 14: return{ 19, 26 };
		case 15: return{ 19, 24 };
				 // INFANTRY
		case 16: return{ 14, 23 };
		case 17: return{ 14, 22 };
		case 18: return{ 15, 23 };
		case 19: return{ 15, 22 };
		case 20: return{ 13, 27 };
		case 21: return{ 14, 25 };
		case 22: return{ 15, 25 };
		case 23: return{ 16, 27 };

		case 24: return{ 14, 27 };
		case 25: return{ 15, 26 };
		case 26: return{ 14, 26 };
		case 27: return{ 13, 26 };
		case 28: return{ 16, 26 };
		case 29: return{ 13, 24 };
		case 30:unitID = 0; return{ 16, 24 };
		}
	}
	return{ 0, 0 };
}

/*Checks if there is enemies behind and returns true if so.*/
bool enemyBehind(struct lionheart::SituationReport r)
{
	for (auto i = 0u; i < 30; ++i){
		if (r.things[i][0].type == lionheart::SituationReport::ENEMY){
			return true;
		}
	}
	for (auto i = 0u; i < 30; ++i){
		if (r.things[i][29].type == lionheart::SituationReport::ENEMY){
			return true;
		}
	}
	return false;
}

/*Calculates enemy average position and returns true if they moved.*/
void lionheart::PaulRoylance::enemyLocationAverage(struct lionheart::SituationReport r)
{
	int xTot = 0;
	int yTot = 0;
	enemyCt = 0;
	for (auto i = 0u; i < 30; ++i){
		for (auto j = 0u; j < 30; ++j){
			if (r.things[i][j].type == lionheart::SituationReport::ENEMY){
				xTot += i;
				yTot += j;
				enemyCt += 1;
			}
		}
	}
	if(enemyCt > 0){
		xTot /= enemyCt;
		yTot /= enemyCt;
	}
	if (xTot != xTotal || yTot != yTotal){
		xTotal = xTot;
		yTotal = yTot;
		time = 0;
	}
	else time += 1;
}



lionheart::Action
lionheart::PaulRoylance::recommendAction(Unit const &u, SituationReport r, Plan p)
{
	if (p.hasAttack()) return p.attackEnemy();
	
	if (time < 5)
	{ // Enemy moving, wait for them to approach.
		if (checkEnemy) {
			enemyLocationAverage(r);
			checkEnemy = false;
		}
		switch (u.getId())
		{
		case 0:
			checkEnemy = true;
			if (enemyBehind(r)){
				if (left) return p.moveToLocation(u.getLocation().row, 4);
				else return p.moveToLocation(u.getLocation().row, 25);
			}
			if (p.movesToEnemy() <= 1)
				return p.attackEnemy();
			return wait();
		case 1:case 2:case 3:
			if (p.movesToEnemy() <= 3)
			{
				return p.attackEnemy();
			}
			return wait();
		case 4:case 5:case 6:
			if (p.movesToEnemy() <= 3)
			{
				return p.attackEnemy();
			}
			return wait();
			// ARCHERS
		case 7:case 8:
			//Attack nearby
			if (p.movesToEnemy() <= 3)
				return p.attackEnemy();
			// If not in position, get into position.
			if (left) {
				if (u.getId() == 7){
					if (u.getLocation().row != 10 || u.getLocation().col != 3)
						return p.moveToLocation(10, 3);
				}
				else if (u.getLocation().row != 10 || u.getLocation().col != 5)
						return p.moveToLocation(10, 5);
			}
			else {
				if (u.getId() == 7){
					if (u.getLocation().row != 10 || u.getLocation().col != 26)
						return p.moveToLocation(10, 26);
				}
				else if (u.getLocation().row != 10 || u.getLocation().col != 24)
						return p.moveToLocation(10, 24);
			}
			// Direction
			return turn(Direction::NORTH);
		case 9:case 12:
			//Attack nearby
			if (p.movesToEnemy() <= 3)
				return p.attackEnemy();
			// If not in position, get into position.
			if (left) {
				if (u.getId() == 9){
					if (u.getLocation().row != 13 || u.getLocation().col != 7)
						return p.moveToLocation(13, 7);
				}
				else if (u.getLocation().row != 16 || u.getLocation().col != 7)
					return p.moveToLocation(16, 7);
			}
			else {
				if (u.getId() == 9){
					if (u.getLocation().row != 13 || u.getLocation().col != 22)
						return p.moveToLocation(13, 22);
				}
				else if (u.getLocation().row != 16 || u.getLocation().col != 22)
					return p.moveToLocation(16, 22);
			}
			// Direction
			if (left)
				return turn(Direction::EAST);
			return turn(Direction::WEST);
		case 10:case 11:
			if (u.getLocation().col == 5) return move(1);
			if (u.getLocation().col == 24) return move(1);
		case 13:case 14:
			//Attack nearby
			if (p.movesToEnemy() <= 3)
				return p.attackEnemy();
			// If not in position, get into position.
			if (left) {
				if (u.getId() == 13){
					if (u.getLocation().row != 19 || u.getLocation().col != 3)
						return p.moveToLocation(19, 3);
				}
				else if (u.getLocation().row != 19 || u.getLocation().col != 5)
					return p.moveToLocation(19, 5);
			}
			else {
				if (u.getId() == 13){
					if (u.getLocation().row != 19 || u.getLocation().col != 26)
						return p.moveToLocation(19, 26);
				}
				else if (u.getLocation().row != 19 || u.getLocation().col != 24)
					return p.moveToLocation(19, 24);
			}
			// Direction
			return turn(Direction::SOUTH);
		case 16:
		case 18:
			break;
		case 15:
		case 17:
		case 19:
		case 20:
			if (p.movesToEnemy() <= 3)
			{
				return p.attackEnemy();
			}
			return move(1);
		// EVERYTHING ELSE
		default:
			if (p.movesToEnemy() <= 3)
			{
				return p.attackEnemy();
			}
			break;
		}
		return wait();
	}




	else if (time < 45)
	{ // Enemy stopped moving so prepare position of army.
		if (checkEnemy) {
			time += 1;
			checkEnemy = false;
		}
		switch (u.getId()){
		case 0:
			checkEnemy = true;
			if (enemyBehind(r)){
				if (left) return p.moveToLocation(u.getLocation().row, 4);
				else return p.moveToLocation(u.getLocation().row, 25);
			}
			if (p.movesToEnemy() <= 1)
				return p.attackEnemy();
			return wait();
		case 1:case 2:case 3:
			if (p.movesToEnemy() <= 3)
			{
				return p.attackEnemy();
			}
			return p.moveToLocation(7, 15);
		case 4:case 5:case 6:
			if (p.movesToEnemy() <= 3)
			{
				return p.attackEnemy();
			}
			return p.moveToLocation(22, 15);
			//ARCHERS
		case 7:case 8:
			//Attack nearby
			if (p.movesToEnemy() <= 3)
				return p.attackEnemy();
			// If not in position, get into position.
			if (left) {
				if (u.getId() == 7){
					if (u.getLocation().row != 10 || u.getLocation().col != 3)
						return p.moveToLocation(10, 3);
				}
				else if (u.getLocation().row != 10 || u.getLocation().col != 5)
					return p.moveToLocation(10, 5);
			}
			else {
				if (u.getId() == 7){
					if (u.getLocation().row != 10 || u.getLocation().col != 26)
						return p.moveToLocation(10, 26);
				}
				else if (u.getLocation().row != 10 || u.getLocation().col != 24)
						return p.moveToLocation(10, 24);
			}
			// Direction
			return turn(Direction::NORTH);
		case 9:case 12:
			//Attack nearby
			if (p.movesToEnemy() <= 3)
				return p.attackEnemy();
			// If not in position, get into position.
			if (left) {
				if (u.getId() == 9){
					if (u.getLocation().row != 13 || u.getLocation().col != 7)
						return p.moveToLocation(13, 7);
				}
				else if (u.getLocation().row != 16 || u.getLocation().col != 7)
					return p.moveToLocation(16, 7);
			}
			else {
				if (u.getId() == 9){
					if (u.getLocation().row != 13 || u.getLocation().col != 22)
						return p.moveToLocation(13, 22);
				}
				else if (u.getLocation().row != 16 || u.getLocation().col != 22)
					return p.moveToLocation(16, 22);
			}
			// Direction
			if (left)
				return turn(Direction::EAST);
			return turn(Direction::WEST);
		case 13:case 14:
			//Attack nearby
			if (p.movesToEnemy() <= 3)
				return p.attackEnemy();
			// If not in position, get into position.
			if (left) {
				if (u.getId() == 13){
					if (u.getLocation().row != 19 || u.getLocation().col != 3)
						return p.moveToLocation(19, 3);
				}
				else if (u.getLocation().row != 19 || u.getLocation().col != 5)
					return p.moveToLocation(19, 5);
			}
			else {
				if (u.getId() == 13){
					if (u.getLocation().row != 19 || u.getLocation().col != 26)
						return p.moveToLocation(19, 26);
				}
				else if (u.getLocation().row != 19 || u.getLocation().col != 24)
					return p.moveToLocation(19, 24);
			}
			// Direction
			return turn(Direction::SOUTH);
			// EVERYTHING ELSE
		default:
			if (p.movesToEnemy() <= 3)
			{
				return p.attackEnemy();
			}
			if (time < 25){
				if (left) return p.moveToLocation(24, 9);
				else return p.moveToLocation(24, 20);
			}
			else{
				if (left) return p.moveToLocation(24, 20);
				else return p.moveToLocation(24, 9);
			}
			break;
		}
	}




	else if (time < 150)
	{ // Direct army to chase down and attack towards the crown.
		if (checkEnemy) {
			time += 1;
			checkEnemy = false;
		}
		switch (u.getId()){
		case 0:
			checkEnemy = true;
			if (enemyBehind(r)){
				if (left) return p.moveToLocation(u.getLocation().row, 4);
				else return p.moveToLocation(u.getLocation().row, 25);
			}
			if (p.movesToEnemy() <= 1)
				return p.attackEnemy();
			return wait();
		case 1:case 2:case 3:
			if (p.movesToEnemy() <= 3)
			{
				return p.attackEnemy();
			}
			return p.moveToLocation(7, 15);
		case 4:case 5:case 6:
			if (p.movesToEnemy() > 3)
			{
				return p.attackEnemy();
			}
			return p.moveToLocation(22, 15);
		// ARCHERS
		case 7:case 8:
			//Attack nearby
			if (p.movesToEnemy() <= 3)
				return p.attackEnemy();
			// If not in position, get into position.
			if (left) {
				if (u.getId() == 7){
					if (u.getLocation().row != 10 || u.getLocation().col != 3)
						return p.moveToLocation(10, 3);
				}
				else if (u.getLocation().row != 10 || u.getLocation().col != 5)
					return p.moveToLocation(10, 5);
			}
			else {
				if (u.getId() == 7){
					if (u.getLocation().row != 10 || u.getLocation().col != 26)
						return p.moveToLocation(10, 26);
				}
				else if (u.getLocation().row != 10 || u.getLocation().col != 24)
					return p.moveToLocation(10, 24);
			}
			// Direction
			return turn(Direction::NORTH);
		case 9:case 12:
			//Attack nearby
			if (p.movesToEnemy() <= 3)
				return p.attackEnemy();
			// If not in position, get into position.
			if (left) {
				if (u.getId() == 9){
					if (u.getLocation().row != 13 || u.getLocation().col != 7)
						return p.moveToLocation(13, 7);
				}
				else if (u.getLocation().row != 16 || u.getLocation().col != 7)
					return p.moveToLocation(16, 7);
			}
			else {
				if (u.getId() == 9){
					if (u.getLocation().row != 13 || u.getLocation().col != 22)
						return p.moveToLocation(13, 22);
				}
				else if (u.getLocation().row != 16 || u.getLocation().col != 22)
					return p.moveToLocation(16, 22);
			}
			// Direction
			if (left)
				return turn(Direction::EAST);
			return turn(Direction::WEST);
		case 13:case 14:
			//Attack nearby
			if (p.movesToEnemy() <= 3)
				return p.attackEnemy();
			// If not in position, get into position.
			if (left) {
				if (u.getId() == 13){
					if (u.getLocation().row != 19 || u.getLocation().col != 3)
						return p.moveToLocation(19, 3);
				}
				else if (u.getLocation().row != 19 || u.getLocation().col != 5)
					return p.moveToLocation(19, 5);
			}
			else {
				if (u.getId() == 13){
					if (u.getLocation().row != 19 || u.getLocation().col != 26)
						return p.moveToLocation(19, 26);
				}
				else if (u.getLocation().row != 19 || u.getLocation().col != 24)
					return p.moveToLocation(19, 24);
			}
			// Direction
			return turn(Direction::SOUTH);
			// EVERYTHING ELSE
		default:
			return p.moveToEnemyCrown();
			break;
		}
	}




	// Final Countdown: all forces chase down and kill the enemy crown.
	if (u.getId() == 0)
	{
		if (enemyBehind(r)){
			if (left) return p.moveToLocation(u.getLocation().row, 4);
			else return p.moveToLocation(u.getLocation().row, 25);
		}
		if (p.movesToEnemy() <= 1)
			return p.attackEnemy();
		return wait();
	}
	return p.moveToEnemyCrown();
}

lionheart::Blazon lionheart::PaulRoylance::getBlazon()
{
	return{ Color::GULES, Color::SABLE, Style::PALE, "Paul Roylance" };
}
