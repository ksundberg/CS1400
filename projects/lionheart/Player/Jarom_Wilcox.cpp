#include "Jarom_Wilcox.hpp"

//Alright, this may not be a great strategy, or look like it took much thought/effort,
//but it took me a long time just to get to this point and I learned A LOT in the process.



lionheart::Placement lionheart::Jarom_Wilcox::placeUnit(UnitType type,
                                              StartBox const &box,
                                              SituationReport report)
{
  /*Fill this out with instructions on how to place your initial units.  Without
   * changes your units will fill the starting box from top left to bottom right
   * in the order constructed.*/

	auto useMin = (box.minCol < static_cast<int>((report.things[0].size() / 2)));
	if (type == CROWN)
	{
		if (useMin)
			crown = { (box.minRow + box.maxRow) / 2, box.minCol };
		else
			crown = { (box.minRow + box.maxRow) / 2, box.maxCol };
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
lionheart::Jarom_Wilcox::recommendAction(Unit const & u, SituationReport, Plan p)
{
  /*Fill this out with the behavior you want for your units.  Without changes
   * your units will just wait to be defeated.  Feel free to look at the other provided players for ideas on how to get certain behavior*/
	  if (u.getType() == CROWN) 
	  {
		  //if someone gets near, move away;
		  return wait();
	  }

	  if (u.getType() == ARCHER)
	  {
		  if (p.hasAttack())
		  {
			  return p.attackEnemy();
		  }
		  return p.moveToEnemyCrown();
	  }
	  return p.attackEnemy();

	  if (u.getType() == INFANTRY)
	  {
		  if (p.hasAttack())
		  {
			  return p.attackEnemy();
		  }
		  return p.moveToEnemyCrown();
	  }
	  return p.attackEnemy();

	  if (u.getType() == KNIGHT)
	  {
		  if (p.hasAttack())
		  {
			  return p.attackEnemy();
		  }
		  return p.moveToEnemyCrown();
	  }
}

lionheart::Blazon lionheart::Jarom_Wilcox::getBlazon()
{
  /*Return your blazon here.  In case of conflicts preference will be given to
   * the students that have registered their blazons in class.*/
  return { Color::AZURE, Color::SABLE, Style::CHEVERON, "Jarom_Wilcox" };
}
