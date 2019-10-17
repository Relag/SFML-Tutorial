//Tutorial for SFML: https://www.linkedin.com/learning/c-plus-plus-game-programming-1/starting-to-code-the-game?u=42358916
//Game based off Timberman
#include <SFML/Graphics.hpp>
#include <sstream>
#include <SFML/Audio.hpp>

using namespace sf;

//function declaration
void updateBranches(int seed);
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

int main() {
	//create a video mode object
	sf::VideoMode vm(1900, 1080);

	//Create and open a window for the game
	sf::RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

	//Create a texture to hold a graphic on the GPU
	Texture textureBackground;

	//Load a graphic into the texture
	textureBackground.loadFromFile("graphics/background.png");

	//Create a sprite. Sprites require a texture class object to display.
	Sprite spriteBackground;

	//Attatch the texture to the sprite
	spriteBackground.setTexture(textureBackground);

	//Set the spritebackground to cover the screen
	spriteBackground.setPosition(0, 0);

	//Make a tree sprite
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);


	//Prepare a bee
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);
	bool bBeeActive = false;
	float fBeeSpeed = 0.0f;

	//Make 3 cload sprites
	Texture textureCload;
	textureCload.loadFromFile("graphics/cloud.png");

	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;
	//set cloud textures
	spriteCloud1.setTexture(textureCload);
	spriteCloud2.setTexture(textureCload);
	spriteCloud3.setTexture(textureCload);
	//set cloud speeds
	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 250);
	spriteCloud3.setPosition(0, 500);
	//are clouds on screen
	bool bCloud1Active = false;
	bool bCloud2Active = false;
	bool bCloud3Active = false;
	//how fast clouds move
	float fCloud1Speed = 0.0f;
	float fCloud2Speed = 0.0f;
	float fCloud3Speed = 0.0f;

	Clock clock;

	//Time bar
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	bool paused = true;

	//Draw some text
	int score = 0;
	sf::Text messageText;
	sf::Text scoreText;

	//Choose a font
	Font font;
	font.loadFromFile("fonts/Komikap_.ttf");

	//Set the font to our message
	messageText.setFont(font);
	scoreText.setFont(font);

	//Assign the actual message
	messageText.setString("Press Enter to Start!");
	scoreText.setCharacterSize(100);

	//Make it big
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);

	//Choose a colour
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);

	//Position the text
	FloatRect textRect = messageText.getLocalBounds();
	//Sets the origin point of the message to the centre of the messagebox.
	messageText.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top + 
		textRect.height / 2.0f);
	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	scoreText.setPosition(20, 20);

	//Prepare 6 branches
	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");

	for (int i = 0; i < NUM_BRANCHES; i++) {
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);
		//Set the sprite's origin to dead centre
		//We can then spin it round without changing its position
		branches[i].setOrigin(220, 20);
	}

	//Prepare the player
	Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580, 720);

	//Player starts on the left
	side playerSide = side::LEFT;

	//Prepare the gravestone
	Texture textureRIP;
	textureRIP.loadFromFile("graphics/rip.png");
	Sprite spriteRip;
	spriteRip.setTexture(textureRIP);
	spriteRip.setPosition(600,800);

	//Prepare axe
	Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);

	//Line the axe up with the player
	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;

	//Prepare the flying log
	Texture textureLog;
	textureLog.loadFromFile("graphics/log.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 720);

	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;

	bool acceptInput = false;

	//For sound effects
	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("sound/chop.wav");
	Sound chop;
	chop.setBuffer(chopBuffer);

	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("sound/death.wav");
	Sound death;
	death.setBuffer(deathBuffer);

	SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("sound/out_of_time.wav");
	Sound outOfTime;
	outOfTime.setBuffer(ootBuffer);

	while (window.isOpen()) {
		//Handle the players input
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Return)) {
			paused = false;

			//Reset time and score
			score = 0;
			timeRemaining = 5;

			for (int i = 1; i < NUM_BRANCHES; i++) {
				branchPositions[i] = side::NONE;
			}

			spriteRip.setPosition(675, 2000);

			spritePlayer.setPosition(580, 720);
			acceptInput = true;
		}

		if (acceptInput) {

			if (Keyboard::isKeyPressed(Keyboard::Left)){
				playerSide = side::LEFT;
				score++;

				timeRemaining += (2 / score) + .15;

				spriteAxe.setPosition(AXE_POSITION_LEFT,
					spriteAxe.getPosition().y);

				spritePlayer.setPosition(580, 720);

				updateBranches(score);

				spriteLog.setPosition(810, 720);
				logSpeedX = 5000;
				logActive = true;

				acceptInput = false;

				chop.play();
			}

			if (Keyboard::isKeyPressed(Keyboard::Right)){
				playerSide = side::RIGHT;
				score++;

				timeRemaining += (2 / score) + .15;

				spriteAxe.setPosition(AXE_POSITION_RIGHT,
					spriteAxe.getPosition().y);

				spritePlayer.setPosition(1200, 720);

				updateBranches(score);

				spriteLog.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;

				acceptInput = false;

				chop.play();
			}

		}

		//events handle everything from key presses to mouse movement.
		//Events happen fast, so use a while loop to check if an event has happened.

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::KeyReleased && !paused) {
				acceptInput = true;

				spriteAxe.setPosition(2000,
					spriteAxe.getPosition().y);
			}
		}

		//Update the Scene
		if (!paused) {
			Time dt = clock.restart();	//dt = delta time

			//Subtract from the amount of time remaining
			timeRemaining -= dt.asSeconds();
			timeBar.setSize(Vector2f(timeBarWidthPerSecond *
				timeRemaining, timeBarHeight));

			if (timeRemaining <= 0.0f) {
				paused = true;
				messageText.setString("Out of Time!!");

				//Reposition text based on new size
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

				outOfTime.play();
			}

			//Setup the bee
			if (!bBeeActive) {
				srand((int)time(0) * 10);
				float fWidth;
				if (rand() % 2 == 0) {
					fBeeSpeed = (rand() % 500) + 200;
					fWidth = 2000;
					spriteBee.setScale(1, 1);
				}
				else {
					fBeeSpeed = ((rand() % 500) + 200) * -1;
					fWidth = -100;
					spriteBee.setScale(-1, 1);
				}
				srand((int)time(0) * 10);
				float fHeight = (rand() % 500) + 500;
				spriteBee.setPosition(fWidth, fHeight);
				bBeeActive = true;
			}
			else {
spriteBee.setPosition(
	spriteBee.getPosition().x -
	(fBeeSpeed * dt.asSeconds()),
	spriteBee.getPosition().y);

if (spriteBee.getPosition().x < -120 || spriteBee.getPosition().x > 2020) {
	bBeeActive = false;
}
			}

			if (!bCloud1Active) {
				srand((int)time(0) * 10);
				fCloud1Speed = (rand() % 200);

				srand((int)time(0) * 10);
				float fHeight = (rand() % 150);
				spriteCloud1.setPosition(200, fHeight);
				bCloud1Active = true;
			}
			else {
				spriteCloud1.setPosition(
					spriteCloud1.getPosition().x +
					(fCloud1Speed * dt.asSeconds()),
					spriteCloud1.getPosition().y);

				if (spriteCloud1.getPosition().x > 2000) {
					bCloud1Active = false;
				}
			}
			if (!bCloud2Active) {
				srand((int)time(0) * 20);
				fCloud2Speed = (rand() % 200);

				srand((int)time(0) * 20);
				float fHeight = (rand() % 150);
				spriteCloud2.setPosition(950, fHeight);
				bCloud2Active = true;
			}
			else {
				spriteCloud2.setPosition(
					spriteCloud2.getPosition().x +
					(fCloud2Speed * dt.asSeconds()),
					spriteCloud2.getPosition().y);
				if (spriteCloud2.getPosition().x > 2000) {
					bCloud2Active = false;
				}
			}
			if (!bCloud3Active) {
				srand((int)time(0) * 30);
				fCloud3Speed = (rand() % 200);

				srand((int)time(0) * 30);
				float fHeight = (rand() % 150);
				spriteCloud3.setPosition(-300, fHeight);
				bCloud3Active = true;
			}
			else {
				spriteCloud3.setPosition(
					spriteCloud3.getPosition().x +
					(fCloud3Speed * dt.asSeconds()),
					spriteCloud3.getPosition().y);
				if (spriteCloud3.getPosition().x > 2000) {
					bCloud3Active = false;
				}
			}

			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());

			for (int i = 0; i < NUM_BRANCHES; i++) {
				float height = i * 150;
				if (branchPositions[i] == side::LEFT) {
					//Move sprite to left side
					branches[i].setPosition(610, height);
					branches[i].setRotation(180);
				}
				else if (branchPositions[i] == side::RIGHT) {
					branches[i].setPosition(1330, height);
					branches[i].setRotation(0);
				}
				else {
					//hide the branch
					branches[i].setPosition(3000, height);
				}
			}
			if (logActive) {
				spriteLog.setPosition(
					spriteLog.getPosition().x +
					(logSpeedX * dt.asSeconds()),
					spriteLog.getPosition().y +
					(logSpeedY * dt.asSeconds()));

				if (spriteLog.getPosition().x < -100 ||
					spriteLog.getPosition().x > 2000) {
					logActive = false;
					spriteLog.setPosition(810, 720);
				}
			}

			if (branchPositions[5] == playerSide){
				//DED
				paused = true;
				acceptInput = false;

				spriteRip.setPosition(525, 760);
				spritePlayer.setPosition(2000, 660);
				messageText.setString("SQUISHED!!");

				FloatRect textRect = messageText.getLocalBounds();

				messageText.setOrigin(textRect.left +
					textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f);

				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

				death.play();

}
		}

		//Draw the scene

		//Clear everything from the last frame
		window.clear();

		//Draw game scene. Note: the order images are drawn are from
		//back to front. Therefore, the background is drawn first.
		window.draw(spriteBackground);

		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);

		for (int i = 0; i < NUM_BRANCHES; i++) {
			window.draw(branches[i]);
		}

		window.draw(spriteTree);

		window.draw(spriteBee);

		window.draw(spritePlayer);

		window.draw(spriteAxe);

		window.draw(spriteLog);

		window.draw(spriteRip);

		//Draw the text
		window.draw(scoreText);
		if (paused) {
			window.draw(messageText);
		}

		//Draw the time bar
		window.draw(timeBar);

		//Show everything drawn
		window.display();
	}


	return 0;
}

void updateBranches(int seed) {
	for (int j = NUM_BRANCHES - 1; j > 0; j--) {
		branchPositions[j] = branchPositions[j - 1];
	}

	srand((int)time(0) + seed);
	int r = (rand() % 5);
	switch (r) {
	case 0:
		branchPositions[0] = side::LEFT;
		break;
	case 1:
		branchPositions[0] = side::RIGHT;
		break;
	default:
		branchPositions[0] = side::NONE;
		break;
	}
}