#ifndef LIONHEART_PAUL_ROYLANCE
#define LIONHEART_PAUL_ROYLANCE
#include "Player.hpp"

namespace lionheart
{
	class PaulRoylance : public Player
	{
	public:
		PaulRoylance() : left(true), checkEnemy(false), unitID(0),
			time(0), enemyCt(30), xTotal(0), yTotal(0){}
		Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
		void enemyLocationAverage(struct SituationReport r);
		Action recommendAction(Unit const &, SituationReport, Plan);
		Blazon getBlazon();

		bool left;
		bool checkEnemy;
		int unitID;
		int time;
		int enemyCt;
		int xTotal;
		int yTotal;
	};
}
#endif
