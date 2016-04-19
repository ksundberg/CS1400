#ifndef LIONHEART_MICHAEL_DAVENPORT
#define LIONHEART_MICHAEL_DAVENPORT
#include "Player.hpp"
#include <math.h>
#include <algorithm>

namespace lionheart
{
	class MichaelDavenport : public Player
	{
	public:
		Placement placeUnit(UnitType, StartBox const& box, SituationReport report) {
			isWest = (box.minCol < static_cast<int>(report.things[0].size() / 2));
			turn = 1;
			subTurn = 1;
			stratSwapThreshold = 80;

			crownHideRow = 14;
			if (isWest)
				crownHideCol = 0;
			else
				crownHideCol = 29;

			++id;
			switch (id){
				// CROWN
				case 1: return placeInBox(0,2, box);
				// KNIGHTS
				case 2: return placeInBox(1,2, box);
				case 3: return placeInBox(2,2, box);
				case 4: return placeInBox(3,2, box);
				case 5: return placeInBox(7,2, box);
				case 6: return placeInBox(8,2, box);
				case 7: return placeInBox(9,2, box);
				// ARCHERS
				case 8: return placeInBox(0,0, box);
				case 9: return placeInBox(1,0, box);
				case 10:return placeInBox(2,0, box);
				case 11:return placeInBox(3,0, box);
				case 12:return placeInBox(6,0, box);
				case 13:return placeInBox(7,0, box);
				case 14:return placeInBox(8,0, box);
				case 15:return placeInBox(9,0, box);
				// INFANTRY
				case 16: return placeInBox(0,1, box);
				case 17: return placeInBox(1,1, box);
				case 18: return placeInBox(2,1, box);
				case 19: return placeInBox(3,1, box);
				case 20: return placeInBox(4,1, box);
				case 21: return placeInBox(5,1, box);
				case 22: return placeInBox(6,1, box);
				case 23: return placeInBox(7,1, box);
				case 24: return placeInBox(8,1, box);
				case 25: return placeInBox(9,1, box);
				case 26: return placeInBox(4,2, box);
				case 27: return placeInBox(5,2, box);
				case 28: return placeInBox(6,2, box);
				case 29: return placeInBox(0,3, box);
				case 30: id=0; return placeInBox(9,3, box);
			}

			return{ 0, 0 };
		}

		Action recommendAction(Unit const& u, SituationReport r, Plan p) {
			updateTurn(r);

			//Attack immediately if available
			if (p.hasAttack()) {
				return p.attackEnemy();
			}

			//Break recommended action down by unit type
			Action action = lionheart::wait();
			if (u.getType() == CROWN) {
				action = moveCrownToHide(r, p);
			}
			else if (u.getType() == KNIGHT) {
				if (turn < stratSwapThreshold)
					action = moveKnightsToKing(u, p);
				else
					action = p.moveToEnemyCrown();
			}
			else if (u.getType() == INFANTRY) {
				if (turn < stratSwapThreshold)
					action = lionheart::wait();
				else
					action = p.moveToEnemyCrown();
			}
			else if (u.getType() == ARCHER) {
				if (archerHasAttack(u,r,p))
					action = archerAttack(u,r,p);
				else {
					if (turn < stratSwapThreshold)
						action = faceArcherToEnemy(u, r);
					else
						action = p.moveToEnemyCrown();
				}
			}
			return action;
		}

		Blazon getBlazon() {
			return{ Color::ARGENT, Color::SABLE, Style::SALTIRE, "memes" };
		}

	private:
		bool isWest;
		int crownHideRow;
		int crownHideCol;
		int turn;
		int subTurn;
		int stratSwapThreshold;
		int id = 0;

		Action moveCrownToHide(SituationReport r, Plan p) {
			if (r.things[crownHideRow][crownHideCol].unit == lionheart::UnitType::CROWN) {//cycle between two positions
				return p.moveToLocation(crownHideRow + 1, crownHideCol);
			}
			return p.moveToLocation(crownHideRow, crownHideCol);
		}

		Action moveKnightsToKing(Unit const& u, Plan p) {
			Action action = lionheart::wait();
			if (turn < 20) {//Knights are likely not in place yet, keep them moving into place
				if (u.getId() == 1 || u.getId() == 2 || u.getId() == 3)
					action = p.moveToLocation(13, crownHideCol);
				else if (u.getId() == 4 || u.getId() == 5 || u.getId() == 6)
					action = p.moveToLocation(16, crownHideCol);
			}
			else {//Knights are likely in place, make them face a defensive position
				if (u.getId() == 1 || u.getId() == 2 || u.getId() == 3)
					action = lionheart::turn(Direction::NORTH);
				else if (u.getId() == 4 || u.getId() == 5 || u.getId() == 6)
					action = lionheart::turn(Direction::SOUTH);
			}
			return action;
		}

		bool archerHasAttack(Unit const& u, SituationReport report, Plan) {
			int c = u.getLocation().col;
			int r = u.getLocation().row;
			auto dir = u.getFacing();
			bool res = false;

			if (dir == Direction::WEST)
				res = enemyExistsIn(r - 1, r + 1, c - 3, c - 1, report);
			else if (dir == Direction::EAST)
				res = enemyExistsIn(r - 1, r + 1, c + 1, c + 3, report);
			else if (dir == Direction::NORTH)
				res = enemyExistsIn(r - 3, r - 1, c - 1, c + 1, report);
			else if (dir == Direction::SOUTH)
				res = enemyExistsIn(r + 1, r + 3, c - 1, c + 1, report);

			return res;
		}

		Action archerAttack(Unit const& u, SituationReport report, Plan){\
			int c = u.getLocation().col;
			int r = u.getLocation().row;
			auto dir = u.getFacing();
			Placement pos;

			if (dir == Direction::WEST)
				pos = getEnemyIn(r - 1, r + 1, c - 3, c - 1, report);
			else if (dir == Direction::EAST)
				pos = getEnemyIn(r - 1, r + 1, c + 1, c + 3, report);
			else if (dir == Direction::NORTH)
				pos = getEnemyIn(r - 3, r - 1, c - 1, c + 1, report);
			else if (dir == Direction::SOUTH)
				pos = getEnemyIn(r + 1, r + 3, c - 1, c + 1, report);

			return lionheart::attack(pos);
		}

		Action faceArcherToEnemy(Unit const& u, SituationReport report) {
			int c = u.getLocation().col;
			int r = u.getLocation().row;
			Action action = lionheart::wait();

			if (enemyExistsIn(r - 1, r + 1, c + 1, c + 3, report)) 
				action = lionheart::turn(Direction::EAST);
			else if (enemyExistsIn(r - 1, r + 1, c - 3, c - 1, report)) 
				action = lionheart::turn(Direction::WEST);
			else if (enemyExistsIn(r + 1, r + 3, c - 1, c + 1, report)) 
				action = lionheart::turn(Direction::SOUTH);
			else if (enemyExistsIn(r - 3, r - 1, c - 1, c + 1, report)) 
				action = lionheart::turn(Direction::NORTH);

			return action;
		}

		bool enemyExistsIn(int minRow, int maxRow, int minCol, int maxCol, SituationReport report) {
			auto pos = getEnemyIn(minRow, maxRow, minCol, maxCol, report);
			if (pos.row == -1 && pos.col == -1)
				return false;
			return true;
		}

		Placement getEnemyIn(int minRow, int maxRow, int minCol, int maxCol, SituationReport report) {
			minRow = boundsCheck(minRow);
			maxRow = boundsCheck(maxRow);
			minCol = boundsCheck(minCol);
			maxCol = boundsCheck(maxCol);

			for (int c = minCol; c <= maxCol; ++c)
				for (int r = minRow; r <= maxRow; ++r)
					if (report.things[r][c].type == SituationReport::ENEMY)
						return {r,c};

			return {-1,-1};
		}

		void updateTurn(SituationReport r) {
			int subTurnMax = std::min(unitsStillAlive(r), enemiesStillAlive(r));
			if (subTurn > subTurnMax) {
				turn++;
				subTurn = 1;
			}
			subTurn++;
		}

		Placement placeInBox(int row, int col, StartBox const& box) {
			int offset = 5;
			if (isWest)
				offset = 0;
			return{ box.minRow + row, box.minCol + abs(col - offset) };
		}

		int unitsStillAlive(SituationReport report) {
			int unitsAlive = 0;
			for (int c = 0; c < 30; ++c)
				for (int r = 0; r < 30; ++r)
					if (report.things[r][c].type == SituationReport::ALLY)
						unitsAlive++;
			return unitsAlive;
		}

		int enemiesStillAlive(SituationReport report) {
			int unitsAlive = 0;
			for (int c = 0; c < 30; ++c)
				for (int r = 0; r < 30; ++r)
					if (report.things[r][c].type == SituationReport::ENEMY)
						unitsAlive++;
			return unitsAlive;
		}

		int boundsCheck(int position) {
			if (position < 0)
				return 0;
			if (position > 29)
				return 29;
			return position;
		}
	};
}

#endif
