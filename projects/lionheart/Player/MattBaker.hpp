#ifndef LIONHEART_MATT_BAKER
#define LIONHEART_MATT_BAKER
#include "Player.hpp"

namespace lionheart
{
  class MattBaker : public Player
  {
  public:
    MattBaker()
    {
      id = 0;
      turnNumber = 0;
      kingRanAway = false;
    }
    Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
    Action recommendAction(Unit const &, SituationReport r, Plan);
    Blazon getBlazon();
  private:
    bool checkBehindWall(int x, int y, SituationReport r);
    bool enemyInMyCastle(SituationReport r);
    bool westSide;
    bool kingRanAway;
    int id;
    int turnNumber;
  };
}

#endif
