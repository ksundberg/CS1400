#ifndef LIONHEART_KYLE_MYERS
#define LIONHEART_KYLE_MYERS
#include "Player.hpp"

// Kyle Myers CS 3100-001
namespace KMYERS{
  struct coordinate{
    int row;
    int col;
  };

  enum Squad{ RGAURD = 0, FGAURD = 1, TGAURD = 2, BGAURD = 3 , UNASSIGNED = -1};

  const int FIRST_MOVE_COL_SHIFT = 20;
}

namespace lionheart
{
  class KyleMyers : public Player
  {
  public:
    Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
    Action recommendAction(Unit const &, SituationReport, Plan);
    Blazon getBlazon();

  private:
    KMYERS::coordinate inRange(lionheart::Unit const & thisUnit, lionheart::SituationReport report);

    
    void assignSquad(lionheart::Unit const &);
    KMYERS::Squad getSqaud(lionheart::Unit const &);

    Placement placeRearGaurd(UnitType, StartBox const& box, SituationReport report);
    Placement placeFrontGaurd(UnitType, StartBox const& box, SituationReport report);
    Placement placeTopGaurd(UnitType, StartBox const& box, SituationReport report);
    Placement placeBottomGaurd(UnitType, StartBox const& box, SituationReport report);

    Action recommendActionBGAURD(Unit const &, SituationReport, Plan);
    Action recommendActionTGAURD(Unit const &, SituationReport, Plan);
    Action recommendActionFGAURD(Unit const &, SituationReport, Plan);
    Action recommendActionRGAURD(Unit const &, SituationReport, Plan);

    int placementCounts[4]; // 0 is the king, 1 is knights, 2 is archers, 3 is infantry
    std::map<int, KMYERS::Squad> assignments;
    KMYERS::coordinate kingloc;
    KMYERS::coordinate frontGaurd;
    KMYERS::coordinate topGaurd;
    KMYERS::coordinate botGaurd;
    bool westSideStart;
  };


}
#endif