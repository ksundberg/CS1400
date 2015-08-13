#include "Alexa.hpp"

lionheart::Placement lionheart::Alexa::placeUnit(UnitType , StartBox const &box, SituationReport report)
{
	for (int r = box.minRow; r < box.maxRow; ++r)
		for (int c = box.minCol; c < box.maxCol; ++c)
			if (report.things[r][c].type == SituationReport::SPACE) return{ r, c };
	return{ 0, 0 };
}
	

  lionheart::Action
lionheart::Alexa::recommendAction(Unit const & u, SituationReport, Plan p)
{
 
	  if (p.hasAttack()) return p.attackEnemy();
	  if (u.getType() == CROWN) {
		  if (p.movesToEnemy() < 6) return p.moveToLocation(15, 15);
	  }
	  if (u.getType() == ARCHER) {
		  if (p.movesToEnemy() < 4) return p.attackEnemy();
		  return p.moveToEnemyCrown();
	  }

	  if (u.getType() == INFANTRY) {
		  if (p.movesToEnemy() < 4) return p.attackEnemy();
		  return p.moveToEnemyCrown();
	  }

	  if (p.movesToAllyCrown() < 10) {
		  return p.moveToAllyCrown();
	  }
	  return p.moveToEnemyCrown();

	  if (p.movesToEnemy() < 3)
	  {
		  return wait();
	  }
}

lionheart::Blazon lionheart::Alexa::getBlazon()
{
  
  return { Color::GULES, Color::SABLE, Style::PALE, "Sangria" };
}
