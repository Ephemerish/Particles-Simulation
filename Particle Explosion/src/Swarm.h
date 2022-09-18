#include "Particle.h"

namespace Daklit
{
	class Swarm
	{
	private:
		Particle* m_pParticle;
		int lastTime;
	public:
		const static int nParticles = 7500;
	public:
		Swarm();
		virtual ~Swarm();
		void update(int elapsed);

		const Particle* const getParticles() { return m_pParticle; };
	};
}


