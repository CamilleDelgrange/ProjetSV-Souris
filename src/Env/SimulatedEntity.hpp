#ifndef SIMULATEDENTITY_HPP
#define SIMULATEDENTITY_HPP
#include <Utility/Vec2d.hpp>
#include "Collider.hpp"
#include <SFML/Graphics.hpp>
#include <Utility/Constants.hpp>
#include <Utility/Utility.hpp>
#include "Box.hpp"
using namespace std;

class Mouse;
class Cheese;

class SimulatedEntity : public Collider
{
public:
    /*constructeur et déstructeur:*/
    SimulatedEntity (double energie, Vec2d position, sf::Texture texture);

    virtual ~SimulatedEntity();

    /* cette méthode fait "vieillir" toute Simulated d'entity, par rapport au temps:*/
    virtual void update(sf::Time dt);

    /*des getters pour la position ainsi que le rayon de certaines entités:*/
    Vec2d getCenter() const;

    virtual double getRadius() const = 0;

    /*méthode de dessin de l'entité:*/
    virtual void drawOn(sf::RenderTarget& target);

    /*méthode qui vérifie si une entité est morte ou pas:*/
    virtual bool isdead()const;

    /*cette méthode vérifie si une entité peut être confinée dans une boîte, on la redéfini selon les entités*/
    virtual bool canBeConfinedIn(Box* boite) const = 0;

    /*méthode qui ajuste la position de l'entité (ex: si on la place proche du mur):*/
    void adjustPosition();

    /*ces méthodes vérifient si une entité est mangeable par une autre entité*/
    virtual bool eatable(SimulatedEntity const* entity) const = 0;

    virtual bool eatableBy(Cheese const* cheese) const = 0;

    virtual bool eatableBy(Mouse const* mouse) const = 0;

    /*cette méthode retourne le vecteur de direction normalisé de l'animal:*/
    Vec2d getHeading();

    /*méthode qui attribue une boîte à notre attribut box_*/
    void setBox(Box* boite);

    /*cette méthode change l'attribut énergie selon notre entité (p.ex: décrémenter l'énergie de notre fromage)*/
    virtual Quantity provideEnergy(Quantity qte)=0;



protected:

    double energie_;

    Vec2d position_;

    Angle anglerad_;

    sf::Time age_;

    Box* box_;

    sf::Texture texture_;



};
#endif
