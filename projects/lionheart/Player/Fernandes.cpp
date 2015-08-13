#include "Fernandes.hpp"

lionheart::Placement lionheart::Fernandes::placeUnit(UnitType,
                                                         StartBox const &box,
                                                         SituationReport report)
{
        for (int r = box.minRow; r < box.maxRow; ++r)
        for (int c = box.minCol; c < box.maxCol; ++c)
            if (report.things[r][c].type == SituationReport::SPACE)
                return { r, c };
    return { 0, 0 };
}

lionheart::Action
lionheart::Fernandes::recommendAction(Unit const & u, SituationReport, Plan p)
{
    if (u.getType() == CROWN) {
        return wait();
    }
    if(u.getType() == KNIGHT)
    {
        if(p.hasAttack())
        {
            return p.attackEnemy();
        }
        return p.moveToEnemyCrown();
    }
    return p.attackEnemy();
    
    return Action();
}

lionheart::Blazon lionheart::Fernandes::getBlazon()
{    return { Color::SABLE, Color::OR, Style::BEND_SINISTER, "Fernandes" };
}
