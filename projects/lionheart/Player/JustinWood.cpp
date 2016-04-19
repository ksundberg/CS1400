#include "JustinWood.hpp"

lionheart::Placement lionheart::JustinWood::placeUnit(UnitType,
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
	  lionheart::JustinWood::recommendAction(Unit const & a, SituationReport, Plan b)
  {
	  if (a.getType() == CROWN){
		  if (b.movesToEnemy() < 2){
			  return move(5);
		  }
		  return wait();
	  }
	  if (a.getType() == KNIGHT){
		  if (b.hasAttack()){
			  return b.attackEnemy();
		  }
		  return b.moveToEnemyCrown();
	  }
	  return b.attackEnemy();

	  if (a.getType() == ARCHER){
		  {
			  if (b.hasAttack()){
				  return b.attackEnemy();
			  }
			  return b.moveToAllyCrown();
		  }
		  return b.attackEnemy();
	  }
	  if (a.getType() == INFANTRY){
		  if (b.hasAttack()){
			  return b.attackEnemy();
		  }
		  return b.moveToEnemyCrown();
	  }
	  return b.attackEnemy();
  }
  /*Fill this out with the behavior you want for your units.  Without changes
   * your units will just wait to be defeated.  Feel free to look at the other provided players for ideas on how to get certain behavior*/

lionheart::Blazon lionheart::JustinWood::getBlazon()
{
  /*Return your blazon here.  In case of conflicts preference will be given to
   * the students that have registered their blazons in class.*/
  return { Color::AZURE, Color::GULES, Style::CROSS, "Justin Wood" };
}
