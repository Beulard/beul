#ifndef GRID_HPP
#define GRID_HPP
#include "Tile.hpp"
#include <vector>


class Grid{
    public:
        Grid(const sf::RenderWindow& W);
        ~Grid();

        void Draw(sf::RenderWindow& W);
        const unsigned int GetNbrColumns()    const;
        const unsigned int GetNbrBoxesPerColumn() const;

    private:
        std::vector<sf::Shape> horizontalLines;
        std::vector<sf::Shape> verticalLines;
        unsigned int nbrColumns;
        unsigned int nbrBoxesPerColumn;
};

#endif // GRID_HPP
