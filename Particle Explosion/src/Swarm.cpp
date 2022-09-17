#include "Swarm.h"

namespace Daklit
{
	Swarm::Swarm()
	{
		m_pParticle = new Particle[nParticles];
	}

	Swarm::~Swarm()
	{
		delete[] m_pParticle; 
	}

	void Swarm	::update()
	{
		for (int i = 0; i < Swarm::nParticles; i++)
		{
			m_pParticle[i].update();
		}
	}
}