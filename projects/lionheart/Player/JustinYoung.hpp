#ifndef LIONHEART_JUSTIN_YOUNG
#define LIONHEART_JUSTIN_YOUNG
#include "Player.hpp"

namespace lionheart
{
/*The : public Player bit allows this code to interact with the framework code
 * provided.  If your class file is Name.hpp the class needs to be named Name or
 * the framework code will not be able to find and add the player to
 * tournaments.*/
  class JustinYoung : public Player
  {
  public:
    JustinYoung(): id(0) {}
    Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
    Action recommendAction(Unit const &, SituationReport, Plan);
    Blazon getBlazon();
    Action kingsguardActions(int unitID, lionheart::Plan);
    Action makeWayTo(int row, int col, lionheart::Plan);
    Action kingsguardFaceEnemy(int unitID);
    bool isKingsguardFacing(Unit const &unit);
    bool isKingsguardInPosition(Unit const &unit);
    bool isKingsguard(int unitID);
  private:
    int id;
    bool leftSide;
    void newRound() ;
  };
}
#endif
