#ifndef LIONHEART_CORBIN_CUTLER
#define LIONHEART_CORBIN_CUTLER
#include "Player.hpp"

namespace lionheart
{
  class CorbinCutler : public Player
  {
  public:
    Placement placeUnit(UnitType, StartBox const& box, SituationReport report)
    {
      for (int r = box.minRow; r < box.maxRow; ++r)
        for (int c = box.minCol; c < box.maxCol; ++c)
          if (report.things[r][c].type == SituationReport::SPACE) return {r, c};
	  return{ 0, 0 };
    }
    Action recommendAction(Unit const& u, SituationReport, Plan p)
    {
      if (u.getType() == CROWN) {
        return wait();
      }
      else
      {
        if(p.hasAttack())
        {
          return p.attackEnemy();
        }
        return p.moveToEnemyCrown();
      }
      return p.attackEnemy();
    }
    Blazon getBlazon() { return {Color::ARGENT, Color::GULES, Style::BEND_SINISTER, "Corbin Cutler"}; }
  };
}
#endif
