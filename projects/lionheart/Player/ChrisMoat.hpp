#ifndef LIONHEART_CHRIS_MOAT
#define LIONHEART_CHRIS_MOAT
#include "Player.hpp"

namespace lionheart
{
  class ChrisMoat : public Player
  {
  public:
    Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
    Action recommendAction(Unit const &, SituationReport, Plan);
    Blazon getBlazon();
  };
}
#endif
