#include "Menu.h"

Menu::Menu()
{
	SetPause(false);
	SetScale(2);
	if (!m_buttonTexture.loadFromFile("images/wood.png")) {
		perror("failed to load texture");
	}

	m_startButton.setTexture(m_buttonTexture);
	m_startButton.setScale(m_scale / 2, m_scale / 2);
	m_startButton.setTextureRect(IntRect(0, 200, 456, 112));

	m_newGameButton.setTexture(m_buttonTexture);
	m_newGameButton.setScale(m_scale / 2, m_scale / 2);
	m_newGameButton.setTextureRect(IntRect(0, 200, 456, 112));

	m_quitButton.setTexture(m_buttonTexture);
	m_quitButton.setScale(m_scale / 2, m_scale / 2);
	m_quitButton.setTextureRect(IntRect(0, 200, 456, 112));

	if (!m_font.loadFromFile("fonts/PetitFormalScript-Regular.ttf")) {
		perror("failed to load font");
	}

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
}

Menu::Menu(double a_scale)
{
	SetPause(false);
	SetScale(a_scale);
	if (!m_buttonTexture.loadFromFile("images/wood.png")) {
		perror("failed to load texture");
	}

	m_startButton.setTexture(m_buttonTexture);
	m_startButton.setScale(m_scale / 2, m_scale / 2);
	m_startButton.setTextureRect(IntRect(0, 200, 456, 112));

	m_newGameButton.setTexture(m_buttonTexture);
	m_newGameButton.setScale(m_scale / 2, m_scale / 2);
	m_newGameButton.setTextureRect(IntRect(0, 200, 456, 112));

	m_quitButton.setTexture(m_buttonTexture);
	m_quitButton.setScale(m_scale / 2, m_scale / 2);
	m_quitButton.setTextureRect(IntRect(0, 200, 456, 112));

	if (!m_font.loadFromFile("fonts/PetitFormalScript-Regular.ttf")) {
		perror("failed to load font");
	}

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

void Menu::OpenStartMenu(RenderWindow& a_win)
{
	m_startButton.setPosition(112 * m_scale, 112 * m_scale + 28 * m_scale);
	m_quitButton.setPosition(112 * m_scale, 112 * m_scale + 140 * m_scale);

	DrawStartButton(a_win);
	DrawQuitButton(a_win);
}

void Menu::OpenPauseMenu(RenderWindow& a_win)
{
	m_newGameButton.setPosition(112 * m_scale, 112 * m_scale + 28 * m_scale);
	m_quitButton.setPosition(112 * m_scale, 112 * m_scale + 140 * m_scale);

	DrawNewGameButton(a_win);
	DrawQuitButton(a_win);
}

void Menu::CloseMenu()
{
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

bool Menu::StartButtonClicked(const int a_x, const int a_y)
{
	if (m_startButton.getGlobalBounds().contains(a_x, a_y)) {
		return true;
	}

	return false;
}

bool Menu::NewGameButtonClicked(const int a_x, const int a_y)
{
	if (m_newGameButton.getGlobalBounds().contains(a_x, a_y)) {
		return true;
	}

	return false;
}

bool Menu::QuitButtonClicked(const int a_x, const int a_y)
{
	if (m_quitButton.getGlobalBounds().contains(a_x, a_y)) {
		return true;
	}

	return false;
}
