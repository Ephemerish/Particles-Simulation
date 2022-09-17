#include "Particle.h"

namespace Daklit
{
	class Swarm
	{
	private:
		Particle* m_pParticle;
	public:
		const static int nParticles = 5000;
	public:
		Swarm();
		virtual ~Swarm();

		const Particle* const getParticles() { return m_pParticle; };
	};
}


