#ifndef DEAL_H
#define DEAL_H

#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "tiletype.h"

using namespace std;

string tileToString(const MahjongTileSet::TileVariant& tileObj);
void printPlayerHand(const vector<MahjongTileSet::TileVariant>& hand, int seat);
vector<MahjongTileSet::TileVariant> createDeck();
void shuffleDeal();

#endif // DEAL_H