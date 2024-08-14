#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>

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

		sf::RectangleShape& getShape() {
			return brick;
		}
};

class Game {
	private:
		sf::RenderWindow window;
		sf::RectangleShape paddle;
		sf::CircleShape ball;
		std::vector<Brick> bricks;
		sf::Vector2f velocity;
		float moveSpeed;

		void initWindow() {
			window.create(sf::VideoMode(600, 800), "Breakout");
		}

		void initPaddle() {
			paddle.setSize(sf::Vector2f(80, 10));
			paddle.setFillColor(sf::Color::White);
			paddle.setPosition(260, 750);
		}

		void initBall() {
			ball.setRadius(10);
			ball.setFillColor(sf::Color::White);
			ball.setPosition(295, 395);
		}

		void initBricks() {
			bricks.push_back(Brick(50, 50, 0, 0));
			bricks.push_back(Brick(50, 50, 55, 0));
			bricks.push_back(Brick(50, 50, 110, 0));
			bricks.push_back(Brick(50, 50, 165, 0));
			bricks.push_back(Brick(50, 50, 220, 0));
			bricks.push_back(Brick(50, 50, 275, 0));
			bricks.push_back(Brick(50, 50, 330, 0));
			bricks.push_back(Brick(50, 50, 385, 0));
			bricks.push_back(Brick(50, 50, 440, 0));
			bricks.push_back(Brick(50, 50, 495, 0));
			bricks.push_back(Brick(50, 50, 550, 0));

			bricks.push_back(Brick(50, 50, 0, 55));
			bricks.push_back(Brick(50, 50, 55, 55));
			bricks.push_back(Brick(50, 50, 110, 55));
			bricks.push_back(Brick(50, 50, 165, 55));
			bricks.push_back(Brick(50, 50, 220, 55));
			bricks.push_back(Brick(50, 50, 275, 55));
			bricks.push_back(Brick(50, 50, 330, 55));
			bricks.push_back(Brick(50, 50, 385, 55));
			bricks.push_back(Brick(50, 50, 440, 55));
			bricks.push_back(Brick(50, 50, 495, 55));
			bricks.push_back(Brick(50, 50, 550, 55));

		}

		void processEvents() {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}
			}
		}

		void update() {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				if (paddle.getPosition().x > 0) {
					paddle.move(-moveSpeed, 0);
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				if (paddle.getPosition().x < 520) {
					paddle.move(moveSpeed, 0);
				}
			}

			if (ball.getPosition().y < 0 || ball.getGlobalBounds().intersects(paddle.getGlobalBounds())) {
				velocity.y = -velocity.y;
			} else if (ball.getPosition().x < 0 || ball.getPosition().x > 580) {
				velocity.x = -velocity.x;
			}

			if (ball.getPosition().y > 780) {
				ball.setPosition(295, 395);
			}

			for (auto& brick : bricks) {
				if (!brick.isBroken() && ball.getGlobalBounds().intersects(brick.getShape().getGlobalBounds())) {
					velocity.y = -velocity.y;
					brick.setBroken();
				}
			}

			ball.move(velocity);
		}

		void render() {
			window.clear();
			window.draw(paddle);
			window.draw(ball);
			for (auto& brick : bricks) {
				if (!brick.isBroken()) {
					window.draw(brick.getShape());
				}
			}
			window.display();
		}

	public:
		Game() : moveSpeed(0.125f), velocity(0.075f, 0.075f) {
			initWindow();
			initPaddle();
			initBall();
			initBricks();
		}

		void run() {
			while (window.isOpen()) {
				processEvents();
				update();
				render();
			}
		}
};

int main() {
	Game game;
	game.run();

	return EXIT_SUCCESS;
}
