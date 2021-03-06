#ifndef CELLECM_HPP
#define CELLECM_HPP
#include "CellOrgan.hpp"
#include "Substance.hpp"
#include <Types.hpp>

class CellECM : public CellOrgan
{
private:
public:
    CellECM(CellHandler* cellHandler_);
    void addSubstance(Substance& substance);
    void update(sf::Time dt);

};

#endif