#ifndef LIONHEART_PlayerPaulFairbanks
#define LIONHEART_PlayerPaulFairbanks
#include "Player.hpp"

namespace lionheart
{
/*The : public Player bit allows this code to interact with the framework code
 * provided.  If your class file is Name.hpp the class needs to be named Name or
 * the framework code will not be able to find and add the player to
 * tournaments.*/
  class PlayerPaulFairbanks : public Player
  {
  public:
	  PlayerPaulFairbanks() : id(0){}
    Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
    Action recommendAction(Unit const & u, SituationReport, Plan p);
    Blazon getBlazon();
	 // StartBox &sbox;
  private:
	  bool westSide;
	  int id;
  };
}
#endif
