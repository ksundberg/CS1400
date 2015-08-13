#ifndef LIONHEART_DUKE_PAPWORTH
#define LIONHEART_DUKE_PAPWORTH
#include "Player.hpp"

namespace lionheart
{
/*The : public Player bit allows this code to interact with the framework code
 * provided.  If your class file is Name.hpp the class needs to be named Name or
 * the framework code will not be able to find and add the player to
 * tournaments.*/
  class DukePapworth : public Player
  {
  private:
	  int point;
	  Placement getPoint(int point);
	  bool westSide;
	  int id;
	  std::map<int, int> g;
	  enum
	  {

	  };

  public:
	 DukePapworth() :id(0){}
    Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
	Action recommendAction(Unit const &, SituationReport, Plan);
    Blazon getBlazon();
	int DetermineDirection(Unit const & u);
	

  };
}
#endif
