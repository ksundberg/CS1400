#ifndef LIONHEART_LEIF_CHIPMAN
#define LIONHEART_LEIF_CHIPMAN
#include "Player.hpp"

namespace lionheart
{
	//GLOBALS

	auto id = 0;
	bool left = true;  // My starting side.
	int turns = 0;

	int valid_loc(int y)
	{
		if (y < 0)
			return 0;
		else if (y > 29)
			return 29;
		else
			return y;
	}


	char meleeAware(SituationReport report, Unit const& u)
	{
		int x1 = u.getLocation().row;
		int y1 = u.getLocation().col;
		for (unsigned int i = -1; i < 2; i++)
			for (unsigned int j = -1; i < 2; j++)
				if (report.things[valid_loc(x1 + i)][valid_loc(y1 + j)].type == lionheart::SituationReport::ENEMY)
				{
					if (i == 0 && y1*j < y1) return 'N';   ///  4 straight directions
					if (i == 0 && y1*j >= y1) return 'S';   ///
					if (j == 0 && x1*i < x1) return 'W';
					if (j == 0 && x1*i <= x1) return 'E';

					if (x1*i < x1 && y1*j < y1) return 'W';   /// Enemy within range, but unit isn't facing enemy
					if (x1*i < x1 && y1*j >= y1) return 'W';
					if (x1*i >= x1 && y1*j < y1) return 'E';
					if (x1*i >= x1 && y1*j >= y1) return 'E';
				}
		return 'q';
	}

	class LeifChipman : public Player
	{
	public:
		Placement placeUnit(UnitType, StartBox const& box, SituationReport report)
		{
			turns = 0;
			id++;
			if (id > 30) id = 1;  // resets id for each new game
			auto leftSide = (box.minCol < static_cast<int>(report.things[0].size() / 2));
			if (leftSide)
			{
				left = true;
				switch (id)
				{
					// CROWN
				case 1:
					return{ 14, 2 };
					// KNIGHTS
				case 2:
					return{ 17, 4 };
				case 3:
					return{ 18, 4 };
				case 4:
					return{ 18, 3 };
				case 5:
					return{ 18, 5 };
				case 6:
					return{ 19, 4 };
				case 7:
					return{ 19, 6 };
					// ARCHERS
				case 8:
					return{ 10, 5 };
				case 9:
					return{ 10, 6 };
				case 10:
					return{ 10, 7 };
				case 11:
					return{ 14, 5 };
				case 12:
					return{ 12, 4 };
				case 13:
					return{ 15, 6 };
				case 14:
					return{ 14, 4 };
				case 15:
					return{ 14, 3 };
					// INFANTRY
				case 16:
					return{ 10, 3 };
				case 17:
					return{ 10, 4 };
				case 18:
					return{ 11, 3 };
				case 19:
					return{ 11, 4 };
				case 20:
					return{ 11, 5 };
				case 21:
					return{ 11, 6 };
				case 22:
					return{ 12, 3 };
				case 23:
					return{ 12, 5 };
				case 24:
					return{ 12, 6 };
				case 25:
					return{ 15, 3 };
				case 26:
					return{ 15, 4 };
				case 27:
					return{ 15, 5 };
				case 28:
					return{ 14, 6 };
				case 29:
					return{ 14, 7 };
				case 30:
					return{ 15, 7 };
				}
			}
			else
			{
				left = false;
				switch (id)
				{
					// CROWN 
				case 1:
					return{ 14, 27 };
					// KNIGHTS
				case 2:
					return{ 17, 25 };
				case 3:
					return{ 18, 25 };
				case 4:
					return{ 18, 26 };
				case 5:
					return{ 18, 24 };
				case 6:
					return{ 19, 25 };
				case 7:
					return{ 19, 23 };
					// ARCHERS
				case 8:
					return{ 10, 24 };
				case 9:
					return{ 10, 23 };
				case 10:
					return{ 10, 22 };
				case 11:
					return{ 14, 24 };
				case 12:
					return{ 12, 25 };
				case 13:
					return{ 15, 23 };
				case 14:
					return{ 14, 25 };
				case 15:
					return{ 14, 26 };
					// INFANTRY
				case 16:
					return{ 10, 26 };
				case 17:
					return{ 10, 25 };
				case 18:
					return{ 11, 25 };
				case 19:
					return{ 11, 26 };
				case 20:
					return{ 11, 24 };
				case 21:
					return{ 11, 23 };
				case 22:
					return{ 12, 26 };
				case 23:
					return{ 12, 24 };
				case 24:
					return{ 12, 23 };
				case 25:
					return{ 15, 26 };
				case 26:
					return{ 15, 25 };
				case 27:
					return{ 15, 24 };
				case 28:
					return{ 14, 23 };
				case 29:
					return{ 14, 22 };
				case 30:
					return{ 15, 22 };
				}
			}
			return{ 0, 0 };
		}

		Action recommendAction(Unit const& u, SituationReport report, Plan p)
		{
			turns = report.turns;
			id = u.getId();
			int x1 = u.getLocation().col;
			int y1 = u.getLocation().row;

			if (u.getType() == CROWN && turns < 33)       //// King's Preparation phase, hoping to send backwall archers over to be decimated by knights
			{
				return wait();
			}

			if (u.getType() == CROWN && turns >= 33 && turns <= 50)   //// King walks out of range and into the safest zone possible.
			{
				if (p.hasAttack()) return p.attackEnemy();
				if (left == true)
					return p.moveToLocation(10, 7);
				else
					return p.moveToLocation(10, 22);
			}
			if (u.getType() == CROWN)
			{
				if (u.getLocation().row == 0 && u.getLocation().col == 0) return p.moveToLocation(3, 12);
				if (u.getLocation().row == 0 && u.getLocation().col == 29) return p.moveToLocation(3, 17);
			}
			if (u.getType() == CROWN)
			{
				if (p.hasAttack()) return p.attackEnemy();
				if (meleeAware(report, u) == 'N') return turn(lionheart::Direction::NORTH);
				if (meleeAware(report, u) == 'W') return turn(lionheart::Direction::WEST);
				if (meleeAware(report, u) == 'E') return turn(lionheart::Direction::EAST);
				if (meleeAware(report, u) == 'S') return turn(lionheart::Direction::SOUTH);
				if (left == true)
					return p.moveToLocation(0, 0);
				else
					return p.moveToLocation(0, 29);
			}
			if (turns > 120)
			if (p.hasAttack()) return p.attackEnemy();
			if (turns > 35) return p.attackEnemy();
			/// ALL ELSE (starting left)

			if (left == true && u.getLocation().col == 12 && u.getLocation().row > 10) return p.moveToLocation(10, 12);
			if (left == true && u.getLocation().col >= 12) return p.attackEnemy();
			if (left == true && u.getLocation().row < 14 && u.getLocation().row > 7 && u.getLocation().col < 9) return p.moveToLocation(8, 9);
			if (left == true && u.getLocation().row == 14 && u.getLocation().col < 10) return p.moveToLocation(13,9);
			if (left == true && u.getLocation().row == 15 && u.getLocation().col < 10) return p.moveToLocation(16,9);
			if (left == true && u.getLocation().row < 22 && u.getLocation().row > 16 && u.getLocation().col < 18) return p.moveToLocation(21, 18);
			///Transition TOP
			if (left == true && u.getLocation().row == 8 && u.getLocation().col == 9 && report.things[7][9].type == lionheart::SituationReport::SPACE) return p.moveToLocation(7, 9);
			if (left == true && u.getLocation().row == 8 && u.getLocation().col == 9 && report.things[7][9].type != lionheart::SituationReport::SPACE) return p.moveToLocation(8, 12);
			if (left == true && u.getLocation().row == 8 && u.getLocation().col < 13) return p.moveToLocation(8, 12);
			if (left == true && u.getLocation().row == 7 && u.getLocation().col < 13) return p.moveToLocation(7, 12);
			///Transition MID
			if (left == true && u.getLocation().row == 13 && u.getLocation().col < 11) return p.moveToLocation(13, 11);
			if (left == true && u.getLocation().row == 16 && u.getLocation().col < 13) return p.moveToLocation(16, 12);
			if (left == true && u.getLocation().col == 11 && u.getLocation().row > 9) return p.moveToLocation(9, 11);
			if (left == true && u.getLocation().col == 11 && u.getLocation().row == 9) return p.moveToLocation(9,12);
			if (left == true && u.getLocation().col == 12 && u.getLocation().row == 10) return p.attackEnemy();

			/// ALL ELSE (starting right)
			if (p.hasAttack()) return p.attackEnemy();
			if (left == false && u.getLocation().col == 17 && u.getLocation().row > 10) return p.moveToLocation(10, 17);
			if (left == false && u.getLocation().col <= 17) return p.attackEnemy();
			if (left == false && u.getLocation().row < 14 && u.getLocation().row > 7 && u.getLocation().col > 20) return p.moveToLocation(8, 20);
			if (left == false && u.getLocation().row == 14 && u.getLocation().col > 19) return p.moveToLocation(13, 20);
			if (left == false && u.getLocation().row == 15 && u.getLocation().col > 19) return p.moveToLocation(16, 20);
			if (left == false && u.getLocation().row < 22 && u.getLocation().row > 16 && u.getLocation().col > 11) return p.moveToLocation(21, 11);
			///Transition TOP
			if (left == false && u.getLocation().row == 8 && u.getLocation().col == 20 && report.things[7][20].type == lionheart::SituationReport::SPACE) return p.moveToLocation(7, 20);
			if (left == false && u.getLocation().row == 8 && u.getLocation().col == 20 && report.things[7][20].type != lionheart::SituationReport::SPACE) return p.moveToLocation(8, 17);
			if (left == false && u.getLocation().row == 8 && u.getLocation().col > 17) return p.moveToLocation(8, 17);
			if (left == false && u.getLocation().row == 7 && u.getLocation().col < 17) return p.moveToLocation(7, 17);
			///Transition MID
			if (left == false && u.getLocation().row == 13 && u.getLocation().col > 18) return p.moveToLocation(13, 18);
			if (left == false && u.getLocation().row == 16 && u.getLocation().col > 16) return p.moveToLocation(16, 17);
			if (left == false && u.getLocation().col == 18 && u.getLocation().row > 9) return p.moveToLocation(9, 18);
			
			if (left == true && u.getLocation().col == 18 && u.getLocation().row == 9) return p.moveToLocation(9,17);
			if (left == true && u.getLocation().col == 17 && u.getLocation().row == 10) return p.attackEnemy();

			return p.attackEnemy();

		}

	Blazon getBlazon() { return{ Color::VERT, Color::SABLE, Style::CHIEF, "Leif Chipman" }; }

  };
}
#endif
