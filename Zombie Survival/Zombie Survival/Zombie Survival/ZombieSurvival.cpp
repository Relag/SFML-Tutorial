#include <SFML/Graphics.hpp>
#include "Player.h"

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
	Vector2f mouseScreenPosition;

	Player player;

	IntRect arena;

	//Main Game Loop
	while (window.isOpen()) {

	}
	return 0;
}