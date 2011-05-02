#include "Grid.hpp"

Grid::Grid(const sf::RenderWindow& W){
    for(unsigned int i=0; i<W.GetHeight(); i+=32)
        horizontalLines.push_back(sf::Shape::Line(0, i, W.GetWidth(), i, 1.f, sf::Color::Black));
    for(unsigned int i=0; i<W.GetWidth(); i+=32)
        verticalLines.push_back(sf::Shape::Line(i, 0, i, W.GetHeight(), 1.f, sf::Color::Black));
    nbrColumns = 64;
    nbrBoxesPerColumn = W.GetHeight() / 32;
}

Grid::~Grid(){

}

void Grid::Draw(sf::RenderWindow& W){
    for(unsigned int i=0; i<verticalLines.size(); ++i)
        W.Draw(verticalLines[i]);
    for(unsigned int i=0; i<horizontalLines.size(); ++i)
        W.Draw(horizontalLines[i]);
}


const unsigned int Grid::GetNbrColumns()  const{
    return nbrColumns;
}

const unsigned int Grid::GetNbrBoxesPerColumn()   const{
    return nbrBoxesPerColumn;
}
