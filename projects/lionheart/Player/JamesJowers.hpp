#ifndef LIONHEART_JAMES_JOWERS
#define LIONHEART_JAMES_JOWERS
#include "Player.hpp"

namespace lionheart
{
    class JamesJowers : public Player
    {
    public:
        Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
        Action recommendAction(Unit const&, SituationReport, Plan);
        Blazon getBlazon();
    };
}

#endif
