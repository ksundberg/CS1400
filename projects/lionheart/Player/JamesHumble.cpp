#include "JamesHumble.hpp"

lionheart::Placement lionheart::JamesHumble::placeUnit(UnitType,
                                              StartBox const &box,
                                              SituationReport report)
{
  /*Fill this out with instructions on how to place your initial units.  Without
   * changes your units will fill the starting box from top left to bottom right
   * in the order constructed.*/

//  if(utype==CROWN)
//	{
		

  
  isEast = (box.minCol > static_cast<int>(report.things[0].size() / 2));


  for (int r = box.minRow; r < box.maxRow; ++r)
    for (int c = box.minCol; c < box.maxCol; ++c)
      if (report.things[r][c].type == SituationReport::SPACE)
        return { r, c };
  return { 0, 0 };
}



lionheart::Action lionheart::JamesHumble::recommendAction(Unit const & u, SituationReport, Plan p)
{
  /*Fill this out with the behavior you want for your units.  Without changes
   * your units will just wait to be defeated.  Feel free to look at the other provided players for ideas on how to get certain behavior*/
  if(u.getType() == CROWN)
  {
    if(isEast)
    {
      return p.moveToLocation(0,29);
    }
    else
    {
      return p.moveToLocation(0,0);
    }
  }
  else
  {
    
    if(p.hasAttack())
    {
      return p.attackEnemy();
    }
    return p.moveToEnemyCrown();	
  }
}

lionheart::Blazon lionheart::JamesHumble::getBlazon()
{
  /*Return your blazon here.  In case of conflicts preference will be given to
   * the students that have registered their blazons in class.*/
  return { Color::AZURE, Color::VERT, Style::BEND, "James Humble" };
}
