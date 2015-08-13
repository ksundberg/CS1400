#include "AsgardianSaphire.hpp"
#include <cstdlib>

//Christian Udall
//A02183052
//CS1400

//namespace lionheart{
    lionheart::Placement lionheart::AsgardianSaphire::placeUnit(UnitType, StartBox const& box, SituationReport report)
{
    for (int r = box.minRow; r < box.maxRow; ++r)
        for (int c = box.minCol; c < box.maxCol; ++c)
          if (report.things[r][c].type == SituationReport::SPACE) return {r, c};
	  return{ 0, 0 };
}
  lionheart::Action
lionheart::AsgardianSaphire::recommendAction(Unit const& u, SituationReport r, Plan p)
{

  /*Fill this out with the behavior you want for your units.  Without changes
   * your units will just wait to be defeated.  Feel free to look at the other provided players for ideas on how to get certain behavior*/
    if (u.getType() == CROWN)
    {
        if (p.movesToEnemy()<=10)
        {
            auto row = rand() % 30 + 1;
            auto cols = rand() % 90 + 1;
            p.moveToLocation(row, cols);
        }
                
        return wait();
    }
    if (r.turns>15)
    {
        lionheart::Map::Location loc = u.getLocation();
        lionheart::SituationReport::ThingType type = lionheart::SituationReport::ThingType::SPACE;
        lionheart::Direction facing = u.getFacing();



        switch (facing) {
            case Direction::NORTH:
                type = r.things[loc.row - 1][loc.col].type;
                break;
            case Direction::EAST:
                type = r.things[loc.row][loc.col + 1].type;
                break;
            case Direction::SOUTH:
                type = r.things[loc.row + 1][loc.col].type;
                break;
            case Direction::WEST:
                type = r.things[loc.row][loc.col - 1].type;
                break;
        }

        int randomval = rand() % 2;

        if (type != lionheart::SituationReport::ThingType::ENEMY && type != lionheart::SituationReport::ThingType::SPACE) {
            switch (facing) {
                case Direction::NORTH:
                    if (randomval == 1)
                        return p.moveToLocation(loc.row, loc.col + 1);
                    else
                        return p.moveToLocation(loc.row, loc.col - 1);
                case Direction::EAST:
                    if (randomval == 1)
                        return p.moveToLocation(loc.row + 1, loc.col);
                    else
                        return p.moveToLocation(loc.row - 1, loc.col);
                case Direction::SOUTH:
                    if (randomval == 1)
                        return p.moveToLocation(loc.row, loc.col + 1);
                    else
                        return p.moveToLocation(loc.row, loc.col - 1);
                case Direction::WEST:
                    if (randomval == 1)
                        return p.moveToLocation(loc.row - 1, loc.col);
                    else
                        return p.moveToLocation(loc.row + 1, loc.col);
            }
        }

        if(u.getType() == KNIGHT)
        {
            if(p.hasAttack())
            {
                return p.attackEnemy();
            }
            return p.moveToEnemyCrown();
        }
        return p.attackEnemy();
    }
    else
    {
        if (p.hasAttack())
        {
            return p.attackEnemy();
        }
        else
        {
            lionheart::Direction facing = u.getFacing();

            switch (facing) {
                case Direction::NORTH:
                    return turn(Direction::EAST);
                case Direction::EAST:
                    return turn(Direction::SOUTH);
                case Direction::SOUTH:
                    return turn(Direction::WEST);
                case Direction::WEST:
                    return turn(Direction::NORTH);
            }
        }
    }
    return Action();
}

lionheart::Blazon lionheart::AsgardianSaphire::getBlazon()
{
  /*Return your blazon here.  In case of conflicts preference will be given to
   * the students that have registered their blazons in class.*/
  return { Color::SABLE, Color::GULES, Style::CHEVERON, "Asgardian Saphire" };
}
//}

