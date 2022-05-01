#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "Game.h"
#include "Menu.h"

using namespace sf;

int main()
{
    //graphical elements
    double m_scale = 3;
    Game m_game(56, m_scale);
    Menu m_menu(m_scale);
    RenderWindow m_window(VideoMode(453 * m_scale, 453 * m_scale), "Chess");
    
    //construct the board and pieces
    m_game.GeneratePieces();
    
    //gret the player in the console
    std::cout << "-=Welcome=-" << std::endl;

    //interactive elements
    bool m_start = false;
    float dx = 0, dy = 0;

    //open window
    while (m_window.isOpen()) {
        //mouse position
        Vector2i pos = Mouse::getPosition(m_window);
        Event event;

        while (m_window.pollEvent(event)) {
            //close
            if (event.type == Event::Closed) {
                std::cout << "-=Goodbye=-" << std::endl;
                m_window.close();
            }
            //pause
            else if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape && m_start && !m_game.HasWinner()) {
                    if (!m_menu.IsPaused()) {
                        m_menu.SetPause(true);
                    }
                    else {
                        m_menu.SetPause(false);
                        m_menu.CloseMenu();
                    }
                }
            }
        }

        //click/drag detection
        if (event.type == Event::MouseButtonPressed) {
            if (event.key.code == Mouse::Left) {
                //check for open menus
                if (!m_start || m_menu.IsPaused() || m_game.HasWinner()) {
                    //button click detection
                    if (m_menu.StartButtonClicked(pos.x, pos.y)) {
                        m_start = true;
                        m_menu.CloseMenu();
                        std::cout<< "-=New Round=-" <<std::endl;
                    }
                    else if (m_menu.NewGameButtonClicked(pos.x, pos.y)) {
                        m_game.ResetPieces();
                        m_menu.CloseMenu();
                        m_menu.SetPause(false);
                    }
                    else if (m_menu.QuitButtonClicked(pos.x, pos.y)) {
                        std::cout << "-=Goodbye=-" << std::endl;
                        m_window.close();
                    }
                }
                //check for held pieces
                else if(m_game.HasTurn()) {
                    m_game.CheckHeld(pos.x, pos.y, dx, dy);
                }
            }
        }

        //drop detection
        if (event.type == Event::MouseButtonReleased) {
            if (event.key.code == Mouse::Left && m_game.HasTurn()) {
                m_game.DropPiece();
            }
        }

        if (!m_game.HasTurn() && !m_game.HasWinner()) {
            //computer's turn
            m_game.ComputerTurn();
        }

        //update
        m_game.UpdatePiecePositions(pos.x, pos.y, dx, dy);

        //draw
        m_window.clear();
        m_game.DrawBoard(m_window);
        m_game.DrawPieces(m_window);

        //check if someone won the game
        if (m_game.HasWinner()) {
            //open the pause menu
            m_menu.OpenPauseMenu(m_window);

            //display the winner
            if (m_game.GetWinner() == "black") {
                m_menu.DrawBlackVictoryText(m_window);
            }
            else if (m_game.GetWinner() == "white") {
                m_menu.DrawWhiteVictoryText(m_window);
            }
        }
        //check if the game was started
        else if (!m_start) {
            m_menu.OpenStartMenu(m_window);
        }
        //ocheck if the game is paused
        else if (m_menu.IsPaused()) {
            m_menu.OpenPauseMenu(m_window);
        }

        m_window.display();
    }

    return 0;
}
