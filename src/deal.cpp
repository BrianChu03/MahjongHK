#include "deal.h"

using namespace std;

// Helper function to convert a TileVariant to a string
string tileToString(const MahjongTileSet::TileVariant& tile)
{
    return visit([](auto&& tileObj) { 
        return tileObj.toString();
    }, tile);
}

// Helper function to print a player's hand
void printPlayerHand(const vector<MahjongTileSet::TileVariant>& hand, int seat)
{
    for (const auto& tile : hand) {
        cout << tileToString(tile) << endl;
    }
    cout << endl;
}

vector<MahjongTileSet::TileVariant> createDeck()
{
    vector<MahjongTileSet::TileVariant> deck;
    deck.reserve(144);
    // Dots, Bamboo, Characters (1-9, 4 copies of each rank)
    // 36 tiles per suit => 3 suits * 36 = 108 tiles
    for (int rank = 1; rank <= 9; ++rank) {
        for (int copy = 0; copy < 4; ++copy) {
            deck.emplace_back(MahjongTile<TileType::Dots>(rank));
        }
    }
    for (int rank = 1; rank <= 9; ++rank) {
        for (int copy = 0; copy < 4; ++copy) {
            deck.emplace_back(MahjongTile<TileType::Bamboo>(rank));
        }
    }
    for (int rank = 1; rank <= 9; ++rank) {
        for (int copy = 0; copy < 4; ++copy) {
            deck.emplace_back(MahjongTile<TileType::Characters>(rank));
        }
    }

    // Winds (4 copies of each wind)
    // 4 winds * 4 copies = 16 tiles
    for (int copy = 0; copy < 4; ++copy) {
        deck.emplace_back(MahjongTile<TileType::Wind>(WindType::East));
        deck.emplace_back(MahjongTile<TileType::Wind>(WindType::South));
        deck.emplace_back(MahjongTile<TileType::Wind>(WindType::West));
        deck.emplace_back(MahjongTile<TileType::Wind>(WindType::North));
    }

    // Dragons (4 copies of each dragon)
    // 3 dragons * 4 copies = 12 tiles
    for (int copy = 0; copy < 4; ++copy) {
        deck.emplace_back(MahjongTile<TileType::Dragon>(DragonType::Red));
        deck.emplace_back(MahjongTile<TileType::Dragon>(DragonType::Green));
        deck.emplace_back(MahjongTile<TileType::Dragon>(DragonType::White));
    }

    // Flowers (1-4, 1 copy of each flower)
    // 4 flowers * 1 copy = 4 tiles
    for (int copy = 1; copy <= 4; ++copy) {
        deck.emplace_back(MahjongTile<TileType::Flower>(FlowerType::Plum));
        deck.emplace_back(MahjongTile<TileType::Flower>(FlowerType::Orchid));
        deck.emplace_back(MahjongTile<TileType::Flower>(FlowerType::Chrysanthemum));
        deck.emplace_back(MahjongTile<TileType::Flower>(FlowerType::Bamboo));
    }

    // Seasons (1-4, 1 copy of each season)
    // 4 seasons * 1 copy = 4 tiles
    for (int copy = 1; copy <= 4; ++copy) {
        deck.emplace_back(MahjongTile<TileType::Season>(SeasonType::Spring));
        deck.emplace_back(MahjongTile<TileType::Season>(SeasonType::Summer));
        deck.emplace_back(MahjongTile<TileType::Season>(SeasonType::Autumn));
        deck.emplace_back(MahjongTile<TileType::Season>(SeasonType::Winter));
    }

    return deck;
}

void shuffleDeal() {
    vector<MahjongTileSet::TileVariant> deck = createDeck();

    // Random generator, Mersenne Twister engine
    random_device rd;
    mt19937 g(rd());

    // Shuffle the deck
    shuffle(deck.begin(), deck.end(), g);

    // Deck is ordered [0-143], 144 tiles in random order
    // We use a ring to simulate the walls circular layout

    // Roll the dice
    uniform_int_distribution<int> dist(1,6);
    int dice1 = dist(g);
    int dice2 = dist(g);
    int dice3 = dist(g);
    int diceSum = dice1 + dice2 + dice3;

    cout << "Dice rolls: " << dice1 << ", " << dice2 << ", " << dice3 << endl;
    cout << "Dice sum: " << diceSum << endl << endl;

    // Determine the prevailing wind (dealer, seats)
    // if seat 0 is East, seat 1 is South, etc.
    int dealer = (diceSum - 1) % 4;
    cout << "Dealer: " << dealer << endl;

    // Determine cut positions in ring
    int cutPos = (dealer * 36 + (diceSum * 2)) % 144;

    int currentIndex = cutPos;

    auto drawTile = [&]() -> MahjongTileSet::TileVariant {
        MahjongTileSet::TileVariant t = deck[currentIndex];
        currentIndex = (currentIndex + 1) % 144; // wrap around
        return t;
    };

    vector<MahjongTileSet::TileVariant> playerHands[4];
    for (int i = 0; i < 4; ++i) {
        playerHands[i].reserve(14);
    }

    // Deal order
    array<int, 4> dealOrder = {0, 3, 2, 1};
    // Grab 4 tiles for each player for 3 rounds
    for (int r = 0; r < 3; ++r) {
        for (int i = 0; i < 4; ++i) {
            int seat = dealOrder[(dealer + i) % 4];
            for (int j = 0; j < 4; ++j) {
                playerHands[seat].push_back(drawTile());
            }
        }
    }
    // Then grab 1 tile each
    // THIS IS SUPER INEFFICENT
    for (int s = 0; s < 4; ++s) {
        int seat = dealOrder[(dealer + s) % 4];
        if (s == 0) {
            for (int i = 0; i < 2; i++) {
                playerHands[seat].push_back(drawTile());
            }
        }
        else {
            playerHands[seat].push_back(drawTile());
        }
    }

    // Print out hands
    for (int s = 0; s < 4; ++s) {
        cout << "Player " << s << " hand:\n";
        printPlayerHand(playerHands[s], s);
    }
}