#ifndef EVEE
#define EVEE
#include "Player.hpp"

namespace lionheart
{
	class Evee : public Player
	{
	public:

		Placement placeUnit(UnitType, StartBox const& box, SituationReport report)
		{
			strong_side = (box.minCol < static_cast<int>(report.things[0].size() / 2));
			for (int r = box.minRow; r < box.maxRow; ++r)
				for (int c = box.minCol; c < box.maxCol; ++c)
					if (report.things[r][c].type == SituationReport::SPACE) return{ r, c }; \
						return{ 0, 0 };
		}

		Action recommendAction(Unit const& u, SituationReport r, Plan p) { 

			// send home boy away
			if (u.getType() == CROWN) 
			{
				if(strong_side)
				{
					if (p.movesToEnemy() > 6) return p.moveToLocation(15, 0);
				}
				else
					if (p.movesToEnemy() > 6) return p.moveToLocation(15, 29);	
		    }
		    // add logic for archers to get behind infantry, let them die for their country
		    // in a few hundred years ranged combat will be the only reliable means of warfare
		    // probably because we are going to let natural selection
		    // send all of these glorious idiots to Valhalla or to the halls of Mandos, yay them!
			if(u.getType() == ARCHER)
			{
				int i = 0;
				int j = 0;
				for(auto &&row : r.things)
				{
					// find an infantryman close to you, move behind them
					j = 0;
					for(auto &&t : row)
					{
						if(t.type == SituationReport::ALLY && t.unit == INFANTRY)
						{
							auto d = p.movesTo(i, j);
							if(d > 1 && d < 4)
							{
								if(strong_side && j > 0)
									return p.moveToLocation(i, j-1);
								else if (!strong_side && j < 30)
									return p.moveToLocation(i, j+1);
								else
									return p.moveToLocation(i, j);
							}
							else
								return p.attackEnemy();
						}
						j++;
					}
					i++;
				}

				// if front line isn't found you are hosed. The only natural response to this is to charge!
				return p.attackEnemy();
			}

			// add logic for knights to attack from sides of enemy
			if(u.getType() == KNIGHT)
			{
				int i = 0;
				int j = 0;
				for(auto &&row : r.things)
				{
					// find enemy archers first, attack them
					j = 0;
					for(auto &&t : row)
					{
						if(t.type == SituationReport::ENEMY && t.unit == ARCHER)
						{
							if(p.movesTo(i, j) > 3 && p.movesToEnemy() > 3)
							{
								auto l = u.getLocation();
								if(l.row > i)
								{
									auto a = i - 2;
									if(a < 0)
										a = 0;
									return p.moveToLocation(a, j);
								}
								else{
									auto a = i + 2;
									if(a > 29)
										a = 29;
									return p.moveToLocation(a, j);
								}
							}
							else
								return p.attackEnemy();
						}
						j++;
					}
					i++;
				}

				// no archers found
				return p.attackEnemy(); 
				
			}

			// my countrymen! Attack for king!  Attack for glory! Attack for family!  Attack because we gosh darn just don't care anymore!
			return p.attackEnemy(); 
		}

		// why Evee? because it's unstable!
		Blazon getBlazon() { return {Color::ARGENT, Color::AZURE, Style::SALTIRE, "Evee"}; }

	private:
		bool strong_side;
  };
}
#endif