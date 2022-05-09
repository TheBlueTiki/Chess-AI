#include "Menu.h"

Menu::Menu()
{
	SetPause(false);
	SetScale(2);

	//load the button texture
	if (!m_buttonTexture.loadFromFile("images/wood.png")) {
		perror("failed to load texture");
	}

	//set button textures
	m_startButton.setTexture(m_buttonTexture);
	m_startButton.setScale(m_scale / 2, m_scale / 2);
	m_startButton.setTextureRect(IntRect(0, 200, 456, 112));

	m_newGameButton.setTexture(m_buttonTexture);
	m_newGameButton.setScale(m_scale / 2, m_scale / 2);
	m_newGameButton.setTextureRect(IntRect(0, 200, 456, 112));

	m_quitButton.setTexture(m_buttonTexture);
	m_quitButton.setScale(m_scale / 2, m_scale / 2);
	m_quitButton.setTextureRect(IntRect(0, 200, 456, 112));

	//load font
	if (!m_font.loadFromFile("fonts/PetitFormalScript-Regular.ttf")) {
		perror("failed to load font");
	}

	//set texts
	m_startButtonText.setFont(m_font);
	m_startButtonText.setString("Play");
	m_startButtonText.setScale(m_scale, m_scale);
	m_startButtonText.setFillColor(Color(255, 255, 255));
	m_startButtonText.setOutlineColor(Color(150, 150, 150));
	m_startButtonText.setOutlineThickness(0.25);

	m_newGameButtonText.setFont(m_font);
	m_newGameButtonText.setString("New Game");
	m_newGameButtonText.setScale(m_scale, m_scale);
	m_newGameButtonText.setFillColor(Color(255, 255, 255));
	m_newGameButtonText.setOutlineColor(Color(150, 150, 150));
	m_newGameButtonText.setOutlineThickness(0.25);

	m_quitButtonText.setFont(m_font);
	m_quitButtonText.setString("Quit");
	m_quitButtonText.setScale(m_scale, m_scale);
	m_quitButtonText.setFillColor(Color(255, 255, 255));
	m_quitButtonText.setOutlineColor(Color(150, 150, 150));
	m_quitButtonText.setOutlineThickness(0.25);

	m_checkmateText.setFont(m_font);
	m_checkmateText.setString("Checkmate!");
	m_checkmateText.setScale(m_scale, m_scale);
	m_checkmateText.setFillColor(Color(255, 255, 255));
	m_checkmateText.setOutlineColor(Color(150, 150, 150));
	m_checkmateText.setOutlineThickness(0.25);

	m_blackWinText.setFont(m_font);
	m_blackWinText.setString("Black Wins");
	m_blackWinText.setScale(m_scale, m_scale);
	m_blackWinText.setFillColor(Color(255, 255, 255));
	m_blackWinText.setOutlineColor(Color(150, 150, 150));
	m_blackWinText.setOutlineThickness(0.25);

	m_whiteWinText.setFont(m_font);
	m_whiteWinText.setString("White Wins");
	m_whiteWinText.setScale(m_scale, m_scale);
	m_whiteWinText.setFillColor(Color(255, 255, 255));
	m_whiteWinText.setOutlineColor(Color(150, 150, 150));
	m_whiteWinText.setOutlineThickness(0.25);

	//set boarders
	m_startButtonBorder.setSize(Vector2f(m_startButton.getGlobalBounds().width, m_startButton.getGlobalBounds().height));
	m_startButtonBorder.setFillColor(Color(0, 0, 0, 0));
	m_startButtonBorder.setOutlineColor(Color(255, 255, 255));
	m_startButtonBorder.setOutlineThickness(2);
	m_newGameButtonBorder = m_startButtonBorder;
	m_quitButtonBorder = m_startButtonBorder;

	//set background fade
	m_fade.setSize(Vector2f(453 * m_scale, 453 * m_scale));
	m_fade.setFillColor(Color(255, 255, 255, 128));
	
}

Menu::Menu(double a_scale)
{
	SetPause(false);
	SetScale(a_scale);

	//load the button texture
	if (!m_buttonTexture.loadFromFile("images/wood.png")) {
		perror("failed to load texture");
	}

	//set button textures
	m_startButton.setTexture(m_buttonTexture);
	m_startButton.setScale(m_scale / 2, m_scale / 2);
	m_startButton.setTextureRect(IntRect(0, 200, 456, 112));

	m_newGameButton.setTexture(m_buttonTexture);
	m_newGameButton.setScale(m_scale / 2, m_scale / 2);
	m_newGameButton.setTextureRect(IntRect(0, 200, 456, 112));

	m_quitButton.setTexture(m_buttonTexture);
	m_quitButton.setScale(m_scale / 2, m_scale / 2);
	m_quitButton.setTextureRect(IntRect(0, 200, 456, 112));

	//load font
	if (!m_font.loadFromFile("fonts/PetitFormalScript-Regular.ttf")) {
		perror("failed to load font");
	}

	//set texts
	m_startButtonText.setFont(m_font);
	m_startButtonText.setString("Play");
	m_startButtonText.setScale(m_scale, m_scale);
	m_startButtonText.setFillColor(Color(255, 255, 255));
	m_startButtonText.setOutlineColor(Color(150, 150, 150));
	m_startButtonText.setOutlineThickness(0.25);

	m_newGameButtonText.setFont(m_font);
	m_newGameButtonText.setString("New Game");
	m_newGameButtonText.setScale(m_scale, m_scale);
	m_newGameButtonText.setFillColor(Color(255, 255, 255));
	m_newGameButtonText.setOutlineColor(Color(150, 150, 150));
	m_newGameButtonText.setOutlineThickness(0.25);

	m_quitButtonText.setFont(m_font);
	m_quitButtonText.setString("Quit");
	m_quitButtonText.setScale(m_scale, m_scale);
	m_quitButtonText.setFillColor(Color(255, 255, 255));
	m_quitButtonText.setOutlineColor(Color(150, 150, 150));
	m_quitButtonText.setOutlineThickness(0.25);

	m_checkmateText.setFont(m_font);
	m_checkmateText.setString("Checkmate!");
	m_checkmateText.setScale(m_scale, m_scale);
	m_checkmateText.setFillColor(Color(255, 255, 255));
	m_checkmateText.setOutlineColor(Color(150, 150, 150));
	m_checkmateText.setOutlineThickness(0.25);

	m_blackWinText.setFont(m_font);
	m_blackWinText.setString("Black Wins");
	m_blackWinText.setScale(m_scale, m_scale);
	m_blackWinText.setFillColor(Color(255, 255, 255));
	m_blackWinText.setOutlineColor(Color(150, 150, 150));
	m_blackWinText.setOutlineThickness(0.25);

	m_whiteWinText.setFont(m_font);
	m_whiteWinText.setString("White Wins");
	m_whiteWinText.setScale(m_scale, m_scale);
	m_whiteWinText.setFillColor(Color(255, 255, 255));
	m_whiteWinText.setOutlineColor(Color(150, 150, 150));
	m_whiteWinText.setOutlineThickness(0.25);

	//set boarders
	m_startButtonBorder.setSize(Vector2f(m_startButton.getGlobalBounds().width, m_startButton.getGlobalBounds().height));
	m_startButtonBorder.setFillColor(Color(0, 0, 0, 0));
	m_startButtonBorder.setOutlineColor(Color(255, 255, 255));
	m_startButtonBorder.setOutlineThickness(2);
	m_newGameButtonBorder = m_startButtonBorder;
	m_quitButtonBorder = m_startButtonBorder;

	//set background fade
	m_fade.setSize(Vector2f(453 * m_scale, 453 * m_scale));
	m_fade.setFillColor(Color(175, 175, 175, 128));
}

double Menu::GetScale()
{
	return m_scale;
}

bool Menu::IsPaused()
{
	return m_isPaused;
}

void Menu::SetScale(double a_scale)
{
	m_scale = a_scale;
}

void Menu::SetPause(bool a_isPaused)
{
	m_isPaused = a_isPaused;
}

/**/
/*
Menu::OpenStartMenu()

NAME

		Menu::OpenStartMenu - displays the elements of the start menu

SYNOPSIS

		void Menu::OpenStartMenu(RenderWindow& a_win);
			a_win  --> the Window object that displays the visual components of the game

DESCRIPTION

		This function will calculate the positioning of the start menu buttons, then draw the backgound
		fade and buttons

RETURNS

		void

*/
/**/
void Menu::OpenStartMenu(RenderWindow& a_win)
{
	//position the buttons
	m_startButton.setPosition(112 * m_scale, 112 * m_scale + 28 * m_scale);
	m_quitButton.setPosition(112 * m_scale, 112 * m_scale + 140 * m_scale);

	//position the boarders
	m_startButtonBorder.setPosition(112 * m_scale, 112 * m_scale + 28 * m_scale);
	m_quitButtonBorder.setPosition(112 * m_scale, 112 * m_scale + 140 * m_scale);
	
	//draw menu elements
	a_win.draw(m_fade);
	DrawStartButton(a_win);
	DrawQuitButton(a_win);
	a_win.draw(m_startButtonBorder);
	a_win.draw(m_quitButtonBorder);
}
/*void Menu::OpenStartMenu(RenderWindow& a_win)*/

/**/
/*
Menu::OpenPauseMenu()

NAME

		Menu::OpenPauseMenu - displays the elements of the pause menu

SYNOPSIS

		void Menu::OpenPauseMenu(RenderWindow& a_win);
			a_win  --> the Window object that displays the visual components of the game

DESCRIPTION

		This function will calculate the positioning of the pause menu buttons, then draw the backgound
		fade and buttons

RETURNS

		void

*/
/**/
void Menu::OpenPauseMenu(RenderWindow& a_win)
{
	//position the buttons
	m_newGameButton.setPosition(112 * m_scale, 112 * m_scale + 28 * m_scale);
	m_quitButton.setPosition(112 * m_scale, 112 * m_scale + 140 * m_scale);

	//position the boarders
	m_newGameButtonBorder.setPosition(112 * m_scale, 112 * m_scale + 28 * m_scale);
	m_quitButtonBorder.setPosition(112 * m_scale, 112 * m_scale + 140 * m_scale);

	//draw menu elements
	a_win.draw(m_fade);
	DrawNewGameButton(a_win);
	DrawQuitButton(a_win);
	a_win.draw(m_newGameButtonBorder);
	a_win.draw(m_quitButtonBorder);
}
/*void Menu::OpenPauseMenu(RenderWindow& a_win)*/

/**/
/*
Menu::CloseMenu()

NAME

		Menu::CloseMenu - closes any menus that are open

SYNOPSIS

		void Menu::CloseMenu();

DESCRIPTION

		This function will remove all menu elements from the screen

RETURNS

		void

*/
/**/
void Menu::CloseMenu()
{
	//move menu elements off the screen
	m_startButton.setPosition(-200, -200);
	m_startButtonText.setPosition(-200, -200);

	m_newGameButton.setPosition(-200, -200);
	m_newGameButtonText.setPosition(-200, -200);

	m_quitButton.setPosition(-200, -200);
	m_quitButtonText.setPosition(-200, -200);

	m_checkmateText.setPosition(-200, -200);
	m_blackWinText.setPosition(-200, -200);
	m_whiteWinText.setPosition(-200, -200);
}
/*void Menu::CloseMenu()*/

/**/
/*
Menu::DrawStartButton()

NAME

		Menu::DrawStartButton - displays the elements of the start button

SYNOPSIS

		void Menu::DrawStartButton(RenderWindow& a_win);
			a_win  --> the Window object that displays the visual components of the game

DESCRIPTION

		This function will calculate the positioning of the button text and display the button.

RETURNS

		void

*/
/**/
void Menu::DrawStartButton(RenderWindow& a_win)
{
	//calculate text position
	double tx, ty;
	tx = m_startButton.getPosition().x + m_startButton.getGlobalBounds().width / 2 - m_startButtonText.getGlobalBounds().width / 2;
	ty = m_startButton.getPosition().y + m_startButton.getGlobalBounds().height / 2 - m_startButtonText.getGlobalBounds().height / 2;

	m_startButtonText.setPosition(tx, ty);

	//draw button
	a_win.draw(m_startButton);
	a_win.draw(m_startButtonText);
}
/*void Menu::DrawStartButton(RenderWindow& a_win)*/

/**/
/*
Menu::DrawNewGameButton()

NAME

		Menu::DrawNewGameButton - displays the elements of the new game button

SYNOPSIS

		void Menu::DrawNewGameButton(RenderWindow& a_win);
			a_win  --> the Window object that displays the visual components of the game

DESCRIPTION

		This function will calculate the positioning of the button text and display the button.

RETURNS

		void

*/
/**/
void Menu::DrawNewGameButton(RenderWindow& a_win)
{
	//calculate text position
	double tx, ty;
	tx = m_newGameButton.getPosition().x + m_newGameButton.getGlobalBounds().width / 2 - m_newGameButtonText.getGlobalBounds().width / 2;
	ty = m_newGameButton.getPosition().y + m_newGameButton.getGlobalBounds().height / 2 - m_newGameButtonText.getGlobalBounds().height / 2;

	m_newGameButtonText.setPosition(tx, ty);

	//draw button
	a_win.draw(m_newGameButton);
	a_win.draw(m_newGameButtonText);
}
/*void Menu::DrawNewGameButton(RenderWindow& a_win)*/

/**/
/*
Menu::DrawQuitButton()

NAME

		Menu::DrawQuitButton - displays the elements of the quit button

SYNOPSIS

		void Menu::DrawQuitButton(RenderWindow& a_win);
			a_win  --> the Window object that displays the visual components of the game

DESCRIPTION

		This function will calculate the positioning of the button text and display the button.

RETURNS

		void

*/
/**/
void Menu::DrawQuitButton(RenderWindow& a_win)
{
	//calculate text position
	double tx, ty;
	tx = m_quitButton.getPosition().x + m_quitButton.getGlobalBounds().width / 2 - m_quitButtonText.getGlobalBounds().width / 2;
	ty = m_quitButton.getPosition().y + m_quitButton.getGlobalBounds().height / 2 - m_quitButtonText.getGlobalBounds().height / 2;
	
	m_quitButtonText.setPosition(tx, ty);

	//draw button
	a_win.draw(m_quitButton);
	a_win.draw(m_quitButtonText);
}
/*void Menu::DrawQuitButton(RenderWindow& a_win)*/

/**/
/*
Menu::DrawBlackVictoryText()

NAME

		Menu::DrawBlackVictoryText - displays the text that declares the black player as the winner

SYNOPSIS

		void Menu::DrawBlackVictoryText(RenderWindow& a_win);
			a_win  --> the Window object that displays the visual components of the game

DESCRIPTION

		This function will calculate the positioning of the victory text and display it.

RETURNS

		void

*/
/**/
void Menu::DrawBlackVictoryText(RenderWindow& a_win)
{
	//calculate text position
	double tx, ty;
	tx = a_win.getSize().x / 2 - m_checkmateText.getGlobalBounds().width / 2;
	ty = 56 * m_scale;
	m_checkmateText.setPosition(tx, ty);

	tx = a_win.getSize().x / 2 - m_blackWinText.getGlobalBounds().width / 2;
	ty = 56 * m_scale + m_checkmateText.getGlobalBounds().height;
	m_blackWinText.setPosition(tx, ty);

	//draw text
	a_win.draw(m_checkmateText);
	a_win.draw(m_blackWinText);
}
/*void Menu::DrawBlackVictoryText(RenderWindow& a_win)*/

/**/
/*
Menu::DrawWhiteVictoryText()

NAME

		Menu::DrawWhiteVictoryText - displays the text that declares the white player as the winner

SYNOPSIS

		void Menu::DrawWhiteVictoryText(RenderWindow& a_win);
			a_win  --> the Window object that displays the visual components of the game

DESCRIPTION

		This function will calculate the positioning of the victory text and display it.

RETURNS

		void

*/
/**/
void Menu::DrawWhiteVictoryText(RenderWindow& a_win)
{
	//calculate text position
	double tx, ty;
	tx = a_win.getSize().x / 2 - m_checkmateText.getGlobalBounds().width / 2;
	ty = 56 * m_scale;
	m_checkmateText.setPosition(tx, ty);

	tx = a_win.getSize().x / 2 - m_whiteWinText.getGlobalBounds().width / 2;
	ty = 56 * m_scale + m_checkmateText.getGlobalBounds().height;
	m_whiteWinText.setPosition(tx, ty);

	//draw text
	a_win.draw(m_checkmateText);
	a_win.draw(m_whiteWinText);
}
/*void Menu::DrawWhiteVictoryText(RenderWindow& a_win)*/

/**/
/*
Menu::StartButtonClicked()

NAME

		Menu::StartButtonClicked - checks if the start button was clicked by the player

SYNOPSIS

		bool Menu::StartButtonClicked(const int a_x, const int a_y);
			a_x  --> the x coordinate of the mouse position
			a_y	 --> the y coordinate of the mouse position

DESCRIPTION

		This function will check if the mouse is positioned within the bounds of the
		button.

RETURNS

		Returns true if the mouse is positioned over the button, false if it is not.

*/
/**/
bool Menu::StartButtonClicked(const int a_x, const int a_y)
{
	//check if the mouse is positioned on the button
	if (m_startButton.getGlobalBounds().contains(a_x, a_y)) {
		return true;
	}

	return false;
}
/*bool Menu::StartButtonClicked(const int a_x, const int a_y)*/

/**/
/*
Menu::NewGameButtonClicked()

NAME

		Menu::NewGameButtonClicked - checks if the new game button was clicked by the player

SYNOPSIS

		bool Menu::NewGameButtonClicked(const int a_x, const int a_y);
			a_x  --> the x coordinate of the mouse position
			a_y	 --> the y coordinate of the mouse position

DESCRIPTION

		This function will check if the mouse is positioned within the bounds of the
		button.

RETURNS

		Returns true if the mouse is positioned over the button, false if it is not.

*/
/**/
bool Menu::NewGameButtonClicked(const int a_x, const int a_y)
{
	//check if the mouse is positioned on the button
	if (m_newGameButton.getGlobalBounds().contains(a_x, a_y)) {
		return true;
	}

	return false;
}
/*bool Menu::NewGameButtonClicked(const int a_x, const int a_y)*/

/**/
/*
Menu::QuitButtonClicked()

NAME

		Menu::QuitButtonClicked - checks if the quit button was clicked by the player

SYNOPSIS

		bool Menu::QuitButtonClicked(const int a_x, const int a_y);
			a_x  --> the x coordinate of the mouse position
			a_y	 --> the y coordinate of the mouse position

DESCRIPTION

		This function will check if the mouse is positioned within the bounds of the 
		button.

RETURNS

		Returns true if the mouse is positioned over the button, false if it is not.

*/
/**/
bool Menu::QuitButtonClicked(const int a_x, const int a_y)
{
	//check if the mouse is positioned on the button
	if (m_quitButton.getGlobalBounds().contains(a_x, a_y)) {
		return true;
	}

	return false;
}
/*bool Menu::QuitButtonClicked(const int a_x, const int a_y)*/
