#include<iostream>
#include<SFML/Graphics.hpp>

class Brick {
	private:
		int width;
		int height;
		int xPos;
		int yPos;
		bool broken = false;

		sf::RectangleShape brick;
	
	public:
		Brick(int w, int h, int x, int y) : width(w), height(h), xPos(x), yPos(y) {
			brick.setPosition(xPos, yPos);
			brick.setSize(sf::Vector2f(width, height));
			brick.setFillColor(sf::Color::White);
		}

		bool isBroken() {
			return broken;
		}

		void setBroken() {
			broken = true;
		}

		sf::RectangleShape getShape() {
			return brick;
		}
};

int main() {
	sf::RenderWindow window(sf::VideoMode(600, 800), "Breakout");

	sf::RectangleShape paddle;
	paddle.setSize(sf::Vector2f(80, 10));
	paddle.setFillColor(sf::Color::White);
	paddle.setOutlineColor(sf::Color::White);
	paddle.setPosition(260, 750);

	sf::CircleShape ball;
	ball.setRadius(10);
	ball.setFillColor(sf::Color::White);
	ball.setOutlineColor(sf::Color::White);
	ball.setPosition(295, 395);

	float moveSpeed = 0.125f;
	sf::Vector2f velocity(0.075f, 0.075f);

	std::vector<Brick> bricks;
	bricks.push_back(Brick(20, 20, 0, 0));
	bricks.push_back(Brick(20, 20, 25, 0));
	bricks.push_back(Brick(20, 20, 50, 0));
	bricks.push_back(Brick(20, 20, 75, 0));


	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			float newX = paddle.getPosition().x;
			if (newX > 0) {
				paddle.move(-moveSpeed, 0);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			float newX = paddle.getPosition().x;
			if (newX < 520) {
				paddle.move(moveSpeed, 0);
			}
		}

		if (ball.getPosition().y < 0 || ball.getGlobalBounds().intersects(paddle.getGlobalBounds())) {
			velocity.y = -velocity.y;
		} else if (ball.getPosition().x < 0 || ball.getPosition().x > 580) {
			velocity.x = -velocity.x;
		}

		for (auto& brick: bricks) {
			if (ball.getGlobalBounds().intersects(brick.getShape().getGlobalBounds())) {
				velocity.y = -velocity.y;
				brick.setBroken();
			}
		}

		ball.move(velocity);

		window.clear();
		window.draw(paddle);
		window.draw(ball);
		for (auto& brick: bricks) {
			if (!brick.isBroken()) {
				window.draw(brick.getShape());
			}
		}
		window.display();
	}

	return EXIT_SUCCESS;
}
