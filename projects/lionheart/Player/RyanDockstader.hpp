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

	  struct locationRyan
	  {
		  int row;
		  int col;
	  };
	  locationRyan enemyCrown;


    Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
    Action recommendAction(Unit const &, SituationReport, Plan);
    Blazon getBlazon();
 
  private:

	  lionheart::Action goodEyeSniper(lionheart::Unit const &unit, lionheart::SituationReport const &report, lionheart::Plan const &plan);
	  bool checkForCrown(Unit const &, lionheart::SituationReport);
	  void getEnemyCrownLocation(lionheart::SituationReport);
	  lionheart::Placement crownLocation;
	  int id = 0;
	  bool westSide = true;


  };
}
#endif
