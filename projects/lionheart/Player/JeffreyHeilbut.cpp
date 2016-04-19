#include "JeffreyHeilbut.hpp"
#include "SituationReport.hpp"
#include "Plan.hpp"
#include "Player.hpp"

lionheart::Placement lionheart::JeffreyHeilbut::placeUnit(UnitType,
	StartBox const &box,
	SituationReport report)
{
	/*Fill this out with instructions on how to place your initial units.  Without
	* changes your units will fill the starting box from top left to bottom right
	* in the order constructed.*/
	for (int r = box.minRow; r < box.maxRow; ++r)
		for (int c = box.minCol; c < box.maxCol; ++c)
			if (report.things[r][c].type == SituationReport::SPACE)
				return{ r, c };
	return{ 0, 0 };
}

lionheart::Action
lionheart::JeffreyHeilbut::recommendAction(Unit const &u, SituationReport , Plan p)
{
	/*Fill this out with the behavior you want for your units.  Without changes
	* your units will just wait to be defeated.  Feel free to look at the other 
	provided players for ideas on how to get certain behavior*/
	if (u.getType() == CROWN) {
		if (u.inRange(u.getLocation())) {
			p.moveToLocation(5, u.getLocation().col - 1);
		}
		else {
			p.moveToLocation(0, u.getLocation().col);
		}
	}
	else if (u.getType() == KNIGHT) {
		if (p.hasAttack()) {
			return p.attackEnemy();
		}
		return p.moveToEnemyCrown();
	}
	else if (u.getType() == INFANTRY) {
		if (p.hasAttack()) {
			return p.attackEnemy();
		}
		return p.moveToEnemy();
	}
	else if (u.getType() == ARCHER) {
		if (p.hasAttack()) {
			return p.attackEnemy();
		}
		return p.moveToEnemy();
	}
	else {
		if (p.hasAttack()) {
			return p.attackEnemy();
		}
		return p.moveToEnemy();
	}

	return Action();
}

lionheart::Blazon lionheart::JeffreyHeilbut::getBlazon()
{
	/*Return your blazon here.  In case of conflicts preference will be given to
	* the students that have registered their blazons in class.*/
	return{ Color::GULES, Color::SABLE, Style::CROSS, "Jeff Heilbut" };
}
