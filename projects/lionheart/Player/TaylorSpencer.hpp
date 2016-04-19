#ifndef LIONHEART_TAYLORSPENCER
#define LIONHEART_TAYLORSPENCER
#include "Player.hpp"

namespace lionheart
{
/*The : public Player bit allows this code to interact with the framework code
 * provided.  If your class file is Name.hpp the class needs to be named Name or
 * the framework code will not be able to find and add the player to
 * tournaments.*/
  class TaylorSpencer : public Player
  {
  public:
    Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
    Action recommendAction(Unit const &, SituationReport, Plan);
    Blazon getBlazon();

  private:
    Placement getPoint(int point)
    {
      if(!westFirst)
      {
        point +=2;
        point %=4;
      }
      switch(point)
      {
        case 0: return {3,3};
        case 1: return {3,26};
        case 2: return {26,26};
        case 3: return {26,3};
      }
      return {15,15};
    }
    std::map<int,int> dest;
    bool westFirst;
  };
}
#endif
