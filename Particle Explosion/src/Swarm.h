#include "Particle.h"

namespace Daklit
{
	class Swarm
	{
	private:
		Particle* m_pParticle;
	public:
		const static int nParticles = 2500;
	public:
		Swarm();
		virtual ~Swarm();
		void update();

		const Particle* const getParticles() { return m_pParticle; };
	};
}


