#include "JoshuaCrane.hpp"

lionheart::Placement lionheart::JoshuaCrane::placeUnit(UnitType,
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
		lionheart::JoshuaCrane::recommendAction(Unit const &, SituationReport, Plan)
		{
			if (u.getType() == KNIGHT)
			{
				if (p.hasAttack())
				{
					return p.attackEnemy();
				}
				return p.moveToEnemyCrown();
			}
			return p.attackEnemy();

			if (u.getType() == ARCHER)
			{
				{
					if (p.hasAttack())
					{
						return p.attackEnemy();
					}
					return p.moveToEnemyCrown();
				}
				return p.attackEnemy();
			}
			if (u.getType() == INFANTRY)
			{
				if (p.hasAttack())
				{
					return p.attackEnemy();
				}
				return p.moveToEnemyCrown();
			}
			return p.attackEnemy();
		}

		lionheart::Blazon lionheart::JoshuaCrane::getBlazon()
		{
			return { Color::VERT, Color::GULES, Style::BEND, "Joshua Crane" };
		}
