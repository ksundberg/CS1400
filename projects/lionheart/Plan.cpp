#include "Plan.hpp"
#include <limits>
#include <algorithm>

namespace
{
  lionheart::PathVertex getClosest(lionheart::PathVertex start,std::shared_ptr<lionheart::Unit> u,
    std::shared_ptr<const lionheart::Paths> paths)
  {
    lionheart::PathVertex result;
    auto dist = std::numeric_limits<int>::max();
    auto l1Dist = std::numeric_limits<int>::max();
    std::vector<lionheart::Direction> const dirs{lionheart::Direction::NORTH, lionheart::Direction::EAST, lionheart::Direction::SOUTH, lionheart::Direction::WEST};
    for(auto&& dir:dirs)
    {
      lionheart::PathVertex loc({u->getLocation().row,u->getLocation().col},dir);
      auto toLoc = paths->distance(start,loc);
      auto toLocL1 = abs(start.location.row - loc.location.row) + abs(start.location.col - loc.location.col);
      if(toLoc == dist)
      {
        //break ties with L1-norm
        if(toLocL1 < l1Dist)
        {
          dist = toLoc;
          l1Dist = toLocL1;
          result = loc;
        }
      }
      if(toLoc < dist)
      {
        dist = toLoc;
        l1Dist = toLocL1;
        result = loc;
      }
    }
    return result;
  }
}

lionheart::Plan::Plan(Unit const& s,
                      std::vector<std::shared_ptr<lionheart::Unit>> const& allies,
                      std::vector<std::shared_ptr<lionheart::Unit>> const& enemies,
                      std::shared_ptr<const Paths> p)
  : paths(p)
  , self({s.getLocation().row, s.getLocation().col}, s.getFacing())
  , enemy()
  , enemyCrown()
  , allyCrown()
  , inRange(false)
{
  //find closest enemy and if that enemy is in range
  auto dist = std::numeric_limits<int>::max();
  for (auto&& e : enemies)
  {
    auto loc = getClosest(self, e, paths);
    auto toLoc = paths->distance(self, loc);
    if (toLoc < dist) {
      dist = toLoc;
      enemy = loc;
      inRange = s.inRange(e->getLocation());
    }
  }
  auto findCrown = [](std::shared_ptr<lionheart::Unit> u)
  {
    return u->getType() == CROWN;
  };
  //find enemy crown
  auto eCrownIter = std::find_if(enemies.begin(),enemies.end(),findCrown);
  if(eCrownIter!=enemies.end())
  {
    enemyCrown = getClosest(self,*eCrownIter,paths);
  }
  //find ally crown
  auto aCrownIter = std::find_if(allies.begin(), allies.end(), findCrown);
  if(aCrownIter!=allies.end())
  {
    allyCrown = getClosest(self,*aCrownIter,paths);
  }
}

lionheart::Action lionheart::Plan::attackEnemy() const
{
  //return an attack if legal
  if(inRange)
  {
    return attack(enemy.location);
  }

  //otherwise approach enemy
  return moveToEnemy();
}

lionheart::Action lionheart::Plan::moveToEnemy() const
{
  if(paths)
  {
    return paths->next(self,enemy);
  }
  return Action();
}

lionheart::Action lionheart::Plan::moveToEnemyCrown() const
{
  if(paths)
  {
    return paths->next(self,enemyCrown);
  }
  return Action();
}

lionheart::Action lionheart::Plan::moveToAllyCrown() const
{
  if (paths) 
  {
    return paths->next(self, allyCrown);
  }
  return Action();
}

lionheart::Action lionheart::Plan::moveToLocation(int row,int col) const
{
  PathVertex dest({row,col},self.facing);
  if(paths)
  {
    return paths->next(self,dest);
  }
  return Action();
}

int lionheart::Plan::movesTo(int row,int col) const
{
  PathVertex dest({row,col},self.facing);
  if(paths)
  {
    return paths->distance(self,dest);
  }
  return std::numeric_limits<int>::max();
}

int lionheart::Plan::movesToEnemy() const
{
  if(paths)
  {
    return paths->distance(self,enemy);
  }
  return std::numeric_limits<int>::max();
}

int lionheart::Plan::movesToEnemyCrown() const
{
  if(paths)
  {
    return paths->distance(self,enemyCrown);
  }
  return std::numeric_limits<int>::max();
}

int lionheart::Plan::movesToAllyCrown() const
{
  if(paths)
  {
    return paths->distance(self,allyCrown);
  }
  return std::numeric_limits<int>::max();
}
