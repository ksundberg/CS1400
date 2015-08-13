#include "TylerClark.hpp"
// have archers stay and knight,infatry attack!!!
//attack enemy and stay within 3 of king.
//knight and inf to go straight attack at crown also if other enemeies in range of 3


lionheart::Placement lionheart::TylerClark::placeUnit(UnitType,
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
lionheart::TylerClark::recommendAction(Unit const & u, SituationReport, Plan p)
{
  /*Fill this out with the behavior you want for your units.  Without changes
   * your units will just wait to be defeated.  Feel free to look at the other provided players for ideas on how to get certain behavior*/
	if (u.getType() == KNIGHT)
	{
		return p.attackEnemy();
	}
	if (u.getType() == INFANTRY)
	{
		return p.attackEnemy();
	}
	if (p.hasAttack())
	{
		return p.attackEnemy();
	}
	return wait();
  }


lionheart::Blazon lionheart::TylerClark::getBlazon()
{
  /*Return your blazon here.  In case of conflicts preference will be given to
   * the students that have registered their blazons in class.*/
  return { Color::GULES, Color::ARGENT, Style::CHEVERON, "Sir Lancealot?" };
}
