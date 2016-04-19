

#include "CameronCummings.hpp"
#include "Unit.hpp"

namespace
{
    auto id = 0;
    bool westSide = true;
    auto numTurns = 0;
}


lionheart::Placement lionheart::CameronCummings::placeUnit(UnitType,
                                              StartBox const &box,
                                              SituationReport report)
{
  /* Place units in fort */
    numTurns = 0;
    ++id;
    westSide = (box.minCol < static_cast<int>(report.things[0].size() / 2));
    
    if (westSide)
    {
        switch (id)
        {
            // Crown
            case 1: return {14,5}
            // Knights
            case 2: return {13,4}
            case 3: return {13,5}
            case 4: return {13,6}
            case 5: return {15,4}
            case 6: return {15,5}
            case 7: return {15,6}
            // Archers
            case 8: return {10,4}
            case 9: return {10,5}
            case 10: return {13,7}
            case 11: return {14,7}
            case 12: return {15,7}
            case 13: return {16,7}
            case 14: return {19,4}
            case 15: return {19,5}
            // Infantry
            case 16: return {11,3}
            case 17: return {11,4}
            case 18: return {11,5}
            case 19: return {12,3}
            case 20: return {12,4}
            case 21: return {12,5}
            case 22: return {14,4}
            case 23: return {14,6}
            case 24: return {16,6}
            case 25: return {17,3}
            case 26: return {17,4}
            case 27: return {17,5}
            case 28: return {18,3}
            case 29: return {18,4}
            case 30: id=0
                return {18,5}
        }
    }
    else
    {
        switch (id)
        {
            // Crown
            case 1: return {14,24}
            // Knights
            case 2: return {13,23}
            case 3: return {13,24}
            case 4: return {13,25}
            case 5: return {15,23}
            case 6: return {15,24}
            case 7: return {15,25}
            // Archers
            case 8: return {10,25}
            case 9: return {10,26}
            case 10: return {13,22}
            case 11: return {14,22}
            case 12: return {15,22}
            case 13: return {16,22}
            case 14: return {19,25}
            case 15: return {19,26}
            // Infantry
            case 16: return {11,24}
            case 17: return {11,25}
            case 18: return {11,26}
            case 19: return {12,24}
            case 20: return {12,25}
            case 21: return {12,26}
            case 22: return {14,23}
            case 23: return {14,25}
            case 24: return {16,23}
            case 25: return {17,24}
            case 26: return {17,25}
            case 27: return {17,26}
            case 28: return {18,24}
            case 29: return {18,25}
            case 30: id=0
                return {18,26}
        }
    }
    return {0,0};
}

  lionheart::Action
lionheart::CameronCummings::recommendAction(Unit const& u, SituationReport report, Plan p)
{
    ++numTurns;
    if (numTurns/30 < 55) // defend until turn 55
    {
        if (p.hasAttack())
        {
            return p.attackEnemy();
        }
        if (westSide) // West Fort Defense
        {
            switch (u.getId())
            {
                // Crown
                case 1: return wait();
                // Knights
                case 2:
                    if (movesToEnemy > 3)
                    {
                        return turn(Direction::NORTH)
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 3:
                    if (movesToEnemy > 3)
                    {
                        return turn(Direction::NORTH)
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 4:
                    if (movesToEnemy > 3)
                    {
                        return turn(Direction::EAST)
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 5:
                    if (movesToEnemy > 3)
                    {
                        return turn(Direction::SOUTH)
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 6:
                    if (movesToEnemy > 3)
                    {
                        return turn(Direction::SOUTH)
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 7:
                    if (movesToEnemy > 3)
                    {
                        return turn(Direction::EAST)
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                // Archers
                case 8:
                    return turn(Direction::NORTH);
                case 9:
                    return turn(Direction::NORTH);
                case 10:
                    return turn(Direction::EAST);
                case 11:
                    return turn(Direction::EAST);
                case 12:
                    return turn(Direction::EAST);
                case 13:
                    return turn(Direction::EAST);
                case 14:
                    return turn(Direction::SOUTH);
                case 15:
                    return turn(Direction::SOUTH);
                // Infantry
                case 16:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::EAST);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 17:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::NORTH);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 18:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::WEST);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 19:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::EAST);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 20:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::NORTH);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 21:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::WEST);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 22:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::WEST);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 23:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::EAST);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 24:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::EAST);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 25:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::EAST);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 26:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::SOUTH);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 27:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::WEST);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 28:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::EAST);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 29:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::SOUTH);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 30:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::WEST);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
            }
        }
        else    // East Fort Defense
        {
            switch (u.getId())
            {
                // Crown
                case 1: return wait();
                // Knights
                case 2:
                    if (movesToEnemy > 3)
                    {
                        return turn(Direction::WEST)
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 3:
                    if (movesToEnemy > 3)
                    {
                        return turn(Direction::NORTH)
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 4:
                    if (movesToEnemy > 3)
                    {
                        return turn(Direction::NORTH)
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 5:
                    if (movesToEnemy > 3)
                    {
                        return turn(Direction::WEST)
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 6:
                    if (movesToEnemy > 3)
                    {
                        return turn(Direction::SOUTH)
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 7:
                    if (movesToEnemy > 3)
                    {
                        return turn(Direction::SOUTH)
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                    // Archers
                case 8:
                    return turn(Direction::NORTH);
                case 9:
                    return turn(Direction::NORTH);
                case 10:
                    return turn(Direction::WEST);
                case 11:
                    return turn(Direction::WEST);
                case 12:
                    return turn(Direction::WEST);
                case 13:
                    return turn(Direction::WEST);
                case 14:
                    return turn(Direction::SOUTH);
                case 15:
                    return turn(Direction::SOUTH);
                    // Infantry
                case 16:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::EAST);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 17:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::NORTH);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 18:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::WEST);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 19:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::EAST);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 20:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::NORTH);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 21:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::WEST);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 22:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::EAST);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 23:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::WEST);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 24:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::WEST);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 25:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::EAST);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 26:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::SOUTH);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 27:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::WEST);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 28:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::EAST);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 29:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::SOUTH);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
                case 30:
                    if (movesToEnemy > 1)
                    {
                        return turn(Direction::WEST);
                    }
                    else
                    {
                        return p.attackEnemy();
                    }
            }
        }
    }
    else    // numTurns is >55 at this point - CHARGE!
    {
        if (u.getType() == CROWN)
        {
            if (numTurns/30 > 80)
            {
                if (p.hasAttack())
                {
                    return p.attackEnemy();
                }
                return p.moveToEnemyCrown();
            }
            else
            {
                return wait();
            }
        }
        if(u.getType() == KNIGHT)
        {
            if (numTurns/30 > 78)
            {
                if(p.hasAttack())
                {
                    return p.attackEnemy();
                }
                return p.moveToEnemyCrown();
            }
            else
            {
                return wait();
            }
        }
        if (p.hasAttack())
        {
            p.attackEnemy();
        }
        else
        {
            return p.moveToEnemyCrown();
        }
    }
}

lionheart::Blazon lionheart::CameronCummings::getBlazon()
{
  return { Color::SABLE, Color::GULES, Style::INVERTED_CHEVERON, "Cameron Cummings" };
}
