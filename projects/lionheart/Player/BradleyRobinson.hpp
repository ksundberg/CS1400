#ifndef LIONHEART_BRADLEY_ROBINSON
#define LIONHEART_BRADLEY_ROBINSON
#include "Player.hpp"
#include <array>

namespace lionheart
{
	class BradleyRobinson: public Player
	{
	public:
		BradleyRobinson() :id(0){}
		Placement placeUnit(UnitType, StartBox const& box, SituationReport report)
		{
			++id;
			turnAt = 0;
			startOver = 0;
			westSide = (box.minCol < static_cast<int>(report.things[0].size() / 2));
			if (westSide)
			{
				switch (id)
				{
					// CROWN
				case 1: return{ 15, 2 };
						// KNIGHTS
				case 2: return{ 10, 4 };
				case 3: return{ 11, 4 };
				case 4: return{ 12, 4 };
				case 5: return{ 17, 4 };
				case 6: return{ 18, 4 };
				case 7: return{ 19, 4 };
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
				case 20: return{ 13, 4 };
				case 21: return{ 14, 4 };
				case 22: return{ 15, 4 };
				case 23: return{ 16, 4 };

				case 24: return{ 14, 2 };
				case 25: return{ 15, 3 };
				case 26: return{ 14, 3 };
				case 27: return{ 13, 3 };
				case 28: return{ 16, 3 };
				case 29: return{ 13, 5 };
				case 30: return{ 16, 5 };
				}
			}
			else
			{
				switch (id)
				{
					// CROWN
				case 1: return{ 15, 27 };
						// KNIGHTS
				case 2: return{ 10, 25 };
				case 3: return{ 11, 25 };
				case 4: return{ 12, 25 };
				case 5: return{ 17, 25 };
				case 6: return{ 18, 25 };
				case 7: return{ 19, 25 };
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
				case 20: return{ 13, 25 };
				case 21: return{ 14, 25 };
				case 22: return{ 15, 25 };
				case 23: return{ 16, 25 };

				case 24: return{ 14, 27 };
				case 25: return{ 15, 26 };
				case 26: return{ 14, 26 };
				case 27: return{ 13, 26 };
				case 28: return{ 16, 26 };
				case 29: return{ 13, 24 };
				case 30: return{ 16, 24 };
				}
			}
			return{ 0, 0 };
		}
		Action recommendAction(Unit const& u, SituationReport , Plan p)
		{
			++startOver;
			++turnAt;
			if (turnAt < 30*id)
			{
				if (p.hasAttack()) return p.attackEnemy();
				else return wait();
			}
			
			if (startOver == 31)
			{
				survivingPlayers = 0;
			}
			if (p.hasAttack()) return p.attackEnemy();
			if (!u.isAlive()) ++survivingPlayers;
			switch (u.getId())
			{
			case 0: 
				if (p.movesToEnemy() < 10) defendCrown = true;
				else defendCrown = false;
				return wait();
			case 1:case 2:case 3:
				return p.moveToEnemyCrown();
			case 4:case 5:case 6:	
				if (defendCrown) return p.moveToAllyCrown();
				else return p.moveToEnemyCrown();
			case 7:case 8:
				if ((survivingPlayers < 10) && (turnAt > 10)) return p.moveToEnemyCrown();
				if (turnAt < 3) return turn(Direction::NORTH);
				else wait();
			case 9:case 12:case 13:case 16: case 17:case 18:case 19:case 20:case 21: case 22: case 23:
				return p.moveToEnemy();
			case 10:case 11:
				if (defendCrown && p.movesToEnemy() > 3) return p.moveToAllyCrown();
				else return p.moveToEnemyCrown();
			case 14: case 15:
				if ((survivingPlayers < 10) && (turnAt > 10)) return p.moveToEnemyCrown();
				if (turnAt < 3) return turn(Direction::SOUTH);
				else wait();
			case 24: case 25: case 26: case 27: case 28: case 29: case 30:
				if (turnAt > 100 * 30) return p.moveToEnemyCrown();
			default:
				break;
			}
			return p.moveToEnemyCrown();
		}
		Blazon getBlazon() { return{ Color::GULES, Color::SABLE, Style::SALTIRE, "Burning Bombs" }; }
	private:
		bool westSide;
		int id;
		int turnAt;
		int survivingPlayers;
		int startOver;
		bool defendCrown;
	};
}


#endif
