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
}