#include "CellOrgan.hpp"
#include <SFML/Graphics.hpp>
#include <Application.hpp>
#include "CellHandler.hpp"
#include "Substance.hpp"
using namespace std;

CellOrgan::CellOrgan(CellHandler* cellHandler)
    : cellHandler_(cellHandler)
{
    substance_ = new Substance(0.0, 0.0, 0.0);
}

CellOrgan::~CellOrgan()
{
    delete substance_;
}

void CellOrgan::ecmUptakeOnGradient(double fraction, CellOrgan* cellOrgan, SubstanceId id)
{
    substance_->uptakeOnGradient(fraction, *(cellOrgan->substance_), id);
}

double CellOrgan::getQuantity(SubstanceId id)
{
    return (*substance_)[id];
}