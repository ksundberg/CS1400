#ifndef LIONHEART_DEVIN_PARSONS
#define LIONHEART_DEVIN_PARSONS
#include "Player.hpp"

namespace lionheart
{
  class DevinParsons : public Player
  {
  public:
	  Placement placeUnit(UnitType type, StartBox const& box, SituationReport report);
	  Action recommendAction(Unit const& u, SituationReport, Plan p);
	  Blazon getBlazon();
  private:
	  Placement crown;
  };
}
#endif
