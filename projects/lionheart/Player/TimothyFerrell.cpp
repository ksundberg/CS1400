#include "TimothyFerrell.hpp"

lionheart::Placement lionheart::TimothyFerrell::placeUnit(UnitType type, StartBox const &box, SituationReport ) {
    if(box.maxCol  < 14)currSide = lhs;
    else currSide = rhs;
    if(currSide == lhs){
        //Left Side
        if(type == CROWN) return {15,2};
        if(type == ARCHER){
            Placement tmp = lhsArcher.back();
            lhsArcher.pop_back();
            return tmp;
        }
        if(type == KNIGHT){
            Placement tmp = lhsKnights.back();
            lhsKnights.pop_back();
            return tmp;
        }
        if(type == INFANTRY){
            Placement tmp = lhsInfantry.back();
            lhsInfantry.pop_back();
            return tmp;
        }
    }else{
        //right side
        if(type == CROWN) return {15,27};
        if(type == ARCHER){
            Placement tmp = rhsArcher.back();
            rhsArcher.pop_back();
            return tmp;
        }
        if(type == KNIGHT){
            Placement tmp = rhsKnights.back();
            rhsKnights.pop_back();
            return tmp;
        }
        if(type == INFANTRY){
            Placement tmp = rhsInfantry.back();
            rhsInfantry.pop_back();
            return tmp;
        }
    }
    return { 0, 0 };
}

lionheart::Action
lionheart::TimothyFerrell::recommendAction(Unit const & me, SituationReport sit, Plan p)
{
    /*Fill this out with the behavior you want for your units.  Without changes
     * your units will just wait to be defeated.  Feel free to look at the other provided players for
     * ideas on how to get certain behavior*/
    Map::Location currentLoc = me.getLocation();
    // at turn 120 abandon d!
    if(sit.turns >= 120){
        lhsDefence.clear();
        rhsDefence.clear();
    }
    int index = isDefense(currentLoc.row, currentLoc.col);
    int playIndex = -1;
    lionheart::Placement toGo;
    if(index <= 0){
        playIndex = isInPlay(me.getId());
    }
    //first move every one to the right dirs
    if(sit.turns ==1){
        if(!isBrandon){
            if(detectBrandon(sit)){
                isBrandon = true;
            }else{
            }
        }
        if(index >=0 ){
            //we are defensive get into position.
            std::vector<defenseTimothy> *defense;
            if(currSide == lhs) defense = &lhsDefence;
            else defense = &rhsDefence;
            defenseTimothy tmp = defense->at(index);
            //if not in proper direction tell it to turn...
            if(me.getFacing() != tmp.face){
                return turn(tmp.face);
            }
        }
        //send sacrifice to poke
        if((currentLoc.col == 7 || currentLoc.col == 22) && currentLoc.row == 15){
            inPlay.push_back({me.getId(),lionheart::timAction::atk,{0,0}});
            sacrifice = me.getId();
        }
        //Move 3 infantry behind sacrifice up to fill ranks
        if((currentLoc.col == 6 || currentLoc.col == 23) && currentLoc.row == 15){
            if(currSide == lhs) toGo = {7,15};
            else toGo = {22,15};
            inPlay.push_back({me.getId(), lionheart::timAction::mv, toGo});
        }
        if((currentLoc.col == 5 || currentLoc.col == 24) && currentLoc.row == 15){
            if(currSide == lhs) toGo = {6,15};
            else toGo = {23,15};
            inPlay.push_back({me.getId(), mv, toGo});
        }
        if((currentLoc.col == 4 || currentLoc.col == 25) && currentLoc.row == 15){
            if(currSide == lhs) toGo = {5,15};
            else toGo = {24,15};
            inPlay.push_back({me.getId(), mv, toGo});
        }
        if((currentLoc.col == 4 || currentLoc.col == 25) && currentLoc.row == 10){
            return turn(lionheart::Direction::NORTH);
        }
        if((currentLoc.col == 4 || currentLoc.col == 25) && currentLoc.row == 19){
            return turn(lionheart::Direction::SOUTH);
        }
    }
    //For all other turns
    if(me.getType() == CROWN ){
        //king shouldt do anything! Unless sneak
        if(kingNoMove && archerSneak(sit)){
            kingNoMove = false;
            if(currSide == lhs ) return p.moveToLocation(15,4);
            if(currSide == rhs ) return p.moveToLocation(15,25);
        }
        return wait();
    }
    if(enemyPresent(sit) && !isBrandon){
        return p.attackEnemy();
    }
    if(isBrandon && enemyPresent(sit)){
        if(!kingNoMove) return p.attackEnemy();
    }

    if(index >=0){
        if(p.hasAttack()) return p.attackEnemy();
        return wait();
    }
    if(sit.turns >= 55 && !isBrandon){
        return p.attackEnemy();
    }
    if(sit.turns >= 5) inPlay.clear();
    if(playIndex >= 0){
        lionheart::timException tmp = inPlay[playIndex];
        if(tmp.action == lionheart::timAction::atk) return p.attackEnemy();
        if(tmp.action == lionheart::timAction::mv)return p.moveToLocation(tmp.goTo.col, tmp.goTo.row);
    }
    if(me.getId() == sacrifice) return p.attackEnemy();
    if(p.hasAttack()) return p.attackEnemy();
    else return wait();
}

lionheart::Blazon lionheart::TimothyFerrell::getBlazon()
{
    /*Return your blazon here.  In case of conflicts preference will be given to
     * the students that have registered their blazons in class.*/
    return { Color::OR, Color::SABLE, Style::INVERTED_CHEVERON, "Timothy Ferrell" };
}


//Helpers
lionheart::TimothyFerrell::TimothyFerrell() {
    kingNoMove = true;
    isBrandon = false;
    buildArchers();
    buildKnights();
    buildInfantry();
    buildDefense();
}

//Building original placements
void lionheart::TimothyFerrell::buildArchers() {
    lhsArcher.push_back({10,5});
    lhsArcher.push_back({14,2});
    lhsArcher.push_back({13,7});
    lhsArcher.push_back({12,7});
    lhsArcher.push_back({16,2});
    lhsArcher.push_back({17,7});
    lhsArcher.push_back({16,7});
    lhsArcher.push_back({19,5});
    //RHS
    rhsArcher.push_back({10,24});
    rhsArcher.push_back({14,27});
    rhsArcher.push_back({13,22});
    rhsArcher.push_back({16,27});
    rhsArcher.push_back({12,22});
    rhsArcher.push_back({17,22});
    rhsArcher.push_back({16,22});
    rhsArcher.push_back({19,24});
}
void lionheart::TimothyFerrell::buildKnights() {
    lhsKnights.push_back({10,3});
    lhsKnights.push_back({10,4});
    lhsKnights.push_back({14,3});
    lhsKnights.push_back({16,3});
    lhsKnights.push_back({19,3});
    lhsKnights.push_back({19,4});
    //RHS
    rhsKnights.push_back({10,26});
    rhsKnights.push_back({10,25});
    rhsKnights.push_back({14,26});
    rhsKnights.push_back({16,26});
    rhsKnights.push_back({19,26});
    rhsKnights.push_back({19,25});
}
void lionheart::TimothyFerrell::buildInfantry() {
    lhsInfantry.push_back({11,3});
    lhsInfantry.push_back({11,4});
    lhsInfantry.push_back({12,4});
    lhsInfantry.push_back({13,6});
    lhsInfantry.push_back({14,6});
    lhsInfantry.push_back({14,5});
    lhsInfantry.push_back({14,7});
    lhsInfantry.push_back({15,6});
    lhsInfantry.push_back({15,4});
    lhsInfantry.push_back({15,5});
    lhsInfantry.push_back({15,7});
    lhsInfantry.push_back({16,6});
    lhsInfantry.push_back({17,4});
    lhsInfantry.push_back({18,3});
    lhsInfantry.push_back({18,4});
    //RHS
    rhsInfantry.push_back({11,26});
    rhsInfantry.push_back({11,25});
    rhsInfantry.push_back({12,25});
    rhsInfantry.push_back({13,23});
    rhsInfantry.push_back({14,23});
    rhsInfantry.push_back({14,24});
    rhsInfantry.push_back({14,22});
    rhsInfantry.push_back({15,23});
    rhsInfantry.push_back({15,25});
    rhsInfantry.push_back({15,24});
    rhsInfantry.push_back({15,22});
    rhsInfantry.push_back({16,23});
    rhsInfantry.push_back({17,25});
    rhsInfantry.push_back({18,26});
    rhsInfantry.push_back({18,25});
}

//Build defensive array...
void lionheart::TimothyFerrell::buildDefense() {
    //lhs
    lhsDefence.push_back({{10,5}, lionheart::Direction::NORTH});
    lhsDefence.push_back({{13,7}, lionheart::Direction::EAST});
    lhsDefence.push_back({{16,7}, lionheart::Direction::EAST});
    lhsDefence.push_back({{19,5}, lionheart::Direction::SOUTH});
    lhsDefence.push_back({{14,2}, lionheart::Direction::WEST});
    lhsDefence.push_back({{16,2}, lionheart::Direction::WEST});
    lhsDefence.push_back({{12,7}, lionheart::Direction::EAST});
    lhsDefence.push_back({{17,7}, lionheart::Direction::EAST});
    lhsDefence.push_back({{14,3}, lionheart::Direction::NORTH});
    lhsDefence.push_back({{16,3}, lionheart::Direction::SOUTH});

    //rhs
    rhsDefence.push_back({{10,24}, lionheart::Direction::NORTH});
    rhsDefence.push_back({{13,22}, lionheart::Direction::EAST});
    rhsDefence.push_back({{16,22}, lionheart::Direction::EAST});
    rhsDefence.push_back({{19,24}, lionheart::Direction::SOUTH});
    rhsDefence.push_back({{14,27}, lionheart::Direction::WEST});
    rhsDefence.push_back({{16,27}, lionheart::Direction::WEST});
    rhsDefence.push_back({{12,22}, lionheart::Direction::EAST});
    rhsDefence.push_back({{17,22}, lionheart::Direction::EAST});
    rhsDefence.push_back({{14,26}, lionheart::Direction::NORTH});
    rhsDefence.push_back({{16,26}, lionheart::Direction::SOUTH});
}

//is Defense
int lionheart::TimothyFerrell::isDefense(int row, int col) {
    std::vector<defenseTimothy> *defense;
    defenseTimothy tmp;
    if(currSide == lhs) defense = &lhsDefence;
    else defense = &rhsDefence;
    int size = (unsigned int)defense->size();
    for(int i=0; i < size; i++){
        tmp = defense->at(i);
        if(col == tmp.local.col && row == tmp.local.row) return i;
    }
    return -1;
}

//Check if there is an exception for this piece
int lionheart::TimothyFerrell::isInPlay(int id) {
    int size = (unsigned int)inPlay.size();
    for(int i=0; i<size; i++){
        if(inPlay[i].id == id) return i;
    }
    return -1;
}

//Check if there is an enemy in my base
bool lionheart::TimothyFerrell::enemyPresent(lionheart::SituationReport sit) {
    for (int i = 0; i < 10; ++i) {
        if (currSide == rhs) {
            for (int j = 0; j < 6; ++j) {
                if (sit.things[(i + 10)][(j + 22)].type == lionheart::SituationReport::ENEMY) {
                    return true;
                }
            }
        }
        else{
            for (int j = 0; j < 6; ++j) {
                if (sit.things[(i + 10)][(j + 2)].type == lionheart::SituationReport::ENEMY) return true;
            }
        }
    }
    return false;
}

//Check for that sneak
bool lionheart::TimothyFerrell::archerSneak(lionheart::SituationReport sit) {
    for(int i = 0; i < 10; ++i){
        if(currSide == rhs){
             if(sit.things[(i+10)][29].type == lionheart::SituationReport::ENEMY) return true;
        }
        if(currSide == lhs){
            if(sit.things[(i+10)][0].type == lionheart::SituationReport::ENEMY) return true;
        }
    }
    return false;
}

//This adjusts my strategy for all who might have copied brandonSmiths file (i only have a 30% victory with normal)
bool lionheart::TimothyFerrell::detectBrandon(lionheart::SituationReport sit) {
    //go over cols
    if(currSide == rhs){
        for(int i = 7; i >= 2; i--){
            if(i == 7 || i == 6 || i == 2){
                if(sit.things[14][i].type != lionheart::SituationReport::ENEMY) return false;
            }
            if( i == 3 || i == 4 || i == 5){
                if(sit.things[14][i].type != lionheart::SituationReport::SPACE) return false;
            }
        }
    }else{
        for(int i = 22; i <= 27; i++){
            if(i == 22 || i == 23 || i == 27){
                if(sit.things[14][i].type != lionheart::SituationReport::ENEMY) return false;
            }
            if( i == 24 || i == 25 || i == 26){
                if(sit.things[14][i].type != lionheart::SituationReport::SPACE) return false;
            }
        }
    }
    return true;
}
