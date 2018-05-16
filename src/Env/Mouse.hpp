#ifndef MOUSE_HPP
#define MOUSE_HPP
#include "SimulatedEntity.hpp"
#include "Animal.hpp"
#include <SFML/Graphics.hpp>

class Mouse : public Animal
{

public:
    /*constructeur et déstructeur:*/
    Mouse(Vec2d position);

    virtual ~Mouse();

    /*getter qui retourne la taille de la souris*/
    double getRadius() const;

    /*getter qui retourne la vitesse maximale que peut avoir la souris*/
    double getMaxSpeed();

    /*getter qui retourne l'angle de vision de la souris*/
    double getViewRange()const;

    /*getter qui retourne la distance maximale de vision de la souris*/
    double getViewDistance()const;

    /*getter qui retourne la masse de la souris*/
    double getMasse() const;

    /*getter qui retourne un facteur de perte d'énergie de la souris*/
    double getLossFactor();

    /*méthode qui vérifie si une souris est morte*/
    bool isdead()const;

    /*méthode qui vérifie si une souris peut être confinée dans une boîte*/
    bool canBeConfinedIn(Box* boite) const;

    /*méthodes pour vérifier si une souris est mangeable par certaines entités*/
    bool eatable(SimulatedEntity const* entity) const;

    bool eatableBy(Mouse const*) const;

    bool eatableBy(Cheese const*) const;

    /*retourne une quantité d'énergie que fait perdre au fromage la souris à chaque fois qu'elle en mange un*/
    Quantity FoodQuantity();

    /*cette méthode n'est pas redéfinie ici, elle est surtout utile pour le fromage; la méthode décremente son énergie d'une certaine quantité*/
    Quantity provideEnergy(Quantity qte);

protected:
    sf::Texture texture_;

};


#endif