#ifndef CELLBLOOD_HPP
#define CELLBLOOD_HPP
#include "CellOrgan.hpp"
#include "Substance.hpp"
#include <Types.hpp>

class CellBlood : public CellOrgan
{

private:
    TypeBloodCell typeBloodCell_; //le type de cellule sanguine -> capillaire (véhicule substances) -> artère
public :
    CellBlood(CellHandler* cellHandler, TypeBloodCell typeBloodCell = ARTERY);
    void update(sf::Time dt);

};

#endif