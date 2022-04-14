//
//	Menu - handles all of the UI elements
//

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

class Menu {
private:
	double m_scale;
	bool m_isPaused;
	Texture m_buttonTexture;
	Sprite m_startButton, m_newGameButton, m_quitButton;
	Font m_font;
	Text m_startButtonText, m_newGameButtonText, m_quitButtonText, m_checkmateText, m_blackWinText, m_whiteWinText;
	RectangleShape m_fade;
public:
	//constructors
	Menu();
	Menu(double a_scale);

	//selectors
	double GetScale();
	bool IsPaused();

	//mutators
	void SetScale(double a_scale);
	void SetPause(bool a_isPaused);

	//menu displays
	void OpenStartMenu(RenderWindow& a_win);
	void OpenPauseMenu(RenderWindow& a_win);
	void CloseMenu();

	//button drawing
	void DrawStartButton(RenderWindow& a_win);
	void DrawNewGameButton(RenderWindow& a_win);
	void DrawQuitButton(RenderWindow& a_win);
	void DrawBlackVictoryText(RenderWindow& a_win);
	void DrawWhiteVictoryText(RenderWindow& a_win);

	//click detection
	bool StartButtonClicked(const int a_x, const int a_y);
	bool NewGameButtonClicked(const int a_x, const int a_y);
	bool QuitButtonClicked(const int a_x, const int a_y);
};