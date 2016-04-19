#ifndef LIONHEART_SHEM_HALE
#define LIONHEART_SHEM_HALE
#include "Player.hpp"
#include <vector>

namespace lionheart
{
/*The : public Player bit allows this code to interact with the framework code
 * provided.  If your class file is Name.hpp the class needs to be named Name or
 * the framework code will not be able to find and add the player to
 * tournaments.*/
  class ShemHale : public Player
  {
  public:
    
    bool canArcherBait(lionheart::Map::Location, lionheart::Direction, lionheart::SituationReport);
    bool canFlank(lionheart::Direction, lionheart::SituationReport report);
    lionheart::Action moveForward(lionheart::Map::Location, lionheart::Direction, lionheart::Plan);
    bool canHitEnemyLeft(lionheart::Map::Location, lionheart::Direction, lionheart::SituationReport report);
    bool canHitEnemyRight(lionheart::Map::Location, lionheart::Direction, lionheart::SituationReport report);

    bool canArcherShootEnemyLeft(lionheart::Map::Location, lionheart::Direction, lionheart::SituationReport report);
    bool canArcherShootEnemyRight(lionheart::Map::Location, lionheart::Direction, lionheart::SituationReport report);
    bool canArcherShootKing(lionheart::Map::Location, lionheart::Direction, lionheart::SituationReport report);
    lionheart::Action turnRight(lionheart::Direction);
    bool canArcherShootKingRight(lionheart::Map::Location, lionheart::Direction, lionheart::SituationReport report);
    lionheart::Action turnLeft(lionheart::Direction);
    bool canArcherShootKingLeft(lionheart::Map::Location, lionheart::Direction, lionheart::SituationReport report);

    void checkLineOfSight(int i, lionheart::Map::Location, lionheart::Direction);
    void locateEnemyKing(lionheart::SituationReport report);
    void update(lionheart::Map::Location, lionheart::Direction);

    Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
    Action recommendAction(Unit const &, SituationReport, Plan);
    Blazon getBlazon();
  };
}
#endif
