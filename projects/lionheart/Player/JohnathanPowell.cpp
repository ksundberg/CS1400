#include "JohnathanPowell.hpp"
#include "Unit.hpp"
#include "Map.hpp"

namespace
{
//globals
lionheart::Placement ekingloc;
lionheart::Placement akingloc;
}

//Just to make sure I don't call number outside of map
int testValid(int in)
{
  if (in < 0)
  {
    return 0;
  }
  else if (in > 29)
  {
    return 29;
  }
  else
  {
    return in;
  }
}

// finds location of both kings
void find_kings(struct lionheart::SituationReport report)
{
  for (auto i = 0; i < 30; ++i)
  {
    for (auto j = 0; j < 30; ++j)
    {
      if (report.things[i][j].unit == lionheart::UnitType::CROWN)
      {
        if (report.things[i][j].type == lionheart::SituationReport::ENEMY)
        {
          ekingloc.row = i;
          ekingloc.col = j;
        }
        if (report.things[i][j].type == lionheart::SituationReport::ALLY)
        {
          akingloc.row = i;
          akingloc.col = j;
        }
      }
    }
  }
}

//returns number of enemies in an area
int enArea(int x1, int y1, int x2, int y2, lionheart::SituationReport report)
{
  int count = 0;
  for(int i = x1; i < x2; i++)
  {
    for(int j = y1; j < y2; j++)
    {
      if (report.things[testValid(i)][testValid(j)].type ==
        lionheart::SituationReport::ENEMY)
        {
          count++;
        }
    }
  }
  return count;
}

//returns direction king should run to avoid enemy
// 0 for north, 1 for east, 2 for south, 3 for west
int kingFlee(lionheart::SituationReport report)
{
    //TODO flee archers and infantry
    find_kings(report);

    int kingCol = akingloc.col;
    int kingRow = akingloc.row;

    int eNor = enArea(kingCol-2, kingRow-1, kingCol+2, kingRow-5, report);
    int eEst = enArea(kingCol+1, kingRow-2, kingCol+5, kingRow+2, report);
    int eSou = enArea(kingCol-2, kingRow+1, kingCol+2, kingRow+5, report);
    int eWst = enArea(kingCol-1, kingRow-2, kingCol-5, kingRow+2, report);

    if(eNor >= eEst && eNor >= eSou && eNor >= eWst)
    {
      return 0;
    }
    else if(eEst >= eSou && eEst >= eWst)
    {
      return 1;
    }
    else if(eSou >= eWst)
    {
      return 2;
    }
    else
    {
      return 3;
    }
}

int id;
bool westSide;

lionheart::Placement lionheart::JohnathanPowell::placeUnit(UnitType,
                                              StartBox const &box,
                                              SituationReport report)
{
  /*Fill this out with instructions on how to place your initial units.  Without
   * changes your units will fill the starting box from top left to bottom right
   * in the order constructed.*/
   ++id;
   westSide = (box.minCol < static_cast<int>(report.things[0].size() / 2));
   if(westSide)
   {
     switch(id)
     {
     // CROWN
     case 1: return {15, 2};
     // KNIGHTS
     case 2: return {10,4};
     case 3: return {11,4};
     case 4: return {12,4};
     case 5: return {17,4};
     case 6: return {18,4};
     case 7: return {19,4};
     // ARCHERS
     case 8: return {10,3};
     case 9: return {10,5};
     case 10:return {13,7};
     case 11:return {14,5};
     case 12:return {15,5};
     case 13:return {16,7};
     case 14: return {19,3};
     case 15: return {19,5};
     // INFANTRY
     case 16: return {14,6};
     case 17: return {14,7};
     case 18: return {15,6};
     case 19: return {15,7};
     case 20: return {13,4};
     case 21: return {14,4};
     case 22: return {15,4};
     case 23: return {16,4};

     case 24: return {14,2};
     case 25: return {15,3};
     case 26: return {14,3};
     case 27: return {13,3};
     case 28: return {16,3};
     case 29: return {13,5};
     case 30: id=0;return {16,5};
     }
   }
   else
   {
     switch (id)
     {
     // CROWN
     case 1: return {15, 27};
     // KNIGHTS
     case 2: return {10,25};
     case 3: return {11,25};
     case 4: return {12,25};
     case 5: return {17,25};
     case 6: return {18,25};
     case 7: return {19,25};
     // ARCHERS
     case 8: return {10,26};
     case 9: return {10,24};
     case 10:return {13,22};
     case 11:return {14,24};
     case 12:return {15,24};
     case 13:return {16,22};
     case 14: return {19,26};
     case 15: return {19,24};
     // INFANTRY
     case 16: return {14,23};
     case 17: return {14,22};
     case 18: return {15,23};
     case 19: return {15,22};
     case 20: return {13,25};
     case 21: return {14,25};
     case 22: return {15,25};
     case 23: return {16,25};

     case 24: return {14,27};
     case 25: return {15,26};
     case 26: return {14,26};
     case 27: return {13,26};
     case 28: return {16,26};
     case 29: return {13,24};
     case 30:id=0; return {16,24};
     }
   }
   return {0,0};
}

int hostile = -1;
int hostCap = 1;

  lionheart::Action
lionheart::JohnathanPowell::recommendAction(Unit const& u, SituationReport report, Plan p)
{
  /*Fill this out with the behavior you want for your units.  Without changes
   * your units will just wait to be defeated.  Feel free to look at the other provided players for ideas on how to get certain behavior*/

   //hostility slowdown counter
   hostile++;
   if(hostile == hostCap)
   {
     hostile = 0;
   }

  //crown actions
  if(u.getType() == CROWN)
  {
    //TODO crown actions
    int danger = kingFlee(report);

    if(danger == 0)
    {
      return p.moveToLocation(akingloc.col, testValid(akingloc.row+4));
    }
    if(danger == 1)
    {
      return p.moveToLocation(testValid(akingloc.col-4), akingloc.row);
    }
    if(danger == 2)
    {
      return p.moveToLocation(akingloc.col, testValid(akingloc.row-4));
    }
    if(danger == 3)
    {
      return p.moveToLocation(testValid(akingloc.col+2), akingloc.row);
    }

    return Action();
  }

  //knight actions
  if(u.getType() == KNIGHT)
  {
    //TODO knight actions
    if(p.hasAttack() || hostile == 0)
    {
      return p.attackEnemy();
    }
  }

  //infantry actions
  if(u.getType() == INFANTRY)
  {
    //TODO infantry actions
    if(p.hasAttack() || hostile == 0)
    {
      return p.attackEnemy();
    }
  }

  //archer actions
  if(u.getType() == ARCHER)
  {
    //TODO archer actions
    if(p.hasAttack() || hostile == 0)
    {
      return p.attackEnemy();
    }
  }
  return Action();
}

lionheart::Blazon lionheart::JohnathanPowell::getBlazon()
{
  /*Return your blazon here.  In case of conflicts preference will be given to
   * the students that have registered their blazons in class.*/
  return { Color::AZURE, Color::ARGENT, Style::QUARTERLY, "Johnathan Powell" };
}
