#include "WindowManager.h"
#include <windows.h>

void windowCycle(WindowManager &);

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow ){
    WindowManager windowManager;
    windowCycle(windowManager);
    return 0;
}

void windowCycle(WindowManager &windowManager) {
    sf::Clock deltaClock;
    sf::Time dt = deltaClock.restart();
    sf::Vector2i pieceLastPosition;
    sf::Vector2<int> mousePositionOnBoard;
    
    
    while (windowManager.windowIsOpen()) {
        
        sf::Event event{};
        
        while (windowManager.windowGetPollEvent(event)) {
            
            if (event.type == sf::Event::Closed) {
                windowManager.closeWindow();
            }
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && windowManager.windowHasFocus()) {
                windowManager.buttonPressedAction(pieceLastPosition);
            }
            
            if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && windowManager.windowHasFocus() &&
                windowManager.isMovingAPiece()) {
                mousePositionOnBoard = windowManager.buttonUnPressedAction(pieceLastPosition);
            }
        }
        
        windowManager.renderFrame(dt);
        
        if (windowManager.isCanPromote()) {
            windowManager.promote(mousePositionOnBoard);
            windowManager.setCanPromote(false);
        }
        
        dt = deltaClock.restart();
        
        if (windowManager.checkForCheckmate(Chess::Color::White) && !windowManager.isSomeoneLost()) {
            std::cout << "The white pieces won" << std::endl;
            windowManager.setSomeoneLost(true);
            
        }
        else if (windowManager.checkForCheckmate(Chess::Color::Black) && !windowManager.isSomeoneLost()) {
            std::cout << "The black pieces won" << std::endl;
            windowManager.setSomeoneLost(true);
        }
    
        if (windowManager.checkForDraw() && !windowManager.getIsDraw()){
            std::cout << "Its a draw" << std::endl;
            windowManager.setIsDraw(true);
        }
    }
    
}

