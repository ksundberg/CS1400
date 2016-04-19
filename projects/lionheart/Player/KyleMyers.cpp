#include "KyleMyers.hpp"

lionheart::Placement lionheart::KyleMyers::placeUnit(UnitType thisUnit,
                                                     StartBox const &box,
                                                     SituationReport report)
{
  auto colRange = box.maxCol - box.minCol;
  auto rowRange = box.maxRow - box.minRow;
  switch (thisUnit)
  {
  case lionheart::CROWN:
    // reassign values at game start
    for (int i = 0; i < 4; i++)
    {
      placementCounts[i] = 0;
    }
    assignments.clear();

    placementCounts[0] = 1;
    westSideStart =
        (box.minCol < static_cast<int>(report.things[0].size() / 2));
    kingloc.row = rowRange / 2 + box.minRow;
    kingloc.col = colRange / 2 + box.minCol;
    topGaurd.row = box.minRow;
    topGaurd.col = kingloc.col;
    botGaurd.row = box.maxRow;
    botGaurd.col = kingloc.col;
    frontGaurd.row = kingloc.row;
    if (westSideStart)
      frontGaurd.col = box.maxCol;
    else
      frontGaurd.col = box.minCol;
    return { kingloc.row, kingloc.col };
    break;
  case lionheart::KNIGHT:
    // assign the kings rear gaurd
    if (placementCounts[1] < 2)
    {
      placementCounts[1]++;
      return placeRearGaurd(thisUnit, box, report);
    }
    // assign front gaurd
    else if (placementCounts[1] < 4)
    {
      placementCounts[1]++;
      return placeFrontGaurd(thisUnit, box, report);
    }
    // assign top gaurd
    else if (placementCounts[1] < 5)
    {
      placementCounts[1]++;
      return placeTopGaurd(thisUnit, box, report);
    }
    // assign bottom gaurd
    else
    {
      placementCounts[1]++;
      return placeBottomGaurd(thisUnit, box, report);
    }
    return { 0, 0 };
    break;
  case lionheart::ARCHER:
    // assign the kings rear gaurd
    if (placementCounts[2] < 2)
    {
      placementCounts[2]++;
      return placeRearGaurd(thisUnit, box, report);
    }
    // assign front gaurd
    else if (placementCounts[2] < 4)
    {
      placementCounts[2]++;
      return placeFrontGaurd(thisUnit, box, report);
    }
    // assign top gaurd
    else if (placementCounts[2] < 6)
    {
      placementCounts[2]++;
      return placeTopGaurd(thisUnit, box, report);
    }
    // assign bottom gaurd
    else
    {
      placementCounts[2]++;
      return placeBottomGaurd(thisUnit, box, report);
    }
    return { 0, 0 };
    break;
  case lionheart::INFANTRY:
    // assign the kings rear gaurd
    if (placementCounts[3] < 3)
    {
      placementCounts[3]++;
      return placeRearGaurd(thisUnit, box, report);
    }
    // assign front gaurd
    else if (placementCounts[3] < 9)
    {
      placementCounts[3]++;
      return placeFrontGaurd(thisUnit, box, report);
    }
    // assign top gaurd
    else if (placementCounts[3] < 12)
    {
      placementCounts[3]++;
      return placeTopGaurd(thisUnit, box, report);
    }
    // assign bottom gaurd
    else
    {
      placementCounts[3]++;
      return placeBottomGaurd(thisUnit, box, report);
    }
    return { 0, 0 };
    break;
  case lionheart::NONE:
    return { 0, 0 };
    break;
  default:
    return { 0, 0 };
    break;
  }
}

lionheart::Placement lionheart::KyleMyers::placeRearGaurd(
    UnitType type, StartBox const &, SituationReport report)
{
  if (westSideStart)
  {
    switch (type)
    {
    case lionheart::KNIGHT:
      if (report.things[kingloc.row - 1][kingloc.col].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { kingloc.row - 1, kingloc.col };
      }
      if (report.things[kingloc.row + 1][kingloc.col].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { kingloc.row + 1, kingloc.col };
      }
      break;
    case lionheart::ARCHER:
      if (report.things[kingloc.row - 1][kingloc.col - 1].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { kingloc.row - 1, kingloc.col - 1 };
      }
      if (report.things[kingloc.row + 1][kingloc.col - 1].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { kingloc.row + 1, kingloc.col - 1 };
      }
      break;
    case lionheart::INFANTRY:
      if (report.things[kingloc.row - 1][kingloc.col + 1].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { kingloc.row - 1, kingloc.col + 1 };
      }
      if (report.things[kingloc.row + 1][kingloc.col + 1].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { kingloc.row + 1, kingloc.col + 1 };
      }
      if (report.things[kingloc.row][kingloc.col + 1].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { kingloc.row, kingloc.col + 1 };
      }
      break;
    case lionheart::NONE:
      return { 0, 0 };
      break;
    default:
      return { 0, 0 };
      break;
    }
  }
  else
  {
    switch (type)
    {
    case lionheart::KNIGHT:
      if (report.things[kingloc.row - 1][kingloc.col].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { kingloc.row - 1, kingloc.col };
      }
      if (report.things[kingloc.row + 1][kingloc.col].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { kingloc.row + 1, kingloc.col };
      }
      break;
    case lionheart::ARCHER:
      if (report.things[kingloc.row - 1][kingloc.col + 1].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { kingloc.row - 1, kingloc.col + 1 };
      }
      if (report.things[kingloc.row + 1][kingloc.col + 1].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { kingloc.row + 1, kingloc.col + 1 };
      }
      if (report.things[kingloc.row][kingloc.col + 1].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { kingloc.row, kingloc.col + 1 };
      }
      break;
    case lionheart::INFANTRY:
      if (report.things[kingloc.row - 1][kingloc.col - 1].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { kingloc.row - 1, kingloc.col - 1 };
      }
      if (report.things[kingloc.row + 1][kingloc.col - 1].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { kingloc.row + 1, kingloc.col - 1 };
      }
      if (report.things[kingloc.row][kingloc.col - 1].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { kingloc.row, kingloc.col - 1 };
      }
      break;
    case lionheart::NONE:
      return { 0, 0 };
      break;
    default:
      return { 0, 0 };
      break;
    }
  }
  return { 0, 0 };
}
lionheart::Placement lionheart::KyleMyers::placeFrontGaurd(
    UnitType type, StartBox const &, SituationReport report)
{
  if (westSideStart)
  {
    switch (type)
    {
    case lionheart::KNIGHT:
      if (report.things[frontGaurd.row - 1][frontGaurd.col].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { frontGaurd.row - 1, frontGaurd.col };
      }
      if (report.things[frontGaurd.row + 2][frontGaurd.col].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { frontGaurd.row + 2, frontGaurd.col };
      }
      return { 0, 0 };
      break;
    case lionheart::ARCHER:
      if (report.things[frontGaurd.row][frontGaurd.col - 1].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { frontGaurd.row, frontGaurd.col - 1 };
      }
      if (report.things[frontGaurd.row + 1][frontGaurd.col - 1].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { frontGaurd.row + 1, frontGaurd.col - 1 };
      }
      return { 0, 0 };
      break;
    case lionheart::INFANTRY:
      if (report.things[frontGaurd.row][frontGaurd.col].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { frontGaurd.row, frontGaurd.col };
      }
      if (report.things[frontGaurd.row + 1][frontGaurd.col].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { frontGaurd.row + 1, frontGaurd.col };
      }
      if (report.things[frontGaurd.row - 1][frontGaurd.col - 1].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { frontGaurd.row - 1, frontGaurd.col - 1 };
      }
      if (report.things[frontGaurd.row + 2][frontGaurd.col - 1].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { frontGaurd.row + 2, frontGaurd.col - 1 };
      }
      if (report.things[frontGaurd.row + 3][frontGaurd.col].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { frontGaurd.row + 3, frontGaurd.col };
      }
      if (report.things[frontGaurd.row - 2][frontGaurd.col].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { frontGaurd.row - 2, frontGaurd.col };
      }
      return { 0, 0 };
      break;
    case lionheart::NONE:
      return { 0, 0 };
      break;
    default:
      return { 0, 0 };
      break;
    }
  }
  else
  {
    switch (type)
    {
    case lionheart::KNIGHT:
      if (report.things[frontGaurd.row - 1][frontGaurd.col + 1].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { frontGaurd.row - 1, frontGaurd.col + 1 };
      }
      if (report.things[frontGaurd.row + 2][frontGaurd.col + 1].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { frontGaurd.row + 2, frontGaurd.col + 1 };
      }
      return { 0, 0 };
      break;
    case lionheart::ARCHER:
      if (report.things[frontGaurd.row][frontGaurd.col + 1].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { frontGaurd.row, frontGaurd.col + 1 };
      }
      if (report.things[frontGaurd.row + 1][frontGaurd.col + 1].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { frontGaurd.row + 1, frontGaurd.col + 1 };
      }
      return { 0, 0 };
      break;
    case lionheart::INFANTRY:
      if (report.things[frontGaurd.row][frontGaurd.col].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { frontGaurd.row, frontGaurd.col };
      }
      if (report.things[frontGaurd.row + 1][frontGaurd.col].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { frontGaurd.row + 1, frontGaurd.col };
      }
      if (report.things[frontGaurd.row - 1][frontGaurd.col + 1].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { frontGaurd.row - 1, frontGaurd.col - 1 };
      }
      if (report.things[frontGaurd.row + 2][frontGaurd.col + 1].type ==
          lionheart::SituationReport::ThingType::SPACE)
      {
        return { frontGaurd.row + 2, frontGaurd.col - 1 };
      }
      return { 0, 0 };
      break;
    case lionheart::NONE:
      return { 0, 0 };
      break;
    default:
      return { 0, 0 };
      break;
    }
  }
  return { 0, 0 };
}
lionheart::Placement lionheart::KyleMyers::placeTopGaurd(UnitType type,
                                                         StartBox const &,
                                                         SituationReport report)
{
  switch (type)
  {
  case lionheart::KNIGHT:
    return { topGaurd.row, topGaurd.col };
    break;
  case lionheart::ARCHER:
    if (report.things[topGaurd.row][topGaurd.col - 1].type ==
        lionheart::SituationReport::ThingType::SPACE)
    {
      return { topGaurd.row, topGaurd.col - 1 };
    }
    if (report.things[topGaurd.row][topGaurd.col + 1].type ==
        lionheart::SituationReport::ThingType::SPACE)
    {
      return { topGaurd.row, topGaurd.col + 1 };
    }
    return { 0, 0 };
    break;
  case lionheart::INFANTRY:
    if (report.things[topGaurd.row + 1][topGaurd.col + 1].type ==
        lionheart::SituationReport::ThingType::SPACE)
    {
      return { topGaurd.row + 1, topGaurd.col + 1 };
    }
    if (report.things[topGaurd.row + 1][topGaurd.col - 1].type ==
        lionheart::SituationReport::ThingType::SPACE)
    {
      return { topGaurd.row + 1, topGaurd.col - 1 };
    }
    if (report.things[topGaurd.row + 1][topGaurd.col].type ==
        lionheart::SituationReport::ThingType::SPACE)
    {
      return { topGaurd.row + 1, topGaurd.col };
    }
    return { 0, 0 };
    break;
  case lionheart::NONE:
    return { 0, 0 };
    break;
  default:
    return { 0, 0 };
    break;
  }
  return { 0, 0 };
}
lionheart::Placement lionheart::KyleMyers::placeBottomGaurd(
    UnitType type, StartBox const &, SituationReport report)
{
  switch (type)
  {
  case lionheart::KNIGHT:
    return { botGaurd.row, botGaurd.col };
    break;
  case lionheart::ARCHER:
    if (report.things[botGaurd.row][botGaurd.col + 1].type ==
        lionheart::SituationReport::ThingType::SPACE)
    {
      return { botGaurd.row, botGaurd.col + 1 };
    }
    if (report.things[botGaurd.row][botGaurd.col - 1].type ==
        lionheart::SituationReport::ThingType::SPACE)
    {
      return { botGaurd.row, botGaurd.col - 1 };
    }
    return { 0, 0 };
    break;
  case lionheart::INFANTRY:
    if (report.things[botGaurd.row - 1][botGaurd.col - 1].type ==
        lionheart::SituationReport::ThingType::SPACE)
    {
      return { botGaurd.row - 1, botGaurd.col - 1 };
    }
    if (report.things[botGaurd.row - 1][botGaurd.col + 1].type ==
        lionheart::SituationReport::ThingType::SPACE)
    {
      return { botGaurd.row - 1, botGaurd.col + 1 };
    }
    if (report.things[botGaurd.row - 1][botGaurd.col].type ==
        lionheart::SituationReport::ThingType::SPACE)
    {
      return { botGaurd.row - 1, botGaurd.col };
    }
    return { 0, 0 };
    break;
  case lionheart::NONE:
    return { 0, 0 };
    break;
  default:
    return { 0, 0 };
    break;
  }
  return { 0, 0 };
}

bool validateCoord(KMYERS::coordinate loc, lionheart::SituationReport report)
{
  if (loc.col < 0 || loc.row < 0 || (unsigned)loc.row >= report.things.size() ||
      (unsigned)loc.col >= report.things[0].size())
  {
    return false;
  }
  else
  {
    return true;
  }
}

void lionheart::KyleMyers::assignSquad(lionheart::Unit const &unit)
{
  if (unit.getLocation().col - frontGaurd.col <= 1 &&
      unit.getLocation().col - frontGaurd.col >= -1)
    assignments.emplace(unit.getId(), KMYERS::Squad::FGAURD);
  if (unit.getLocation().col - kingloc.col <= 1 &&
      unit.getLocation().col - kingloc.col >= -1 &&
      unit.getLocation().row - kingloc.row <= 1 &&
      unit.getLocation().row - kingloc.row >= -1)
    assignments.emplace(unit.getId(), KMYERS::Squad::RGAURD);
  if (unit.getLocation().col - botGaurd.col <= 1 &&
      unit.getLocation().col - botGaurd.col >= -1 &&
      unit.getLocation().row - botGaurd.row <= 1 &&
      unit.getLocation().row - botGaurd.row >= -1)
    assignments.emplace(unit.getId(), KMYERS::Squad::BGAURD);
  if (unit.getLocation().col - topGaurd.col <= 1 &&
      unit.getLocation().col - topGaurd.col >= -1 &&
      unit.getLocation().row - topGaurd.row <= 1 &&
      unit.getLocation().row - topGaurd.row >= -1)
    assignments.emplace(unit.getId(), KMYERS::Squad::TGAURD);
}

KMYERS::Squad lionheart::KyleMyers::getSqaud(lionheart::Unit const &unit)
{
  auto search = assignments.find(unit.getId());
  if (search != assignments.end())
  {
    return search->second;
  }
  else
  {
    return KMYERS::Squad::UNASSIGNED;
  }
}

lionheart::Action lionheart::KyleMyers::recommendAction(Unit const &thisUnit,
                                                        SituationReport report,
                                                        Plan plan)
{
  if (report.turns == 1)
  {
    // it is the begining assign squads
    assignSquad(thisUnit);
  }

  /* They all have 1 HP!!!!?????!!!!!! What!!!???!!!
  if (thisUnit.getHp() == 1){
    auto reassign = assignments.find(thisUnit.getId());
    reassign->second = KMYERS::Squad::RGAURD;
    return plan.moveToAllyCrown();
  }
  */

  if (thisUnit.getType() == lionheart::UnitType::CROWN)
  {
    kingloc.row = thisUnit.getLocation().row;
    kingloc.col = thisUnit.getLocation().col;
  }

  switch (getSqaud(thisUnit))
  {
  case KMYERS::Squad::BGAURD:
    return recommendActionBGAURD(thisUnit, report, plan);
    break;
  case KMYERS::Squad::RGAURD:
    return recommendActionRGAURD(thisUnit, report, plan);
    break;
  case KMYERS::Squad::TGAURD:
    return recommendActionTGAURD(thisUnit, report, plan);
    break;
  case KMYERS::Squad::FGAURD:
    return recommendActionFGAURD(thisUnit, report, plan);
    break;
  case KMYERS::Squad::UNASSIGNED:
    return plan.moveToAllyCrown();
    break;
  }

  return Action();
}

lionheart::Action lionheart::KyleMyers::recommendActionBGAURD(
    Unit const &, SituationReport report, Plan plan)
{
  if (report.turns < 2)
  {
    botGaurd.row += 5;
    if (westSideStart)
      botGaurd.col += KMYERS::FIRST_MOVE_COL_SHIFT;
    else
      botGaurd.col -= KMYERS::FIRST_MOVE_COL_SHIFT;
  }
  if (report.turns > KMYERS::FIRST_MOVE_COL_SHIFT)
  {
    if (plan.hasAttack())
      return plan.attackEnemy();
    return plan.moveToEnemyCrown();
  }
  return plan.moveToLocation(botGaurd.row, botGaurd.col);
}
lionheart::Action lionheart::KyleMyers::recommendActionTGAURD(
    Unit const &, SituationReport report, Plan plan)
{
  if (report.turns < 2)
  {
    topGaurd.row -= 5;
    if (westSideStart)
      topGaurd.col += KMYERS::FIRST_MOVE_COL_SHIFT;
    else
      topGaurd.col -= KMYERS::FIRST_MOVE_COL_SHIFT;
  }
  if (report.turns > KMYERS::FIRST_MOVE_COL_SHIFT)
  {
    if (plan.hasAttack())
      return plan.attackEnemy();
    return plan.moveToEnemyCrown();
  }
  return plan.moveToLocation(topGaurd.row, topGaurd.col);
}
lionheart::Action lionheart::KyleMyers::recommendActionFGAURD(
    Unit const &, SituationReport report, Plan plan)
{
  if (report.turns < 2)
  {
    if (westSideStart)
      frontGaurd.col += KMYERS::FIRST_MOVE_COL_SHIFT / 2;
    else
      frontGaurd.col -= KMYERS::FIRST_MOVE_COL_SHIFT / 2;
  }
  if (report.turns > KMYERS::FIRST_MOVE_COL_SHIFT)
  {
    if (plan.hasAttack())
      return plan.attackEnemy();
    return plan.moveToEnemyCrown();
  }
  return plan.moveToLocation(frontGaurd.row, frontGaurd.col);
}
lionheart::Action lionheart::KyleMyers::recommendActionRGAURD(
    Unit const &thisUnit, SituationReport, Plan plan)
{
  if (plan.hasAttack())
    return plan.attackEnemy();
  if (thisUnit.getType() != lionheart::ARCHER)
  {
    if (plan.movesToEnemy() > 2)
    {
      return plan.moveToAllyCrown();
    }
    else
    {
      return plan.moveToEnemy();
    }
  }
  return plan.moveToAllyCrown();
}

lionheart::Blazon lionheart::KyleMyers::getBlazon()
{
  return { Color::AZURE,   Color::GULES,
           Style::SALTIRE, "Kyle Myers's Divide and Destroy" };
}
