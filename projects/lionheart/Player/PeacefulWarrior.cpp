#include "PeacefulWarrior.hpp"


lionheart::Placement lionheart::PeacefulWarrior::placeUnit(UnitType type, StartBox const& box, SituationReport report)
{
  lionheart::Placement crown;
  auto useMin = (box.minCol < static_cast<int>((report.things[0].size() / 2)));
  if (useMin)
    crown = {(box.minRow + box.maxRow) / 2, box.minCol };
  else
    crown = {(box.minRow + box.maxRow) / 2, box.maxCol };

  if (type == CROWN)
  {
    return crown;
  }
        auto minR = box.minRow;
	auto maxR = box.maxRow;
	auto minC = box.minCol;
	auto maxC = box.maxCol;

	if (type == KNIGHT)
	{
		minR = crown.row - 3;
		maxR = crown.row + 3;
		if (useMin) {
			maxC = crown.col + 4;
			minC = crown.col + 4;
		}
		else
		{
			maxC = crown.col - 4;
			minC = crown.col - 4;
		}
	}
	if (type == INFANTRY)
	{
		minR = crown.row - 3;
		maxR = crown.row + 3;
		if (useMin) {
			maxC = crown.col + 3;
			minC = crown.col;
		}
		else
		{
			maxC = crown.col;
			minC = crown.col - 3;
		}
	}
	if (type == ARCHER)
	{
		minR = crown.row - 1;
		maxR = crown.row + 1;
		if (useMin)
		{
			maxC = crown.col + 2;
			minC = crown.col;
		}
		else
		{
			maxC = crown.col;
			minC = crown.col - 2;
		}

	}

	for (int r = minR; r <= maxR; ++r)
		for (int c = minC; c <= maxC; ++c)
			if (report.things[r][c].type == SituationReport::SPACE) return{ r, c };
	return{ maxR, maxC };
}

  lionheart::Action
lionheart::PeacefulWarrior::recommendAction(Unit const& u, SituationReport , Plan p)
{
	  for (int i = 0; i <= 5; i++)
	  {
		  if (p.hasAttack()) return p.attackEnemy();
		  if (u.getType() == CROWN) {
			  if (p.movesToEnemy() > 6) return p.moveToLocation(15, 15);
		  }
		  if (u.getType() == ARCHER) {
			  if (p.movesToEnemy() < 4) return p.attackEnemy();
			  return p.moveToAllyCrown();
		  }

		  if (p.movesToAllyCrown() > 10) {
			  return p.moveToAllyCrown();
		  }
		  return p.moveToEnemyCrown();
	  }

	  if (u.getType() == CROWN) {
		  return wait();
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

lionheart::Blazon lionheart::PeacefulWarrior::getBlazon()
{

	return{ Color::AZURE, Color::ARGENT, Style::CHIEF, "PeacefulWarrior" };
}
