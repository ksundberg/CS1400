#include "KylerJensen.hpp"

lionheart::KylerJensen::Formation
lionheart::KylerJensen::spacesOrEnemies(Formation positions, SituationReport report) {
    Formation spaces;
    for(auto position : positions) {
        auto thing = report.things[position.r][position.c];
        if(thing.type == SituationReport::SPACE || thing.type == SituationReport::ENEMY) {
            spaces.push_back(position);
        }
    }
    return spaces;
}

lionheart::KylerJensen::Formation
lionheart::KylerJensen::enemies(SituationReport report) {
    Formation positions;
    for(auto r = 0; r < (int)report.things.size(); r++) {
        for(auto c = 0; c < (int)report.things[r].size(); c++) {
            auto thing = report.things[r][c];
            if (thing.type == SituationReport::ENEMY) {
                positions.push_back({r,c,thing.direction});
            }
        }
    }
    return positions;
}

lionheart::KylerJensen::Position
lionheart::KylerJensen::positionOfAllyCrown(SituationReport report) {
    for(auto r = 0; r < (int)report.things.size(); r++) {
        for(auto c = 0; c < (int)report.things[r].size(); c++) {
            auto thing = report.things[r][c];
            if (thing.type == SituationReport::ALLY && thing.unit == CROWN) {
               return {r,c,thing.direction};
            }
        }
    }
    throw std::runtime_error("Could not find ally crown!");
}

lionheart::KylerJensen::Position
lionheart::KylerJensen::nearest(Formation positions, const Unit & unit, Plan plan) {
    auto nearest = positions.front();
    for (auto position : positions) {
        if (movesTo(position, unit, plan) < movesTo(nearest, unit, plan)) {
            nearest = position;
        }
    }
    return nearest;
}

lionheart::Blazon
lionheart::KylerJensen::getBlazon() {
    return {Color::SABLE, Color::OR, Style::PER_BEND, "Kyler Jensen"};
}

lionheart::Placement
lionheart::KylerJensen::placeUnit(UnitType type, StartBox const &box, SituationReport report) {
    startSide = determineStartSide(box, report);
    Formation posts;
    switch (type) {
        case CROWN:
            posts = { crownDefensivePost };
            break;
        case ARCHER:
            posts = archerStartPlacements;
            break;
        case INFANTRY:
            posts = infantryStartPlacements;
            break;
        case KNIGHT:
            posts = knightStartPlacements;
            break;
        default:
            throw std::runtime_error("Piece was not placed on the board!");
    }
    if(startSide == StartSide::RIGHT_SIDE)
        posts = posts.flippedHorizontally(report);
    auto placement = spacesOrEnemies(posts, report).front();
    return { placement.r, placement.c };
}

lionheart::Action
lionheart::KylerJensen::recommendAction(Unit const &unit, SituationReport report, Plan plan) {
    if (report.turns > 52)
        return recommendOffensiveAction(unit, report, plan);
    else
        return recommendDefensiveAction(unit, report, plan);
}

lionheart::Action
lionheart::KylerJensen::recommendDefensiveAction(const Unit &unit, SituationReport report, Plan plan) {
    switch (unit.getType()) {
        case CROWN:
            if (crownIsInDanger(report))
                return guard(positionOf(unit), unit, report, plan);
            return guardDefensivePost(unit, report, plan);
        case KNIGHT:
        case INFANTRY:
        case ARCHER:
            if (crownIsInDanger(report))
                return guardAllyCrown(unit, report, plan);
            else return guardDefensivePost(unit, report, plan);
        default:
            return plan.hasAttack() ? plan.attackEnemy() : wait();
    }
}

lionheart::Action
lionheart::KylerJensen::recommendOffensiveAction(const Unit &unit, SituationReport report, Plan plan) {
    switch (unit.getType()) {
        case CROWN:
            return recommendDefensiveAction(unit, report, plan);
        case KNIGHT:
            if (plan.hasAttack()) return plan.attackEnemy();
            else return plan.moveToEnemyCrown();
        case INFANTRY:
            return smartAttack(unit, report, plan);
        case ARCHER:
            return proceedToNextCheckpointOrAttack(unit, report, plan);
        default:
            return plan.attackEnemy();
    }
}

lionheart::Action
lionheart::KylerJensen::proceedToNextCheckpointOrAttack(const Unit &archer, SituationReport report, Plan plan) {
    if(plan.hasAttack()) return plan.attackEnemy();
    auto myPosition = positionOf(archer);
    Formation checkpoints = archerOffensiveCheckpoints;
    auto flipped_vertically = false;

    if(myPosition.r >= ((int)report.things.size() / 2)) {
        myPosition = myPosition.flippedVertically(report);
        flipped_vertically = true;
    }
    if(startSide == StartSide::RIGHT_SIDE)
        myPosition = myPosition.flippedHorizontally(report);

    Position nextCheckpoint = checkpoints.back();
    for(auto cp : checkpoints) {
        if(cp.c >= myPosition.c && !(cp == myPosition)) {
            nextCheckpoint = cp;
            break;
        }
    }
    if(flipped_vertically) {
        nextCheckpoint = nextCheckpoint.flippedVertically(report);
        myPosition = myPosition.flippedVertically(report);
    }
    if(startSide == StartSide::RIGHT_SIDE) {
        nextCheckpoint = nextCheckpoint.flippedHorizontally(report);
    }
    if(report.things[nextCheckpoint.r][nextCheckpoint.c].type != SituationReport::SPACE)
        return moveTo(myPosition.addInDirection(1, directionOf(nearest(enemies(report), archer, plan), archer)), plan);
    return moveTo(nextCheckpoint, plan);
}

lionheart::KylerJensen::Position
lionheart::KylerJensen::positionOf(const Unit &unit) {
    return {unit.getLocation().row, unit.getLocation().col, unit.getFacing()};
}

lionheart::Action
lionheart::KylerJensen::guardDefensivePost(const Unit &unit, SituationReport report, Plan plan) {
    if(!atDefensivePost(unit, report)) {
        auto posts = spacesOrEnemies(defensivePostsForUnit(unit, report), report);
        if (!posts.empty())
            return guard(nearest(posts, unit, plan), unit, report, plan);
    }
    return guard(positionOf(unit), unit, report, plan);
}

lionheart::Action
lionheart::KylerJensen::guard(Position position, const Unit & unit, SituationReport report, Plan plan) {
    if(plan.movesToEnemy() <= 2 || plan.hasAttack()) return smartAttack(unit, report, plan);
    else return moveTo(position, plan);
}

lionheart::KylerJensen::StartSide
lionheart::KylerJensen::determineStartSide(StartBox box, SituationReport report) {
    int cMin = box.minCol, cMax = box.maxCol;
    int midCol = (cMin + cMax) / 2;
    if (midCol < ((int) report.things.size() / 2)) {
        if (startSide != LEFT_SIDE)
        return LEFT_SIDE;
    }
    else {
        if (startSide != RIGHT_SIDE)
        return RIGHT_SIDE;
    }
    return LEFT_SIDE;
}

std::vector<lionheart::KylerJensen::Position>
lionheart::KylerJensen::Position::smartAttackPositions(SituationReport report) {
    Formation smartAttackPositions;
    Position p1 { r - 1, c, Direction::SOUTH };
    Position p2 { r + 1, c, Direction::NORTH };
    Position p3 { r, c + 1, Direction::WEST };
    Position p4 { r, c - 1, Direction::EAST };
    switch(direction) {
        case Direction::NORTH:
            p1.r--;
        case Direction::SOUTH:
            p2.r++;
        case Direction::EAST:
            p3.c++;
        case Direction::WEST:
            p4.c--;
    }
    for(auto p : {p1,p2,p3,p4}) {
        if(p.r < (int)report.things.size())
            if(p.c < (int)report.things[p.r].size())
                if(report.things[p.r][p.c].type == SituationReport::SPACE)
                    smartAttackPositions.push_back(p);
    }
    return smartAttackPositions;
}

lionheart::KylerJensen::Position
lionheart::KylerJensen::Position::flippedHorizontally(SituationReport report) {
    int maxCol = (int)report.things[0].size() - 1;
    Direction desiredDirection;
    switch(direction) {
        case Direction::EAST:
            desiredDirection = Direction::WEST;
            break;
        case Direction::WEST:
            desiredDirection = Direction::EAST;
            break;
        default:
            desiredDirection = direction;
    }
    return {r, maxCol - c, desiredDirection};
}

lionheart::KylerJensen::Position
lionheart::KylerJensen::Position::flippedVertically(SituationReport report) {
    int maxRow = (int)report.things.size() - 1;
    Direction desiredDirection;
    switch(direction) {
        case Direction::NORTH:
            desiredDirection = Direction::SOUTH;
            break;
        case Direction::SOUTH:
            desiredDirection = Direction::NORTH;
            break;
        default:
            desiredDirection = direction;
    }
    return {maxRow - r, c, desiredDirection};
}

lionheart::KylerJensen::Position
lionheart::KylerJensen::Position::addInDirection(int amount, Direction direction) {
    auto copy = (*this);
    switch(direction) {
        case Direction::NORTH:
            copy.r-=amount;
            break;
        case Direction::SOUTH:
            copy.r+=amount;
            break;
        case Direction::EAST:
            copy.c+=amount;
            break;
        case Direction::WEST:
            copy.c-=amount;
            break;
    }
    return copy;
}

bool lionheart::KylerJensen::Position::operator==(const lionheart::KylerJensen::Position & other) const {
    return r == other.r && c == other.c;
}

int lionheart::KylerJensen::movesTo(Position other, const Unit &unit, Plan plan) {
    auto moves = plan.movesTo(other.r, other.c);
    if (positionOf(unit).direction != other.direction) moves++;
    return moves;
}

lionheart::Action
lionheart::KylerJensen::moveTo(Position other, Plan plan) {
    return plan.moveToLocation(other.r, other.c);
}

lionheart::Action
lionheart::KylerJensen::guardAllyCrown(const Unit &unit, SituationReport report, Plan plan) {
    return guard(positionOfAllyCrown(report), unit, report, plan);
}

lionheart::KylerJensen::Formation
lionheart::KylerJensen::enemyPositions(SituationReport report) {
    Formation enemyPositions;
    for (auto r = 0; r < (int) report.things.size(); r++) {
        for (auto c = 0; c < (int) report.things[r].size(); c++) {
            auto thing = report.things[r][c];
            if (thing.type == SituationReport::ENEMY) {
                enemyPositions.push_back({r, c, thing.direction});
            }
        }
    }
    return enemyPositions;
}

lionheart::KylerJensen::Formation
lionheart::KylerJensen::allSmartAttackPositions(SituationReport report) {
    auto enemies = enemyPositions(report);
    Formation positions;
    for (auto enemy : enemies) {
        for (auto p : enemy.smartAttackPositions(report)) {
            positions.push_back(p);
        }
    }
    return positions;
}

bool lionheart::KylerJensen::atSmartAttackPosition(const Unit &unit, SituationReport report) {
    for(auto position : allSmartAttackPositions(report)) {
        if(positionOf(unit) == position) {
            return true;
        }
    }
    return false;
}

lionheart::KylerJensen::Position
lionheart::KylerJensen::currentSmartAttackPosition(const Unit &unit, SituationReport report) {
    for(auto position : allSmartAttackPositions(report)) {
        if(positionOf(unit) == position) {
            return position;
        }
    }
    throw std::runtime_error("Not currently at a smart attack position!");
}

lionheart::Action
lionheart::KylerJensen::smartAttack(const Unit &unit, SituationReport report, Plan plan) {
    switch (unit.getType()) {
        case ARCHER:
            return plan.attackEnemy();
        default:
            if (plan.hasAttack()) return plan.attackEnemy();
            if (atSmartAttackPosition(unit, report)) {
                if (unit.getFacing() != currentSmartAttackPosition(unit, report).direction)
                    return plan.moveToEnemy();
                if (chickenDetector.count(unit.getId()) > 0) {
                    if (chickenDetector[unit.getId()] == positionOf(unit)) {
                        return plan.attackEnemy();
                    }
                }
                chickenDetector[unit.getId()] = positionOf(unit);
                return wait();
            }
            return moveTo(nearest(allSmartAttackPositions(report), unit, plan), plan);
    }
}

bool lionheart::KylerJensen::crownIsInDanger(SituationReport report) {
    int crownR = 0, crownC = 0;
    int crownHP = 0;
    int r, c;
    for (r = 0; r < (int) report.things.size(); r++)
        for (c = 0; c < (int) report.things[r].size(); c++)
            if (report.things[r][c].type == SituationReport::ALLY) if (report.things[r][c].unit == CROWN) {
                crownR = r;
                crownC = c;
                crownHP = report.things[r][c].hp;
            }
    for (r = 0; r < (int) report.things.size(); r++)
        for (c = 0; c < (int) report.things[r].size(); c++) {
            auto thing = report.things[r][c];
            if (thing.type == SituationReport::ENEMY) {
                int distance = abs(r - crownR) + abs(c - crownC);
                if (thing.unit == KNIGHT || thing.unit == CROWN) distance /= 5;
                if (thing.unit == ARCHER) distance -= 3;
                distance -= thing.hp;
                distance += crownHP;
                if (distance < crownDangerThreshold) {
                    if (!crownInDanger) {
                        crownInDanger = true;
                    }
                    return true;

                }
            }
        }
    if (crownInDanger) {
        crownInDanger = false;
    }
    return false;
}

lionheart::Direction
lionheart::KylerJensen::directionOf(lionheart::KylerJensen::Position p, const Unit &unit) {
    int greatestDist = 0;
    lionheart::Direction bestDirection = Direction::WEST;
    auto myPosition = positionOf(unit);
    if(p.r > myPosition.r && abs(p.r - myPosition.r) > greatestDist) return Direction::NORTH;
    if(p.r < myPosition.r && abs(p.r - myPosition.r) > greatestDist) return Direction::SOUTH;
    if(p.c > myPosition.c && abs(p.c - myPosition.c) > greatestDist) return Direction::EAST;
    if(p.c < myPosition.c && abs(p.c - myPosition.c) > greatestDist) return Direction::WEST;
    return bestDirection;
}

bool lionheart::KylerJensen::blockedIn(Direction direction, const Unit &unit, SituationReport report) {
    auto myPosition = positionOf(unit);
    int r=0,c=0;
    switch(direction) {
        case Direction::NORTH:
            r = myPosition.r - 1;
            c = myPosition.c;
            break;
        case Direction::SOUTH:
            r = myPosition.r + 1;
            c = myPosition.c;
            break;
        case Direction::EAST:
            r = myPosition.r;
            c = myPosition.c + 1;
            break;
        case Direction::WEST:
            r = myPosition.r;
            c = myPosition.c - 1;
            break;
    }
    if(r < (int)report.things.size()) {
        if(c < (int)report.things[r].size()) {
            auto thing = report.things[r][c];
            if(thing.type != SituationReport::SPACE) {
                return true;
            }
        }
    }
    return false;
}

bool lionheart::KylerJensen::atDefensivePost(const Unit &unit, SituationReport report) {
    for(auto post : defensivePostsForUnit(unit, report)) {
        if(positionOf(unit) == post)
            return true;
    }
    return false;
}

lionheart::KylerJensen::Formation
lionheart::KylerJensen::defensivePostsForUnit(const Unit & unit, SituationReport report) {
    Formation posts;
    switch (unit.getType()) {
        case CROWN:
            posts.push_back(crownDefensivePost);
            break;
        case ARCHER:
            posts = archerDefensivePosts;
            break;
        case INFANTRY:
            posts = infantryDefensivePosts;
            break;
        case KNIGHT:
            posts = knightDefensivePosts;
            break;
        default:
            posts = {};
    }
    if(startSide == StartSide::RIGHT_SIDE)
        return posts.flippedHorizontally(report);
    else
        return posts;
}


lionheart::KylerJensen::Formation
lionheart::KylerJensen::Formation::flippedHorizontally(lionheart::SituationReport report) {
    Formation result;
    for(auto p : *this) {
        result.push_back(p.flippedHorizontally(report));
    }
    return result;
}

