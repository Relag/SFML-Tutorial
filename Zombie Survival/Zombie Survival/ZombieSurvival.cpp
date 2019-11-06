#include <SFML/Graphics.hpp>
#include "Player.h"
#include "ZombieSurvival.h"

using namespace sf;

int main() {
	enum class State {
		PAUSED, LEVELING_UP, GAME_OVER, PLAYING
	};

	State state = State::GAME_OVER;

	//Get Screen Resolution and create window.
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y),
		"Zombie Survival", Style::Fullscreen);

	//Create an SFML View for the main action
	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

	Clock clock;

	Time gameTimeTotal;

	Vector2f mouseWorldPosition;
	Vector2i mouseScreenPosition;

	Player player;

	IntRect arena;

	//Create the backgroundVertexArray background
	//Load the texture for the background
	Texture textureBackground;
	textureBackground.loadFromFile("graphics/background_sheet.png");

	VertexArray background;

	//Main Game Loop
	while (window.isOpen()) {
		//Handle ievents by polling
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Return &&
					state == State::PLAYING) {
					state = State::PAUSED;
				}
				else if (event.key.code == Keyboard::Return &&
					state == State::PAUSED) {
					state = State::PLAYING;
					clock.restart();
				}
				else if (event.key.code == Keyboard::Return &&
					state == State::GAME_OVER) {
					state = State::LEVELING_UP;
				}
				if (state == State::PLAYING) {
				}
			}
		}
		//Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
		//Handle WASD
		if (state == State::PLAYING) {
			if (Keyboard::isKeyPressed(Keyboard::W)) {
				player.MoveUp();
			}
			else{
				player.StopUp();
			}
			if (Keyboard::isKeyPressed(Keyboard::S)) {
				player.MoveDown();
			}
			else {
				player.StopDown();
			}
			if (Keyboard::isKeyPressed(Keyboard::A)) {
				player.MoveLeft();
			}
			else {
				player.StopLeft();
			}
			if (Keyboard::isKeyPressed(Keyboard::D)){
				player.MoveRight();
			}
			else {
				player.StopRight();
			}
		}//End WASD While Playing

		//Handle Leveling up
		if (state == State::LEVELING_UP) {
			if (event.key.code == Keyboard::Num1) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num2) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num3) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num4) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num5) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num6) {
				state = State::PLAYING;
			}

			if (state == State::PLAYING) {
				//Prepare level
				arena.width = 500;
				arena.height = 500;
				arena.left = 0;
				arena.top = 0;

				//Pass the vetex array by reference
				int tileSize = createBackground(background, arena);

				player.Spawn(arena, resolution, tileSize);

				clock.restart();
			}
		}//End Level up.

		if (state == State::PLAYING) {
			Time dt = clock.restart();

			gameTimeTotal += dt;

			float dtAsSeconds = dt.asSeconds();

			mouseScreenPosition = Mouse::getPosition();

			mouseWorldPosition = window.mapPixelToCoords(
				Mouse::getPosition(), mainView);

			//Update player
			player.Update(dtAsSeconds, Mouse::getPosition());

			Vector2f playerPosition(player.GetCentre());

			mainView.setCenter(player.GetCentre());
		}//End Update
		

		//Draw the scene
		if (state == State::PLAYING) {
			window.clear();
			window.setView(mainView);

			//Takes a vertex array, and draws the background according
			//to the coordinates of each vertice.
			window.draw(background, &textureBackground);

			window.draw(player.GetSprite());
		}

		if (state == State::LEVELING_UP) {

		}
		if (state == State::PAUSED){

		}
		if (state == State::GAME_OVER) {
			
		}
		window.display();
	}//End game loop.
	return 0;
}