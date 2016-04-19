#ifndef LIONHEART_CHRIS_WAGNER
#define LIONHEART_CHRIS_WAGNER
#include "Player.hpp"
#include <unordered_map>

namespace lionheart
{
/*The : public Player bit allows this code to interact with the framework code
 * provided.  If your class file is Name.hpp the class needs to be named Name or
 * the framework code will not be able to find and add the player to
 * tournaments.*/
  class ChrisWagner : public Player
  {
	public:
	Placement placeUnit(UnitType, StartBox const&, SituationReport);
	Action recommendAction(Unit const &, SituationReport, Plan);
	Blazon getBlazon();
	
	private:
	bool leftSide;	
	StartBox fortress;
	enum mode { HOLD, ATTACK, LOCKDOWN };	
	mode currentState = HOLD;
	
	int defcon = 3;
	std::unordered_map<const Unit*, int> shiftingArchers;
	
	//placement
	Placement placeInfantry(StartBox const&, SituationReport);
	Placement placeArcher(StartBox const&, SituationReport);
	Placement placeKnight(StartBox const&, SituationReport);	
	int reflectToR(int, SituationReport);
	
	//intelligence
	bool inImmediateDanger(int, int, SituationReport);
	bool inDangerSoon(int, int, SituationReport);	
	bool enemiesComing(Unit const &, SituationReport);
	bool inTheCrownsCourt(Unit const &, SituationReport);
	bool isInBounds(int, int, SituationReport);
	bool enemyBackOpening(SituationReport);
	lionheart::Direction bestArcherDirection(Unit const &, SituationReport);
	lionheart::Placement bestArcherAttack(Unit const &, SituationReport);
	lionheart::Direction defaultDirection(Unit const &);
	lionheart::Direction bestEvasionDirection(Unit const &, SituationReport);
	int spacesToMove(lionheart::Direction, int, int, SituationReport, int);
	lionheart::Placement projectMovement(int, Unit const &);
	lionheart::Direction turnToMow(Unit const &, SituationReport);
  };
}
#endif
