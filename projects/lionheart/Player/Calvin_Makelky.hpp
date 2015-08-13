#ifndef LIONHEART_CALVIN_MAKELKY
#define LIONHEART_CALVIN_MAKELKY
#include "Player.hpp"

namespace lionheart
{
  class Calvin_Makelky : public Player
  {
  public:
	  Calvin_Makelky() :id(0) {}
    Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
    Action recommendAction(Unit const &, SituationReport, Plan);
    Blazon getBlazon();
  private:
	  bool westSide;
	  int id;
  };
}
#endif
