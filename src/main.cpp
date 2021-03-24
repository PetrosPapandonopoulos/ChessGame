#include "WindowManager.h"

void windowCycle(WindowManager&);

int main() {
    WindowManager windowManager;
    windowCycle(windowManager);
    return 0;
}

void windowCycle(WindowManager& windowManager) {
    
    Chess::Board mainBoard;
    
    sf::Clock deltaClock;
    sf::Time dt = deltaClock.restart();
    
    sf::Vector2i pieceLastPosition;
    sf::Vector2<int> mousePositionOnBoard;
    
    int fadeTransparency = 255;
    
    bool canPromote = false;
    bool movingAPiece = false;
    bool someoneLost = false;
    
    
    while (window.isOpen()) {
        
        sf::Event event{};
        
        while (window.pollEvent(event)) {
            
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && window.hasFocus()) {
                buttonPressedAction(window, mainBoard, tileDim, piecesSprites, movingAPiece, pieceLastPosition,
                                    someoneLost);
            }
            
            if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && window.hasFocus() && movingAPiece) {
                mousePositionOnBoard = buttonUnPressedAction(window, mainBoard, tileDim, piecesSprites, movingAPiece,
                                                             pieceLastPosition, canPromote, moveSound);
            }
        }
        
        renderFrame(window, mainBoard, tileDim, piecesSprites, cordTipsSprites, fadeTransparency, dt, someoneLost);
        
        
        if (canPromote) {
            sf::Vector2i mainWindowCoordinates = window.getPosition();
            promote(mainBoard.checkForPromotion(), piecesTexture, piecesSprites, mainBoard, mousePositionOnBoard,
                    mainWindowCoordinates);
            canPromote = false;
        }
        
        dt = deltaClock.restart();
        
        if (checkForCheckMate(mainBoard, Chess::Color::White) && !someoneLost) {
            std::cout << "The white pieces won" << std::endl;
            someoneLost = true;
            
        }
        else if (checkForCheckMate(mainBoard, Chess::Color::Black) && !someoneLost) {
            std::cout << "The black pieces won" << std::endl;
            someoneLost = true;
        }
    }
    
}

