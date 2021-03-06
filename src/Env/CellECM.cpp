#include "CellECM.hpp"
#include <Application.hpp>

CellECM::CellECM(CellHandler* cellHandler)
    : CellOrgan(cellHandler)
{}

void CellECM::addSubstance(Substance& substance)
{
    (*substance_) += (substance);
}

void CellECM::update(sf::Time dt)
{
	
}