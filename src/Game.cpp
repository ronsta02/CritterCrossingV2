
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
	: window(game_window)
{
	srand(time(NULL));
}

Game::~Game()
{
	delete[] animals;
	delete[] passports;
	delete character;
	delete passport;
}

bool Game::init()
{
	character = new sf::Sprite();
	passport = new sf::Sprite();
	lives = 3;

	font.loadFromFile("../Data/Fonts/OpenSans-Bold.ttf");
	menuText.setFont(font);
	menuText.setString("Critter Crossing \n \n Click To Play");
	menuText.setCharacterSize(75);
	menuText.setFillColor(sf::Color::Black);
	menuText.setOutlineColor(sf::Color::White);
	menuText.setOutlineThickness(3);
	//menuText.setPosition((window.getSize().x / 2.f), (window.getSize().y / 2.f));
	menuText.setPosition((window.getSize().x / 2.f) - (menuText.getLocalBounds().width / 2), (window.getSize().y / 2.f) - (menuText.getLocalBounds().height / 2));

	gameOverText.setFont(font);
	gameOverText.setString("Left Click To Play Again \n Right Click to Quit");
	gameOverText.setCharacterSize(50);
	gameOverText.setFillColor(sf::Color::Black);

	//gameOverText.setPosition((window.getSize().x / 2.f), (window.getSize().y / 2.f));
	gameOverText.setPosition((window.getSize().x / 2.f) - (gameOverText.getLocalBounds().width / 2), (window.getSize().y / 2.f) - (gameOverText.getLocalBounds().height / 2));

	state = menu;

	contextMenuOpen = false;

	// Two '.'s for parent directory!!
	animals[0].loadFromFile("../Data/Images/Critter Crossing Customs/penguin.PNG");
	animals[1].loadFromFile("../Data/Images/Critter Crossing Customs/elephant.png");
	animals[2].loadFromFile("../Data/Images/Critter Crossing Customs/moose.png");

	passports[0].loadFromFile("../Data/Images/Critter Crossing Customs/penguin passport.png");
	passports[1].loadFromFile("../Data/Images/Critter Crossing Customs/elephant passport.png");
	passports[2].loadFromFile("../Data/Images/Critter Crossing Customs/moose passport.png");

	if (!backgroundTexture.loadFromFile("../Data/Images/Icecaps Background.jpg"))
	{
		std::cout << "background texture did not load.";
	}
	background.setTexture(backgroundTexture);
	background.setPosition(0, 0);
	background.setScale(2.5, 2.5);

	// A / R Button and stamp texture loading

	if (!acceptStampTexture.loadFromFile("../Data/Images/Critter Crossing Customs/accept.PNG"))

	{
		std::cout << "accept stamp texture did not load.";
	}


	if (!rejectStampTexture.loadFromFile("../Data/Images/Critter Crossing Customs/reject.PNG"))

	{
		std::cout << "reject stamp texture did not load.";
	}

	if (!acceptButtonTexture.loadFromFile("../Data/Images/Critter Crossing Customs/accept button.PNG"))

	{
		std::cout << "accept button texture did not load.";
	}


	if (!rejectButtonTexture.loadFromFile("../Data/Images/Critter Crossing Customs/reject button.PNG"))

	{
		std::cout << "reject button texture did not load.";
	}

	//lives
	if (!livesTexture.loadFromFile("../Data/Images/kenney_physicspack/PNG/Explosive elements/elementExplosive001.PNG"))

	{
		std::cout << "lives texture did not load.";
	}

	livesSprite.setTexture(livesTexture);


	// A / R Button and stamp sprite & texure matching

	acceptStampSprite.setTexture(acceptStampTexture);
	rejectStampSprite.setTexture(rejectStampTexture);
	acceptButtonSprite.setTexture(acceptButtonTexture);
	rejectButtonSprite.setTexture(rejectButtonTexture);


	// Set Position of buttons just offscreen ready to slide in (animation prep for context menu)
	acceptButtonSprite.setPosition((window.getSize().x), (window.getSize().y - (2 * acceptButtonSprite.getLocalBounds().height) - 5));
	rejectButtonSprite.setPosition((window.getSize().x), (window.getSize().y - rejectButtonSprite.getLocalBounds().height));


	newAnimal();


	return true;
}

void Game::newAnimal()
{
	passport_accepted = false;
	passport_rejected = false;

	int animal_index = rand() % 3;
	int passport_index = rand() % 3;

	if (animal_index == passport_index)
	{
		should_accept = true;
	}
	else
	{
		should_accept = false;
	}

	character->setTexture(animals[animal_index], true);
	character->setScale(1.8, 1.8);
	character->setPosition(window.getSize().x / 12, window.getSize().y / 12);

	passport->setTexture(passports[passport_index]);
	passport->setScale(0.6, 0.6);
	passport->setPosition(window.getSize().x / 2, window.getSize().y / 3);



}

void Game::contextMenu()
{
	if (contextMenuOpen)
	{
		acceptButtonSprite.move(acceptButtonSprite.getLocalBounds().width, 0);
		rejectButtonSprite.move(rejectButtonSprite.getLocalBounds().width, 0);
		contextMenuOpen = false;
	}
	else
	{

		acceptButtonSprite.move(-acceptButtonSprite.getLocalBounds().width, 0);
		rejectButtonSprite.move(-rejectButtonSprite.getLocalBounds().width, 0);
		contextMenuOpen = true;
	}

}

void Game::mouseButtonPressed(sf::Event event)
{
	switch (state) {
	case menu:
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2i click = sf::Mouse::getPosition(window);
			sf::Vector2f clickf = static_cast<sf::Vector2f>(click);
			std::cout << "LC";
			if (menuText.getGlobalBounds().contains(clickf))
			{
				state = playing;
				std::cout << "Play Button Clicked" << std::endl;
			}
		}
		break;
	case playing:
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2i click = sf::Mouse::getPosition(window);
			sf::Vector2f clickf = static_cast<sf::Vector2f>(click);
			std::cout << "LC";

			if (passport->getGlobalBounds().contains(clickf))
			{
				dragged = passport;
				mouseOffset = clickf - passport->getPosition();


			}
			if (acceptButtonSprite.getGlobalBounds().contains(clickf) && !(passport_accepted || passport_rejected))
			{
				passport_accepted = true;
				std::cout << "Accept Button Clicked" << std::endl;
				acceptStampSprite.setPosition(passport->getPosition().x + (passport->getLocalBounds().width / 2) - (acceptStampSprite.getLocalBounds().width / 2), passport->getPosition().y + (passport->getLocalBounds().height / 2) - (acceptStampSprite.getLocalBounds().height / 2));

			}
			else if (rejectButtonSprite.getGlobalBounds().contains(clickf) && !(passport_accepted || passport_rejected))
			{
				passport_rejected = true;
				std::cout << "Reject Button Clicked" << std::endl;
			}
		}

		if (event.mouseButton.button == sf::Mouse::Right)
		{
			contextMenu();
			std::cout << "RC";
		}
		break;
	case gameOver:
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			lives = 3;
			state = playing;
		}
		if (event.mouseButton.button == sf::Mouse::Right)
		{
			window.close();
		}
		break;
	}

	//pre gamestates

	/*if (event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i click = sf::Mouse::getPosition(window);
		sf::Vector2f clickf = static_cast<sf::Vector2f>(click);
		std::cout << "LC" ;

		if (passport->getGlobalBounds().contains(clickf))
		{
			dragged = passport;
			mouseOffset = clickf - passport->getPosition();


		}
		if (acceptButtonSprite.getGlobalBounds().contains(clickf) && !(passport_accepted || passport_rejected))
		{
			passport_accepted = true;
			std::cout << "Accept Button Clicked" << std::endl;
			acceptStampSprite.setPosition(passport->getPosition().x + (passport->getLocalBounds().width / 2) - (acceptStampSprite.getLocalBounds().width / 2), passport->getPosition().y + (passport->getLocalBounds().height / 2) - (acceptStampSprite.getLocalBounds().height / 2));

		}
		else if (rejectButtonSprite.getGlobalBounds().contains(clickf) && !(passport_accepted || passport_rejected))
		{
			passport_rejected = true;
			std::cout << "Reject Button Clicked" << std::endl;
		}
	}

	if (event.mouseButton.button == sf::Mouse::Right)
	{
		contextMenu();
		std::cout << "RC";
	}*/
}

void Game::mouseButtonReleased(sf::Event event)
{

	if (event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i click = sf::Mouse::getPosition(window);
		sf::Vector2f clickf = static_cast<sf::Vector2f>(click);
		std::cout << "LCR";
		dragged = nullptr;
		//if (passport->getGlobalBounds().getPosition() < (sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f)))
		if (passport->getGlobalBounds().left < window.getSize().x / 2.f && passport->getGlobalBounds().top < window.getSize().y / 2.f)
			if (passport->getGlobalBounds().contains(clickf))
				if (should_accept && passport_accepted)
				{

					std::cout << "yippe Accepted" << std::endl;

					newAnimal();

					passport_rejected = false;
					passport_accepted = false;

				}
				else if (!should_accept && passport_rejected)
				{
					std::cout << "yippe Rejected" << std::endl;
					newAnimal();

					passport_rejected = false;
					passport_accepted = false;
				}
				else if (passport_accepted || passport_rejected)
				{
					std::cout << "BOOOOOO";
					lives -= 1;
					if (lives <= 0)
					{
						std::cout << "Game Over" << std::endl;
						state = gameOver;
					}
					newAnimal();
					std::cout << "lives remaining: " << lives << std::endl;

					passport_rejected = false;
					passport_accepted = false;
				}
	}




	//if (passport->getGlobalBounds().contains(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f)))
	/*if (passport->getGlobalBounds().left < window.getSize().x / 2.f && passport->getGlobalBounds().top < window.getSize().y / 2.f)
		if (passport->getGlobalBounds().contains(clickf))
			if (!should_accept && passport_rejected)
				{

					std::cout << "yippe Rejected"<<std::endl;

					newAnimal();

					passport_rejected = false;
					passport_accepted = false;

				}*/




}



void Game::dragSprite(sf::Sprite* sprite)
{
	if (sprite != nullptr)
	{
		sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
		sf::Vector2f mouse_positionf = static_cast<sf::Vector2f>(mouse_position);



		sf::Vector2f drag_position = mouse_positionf - mouseOffset;
		sprite->setPosition(drag_position.x, drag_position.y);
	}
}


void Game::update(float dt)
{

	dragSprite(dragged);
	acceptStampSprite.setPosition(passport->getPosition().x + (passport->getLocalBounds().width / 2) - (acceptStampSprite.getLocalBounds().width / 2), passport->getPosition().y + (passport->getLocalBounds().height / 2) - (acceptStampSprite.getLocalBounds().height / 2));
	rejectStampSprite.setPosition(passport->getPosition().x + (passport->getLocalBounds().width / 2) - (rejectStampSprite.getLocalBounds().width / 2), passport->getPosition().y + (passport->getLocalBounds().height / 2) - (rejectStampSprite.getLocalBounds().height / 2));

}

void Game::render()
{
	window.draw(background);

	switch (state) {
	case menu:
		window.draw(menuText);
		//render menu
		break;
	case playing:
		//render game

		window.draw(*character);
		window.draw(*passport);
		if (passport_accepted)
		{
			window.draw(acceptStampSprite);
		}
		if (passport_rejected)
		{
			window.draw(rejectStampSprite);
		}
		window.draw(acceptButtonSprite);
		window.draw(rejectButtonSprite);
		//for (lives)
		if (lives > 0)
			for (int i = 0; i < lives; i++)
			{
				livesSprite.setPosition(window.getSize().x - 75 - livesSprite.getLocalBounds().width * i - 25 * i, livesSprite.getLocalBounds().height);
				window.draw(livesSprite);

			}

		break;
	case gameOver:
		//render game over screen
		window.draw(gameOverText);
		break;
	}

	//switch (state) {
	//case menu:
	//	//render menu
	//	break;
	//case playing:
	//	//render game
	//	break;
	//case gameOver:
	//	//render game over screen
	//	break;
	//}



	/*window.draw(background);
	window.draw(*character);
	window.draw(*passport);
	if (passport_accepted)
	{
		window.draw(acceptStampSprite);
	}
	if (passport_rejected)
	{
		window.draw(rejectStampSprite);
	}
	window.draw(acceptButtonSprite);
	window.draw(rejectButtonSprite);

	if (lives > 0)
		for (int i = 0; i < lives; i++)
		{
			livesSprite.setPosition(window.getSize().x - 75 - livesSprite.getLocalBounds().width * i - 25 * i, livesSprite.getLocalBounds().height);
			window.draw(livesSprite);

		}*/

}

void Game::mouseClicked(sf::Event event)
{
	//get the click position
	sf::Vector2i click = sf::Mouse::getPosition(window);



}



void Game::keyPressed(sf::Event event)
{

}

