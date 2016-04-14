#ifndef LIONHEART_PLAN_HPP
#define LIONHEART_PLAN_HPP

#include "Map.hpp"
#include "Action.hpp"
#include "Paths.hpp"

namespace lionheart
{

    class Plan
  {
  public:
    Plan(Unit const& self,
         std::vector<std::shared_ptr<lionheart::Unit>> const& allies,
         std::vector<std::shared_ptr<lionheart::Unit>> const& enemies,
         std::shared_ptr<const Paths> paths);
    Action attackEnemy() const;
    Action moveToEnemy() const;
    Action moveToEnemyCrown() const;
    Action moveToAllyCrown() const;
    Action moveToLocation(int row,int col) const;
    int movesTo(int row,int col) const;
    int movesToEnemy() const;
    int movesToEnemyCrown() const;
    int movesToAllyCrown() const;
    bool hasAttack() const {return inRange;}
  private:
    std::shared_ptr<const Paths> paths;
    PathVertex self;
    PathVertex enemy;
    PathVertex enemyCrown;
    PathVertex allyCrown;
    bool inRange;
  };
}
#endif
