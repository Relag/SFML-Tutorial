#include "Engine.h"

void Engine::draw() {
	m_Window.clear(Color::White);

	if (!m_SplitScreen) {
		//Single-player view
m_Window.setView(m_BGMainView);
		m_Window.draw(m_BackgroundSprite);
		m_Window.setView(m_MainView);
	}
	else {
		//Splitscreen view
		m_Window.setView(m_BGLeftView);
		m_Window.draw(m_BackgroundSprite);
		m_Window.setView(m_LeftView);

		m_Window.setView(m_BGRightView);
		m_Window.draw(m_BackgroundSprite);
		m_Window.setView(m_RightView);
	}
		//Draw hud
	m_Window.setView(m_HudView);
	m_Window.display();
	
}