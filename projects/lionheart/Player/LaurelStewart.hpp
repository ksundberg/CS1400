#ifndef LIONHEART_LAUREL_STEWART
#define LIONHEART_LAUREL_STEWART
#include "Player.hpp"

// Spring 2016 CS 3100 - Laurel Stewart

namespace lionheart
{
  class LaurelStewart : public Player
  {
  public:
    Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
    Action recommendAction(Unit const&, SituationReport, Plan);
    Blazon getBlazon();
  };
}
#endif
