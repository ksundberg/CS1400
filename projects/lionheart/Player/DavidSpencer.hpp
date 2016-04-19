#ifndef LIONHEART_DAVID_SPENCER
#define LIONHEART_DAVID_SPENCER
#include "Player.hpp"
#include <cmath>
#include <vector>

namespace lionheart
{
  class DavidSpencer : public Player
  {
  public:
    Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
    Action recommendAction(Unit const&, SituationReport, Plan);
    Blazon getBlazon();

    int crownMoves;
    const std::vector<std::pair<int, int>> WestCrownStartPosition = { {14, 2} };
    const std::vector<std::pair<int, int>> EastCrownStartPosition = { {14, 28} };

    const std::vector<std::pair<int, int>> WestArcherStartPositions = { {11, 3}, {11, 5}, {18, 3}, {18, 5}, {12, 7}, {13, 7}, {16, 7}, {17, 7} };
    const std::vector<std::pair<int, int>> EastArcherStartPositions = { {11, 26}, {11, 24}, {18, 26}, {18, 24}, {12, 22}, {13, 22}, {15, 22}, {16, 22} };

    const std::vector<std::pair<int, int>> WestKnightStartPositions = { {11, 4}, {12, 4}, {17, 4}, {18, 4}, {14, 6}, {15, 6} };
    const std::vector<std::pair<int, int>> EastKnightStartPositions = { {11, 25}, {12, 25}, {17, 25}, {18, 25}, {14, 23}, {15, 23} };

    const std::vector<std::pair<int, int>> WestInfantryStartPositions = { {10, 3}, {10, 4}, {10, 5}, {12, 3}, {12, 5}, {19, 3}, {19, 4}, {19, 5}, {17, 3}, {17, 5}, {14, 7}, {15, 7}, {13, 6}, {16, 6}, {15, 5}} ;
    const std::vector<std::pair<int, int>> EastInfantryStartPositions = { {10, 26}, {10, 25}, {10, 24}, {11, 26}, {11, 24}, {19, 26}, {19, 25}, {19, 24}, {19, 26}, {19, 24}, {14, 22}, {15, 22}, {13, 23}, {16, 23}, {15, 24}} ;

    int isAllyEast;

    lionheart::Placement placeUnitByStartPositions(lionheart::SituationReport report, std::vector<std::pair<int, int>> const& positions);

    bool inEnemyBox(lionheart::Unit const& u);

    bool isEnemyInBox(lionheart::SituationReport report);

    bool isBottomUnit(lionheart::Unit const& u);

    bool isTopUnit(lionheart::Unit const& u);

    lionheart::Action runAway(Unit const& u, Plan p, SituationReport report);

    auto getClosestEnemy(Plan p, SituationReport report);

    lionheart::Action moveToNorthCorner(Plan p);

    lionheart::Action moveToSouthCorner(Plan p);

    lionheart::Action runAwayFromRearWall(Unit const& u, Plan p);

    bool isArcherBehindBox(SituationReport report);
  };
}
#endif
