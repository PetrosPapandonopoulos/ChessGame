#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H
#define MAIN_WINDOW_SIZE        900
#define FONT_SIZE               MAIN_WINDOW_SIZE / 37.5
#define FONT_POS                MAIN_WINDOW_SIZE / 180
#define FONT_LETTERS_X          MAIN_WINDOW_SIZE / 45
#define FONT_LETTERS_Y          MAIN_WINDOW_SIZE / 30
#define SPRITE_SIZE             MAIN_WINDOW_SIZE / 10
#define BOARD_BLACK             sf::Color(148, 118, 93)
#define BOARD_WHITE             sf::Color(238, 238, 213)

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Board.h"
#include <string>
#include <iostream>


class WindowManager {
    private:
        sf::RenderWindow window;
        sf::Sprite *piecesSprites;
        sf::Texture *piecesTextures;
        sf::Text *cordTipsSprites;
        sf::Vector2f tileDim;
        Chess::Board mainBoard;
        int fadeTransparency = 255;
        sf::Image icon;
        sf::Font font;
        sf::SoundBuffer buffer;
        sf::Sound moveSound;
        bool canPromote;
        bool movingAPiece;
        bool someoneLost;
        
        void loadSprites();
        
        void loadCordTips();
        
        void drawTiles(sf::RenderWindow& renderWindow, std::pair<int, int> dimOnWindow) const;
        
        void drawATileRed(std::pair<int, int> tileCoordinates);
        
        void drawCordTips();
        
        void drawBoardPieces();
        
        void drawFadeEffect(std::pair<int, int> tileCoordinates);
        
        void checkAndDrawFadeEffect(sf::Time dt);
        
        void placeAPieceBack(sf::Vector2i pieceLastPosition);
    
        Chess::Type choiceWindow(Chess::Color color);
    
        bool checkForEitherChecks(std::pair<int, int> &kingCoordinates);
    
        void changeSprite(Chess::Color color, sf::Vector2i spriteIndexCoordinates, Chess::Type ch);
    
        bool checkForCheckMate(Chess::Color color);
        
        void promote(Chess::Color color, sf::Vector2i mousePositionOnBoard);
    
    public:
        WindowManager();
        
        void renderFrame(sf::Time dt);
    
        void setNewPositionStatic(sf::Vector2i newPosition);
    
        void setNewPosition(sf::Vector2i mousePosition, sf::Vector2i mousePositionOnBoard);
    
        bool checkBounds(sf::Vector2i mousePositionOnBoard);
    
        bool checkTurn(sf::Vector2i Coordinates);
    
        void findAndIndicateKing();
    
        sf::Vector2i buttonPressedAction(sf::Vector2i &pieceLastPosition);
    
        sf::Vector2i buttonUnPressedAction(sf::Vector2i &pieceLastPosition);
};

#endif WINDOWMANAGER_H