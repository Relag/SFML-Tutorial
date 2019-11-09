#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

void Engine::update(float dtAsSeconds) {
	if (m_Playing) {
		m_Timeremaining -= dtAsSeconds;
	}

	if (m_Timeremaining <= 0) {
		m_NewLevelRequired = true;
	}
}
