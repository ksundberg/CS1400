#ifndef LIONHEART_EMILY_JOWERS
#define LIONHEART_EMILY_JOWERS
#include "Player.hpp"

namespace lionheart
{
    class EmilyJowers : public Player
    {
    public:
        Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
        Action recommendAction(Unit const&, SituationReport, Plan);
        Blazon getBlazon();
    };
}

#endif
