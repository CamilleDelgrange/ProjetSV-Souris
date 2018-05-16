#ifndef LAB_HPP
#define LAB_HPP
#include <iostream>
#include "Box.hpp"
#include <SFML/Graphics.hpp>
#include <Utility/Utility.hpp>
#include <Types.hpp>
//#include "Cheese.hpp"
//#include "Mouse.hpp"
//#include "Animal.hpp"
#include <memory>
using namespace std;

class Cheese;
class Mouse;
class Animal;
class SimulatedEntity;


typedef vector<vector<Box*>> Laboratoire;

class Lab
{

private:
    Laboratoire lab_;
    vector<SimulatedEntity*> entites_;
    vector<Cheese*> fromages_;
    vector<Animal*> animaux_;
    Animal* trackedAnimal_;
    /*cet attribut nous sert à avoir un animal que l'on veut "traquer", de telle sorte
     * à pouvoir l'utiliser dans plusieurs méthodes.*/

public:

    ~Lab();

    Lab();

    void update(sf::Time dt); //fait évoluer le contenu de chaque boite au cours du temps, après dt

    void drawOn(sf::RenderTarget& targetWindow); //dessine le contenu du labo

    void reset(); //vide toutes les boites de leur contenu

    void makeBoxes(unsigned int nbCagesPerRow); // permet de quadriller le lab avec nb donne de boites par ligne

    void destroyBoxes(); // supprime toutes les boites du laboratoire (le laboratoire devient vide)

    bool addAnimal(Animal* animal);

    bool addCheese(Cheese* cheese);

    bool addEntity(SimulatedEntity* entite); //on ajoute une entite à la simulation

    Box* TheBoxOf(SimulatedEntity* entite); //retourne la boite correspondant à l'entite simulée

    SimulatedEntity* FindTargetInSight(Animal* animal); //retourne la cible en vue de l'animal

    /*Cette méthode traque un animal par rapport à une certaine position.
         * Dans notre cas, la position passée en paramètre va notamment être la position de notre curseur.*/
    void trackAnimal(const Vec2d& position);

    /*Cette méthode est un setter de notre attribut "trackedAnimal_"*/
    void trackAnimal(Animal* animal);

    /*cette méthode permet de passer de la vue externe (du lab) à la vue interne (celle de l'organe)*/
    void switchToView(View view);

    /*cette méthode sert à indiquer que plus aucun individu n'est traqué.*/
    void stopTrackingAnyEntity();

    /*méthode qui permet de faire évoluer l'organe de notre animal traqué*/
    void updateTrackedAnimal();

    /*méthode qui permet de dessiner l'organe de notre animal traqué, s'il existe*/
    void drawCurrentOrgan(sf::RenderTarget& targetWindow);


};

#endif
