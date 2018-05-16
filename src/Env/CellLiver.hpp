#ifndef CELLLIVER_HPP
#define CELLLIVER_HPP
#include "CellOrgan.hpp"
#include "Substance.hpp"
#include <SFML/Graphics.hpp>
#include <Random/Random.hpp>
#include <Config.hpp>

class CellLiver : public CellOrgan
{
private:
	double atp_; //niveau d'énergie
	bool dead_;
public:
    CellLiver(CellHandler* cellHandler);
    void update(sf::Time dt);
    bool cellLiverIsDead();
};

#endif