#ifndef MAHJONGTILE_H
#define MAHJONGTILE_H

#include <string>
#include <stdexcept>
#include <iostream>
#include <variant>

/**
 * @brief An enum class to denote the tile category.
 */
enum class TileType {
    Dots,
    Bamboo,
    Characters,
    Wind,
    Dragon,
    Flower,
    Season
};

/**
 * @brief An enum class to represent the four winds.
 */
enum class WindType {
    East,
    South,
    West,
    North
};

/**
 * @brief An enum class to represent the three dragon tiles.
 */
enum class DragonType {
    Red,
    Green,
    White
};

/**
 * @brief An enum class to represent the four flower tiles.
 */
enum class FlowerType {
    Plum,
    Orchid,
    Chrysanthemum,
    Bamboo
};

/**
 * @brief An enum class to represent the four season tiles.
 */
enum class SeasonType {
    Spring,
    Summer,
    Autumn,
    Winter
};

/**
 * @brief Primary template for a MahjongTile. 
 *        We will fully specialize it for each TileType.
 */
template <TileType T>
class MahjongTile {
    // Intentionally empty. All behavior comes from partial specializations.
};

/**
 * @brief Specialization for tiles with numbered suits: Dots.
 */
template <>
class MahjongTile<TileType::Dots> {
public:
    /**
     * @brief Construct a Dots tile with a specified rank (1–9).
     * @param rank The rank of the tile (1–9).
     * @throws std::out_of_range if rank is out of the valid range.
     */
    explicit MahjongTile(int rank) : rank_(rank) {
        if (rank < 1 || rank > 9) {
            throw std::out_of_range("Dots rank must be between 1 and 9");
        }
    }

    /**
     * @brief Returns the rank of the tile (1–9).
     */
    int getRank() const { return rank_; }

    /**
     * @brief Returns a string representation of the tile (e.g. "Dots 5").
     */
    std::string toString() const {
        return "Dots " + std::to_string(rank_);
    }

private:
    int rank_;
};

/**
 * @brief Specialization for tiles with numbered suits: Bamboo.
 */
template <>
class MahjongTile<TileType::Bamboo> {
public:
    explicit MahjongTile(int rank) : rank_(rank) {
        if (rank < 1 || rank > 9) {
            throw std::out_of_range("Bamboo rank must be between 1 and 9");
        }
    }

    int getRank() const { return rank_; }

    std::string toString() const {
        return "Bamboo " + std::to_string(rank_);
    }

private:
    int rank_;
};

/**
 * @brief Specialization for tiles with numbered suits: Characters.
 */
template <>
class MahjongTile<TileType::Characters> {
public:
    explicit MahjongTile(int rank) : rank_(rank) {
        if (rank < 1 || rank > 9) {
            throw std::out_of_range("Characters rank must be between 1 and 9");
        }
    }

    int getRank() const { return rank_; }

    std::string toString() const {
        return "Characters " + std::to_string(rank_);
    }

private:
    int rank_;
};

/**
 * @brief Specialization for Wind tiles.
 */
template <>
class MahjongTile<TileType::Wind> {
public:
    explicit MahjongTile(WindType wind) : wind_(wind) {}

    WindType getWind() const { return wind_; }

    std::string toString() const {
        switch (wind_) {
            case WindType::East:  return "East Wind";
            case WindType::South: return "South Wind";
            case WindType::West:  return "West Wind";
            case WindType::North: return "North Wind";
        }
        return "Unknown Wind";  // should never happen
    }

private:
    WindType wind_;
};

/**
 * @brief Specialization for Dragon tiles.
 */
template <>
class MahjongTile<TileType::Dragon> {
public:
    explicit MahjongTile(DragonType dragon) : dragon_(dragon) {}

    DragonType getDragon() const { return dragon_; }

    std::string toString() const {
        switch (dragon_) {
            case DragonType::Red:   return "Red Dragon";
            case DragonType::Green: return "Green Dragon";
            case DragonType::White: return "White Dragon";
        }
        return "Unknown Dragon";  // should never happen
    }

private:
    DragonType dragon_;
};

/**
 * @brief Specialization for Flower tiles.
 */
template <>
class MahjongTile<TileType::Flower> {
public:
    explicit MahjongTile(FlowerType flower) : flower_(flower) {}

    FlowerType getFlower() const { return flower_; }

    std::string toString() const {
        switch (flower_) {
            case FlowerType::Plum:          return "Plum Flower";
            case FlowerType::Orchid:        return "Orchid Flower";
            case FlowerType::Chrysanthemum: return "Chrysanthemum Flower";
            case FlowerType::Bamboo:        return "Bamboo Flower";
        }
        return "Unknown Flower";  // should never happen
    }

private:
    FlowerType flower_;
};

/**
 * @brief Specialization for Season tiles.
 */
template <>
class MahjongTile<TileType::Season> {
public:
    explicit MahjongTile(SeasonType season) : season_(season) {}

    SeasonType getSeason() const { return season_; }

    std::string toString() const {
        switch (season_) {
            case SeasonType::Spring: return "Spring Season";
            case SeasonType::Summer: return "Summer Season";
            case SeasonType::Autumn: return "Autumn Season";
            case SeasonType::Winter: return "Winter Season";
        }
        return "Unknown Season";  // should never happen
    }

private:
    SeasonType season_;
};

/**
* @brief Tile variant type for a Mahjong tile.
*/
class MahjongTileSet {
    public:
        using TileVariant = std::variant<
            MahjongTile<TileType::Dots>,
            MahjongTile<TileType::Bamboo>,
            MahjongTile<TileType::Characters>,
            MahjongTile<TileType::Wind>,
            MahjongTile<TileType::Dragon>,
            MahjongTile<TileType::Flower>,
            MahjongTile<TileType::Season>
        >;
};

#endif // MAHJONGTILE_H
