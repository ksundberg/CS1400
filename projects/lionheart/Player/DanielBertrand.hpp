#ifndef LIONHEART_Daniel_Bertrand
#define LIONHEART_Daniel_Bertrand
#include "Player.hpp"

namespace lionheart
{
	class DanielBertrand : public Player{
		public:
			DanielBertrand(){ id = 0; westSide = true; moves = 0; turns = 0; charge = false; };
			Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
			Action recommendAction(Unit const &, SituationReport, Plan);
			Blazon getBlazon();
			lionheart::Direction defensiveFace(Unit const&);
			lionheart::Action fillTheGap(Unit const&, SituationReport&);
			bool wallsBreached(SituationReport&);
		private:
			int moves;
			int turns;
			int id;
			bool westSide;
			bool charge;
	};
}
#endif
