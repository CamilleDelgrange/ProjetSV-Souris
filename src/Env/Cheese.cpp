#include "Cheese.hpp"
#include "SimulatedEntity.hpp"
#include <Application.hpp>

//----CONSTRUCTEUR----//
Cheese::Cheese(Vec2d position)
    : SimulatedEntity(getAppConfig().cheese_initial_energy, position, getAppTexture(getAppConfig().cheese_texture))
{}

//----DESTRUCTEUR----//
Cheese::~Cheese()
{}

/*méthode qui décremente l'énergie du fromage d'une certaine quantité "qte"*/
Quantity Cheese::provideEnergy(Quantity qte)
{
    if (energie_<qte) { /*si la quantité qte est plus grande que l'énergie du fromage, alors on met l'énergie du fromage à zéro*/
        Quantity energie_prel;
        energie_prel= qte-energie_;
        energie_=0;
        return energie_prel; /*...et on retourne la quantité d'énergie prélevée.*/
    } else {
        energie_-=qte;
        return energie_;
    }
}

/*getter qui retourne la taille du fromage*/
double Cheese::getRadius() const
{
    return (0.5*energie_);
}

/*méthode qui vérifie si un fromage peut être mis dans une boîte*/
bool Cheese::canBeConfinedIn(Box* boite) const
{
    if(boite != nullptr) { /*un fromage peut être mis dans une boîte si la boîte existe*/
        return true;
    } else {
        return false;
    }
}

/*méthodes qui vérifient si le fromage peut être mangé par une entité ou non*/
bool Cheese::eatable(SimulatedEntity const* entity) const
{
    return entity->eatableBy(this);
}

/*un fromage ne peut pas être mangé par un fromage*/
bool Cheese::eatableBy(Cheese const*) const
{
    return false;
}
/*un fromage peut être mangé par une souris*/
bool Cheese::eatableBy(Mouse const*) const
{
    return true;
}