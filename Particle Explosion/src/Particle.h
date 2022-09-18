
namespace Daklit
{
	class Particle
	{
	public:
		double m_x;
		double m_y;
		double m_direction;
		double m_speed;

	public:
		Particle();
		virtual ~Particle();
		void init();
		void update(int interval);
	};
}

