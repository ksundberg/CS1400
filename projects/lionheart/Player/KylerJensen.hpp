#ifndef LIONHEART_KYLER_JENSEN
#define LIONHEART_KYLER_JENSEN

#include "Player.hpp"

namespace lionheart {
    class KylerJensen : public Player {
    private:
        struct Position {
            int r;
            int c;
            Direction direction;
            Position() {};
            Position(int r, int c) : r(r), c(c) {}
            Position(int r, int c, Direction d) : r(r), c(c), direction(d) {};
            bool operator==(const Position &) const;
            Position addInDirection(int, Direction);
            Position flippedHorizontally(SituationReport);
            Position flippedVertically(SituationReport);
            std::vector<Position> smartAttackPositions(SituationReport report);
        };
        class Formation : public std::vector<Position> {
        public:
            Formation(std::vector<Position> data) : std::vector<Position>(data) {}
            Formation(std::initializer_list<Position> l) : std::vector<Position>(l) {}
            Formation() : std::vector<Position>() {}
            Formation flippedHorizontally(SituationReport);
        };

        Formation archerStartPlacements {
                {11,3}, {11,5}, {13,6}, {16,6},
                {18,3}, {18,5}, {14,6}, {15,6}
        };
        Formation infantryStartPlacements {
                {13,3}, {13,4}, {13,5},
                {14,2}, {14,4}, {14,5},
                {15,3}, {15,4}, {15,5},
                {16,3}, {16,4}, {16,5},
                {14,7}, {15,7}, {15,2},

        };
        Formation knightStartPlacements {
                {10,4}, {11,4}, {12,4},
                {17,4}, {18,4}, {19,4}
        };
        Formation archerDefensivePosts {
                {10,3}, {10,5}, {13,7}, {16,7},
                {19,3}, {19,5}, {14,7}, {15,7}
        };
        Formation infantryDefensivePosts {
                {13,3}, {13,4}, {13,5},
                {14,2}, {14,4}, {14,5},
                {15,3}, {15,4}, {15,5},
                {16,3}, {16,4}, {16,5},
                {14,8}, {15,8}, {15,2},
        };
        Formation knightDefensivePosts {
                {13,10}, {16,10},
                {8, 8 }, {8, 9 },
                {21,8 }, {21,9 }
        };

        Formation archerOffensiveCheckpoints {
                {7,11}, {6,17}, {6,27}, {14,29}
        };
        Position crownDefensivePost {14,3};
        enum StartSide {
            UNKNOWN,
            LEFT_SIDE,
            RIGHT_SIDE
        };
        bool crownInDanger = false;
        StartSide startSide = StartSide::UNKNOWN;
        StartSide determineStartSide(StartBox, SituationReport);
        Action recommendDefensiveAction(const Unit &, SituationReport, Plan);
        Action recommendOffensiveAction(const Unit &, SituationReport, Plan);
        Action smartAttack(const Unit &, SituationReport, Plan);
        Action guardDefensivePost(const Unit &, SituationReport, Plan);
        Action guard(Position, const Unit &, SituationReport, Plan);
        Action guardAllyCrown(const Unit &, SituationReport, Plan);
        Formation spacesOrEnemies(Formation, SituationReport);
        Formation defensivePostsForUnit(const Unit &, SituationReport);
        Position nearest(Formation, const Unit &, Plan);
        Formation allSmartAttackPositions(SituationReport);
        Formation enemyPositions(SituationReport report);
        int movesTo(Position, const Unit &, Plan);
        Action moveTo(Position, Plan);
        Action proceedToNextCheckpointOrAttack(const Unit &, SituationReport, Plan);
        bool atDefensivePost(const Unit &, SituationReport);
        bool blockedIn(Direction, const Unit &, SituationReport);
        bool crownIsInDanger(SituationReport);
        bool atSmartAttackPosition(const Unit &, SituationReport report);
        Direction directionOf(Position, const Unit&);
        Position currentSmartAttackPosition(const Unit &unit, SituationReport report);
        Position positionOf(const Unit &unit);
        Position positionOfAllyCrown(SituationReport report);
        Formation enemies(SituationReport report);
        int crownDangerThreshold = 0;
        std::map<int,Position> chickenDetector;
    public:
        Placement placeUnit(UnitType, StartBox const &, SituationReport);
        Action recommendAction(Unit const &, SituationReport, Plan);
        Blazon getBlazon();
    };
}
#endif
