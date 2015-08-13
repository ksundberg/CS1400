#ifndef LIONHEART_COLTON_BABCOCK
#define LIONHEART_COLTON_BABCOCK
#include "Player.hpp"

namespace lionheart
{

  class ColtonBabcock : public Player
  {
  public:
    Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
    Action recommendAction(Unit const& u, SituationReport, Plan p);
    Blazon getBlazon();
  };
}
#endif
