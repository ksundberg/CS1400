#ifndef LIONHEART_FRITZ_WAECHTLER
#define LIONHEART_FRITZ_WAECHTLER
#include "Player.hpp"

namespace lionheart
{

	class FritzWaechtler : public Player
	{
	public:
		Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
		Action recommendAction(Unit const &, SituationReport, Plan);
		Blazon getBlazon();
	};
}
#endif
