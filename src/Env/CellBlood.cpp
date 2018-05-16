#include "CellBlood.hpp"
#include <Application.hpp>

CellBlood::CellBlood(CellHandler* cellHandler, TypeBloodCell typeBloodCell)
    : CellOrgan(cellHandler)
    , typeBloodCell_(typeBloodCell)
{}

void CellBlood::update(sf::Time dt)
{
	
}