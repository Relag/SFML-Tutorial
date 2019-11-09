#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"

using namespace sf;

class Engine
 {
private:
	TextureHolder th;

	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;

	const int GRAVITY = 300;

	RenderWindow m_Window;

	//the main views
	View m_MainView;
	View m_LeftView;
	View m_RightView;

	//Three views for background;
	View m_BGMainView;
	View m_BGLeftView;
	View m_BGRightView;

	View m_HudView;

	//Declare a sprite and texture for background
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;

	bool m_Playing = false;

	//is character 1 or 2 the focus
	bool m_Character1 = true;
	
	//Start in fullscreen mode
	bool m_SplitScreen = false;

	//Time remaining
	float m_Timeremaining = 10;
	Time m_GameTimeTotal;

	// Is it time for a new level?
	bool m_NewLevelRequired = true;

	void input();
	void update(float dtAsSeconds);
	void draw();

public:
	Engine();

	void run();
};
