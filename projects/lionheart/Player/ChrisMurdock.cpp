#include "ChrisMurdock.hpp"

lionheart::Placement lionheart::ChrisMurdock::placeUnit(UnitType,
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
lionheart::ChrisMurdock::recommendAction(Unit const& u, SituationReport, Plan p)
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
    if(u.getType() == ARCHER)
    {
        p.moveToAllyCrown();
        if(p.movesToEnemy() < 4)
        {
            return p.attackEnemy();
        }
        return wait();
    }
    if(u.getType() == INFANTRY)
    {
        if(p.hasAttack())
        {
            return p.attackEnemy();
        }
        return p.moveToEnemyCrown();
    }
    return p.attackEnemy();
}
lionheart::Blazon lionheart::ChrisMurdock::getBlazon()
{
  return { Color::AZURE, Color::OR, Style::QUARTERLY, "LINK" };
}
