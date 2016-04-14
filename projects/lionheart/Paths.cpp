//
// Created by josep on 4/13/2016.
//

#include <algorithm>
#include <limits>
#include <fstream>
#include "Paths.hpp"

std::ostream& lionheart::serialize(std::ostream& os, const PathVertex& pathVertex){
  serialize(os, pathVertex.location);
  os << " ";
  serialize(os, pathVertex.facing);
  return os;
}
std::istream& lionheart::deserialize(std::istream& is, PathVertex& pathVertex){
  deserialize(is, pathVertex.location);
  deserialize(is, pathVertex.facing);
  return is;
}

lionheart::Paths::Paths(std::shared_ptr<const Map> const &map, int maxSpeed) : vertex(), nextAction(), pathLength() {

  auto pathDataFilename = map->getName() + "." + std::to_string(maxSpeed) + ".path";

  //Check for cached data and load
  std::ifstream pathDataFile(pathDataFilename);
  if (pathDataFile.is_open()) {
    //load the data
    std::cout << "Reading path data from " << pathDataFilename << std::endl;

    //vertex
    int numVertexes;
    pathDataFile >> numVertexes;
    for(int i = 0; i < numVertexes; i++){
      PathVertex pathVertex;
      deserialize(pathDataFile, pathVertex);
      int num;
      pathDataFile >> num;
      vertex[pathVertex] = num;
    }

    //nextAction
    int numActionLists;
    pathDataFile >> numActionLists;
    for(int i = 0; i < numActionLists; i++){
      nextAction.emplace_back();
      int length;
      pathDataFile >> length;
      for(int j = 0; j < length; j++){
        Action action;
        deserialize(pathDataFile, action);
        nextAction[i].push_back(action);
      }
    }

    //pathLength
    int numPathLengthLists;
    pathDataFile >> numPathLengthLists;
    for(int i = 0; i < numPathLengthLists; i++){
      pathLength.emplace_back();
      int length;
      pathDataFile >> length;
      for(int j = 0; j < length; j++){
        int dist;
        pathDataFile >> dist;
        pathLength[i].push_back(dist);
      }
    }

    pathDataFile.close();
  } else {
    calculate(map, maxSpeed);

    //Save cached data

    std::cout << "Writing path data to " << pathDataFilename << std::endl;
    std::ofstream outFile(pathDataFilename);

    //vertex
    outFile << vertex.size() << std::endl;
    for(auto entry : vertex){
      serialize(outFile, entry.first);
      outFile << " " << entry.second << std::endl;
    }

    std::cout << "vertex finished" << std::endl;

    //nextAction
    outFile << nextAction.size() << std::endl;
    for(auto list : nextAction){
      outFile << list.size() << " ";
      for(auto action : list){
        serialize(outFile, action) << " ";
      }
      outFile << std::endl;
    }

    std::cout << "nextAction finished" << std::endl;

    //pathLength
    outFile << pathLength.size() << std::endl;
    for(auto list : pathLength){
      outFile << list.size() << " ";
      for(auto length : list){
        outFile << length << " ";
      }
      outFile << std::endl;
    }

    std::cout << "pathLength finished" << std::endl;

    outFile.close();
  }
}

void lionheart::Paths::calculate(std::shared_ptr<const Map> const &map, int maxSpeed){
  //calculate the data
  std::vector<lionheart::Direction> const dirs{
      lionheart::Direction::NORTH, lionheart::Direction::EAST, lionheart::Direction::SOUTH, lionheart::Direction::WEST};

  //Create all vertexes
  auto vNum = 0;
  for (int r = 0; r < static_cast<int>(map->rows()); ++r)
    for (int c = 0; c < static_cast<int>(map->cols()); ++c) {
      if ((*map)[map->at(r, c)] == Tile::SPACE) {
        for (auto &&d:dirs) {
          vertex[{{r, c}, d}] = vNum;
          ++vNum;
        }
      }
    }
  //create adjacency maps
  for (int i = 0; i < vNum; ++i) {
    nextAction.emplace_back();
    pathLength.emplace_back();
    for (int j = 0; j < vNum; ++j) {
      nextAction[i].emplace_back();
      if (j == i) {
        pathLength[i].emplace_back(0);
      }
      else {
        pathLength[i].emplace_back(vNum * 2);
      }
    }
  }

  for (auto &&v:vertex) {
    //Add turn based adjacencies
    for (auto &&d:dirs) {
      auto vIdx = vertex[PathVertex(v.first.location, d)];
      if (vIdx != v.second) {
        nextAction[v.second][vIdx] = turn(d);
        pathLength[v.second][vIdx] = 1;
      }
    }
    //Add move based adjacencies
    for (auto moveDist = 1; moveDist <= maxSpeed; ++moveDist) {
      //verify move is valid
      PathVertex dest = v.first;
      switch (dest.facing) {
        case Direction::NORTH:
          dest.location.row -= moveDist;
          break;
        case Direction::SOUTH:
          dest.location.row += moveDist;
          break;
        case Direction::WEST:
          dest.location.col -= moveDist;
          break;
        case Direction::EAST:
          dest.location.col += moveDist;
          break;
      }
      auto destIter = vertex.find(dest);
      if (destIter == vertex.end()) {
        //there are no more legal moves in this direction
        break;
      }
      else {
        nextAction[v.second][destIter->second] = move(moveDist);
        pathLength[v.second][destIter->second] = 1;
      }
    }
  }
  //Apply Floyd-Warshall algorithm with paths
  for (int mid = 0; mid < vNum; ++mid) {
    for (int start = 0; start < vNum; ++start)
      for (int stop = 0; stop < vNum; ++stop) {
        auto direct = pathLength[start][stop];
        auto throughMid = pathLength[start][mid] + pathLength[mid][stop];
        if (throughMid < direct) {
          nextAction[start][stop] = nextAction[start][mid];
          pathLength[start][stop] = throughMid;
        }
      }
  }
}