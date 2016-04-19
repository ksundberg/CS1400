#ifndef LIONHEART_JACK_THOMAS
#define LIONHEART_JACK_THOMAS
#include "Player.hpp"

namespace lionheart
{

/*The : public Player bit allows this code to interact with the framework code
 * provided.  If your class file is Name.hpp the class needs to be named Name or
 * the framework code will not be able to find and add the player to
 * tournaments.*/
  class JackThomas : public Player
  {
  public:
    JackThomas():id(0){}
    Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
    Action recommendAction(Unit const &, SituationReport, Plan);
    Blazon getBlazon();
  private:
    struct archerLocation{
      int row;
      int col;
      archerLocation(int r, int c){
        row = r;
        col = c;
      }
      ~archerLocation(){}
    };
    int id;
    bool startOnWestSide;
    int checkWest(int currCol);
    int checkEast(int currCol);
    int checkNorth(int currRow);
    int checkSouth(int currRow);
    archerLocation checkSurroundingsForArcherEastFirst(int tempRow, int tempCol, SituationReport report);
    archerLocation checkSurroundingsForArcherWestFirst(int tempRow, int tempCol, SituationReport report);
    bool isValidLocation(int row, int col);
    bool enemyToTheNorth(int temp, int currRow, int currCol, SituationReport report);
    bool enemyToTheSouth(int temp, int row, int col, SituationReport report);
    bool enemyToTheWest(int temp, int row, int col, SituationReport report);
    bool enemyToTheEast(int temp, int row, int col, SituationReport report);
  };
}
#endif
