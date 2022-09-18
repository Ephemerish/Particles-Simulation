#include "Swarm.h"

namespace Daklit
{
	Swarm::Swarm(): lastTime(0)
	{
		m_pParticle = new Particle[nParticles];
	}

	Swarm::~Swarm()
	{
		delete[] m_pParticle; 
	}

	void Swarm::update(int elapsed)
	{
		int interval = elapsed - lastTime;

		for (int i = 0; i < Swarm::nParticles; i++)
		{
			m_pParticle[i].update(interval);
		}
		lastTime = elapsed;
	}
}