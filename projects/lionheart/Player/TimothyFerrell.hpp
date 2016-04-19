//
// Created by dragonman117 on 4/11/16.
//

#ifndef LIONHEART_TIMOTHYFERRELL_H
#define LIONHEART_TIMOTHYFERRELL_H


#include "Player.hpp"
#include <vector>

namespace lionheart
{
/*The : public Player bit allows this code to interact with the framework code
 * provided.  If your class file is Name.hpp the class needs to be named Name or
 * the framework code will not be able to find and add the player to
 * tournaments.*/
    enum side {lhs,rhs};
    enum timAction{atk, mv};
    struct defenseTimothy{
        Placement local;
        Direction face;
    };
    struct timException{
        int id;
        timAction action;
        Placement goTo;
    };

    class TimothyFerrell : public Player
    {
    private:
        std::vector<Placement> lhsArcher; // Heap for left hand side archers placement
        std::vector<Placement> lhsKnights; // heap for left hand side knights placement
        std::vector<Placement> lhsInfantry; //heap for left  hand side infantry placement
        std::vector<Placement> rhsArcher;
        std::vector<Placement> rhsKnights;
        std::vector<Placement> rhsInfantry;
        std::vector<defenseTimothy> lhsDefence;
        std::vector<defenseTimothy> rhsDefence;
        std::vector<timException> inPlay;
        side currSide;
        int sacrifice;
        bool kingNoMove;
        bool isBrandon;

        void buildArchers();
        void buildKnights();
        void buildInfantry();

        void buildDefense();

        int isDefense(int row, int col);
        int isInPlay(int id);

        bool enemyPresent(lionheart::SituationReport sit);
        bool archerSneak(lionheart::SituationReport sit);
        bool detectBrandon(lionheart::SituationReport sit);
    public:
        TimothyFerrell();
        Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
        Action recommendAction(Unit const &, SituationReport, Plan);
        Blazon getBlazon();
    };
}


#endif //LIONHEART_TIMOTHYFERRELL_H
