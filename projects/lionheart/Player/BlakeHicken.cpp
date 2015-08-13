#include "BlakeHicken.hpp"

lionheart::Placement lionheart::BlakeHicken::placeUnit(UnitType,
                                              StartBox const &box,
                                              SituationReport report)
{
  /*Fill this out with instructions on how to place your initial units.  Without
   * changes your units will fill the starting box from top left to bottom right
   * in the order constructed.*/
  for (int r = box.minRow; r < box.maxRow; ++r)
    for (int c = box.minCol; c < box.maxCol; ++c)
      if (report.things[r][c].type == SituationReport::SPACE)
        return { r, c };
  return { 0, 0 };
}

  lionheart::Action
lionheart::BlakeHicken::recommendAction(Unit const & u, SituationReport, Plan p)
{
  /*Fill this out with the behavior you want for your units.  Without changes
   * your units will just wait to be defeated.  Feel free to look at the other provided players for ideas on how to get certain behavior*/
	if (u.getType() == CROWN) {
		return wait();
	}
	if (u.getType() == ARCHER) {
		if (p.movesToEnemy() < 4) return p.attackEnemy();
		return p.moveToAllyCrown();
	}

	if (u.getType() == KNIGHT)
	{
		if (p.hasAttack())
		{
			return p.attackEnemy();
		}
		return p.moveToEnemyCrown();
	}
	return p.attackEnemy();



}

lionheart::Blazon lionheart::BlakeHicken::getBlazon()
{
  /*Return your blazon here.  In case of conflicts preference will be given to
   * the students that have registered their blazons in class.*/
  return { Color::VERT, Color::SABLE, Style::BEND, "Blake Hicken" };
}
