#ifndef LIONHEART_PEACEFULWARRIOR
#define LIONHEART_PEACEFULWARRIOR
#include "Player.hpp"

namespace lionheart
{
  class PeacefulWarrior : public Player
  {
  public:
    Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
    Action recommendAction(Unit const &, SituationReport, Plan);
    Blazon getBlazon();
  };
}

#endif
