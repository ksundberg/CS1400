#ifndef LIONHEART_JOSHUA_OSTBERG
#define LIONHEART_JOSHUA_OSTBERG
#include "Player.hpp"

namespace lionheart
{
/*The : public Player bit allows this code to interact with the framework code
 * provided.  If your class file is Name.hpp the class needs to be named Name or
 * the framework code will not be able to find and add the player to
 * tournaments.*/
  class JoshuaOstberg : public Player
  {
  public:
	  //ExamplePlayer() :id(0){}
	  Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
	
    Action recommendAction(Unit const &, SituationReport, Plan);
    Blazon getBlazon();
  
  };
}
#endif
