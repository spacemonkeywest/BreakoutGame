#include<iostream>
#include<SFML/Graphics.hpp>

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

	float moveSpeed = 0.1f;

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

		window.clear();
		window.draw(paddle);
		window.draw(ball);
		window.display();
	}

	return EXIT_SUCCESS;
}
