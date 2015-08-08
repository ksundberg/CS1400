#ifndef LIONHEART_EXAMPLE_PLAYER
#define LIONHEART_EXAMPLE_PLAYER
#include "Player.hpp"

namespace lionheart
{
/*The : public Player bit allows this code to interact with the framework code
 * provided.  If your class file is Name.hpp the class needs to be named Name or
 * the framework code will not be able to find and add the player to
 * tournaments.*/
  class RyanDockstader : public Player
  {
  public:

	  RyanDockstader() :id(0){}


    Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
    Action recommendAction(Unit const &, SituationReport, Plan);
    Blazon getBlazon();
	Action ghostProtocol(Unit const &, SituationReport, Plan);
	Action corps(Unit const &, SituationReport, Plan);
	Action patientDefender(Unit const &, SituationReport, Plan , int const & turnCounter);
  
  private:
	 
	  int id = 0;
	  bool westSide = true;
  };
}
#endif
