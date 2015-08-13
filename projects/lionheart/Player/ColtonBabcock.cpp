#include "ColtonBabcock.hpp"
#include <random>

lionheart::Placement lionheart::ColtonBabcock::placeUnit(UnitType , StartBox const &box, SituationReport report )
{
	static std::random_device rd;
	static std::mt19937 engine(rd());

	std::uniform_int_distribution<> row(box.minRow, box.maxRow);
	std::uniform_int_distribution<> col(box.minCol, box.maxCol);
	auto r = row(engine);
	auto c = col(engine);

	while (report.things[r][c].type != SituationReport::SPACE)
	{
		r = row(engine);
		c = col(engine);
	}
	return{ r, c };
}

  lionheart::Action lionheart::ColtonBabcock::recommendAction(Unit const& u, SituationReport, Plan p)
{
	  static std::random_device rd;
	  static std::mt19937 engine(rd());

	  std::uniform_int_distribution<> percent(0, 100);
	  
	if (p.hasAttack()) return p.attackEnemy();
	if (u.getType() == CROWN) {
		if (p.movesToEnemy() > 6) return p.moveToLocation(1, 5);
	}
	if (u.getType() == KNIGHT && percent(engine) < 92) {
		return p.moveToEnemyCrown();
	}
	if (u.getType() == ARCHER) {
		if (p.movesToEnemy() < 6) return p.attackEnemy();
		else if (percent(engine) < 35 ) return p.attackEnemy();
		return p.moveToAllyCrown();
	}

	if (p.movesToAllyCrown() > 10 && percent(engine) < 60) {
		return p.moveToAllyCrown();
	}
	return p.moveToEnemyCrown();
}

lionheart::Blazon lionheart::ColtonBabcock::getBlazon()
{
  return { Color::AZURE, Color::ARGENT, Style::PER_BEND, "Prevalio" };
}
