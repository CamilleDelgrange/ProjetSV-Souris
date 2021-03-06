#ifndef CELLHANDLER_HPP
#define CELLHANDLER_HPP
#include <SFML/Graphics.hpp>
#include <Utility/Utility.hpp>
#include "Substance.hpp"

using namespace std;

class CellECM;
class CellBlood;
class CellLiver;
class Organ;
class CellOrgan;

class CellHandler   //représente la superposition d'au plus 3 types de cellules
{
private:
    CellCoord positionGrille_; //position logique sur la grille
    //représentation des 3 niveaux :
    CellECM* cellECM_; //occupe la position positionGrille_, si cellECM_ = nullptr, pas de cellule ECM à cette position
    CellLiver* cellLiver_; //cellule du foie occupant cette position
    CellBlood* cellBlood_; //cellule du reseau sanguin occupant cette position
    Organ* organ_; //CellHandler a connaissance de l'organe auquel il appartient
public:
    CellHandler(CellCoord positionLogique, Organ* organ);
    virtual ~CellHandler();

    //-------SETTERS-------//
    /*retournent true s'il existe bien une cellule du type CellECM, CellLiver ou CellBlood respectivement au niveau de
    la position gérée par le CellHandler (valeur différente de nullptr), et false dans le cas contraire. */
    bool hasECM();
    bool hasLiver();
    bool hasBlood();
    void setECM();
    void setBlood(TypeBloodCell typeBloodCell);
    void setLiver();

    void updateSubstance(Substance& substance); //met des substances sur le niveau "ECM"

    //-------GETTERS-------//
    //retournent la quantité de substance identifiée par id véhiculée par chaque niveau du CellHandler
    double getECMQuantity(SubstanceId id);
    double getLiverQuantity(SubstanceId id);
    double getBloodQuantity(SubstanceId id);

    /*permettant au
    niveau «ECM» du CellHandler de céder au niveau «foie» une fraction de la substance
    identifié par id. Par exemple, l'appel liverTakeFromECM(GLUCOSE, 0.5),
    permettra au niveau «ECM» de céder 50% de son glucose au niveau «foie».
    Souvenez-vous de Substance::uptakeOnGradient.*/

    /*permet au
    niveau «ECM» du CellHandler de céder au niveau «foie» une fraction de la substance
    identifié par id.*/
    void liverTakeFromEcm(SubstanceId id, double fraction);

    //retourne true si la coordonnées coord est à l'extérieur de l'organe auquel appartient le CellHandler et false sinon.
    bool isOut(const CellCoord& coord);
    //on met à jour toutes les CellOrgan
    void update();
};

#endif