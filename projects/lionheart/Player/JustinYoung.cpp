#include "JustinYoung.hpp"
void lionheart::JustinYoung::newRound(){
    leftSide = false;
}

lionheart::Placement lionheart::JustinYoung::placeUnit(UnitType,
                                                       StartBox const &box,
                                                       SituationReport report) {
    if(id == 0) this->newRound(); //resets player after each round
    ++id;
    leftSide = (box.minCol < (int) (report.things[0].size() / 2));
    if (leftSide) {
        if(id == 1) this->newRound();
        switch (id) {
            // CROWN
            case 1:
                return {19, 4}; //King
            // KNIGHTS
            case 2:
                return {10, 4}; //def top
            case 3:
                return {13, 5}; //def top
            case 4:
                return {15, 5}; //def bot
            case 5:
                return {18, 4}; //def bot
            case 6:
                return {11, 7};
            case 7:
                return {18, 7};
            // ARCHERS
            case 8:
                return {11, 4}; //def top
            case 9:
                return {13, 4}; //def top
            case 10:
                return {15, 4}; //def bot
            case 11:
                return {17, 4}; //def bot
            case 12:
                return {15, 2}; //static mid
            case 13:
                return {10, 2}; //sentry
            case 14:
                return {13, 7};
            case 15:
                return {19, 2}; //sentry
            // INFANTRY
            case 16:
                return {10, 5}; //def top
            case 17:
                return {12, 4}; //def top
            case 18:
                return {14, 4}; //def top
            case 19:
                return {14, 5}; //def bot
            case 20:
                return {16, 4}; //def bot
            case 21:
                return {18, 5}; //def bot
            case 22:
                return {12, 2}; //static top
            case 23:
                return {14, 2}; //static top
            case 24:
                return {16, 2}; //static bot
            case 25:
                return {18, 2}; //static bot
            case 26:
                return {14, 6};
            case 27:
                return {14, 7};
            case 28:
                return {15, 6};
            case 29:
                return {15, 7};
            case 30:
                id = 0;
                return {16, 7};
        }
    }
    else {
        switch(id){
            // CROWN
            case 1:
                return {19, 25}; //King
                // KNIGHTS
            case 2:
                return {10, 25}; //def top
            case 3:
                return {13, 24}; //def top
            case 4:
                return {15, 24}; //def bot
            case 5:
                return {18, 25}; //def bot
            case 6:
                return {11, 22};
            case 7:
                return {18, 22};
                // ARCHERS
            case 8:
                return {11, 25}; //def top
            case 9:
                return {13, 25}; //def top
            case 10:
                return {15, 25}; //def bot
            case 11:
                return {17, 25}; //def bot
            case 12:
                return {15, 27}; //static mid
            case 13:
                return {10, 27}; //sentry
            case 14:
                return {13, 22};
            case 15:
                return {19, 27}; //sentry
                // INFANTRY
            case 16:
                return {10, 24}; //def top
            case 17:
                return {12, 25}; //def top
            case 18:
                return {14, 25}; //def top
            case 19:
                return {14, 24}; //def bot
            case 20:
                return {16, 25}; //def bot
            case 21:
                return {18, 24}; //def bot
            case 22:
                return {12, 27}; //static top
            case 23:
                return {14, 27}; //static top
            case 24:
                return {16, 27}; //static bot
            case 25:
                return {18, 27}; //static bot
            case 26:
                return {14, 23};
            case 27:
                return {14, 22};
            case 28:
                return {15, 23};
            case 29:
                return {15, 22};
            case 30:
                id = 0;
                return {16, 22};
        }
    }
    return {0, 0};
}

lionheart::Action lionheart::JustinYoung::makeWayTo(int row, int col, lionheart::Plan plan){
    return plan.moveToLocation(row, col);
}

lionheart::Action lionheart::JustinYoung::kingsguardActions(int unitID, lionheart::Plan plan){
    if(this->leftSide){
        switch(unitID){
            //Knights
            case 1: return makeWayTo(8, 7, plan);
            case 2: return plan.moveToLocation(7, 0);
            case 3: return plan.moveToLocation(22, 0);
            case 4: return plan.moveToLocation(21, 7);
                //Archers
            case 7: return plan.moveToLocation(14, 0);
            case 8: return plan.moveToLocation(10, 0);
            case 9: return plan.moveToLocation(19, 0);
            case 10: return plan.moveToLocation(16, 0);
                //Infantry
            case 15: return plan.moveToLocation(13, 0);
            case 16: return plan.moveToLocation(11, 0);
            case 17: return plan.moveToLocation(9, 0);
            case 18: return plan.moveToLocation(20, 0);
            case 19: return plan.moveToLocation(18, 0);
            case 20: return plan.moveToLocation(17, 0);
                //Sentries
            case 12: return plan.attackEnemy();
            case 14: return plan.attackEnemy();

            default: return plan.moveToAllyCrown();
        }
    } else {
        switch(unitID){
            //Knights
            case 1: return makeWayTo(8, 22, plan);
            case 2: return plan.moveToLocation(7, 29);
            case 3: return plan.moveToLocation(22, 29);
            case 4: return plan.moveToLocation(21, 22);
                //Archers
            case 7: return plan.moveToLocation(14, 29);
            case 8: return plan.moveToLocation(10, 29);
            case 9: return plan.moveToLocation(19, 29);
            case 10: return plan.moveToLocation(16, 29);
                //Infantry
            case 15: return plan.moveToLocation(13, 29);
            case 16: return plan.moveToLocation(11, 29);
            case 17: return plan.moveToLocation(9, 29);
            case 18: return plan.moveToLocation(20, 29);
            case 19: return plan.moveToLocation(18, 29);
            case 20: return plan.moveToLocation(17, 29);
                //Sentries
            case 12: return plan.attackEnemy();
            case 14: return plan.attackEnemy();

            default: return plan.moveToAllyCrown();
        }
    }
}

lionheart::Action lionheart::JustinYoung::kingsguardFaceEnemy(int unitID) {
    switch(unitID) {
        //Knights
        case 1:
            if (leftSide) return turn(lionheart::Direction::EAST);
            else return turn(lionheart::Direction::WEST);
        case 2: return turn(lionheart::Direction::SOUTH);
        case 3: return turn(lionheart::Direction::NORTH);
        case 4:
            if (leftSide) return turn(lionheart::Direction::EAST);
            else return turn(lionheart::Direction::WEST);
            //Archers
        case 7: return turn(lionheart::Direction::NORTH);
        case 8: return turn(lionheart::Direction::NORTH);
        case 9: return turn(lionheart::Direction::SOUTH);
        case 10: return turn(lionheart::Direction::SOUTH);
            //Infantry
        case 15: return turn(lionheart::Direction::NORTH);
        case 16: return turn(lionheart::Direction::NORTH);
        case 17: return turn(lionheart::Direction::NORTH);
        case 18: return turn(lionheart::Direction::SOUTH);
        case 19: return turn(lionheart::Direction::SOUTH);
        case 20: return turn(lionheart::Direction::SOUTH);
            //Sentries
        case 12: return turn(lionheart::Direction::NORTH);
        case 14: return turn(lionheart::Direction::SOUTH);

        default: if(leftSide) return turn(lionheart::Direction::EAST);
                else return turn(lionheart::Direction::WEST);
    }
}

bool lionheart::JustinYoung::isKingsguardFacing(Unit const &unit){
    switch(unit.getId()) {
        //Knights
        case 1:
            if (leftSide) return (unit.getFacing() == lionheart::Direction::EAST);
            else return (unit.getFacing() == lionheart::Direction::WEST);
        case 2:
            return (unit.getFacing() == lionheart::Direction::SOUTH);
        case 3:
            return (unit.getFacing() == lionheart::Direction::NORTH);
        case 4:
            if (leftSide) return (unit.getFacing() == lionheart::Direction::EAST);
            else return (unit.getFacing() == lionheart::Direction::WEST);
            //Archers
        case 7:
            return (unit.getFacing() == lionheart::Direction::NORTH);
        case 8:
            return (unit.getFacing() == lionheart::Direction::NORTH);
        case 9:
            return (unit.getFacing() == lionheart::Direction::SOUTH);
        case 10:
            return (unit.getFacing() == lionheart::Direction::SOUTH);
            //Infantry
        case 15:
            return (unit.getFacing() == lionheart::Direction::NORTH);
        case 16:
            return (unit.getFacing() == lionheart::Direction::NORTH);
        case 17:
            return (unit.getFacing() == lionheart::Direction::NORTH);
        case 18:
            return (unit.getFacing() == lionheart::Direction::SOUTH);
        case 19:
            return (unit.getFacing() == lionheart::Direction::SOUTH);
        case 20:
            return (unit.getFacing() == lionheart::Direction::SOUTH);
            //Sentries
        case 12:
            return (unit.getFacing() == lionheart::Direction::NORTH);
        case 14:
            return (unit.getFacing() == lionheart::Direction::SOUTH);

        default:
            return false;
    }
}

bool lionheart::JustinYoung::isKingsguardInPosition(Unit const &unit) {
    if(this->leftSide){
        switch(unit.getId()){
            //Knights
            case 1: return (unit.getLocation().row == 8 && unit.getLocation().col == 7);
            case 2: return (unit.getLocation().row == 7 && unit.getLocation().col == 0);
            case 3: return (unit.getLocation().row == 22 && unit.getLocation().col == 0);
            case 4: return (unit.getLocation().row == 21 && unit.getLocation().col == 7);
                //Archers
            case 7: return (unit.getLocation().row == 14 && unit.getLocation().col == 0);
            case 8: return (unit.getLocation().row == 10 && unit.getLocation().col == 0);
            case 9: return (unit.getLocation().row == 19 && unit.getLocation().col == 0);
            case 10: return (unit.getLocation().row == 16 && unit.getLocation().col == 0);
                //Infantry
            case 15: return (unit.getLocation().row == 13 && unit.getLocation().col == 0);
            case 16: return (unit.getLocation().row == 11 && unit.getLocation().col == 0);
            case 17: return (unit.getLocation().row == 9 && unit.getLocation().col == 0);
            case 18: return (unit.getLocation().row == 20 && unit.getLocation().col == 0);
            case 19: return (unit.getLocation().row == 18 && unit.getLocation().col == 0);
            case 20: return (unit.getLocation().row == 17 && unit.getLocation().col == 0);

                //sentries
            case 12: case 14:
                    return true;

            default: return true;
        }
    } else {
        switch(unit.getId()){
            //Knights
            case 1: return (unit.getLocation().row == 8 && unit.getLocation().col == 22);
            case 2: return (unit.getLocation().row == 7 && unit.getLocation().col == 29);
            case 3: return (unit.getLocation().row == 22 && unit.getLocation().col == 29);
            case 4: return (unit.getLocation().row == 21 && unit.getLocation().col == 22);
                //Archers
            case 7: return (unit.getLocation().row == 14 && unit.getLocation().col == 29);
            case 8: return (unit.getLocation().row == 10 && unit.getLocation().col == 29);
            case 9: return (unit.getLocation().row == 19 && unit.getLocation().col == 29);
            case 10: return (unit.getLocation().row == 16 && unit.getLocation().col == 29);
                //Infantry
            case 15: return (unit.getLocation().row == 13 && unit.getLocation().col == 29);
            case 16: return (unit.getLocation().row == 11 && unit.getLocation().col == 29);
            case 17: return (unit.getLocation().row == 9 && unit.getLocation().col == 29);
            case 18: return (unit.getLocation().row == 20 && unit.getLocation().col == 29);
            case 19: return (unit.getLocation().row == 18 && unit.getLocation().col == 29);
            case 20: return (unit.getLocation().row == 17 && unit.getLocation().col == 29);

                //Sentries
            case 12: case 14:
                    return true;

            default: return true;
        }
    }
}

bool lionheart::JustinYoung::isKingsguard(int unitID) {
    switch(unitID){
        case 1: case 2: case 3:
        case 4: return true;

        case 7: case 8: case 9:
        case 10: return true;

        case 15: case 16: case 17: case 18: case 19:
        case 20: return true;

        case 12: case 14: return true;

        default: return false;
    }
}

lionheart::Action
lionheart::JustinYoung::recommendAction(Unit const &unit, SituationReport report, Plan plan) {
    /*Fill this out with the behavior you want for your units.  Without changes
     * your units will just wait to be defeated.  Feel free to look at the other provided players for
     * ideas on how to get certain behavior*/
    ///can turn > 90 degrees

    //printf("UnitID: %d\n", unit.getId());

    Action a;
    //return plan.moveToEnemyCrown();
    if (plan.hasAttack()) return plan.attackEnemy(); //go ahead and take a your swing, return because this is most important

        //Kingsguard: 1 - 4, 7 - 10, 15 - 20
    if (isKingsguard(unit.getId())) {
        if (report.turns > 50) {
            if (unit.getId() == 1 || unit.getId() == 4) {//forward knights
                a = plan.moveToEnemyCrown();
            }
            if (unit.getId() == 2 || unit.getId() == 3) {//flanking knights
                a = plan.moveToEnemyCrown();
            }
            if( report.turns > 60) {
                if (unit.getId() == 18 || unit.getId() == 17) {//outer defense infantry
                    a = plan.moveToEnemyCrown();
                }
            }
        }
        if (isKingsguardInPosition(unit)) {
            if (!isKingsguardFacing(unit)) {
                a = kingsguardFaceEnemy(unit.getId()); //move to face
            }
        } else {
            a = kingsguardActions(unit.getId(), plan); //move to position
        }
    }
    else if (unit.getId() == 0) {
        if (leftSide) {
            a = plan.moveToLocation(15, 0); //behind left fort
        } else {
            a = plan.moveToLocation(15, 29); //behind right fort
        }
    } else { //normal piece
        if(report.turns %2 == 0) { //paritions on parity
            a = plan.moveToEnemy(); //half to units
        } else {
            a = plan.moveToEnemyCrown(); //half to crown
        }
    }

    return a;
}

lionheart::Blazon lionheart::JustinYoung::getBlazon() {

    return {Color::GULES, Color::OR, Style::INVERTED_CHEVERON, "Justin Young"};
}
