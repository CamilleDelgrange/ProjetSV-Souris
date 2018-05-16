#include "CellLiver.hpp"

CellLiver::CellLiver(CellHandler* cellHandler_)
: CellOrgan(cellHandler_), atp_(100)
{}

void CellLiver::update(sf::Time dt)
{
	double atp_min(getAppConfig().base_atp_usage);
	double atp_max(atp_min + getAppConfig().range_atp_usage);
	atp_ = atp_ *(1-exp(-getAppConfig().liver_decay_atp*dt));
	atp_ -= uniform(atp_min, atp_max);
	if(atp_ < 0)
	{
		dead_ = true;
	}
}

bool CellLiver::cellLiverIsDead()
{
	return dead_;
}