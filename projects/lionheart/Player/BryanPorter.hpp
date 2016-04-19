#ifndef LIONHEART_BRYANPORTER
#define LIONHEART_BRYANPORTER
#include "Player.hpp"
#include <vector>

namespace lionheart
{
  class BryanPorter : public Player
  {
  public:
    Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
    Action recommendAction(Unit const& u, SituationReport, Plan p);
    Blazon getBlazon(); 
  
  private:
    bool leaveFort;
    bool westSide;
    int runawayKing; //king remains motionless til enemy reaches box
    int eKingr = -5;
    int eKingc = -5;
    bool archerRange(int, int, int, int, Direction);
    int checkDanger(int, int, SituationReport);
    bool facingRock(Unit const& u, SituationReport r);
    lionheart::Direction getTurn(lionheart::Direction);
    void checkInvaders(SituationReport r){
      if(westSide){
        if(r.things[8][4].type == SituationReport::ENEMY) runawayKing = 0;
        if(r.things[21][4].type == SituationReport::ENEMY) runawayKing = 1;
        if(r.things[14][9].type == SituationReport::ENEMY 
            ||r.things[15][9].type == SituationReport::ENEMY) runawayKing = 2;
      } else {
        if(r.things[8][25].type == SituationReport::ENEMY) runawayKing = 0;
        if(r.things[14][20].type == SituationReport::ENEMY
           || r.things[15][20].type == SituationReport::ENEMY) runawayKing = 2;
        if(r.things[21][25].type == SituationReport::ENEMY) runawayKing = 1;
      }
    }
    
    lionheart::Action recCrown(Unit const &u, SituationReport r, Plan p);
    lionheart::Action recArcher(Unit const &u, SituationReport r, Plan p);
    lionheart::Action recKnight(Unit const &u, SituationReport r, Plan p);
    lionheart::Action recInfant(Unit const &u, SituationReport r, Plan p); 
    
  };
}
#endif
