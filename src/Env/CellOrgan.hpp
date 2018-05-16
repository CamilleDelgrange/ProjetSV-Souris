#ifndef CELLORGAN_HPP
#define CELLORGAN_HPP
#include <SFML/Graphics.hpp>
#include <Types.hpp>
using namespace std;

class Substance;
class CellHandler;

class CellOrgan
{

protected:
    Substance* substance_;
    CellHandler* cellHandler_; /*un CellOrgan a connaissance du CellHandler en charge de sa gestion sur l'organe.
	C'est par ce biais qu'il va savoir quels sont les autres CellOrgan qui occupent la même
	position logique que lui et donc avec lesquels il pourra échanger des substances au cours du temps.*/
public:
    CellOrgan(CellHandler* cellHandler);
    virtual ~CellOrgan();
    void takeSubstance();
    void ecmUptakeOnGradient(double fraction, CellOrgan* cellOrgan, SubstanceId id);
    double getQuantity(SubstanceId id);
    virtual void update(sf::Time dt)=0;

};

#endif