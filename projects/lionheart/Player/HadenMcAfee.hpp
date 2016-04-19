#ifndef LIONHEART_HAYDEN_MCAFEE
#define LIONHEART_HAYDEN_MCAFEE
#include "Player.hpp"

namespace lionheart
{
class HadenMcAfee : public Player
{
public:
  Placement placeUnit(UnitType, StartBox const &box, SituationReport report)
  {
    for (int r = box.minRow; r < box.maxRow; ++r)
      for (int c = box.minCol; c < box.maxCol; ++c)
        if (report.things[r][c].type == SituationReport::SPACE)
          return { r, c };
    return { 0, 0 };
  }
  Action
  recommendAction(Unit const &activeUnit, SituationReport , Plan plan)
  {
    if (activeUnit.getType() != CROWN)
    {
      return plan.attackEnemy();
    }
    return wait();
  }

  Blazon getBlazon()
  {
    return { Color::SABLE, Color::GULES, Style::QUARTERLY, "Haden McAfee" };
  };
};
}
#endif
