#include <SFML/Graphics.hpp>
#include <math.h>
#include "Material_point.h"
#include <iostream>

void check_wall(Ball& for_check);
float dot_product(sf::Vector2f vec1 , sf::Vector2f vec2);
bool check_collision(Ball& ball_i , Ball& ball_j);
sf::Vector2f const_product(float k , sf::Vector2f vec);
void draw_world(std::vector<Ball> balls , sf::RenderWindow* window);

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000 , 1000) , "maboy");
	sf::Clock clock;

	std::vector<Ball> balls;

	int counter = 0;
	float check_time = 0;
	int check_press = 0;

	while(window.isOpen())
	{
		sf::Event event;
		sf::Time time = clock.getElapsedTime();
		float dt = time.asSeconds();

		for (auto it = balls.begin() ; it != balls.end() ; ++it)
		{
			it->UpdatePosition(dt);
			//it->velocity.y += dt * 100 * 0.01 * 5;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			if (check_press ==0)
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				Ball per;
				per.radius = 15;
				per.position.x = mousePosition.x ;
				per.position.y = mousePosition.y ;
				per.velocity.x = 1;
				per.velocity.y = 1;
				per.mass = 2;

				balls.push_back(per);
			}
			check_press = 1;
		}
		else
		{
			check_press = 0;
		}

		clock.restart();

		for (auto it_1 = balls.begin() ; it_1 != balls.end() ; ++it_1)
		{
			for (auto it_2 = balls.begin() ; it_2 != balls.end() ; ++it_2)
			{
				if (it_1 != it_2)
					check_collision(*it_1 , *it_2);
			}
			check_wall(*it_1);
		}

		if(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		}

        window.clear(sf::Color::Black);

        draw_world(balls , &window);

		/*counter++;
		check_time = check_time + dt;

		if (check_time >= 1)
		{
			std::cout << counter << std::endl;
			counter = 0;
			check_time = 0;
		}*/

		window.display();
	}
}

void check_wall(Ball& for_check)
{
	if ((for_check.position.y + 2 * for_check.radius >= 1000) && (for_check.velocity.y > 0))
		{
			for_check.velocity.y = (-1) * for_check.velocity.y;
			for_check.position.y = 1000 - 2 * for_check.radius;
		}

	if ((for_check.position.y <= 0) && (for_check.velocity.y < 0))
		{
			for_check.velocity.y = (-1) * for_check.velocity.y;
			for_check.position.y = 0;
		}

	if ((for_check.position.x <= 0) && (for_check.velocity.x < 0))
		{
			for_check.velocity.x = (-1) * for_check.velocity.x;
			for_check.position.x = 0;
		}

	if ((for_check.position.x + 2 * for_check.radius >= 1000) && (for_check.velocity.x > 0))
		{
			for_check.velocity.x = (-1) * for_check.velocity.x;
			for_check.position.x = 1000 - 2 * for_check.radius;
		}
}

bool check_collision(Ball& ball_i , Ball& ball_j)
{
	sf::Vector2f D = ball_j.position - ball_i.position;
	sf::Vector2f V_sum = ball_j.velocity - ball_i.velocity;
	float d = sqrt(pow(D.x , 2) + pow(D.y , 2));

	if ((d <= ball_i.radius + ball_j.radius) && (dot_product(D , V_sum) <= 0))
	{
		sf::Vector2f n = const_product(1 / d , D);
		V_sum = const_product(1 / ball_i.mass + 1 / ball_j.mass , V_sum);
		float per = dot_product(n , V_sum);
		per = per * 2;
		sf::Vector2f dp = const_product(per , n);

		ball_j.velocity = ball_j.velocity - const_product(1 / ball_j.mass , dp);
		ball_i.velocity = ball_i.velocity + const_product(1 / ball_i.mass , dp);

		ball_i.position = ball_i.position - const_product(3 , n);
		ball_j.position = ball_j.position + const_product(3 , n);

		//std::cout << dp.x << " " << dp.y;

		return true;
	}

	return false;
}

float dot_product(sf::Vector2f vec1 , sf::Vector2f vec2)
{
	float res;
	res = vec1.x * vec2.x + vec1.y * vec2.y;

	return res; 
}

sf::Vector2f const_product(float k , sf::Vector2f vec)
{
	sf::Vector2f res = {vec.x * k , vec.y * k};

	return res;
}

void draw_world(std::vector<Ball> balls , sf::RenderWindow* window)
{
	for (auto it = balls.begin() ; it != balls.end() ; ++it)
	{
		sf::CircleShape circle(it->radius);
        circle.setPosition(it->position.x , it->position.y);
        circle.setFillColor(sf::Color::Red);
        circle.setOutlineThickness(0);

        window->draw(circle);
    }

}
