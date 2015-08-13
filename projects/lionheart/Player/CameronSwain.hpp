#ifndef LIONHEART_CAMERON_SWAIN
#define LIONHEART_CAMERON_SWAIN
#include "Player.hpp"
#include <map>
namespace lionheart
{
/*The : public Player bit allows this code to interact with the framework code
 * provided.  If your class file is Name.hpp the class needs to be named Name or
 * the framework code will not be able to find and add the player to
 * tournaments.*/
	
  class CameronSwain : public Player
  {
  public:
    enum Location
	{
		TOP,
		BOTTOM,
		BACK
	};
	Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
    Action recommendAction(Unit const &, SituationReport, Plan);
    Blazon getBlazon();
	CameronSwain() :id(0){};
	int EnemyNear(Unit const &, SituationReport, int, int, Direction);
	int ArcherNear(Unit const &, SituationReport,int, int);
	Action Destination(Unit const&, SituationReport,Plan,Location);
	int KingInBack(Unit const &, SituationReport);
	int KingInFront(Unit const & , SituationReport );
	//Action protectBase(Unit const&, SituationReport, Plan);
	bool west(Unit const&, SituationReport);
  private:
	  int id;
	  bool westSide;
	  std::map<int, Action> Act;
  };
}
#endif
