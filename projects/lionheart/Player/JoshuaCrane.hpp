#ifndef LIONHEART_JOSHUA_CRANE
#define LIONHEART_JOSHUA_CRANE
#include "Player.hpp"

namespace lionheart
{
  class JoshuaCrane : public Player
  {
  public:
    Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
    Action recommendAction(Unit const &, SituationReport, Plan);
    Blazon getBlazon();
  };
}
#endif
