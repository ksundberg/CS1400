#ifndef LIONHEART_JAROM_WILCOX
#define LIONHEART_JAROM_WILCOX
#include "Player.hpp"


namespace lionheart
{
/*The : public Player bit allows this code to interact with the framework code
 * provided.  If your class file is Name.hpp the class needs to be named Name or
 * the framework code will not be able to find and add the player to
 * tournaments.*/
  class Jarom_Wilcox : public Player
  {
  public:
	  Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
	  Action recommendAction(Unit const &, SituationReport, Plan);
	  Blazon getBlazon();
  private:
	  Placement crown;
  };
}
#endif
