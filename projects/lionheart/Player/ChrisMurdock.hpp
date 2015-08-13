#ifndef LIONHEART_CHRIS_MURDOCK
#define LIONHEART_CHRIS_MURDOCK
#include "Player.hpp"

namespace lionheart
{

  class ChrisMurdock : public Player
  {
  public:
    Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
    Action recommendAction(Unit const &, SituationReport, Plan);
    Blazon getBlazon();
  };
}
#endif
