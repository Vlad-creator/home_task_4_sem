class Material_point
{
public:
	Material_point() {};

	virtual ~Material_point() {};
	virtual void UpdatePosition(float dt);

	sf::Vector2f GetImpulse() const;

	sf::Vector2f velocity;
	sf::Vector2f position;
	sf::Vector2f acceleration;

	float mass;
};

class Ball: public Material_point
{
public:
	Ball() {};
	Ball(int type_ , float radius_): type(type_) , radius(radius_) {};

	float radius;
	int type;
};

void Material_point::UpdatePosition(float dt)
{
	position.x += velocity.x * dt * 500;
	position.y += velocity.y * dt * 500;
}

sf::Vector2f Material_point::GetImpulse() const
{
	sf::Vector2f impulse;
	impulse.x = velocity.x * mass;
	impulse.y = velocity.y * mass;

	return impulse;
}