#include "Box.hpp"
#include <iostream>
#include <vector>
#include <Utility/Vec2d.hpp>
//#include "Animal.hpp"
using namespace std;

//----CONSTRUCTEURS----//
Box::Box(Vec2d centre, double largeur, double hauteur, double epaisseur)
    : centre_(centre), largeur_(largeur), hauteur_(hauteur), epaisseur_(epaisseur), AnimalPresent_(false)
{
    /*construction des murs internes et externes de la boîte*/
    Vec2d TopBottomRight {centre.x+largeur/2-epaisseur, centre.y-hauteur/2+epaisseur};
    Vec2d TopTopLeft {centre.x-largeur/2, centre.y -hauteur/2};
    Vec2d RightBottomRight {centre.x+largeur/2, centre.y+hauteur/2-epaisseur};
    Vec2d RightTopLeft {centre.x+largeur/2-epaisseur, centre.y-hauteur/2};
    Vec2d BottomBottomRight {centre.x+largeur/2, centre.y+hauteur/2};
    Vec2d BottomTopLeft {centre.x-largeur/2+epaisseur, centre.y+hauteur/2-epaisseur};
    Vec2d LeftBottomRight {centre.x-largeur/2+epaisseur, centre.y+hauteur/2};
    Vec2d LeftTopRight {centre.x-largeur/2, centre.y-hauteur/2+epaisseur};

    /*construction des murs de la boîte*/
    Top = make_pair(TopBottomRight, TopTopLeft);
    Right = make_pair(RightBottomRight, RightTopLeft);
    Bottom = make_pair(BottomBottomRight, BottomTopLeft);
    Left = make_pair(LeftBottomRight, LeftTopRight);
}

/*getters qui retournent la face interne du mur si intern vaut true
  * et de la face externe si intern vaut false*/
/*mur de gauche*/
double Box::getLeftLimit(bool intern)
{
    if(intern) {
        return Bottom.second.x; /*retourne la coordonnée x de la face interne*/
    } else {
        return Left.second.x;   /*retourne la coordonnée x de la face externe*/
    }
}

/*mur de droite*/
double Box::getRightLimit(bool intern)
{
    if(intern) {
        return Top.first.x; /*retourne la coordonnée x de la face interne*/
    } else {
        return Right.first.x; /*retourne la coordonnée x de la face externe*/
    }
}

/*mur du bas*/
double Box::getBottomLimit(bool intern)
{
    if(intern) {
        return Bottom.second.y; /*retourne la coordonnée y de la face interne*/
    } else {
        return Bottom.first.y;  /*retourne la coordonnée y de la face externe*/
    }
}

/*mur du haut*/
double Box::getTopLimit(bool intern)
{
    if(intern) {
        return Top.first.y; /*retourne la coordonnée y de la face interne*/

    } else {
        return Right.second.y; /*retourne la coordonnée y de la face externe*/
    }
}

/*méthode qui retourne vrai si un point à une position donnée est COMPLETEMENT a l'interieur de la boite;
 * i.e. un point sur le  bord interne d'un mur ne sera pas considere comme a l'intérieur.*/
bool Box::isPositionInside(const Vec2d& position)
{
    return ((position.x > getLeftLimit(true)) and (position.x < getRightLimit(true))
            and (position.y > getTopLimit(true)) and (position.y < getBottomLimit(true)));

}

/*vérifie si la position est sur l'un des murs de la boîte*/
bool Box::isPositionOnWall(const Vec2d& position)
{
    //ATTENTION DANS SFML, L'AXE DES Y POINTE VERS LE BAS.
    return ((not(isPositionInside(position))) and (position.x >= getLeftLimit()) and (position.x <= getRightLimit())
            and (position.y >= getTopLimit()) and (position.y <= getBottomLimit()));

}

/*méthode qui vérifie si la boîte est vite: càd si notre attribut
 * est à false*/
bool Box::isEmpty()const
{
    return !AnimalPresent_;
}

/*setter qui marque une boîte comme étant "occupée"; càd mettre notre attribut
 * à "true"*/
void Box::addOccupant()
{
    AnimalPresent_=true;
}

/*méthode qui marque la boîte comme étant inocuppée; càd mettre notre attribut
 * à "false"*/
void Box::reset()
{
    AnimalPresent_=false;
}