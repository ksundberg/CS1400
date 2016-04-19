#ifndef LIONHEART_JAY_MATTINSON
#define LIONHEART_JAY_MATTINSON
#include "Player.hpp"

namespace lionheart
{
  class JayMattinson : public Player
  {
  public:
    Placement placeUnit(UnitType, StartBox const& box, SituationReport report)
    {
		for (int r = box.minRow; r < box.maxRow; ++r)
			for (int c = box.minCol; c < box.maxCol; ++c)
				if (report.things[r][c].type == SituationReport::SPACE) return{ r, c }; \
					return{ 0, 0 };
    }
    Action recommendAction(Unit const&, SituationReport,Plan p) { return p.attackEnemy(); }
    Blazon getBlazon() { return {Color::SABLE, Color::GULES, Style::SALTIRE, "Jay Mattinson"}; }
  };
}
#endif
