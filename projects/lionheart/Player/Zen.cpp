#include "Zen.hpp"

lionheart::Placement lionheart::Zen::placeUnit(UnitType,
	StartBox const &box,
	SituationReport )
{
	/*Fill this out with instructions on how to place your initial units.  Without
	* changes your units will fill the starting box from top left to bottom right
	* in the order constructed.*/
	int midRow = (box.maxRow - box.minRow) / 2 + box.minRow;
	int midCol = (box.maxCol - box.minCol) / 2 + box.minCol;

	//int id = 0;
	// for (id = 0; id < 31; id++)
	id++;
	{
		switch (id)
		{
			// CROWN
		case 1: return{ midRow, midCol - 2 };
				// KNIGHTS
		case 2: return{ midRow + 1, midCol + 3 };
		case 3: return{ midRow + 2, midCol + 3 };
		case 4: return{ midRow - 1, midCol + 2 };
		case 5: return{ midRow - 2, midCol + 2 };
		case 6: return{ midRow + 3, midCol + 2 };
		case 7: return{ midRow + 4, midCol + 2 };
				// ARCHERS
		case 8: return{ midRow - 3, midCol };
		case 9: return{ midRow + 5, midCol };
		case 10:return{ midRow + 4, midCol };
		case 11:return{ midRow - 4, midCol };
		case 12:return{ midRow - 3, midCol + 2 };
		case 13:return{ midRow + 5, midCol + 1 };
		case 14: return{ midRow - 3, midCol + 1 };
		case 15: return{ midRow + 5, midCol + 1 };
				 // INFANTRY
		case 16: return{ midRow + 1, midCol - 1 };
		case 17: return{ midRow + 1, midCol - 2 };
		case 18: return{ midRow + 4, midCol - 2 };
		case 19: return{ midRow - 1, midCol - 1 };
		case 20: return{ midRow - 1, midCol };
		case 21: return{ midRow - 1, midCol + 1 };
		case 22: return{ midRow + 2, midCol };
		case 23: return{ midRow + 3, midCol };

		case 24: return{ midRow - 4, midCol - 2 };
		case 25: return{ midRow - 3, midCol - 2 };
		case 26: return{ midRow - 2, midCol - 2 };
		case 27: return{ midRow - 1, midCol - 2 };
		case 28: return{ midRow + 2, midCol - 2 };
		case 29: return{ midRow, midCol };
		case 30: return{ midRow - 3, midCol + 3 };
		}

	}

	return{ 0, 0 };

}

lionheart::Action
lionheart::Zen::recommendAction(Unit const& u, SituationReport, Plan p)
{
	if (p.hasAttack()) return p.attackEnemy();
	if (u.getType() == CROWN) {
		return wait();
	}
	if (u.getType() == ARCHER) {
		if (p.movesToEnemy() < 4) return p.attackEnemy();
		return p.moveToEnemy();
	}
	if (u.getType() == KNIGHT) {

		if (p.hasAttack())
		{
			return p.attackEnemy();
		}
		return p.moveToEnemy();
		
		return p.attackEnemy();
	}
	if (u.getType() == INFANTRY){
		if (p.hasAttack())
		{
			return p.attackEnemy();
		}
		else
		{
			if (p.movesToEnemy() < 3) return p.moveToEnemyCrown();
			return p.attackEnemy();
		}
	}

	if (p.movesToAllyCrown() > 20) {
		return p.moveToAllyCrown();
	}
	return p.moveToEnemyCrown();
}
// return Action();



lionheart::Blazon lionheart::Zen::getBlazon()
{
	/*Return your blazon here.  In case of conflicts preference will be given to
	* the students that have registered their blazons in class.*/

	return{ Color::VERT, Color::OR, Style::BEND_SINISTER, "Zen" };
}
