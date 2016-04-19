#ifndef LIONHEART_CHRISJENKINS
#define LIONHEART_CHRISJENKINS
#include <iostream>
#include "Player.hpp"
#include "Infantry.hpp"
#include "Crown.hpp"
#include "Archer.hpp"
#include "Knight.hpp"

namespace lionheart
{
/*The : public Player bit allows this code to interact with the framework code
 * provided.  If your class file is Name.hpp the class needs to be named Name or
 * the framework code will not be able to find and add the player to
 * tournaments.*/
  class ChrisJenkins : public Player
  {
  public:
    Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
    Action recommendAction(Unit const &, SituationReport, Plan);
    Blazon getBlazon();
  private:
    bool westSide = true;
  };
}
#endif
