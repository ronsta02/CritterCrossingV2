
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>

class Game
{
public:
	Game(sf::RenderWindow& window);
	~Game();
	bool init();
	void update(float dt);
	void render();
	void mouseClicked(sf::Event event);
	void keyPressed(sf::Event event);
	void dragSprite(sf::Sprite* sprite);
	void mouseButtonPressed(sf::Event event);
	void mouseButtonReleased(sf::Event event);
	void contextMenu();


	//
	void newAnimal();



private:
	sf::RenderWindow& window;

	sf::Texture* animals = new sf::Texture[3];
	sf::Texture* passports = new sf::Texture[3];
	sf::Texture backgroundTexture;
	sf::Texture acceptStampTexture;
	sf::Texture rejectStampTexture;
	sf::Texture acceptButtonTexture;
	sf::Texture rejectButtonTexture;
	sf::Texture livesTexture;


	sf::Sprite* character;
	sf::Sprite* passport;
	sf::Sprite background;
	sf::Sprite acceptStampSprite;
	sf::Sprite rejectStampSprite;
	sf::Sprite acceptButtonSprite;
	sf::Sprite rejectButtonSprite;
	sf::Sprite livesSprite;

	sf::Font font;
	sf::Text menuText;
	sf::Text gameOverText;

	enum gameState {
		menu,
		playing,
		gameOver
	};

	gameState state;



	sf::Sprite* dragged = nullptr;

	bool passport_accepted;
	bool passport_rejected;
	bool contextMenuOpen;

	bool should_accept;

	int lives;

	sf::Vector2f mouseOffset;
};

#endif // PLATFORMER_GAME_H
