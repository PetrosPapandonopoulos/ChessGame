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
#include "Board.h"
#include <string>
#include <iostream>

void windowManager();

void windowCycle(sf::RenderWindow &window, sf::Sprite *piecesSprites, sf::Texture *piecesTexture,
                 sf::Vector2f tileDim, sf::Text *cordTipsSprites);

void
renderFrame(sf::RenderWindow &window, const Chess::Board &mainBoard, sf::Vector2f tileDim, sf::Sprite *piecesSprites,
            sf::Text *cordTipsSprites,  int &fadeTransparency, sf::Time dt);

void loadSprites(sf::Sprite *piecesSprites, sf::Texture *piecesTexture, sf::Vector2f tileDim);

void loadCordTips(sf::Text *cordTipsSprites, sf::Vector2f tileDim,  const sf::Font& font);

void drawCordTips(sf::RenderWindow &window, sf::Text *cordTipsSprites);

void drawTiles(sf::RenderWindow &window, sf::Vector2f tileDim);

void drawBoardPieces(sf::RenderWindow &window, sf::Sprite *piecesSprites, const Chess::Board &mainBoard);

void
drawFadeEffect(sf::RenderWindow &window, sf::Vector2f tileDim, std::pair<int, int> kingCoordinates,
               int &fadeTransparency);

void checkAndDrawFadeEffect(sf::RenderWindow &window, const Chess::Board &mainBoard, sf::Vector2f tileDim, sf::Time dt,
                            int &fadeTransparency);

void placeAPieceBack(sf::Sprite *piecesSprites, const Chess::Board &mainBoard, sf::Vector2i pieceLastPosition,
                     sf::Vector2f tileDim);

void setNewPosition(sf::Sprite *piecesSprites, const Chess::Board &mainBoard, sf::Vector2i mousePositionOnBoard,
                    sf::Vector2i mousePosition, sf::Vector2f tileDim);

bool checkBounds(sf::Vector2i mousePositionOnBoard);

bool checkTurn(const Chess::Board &mainBoard, sf::Vector2i mousePositionOnBoard);

Chess::Type getAChoiceWindow(sf::Texture *PiecesTextures, Chess::Color color);

void changeSprite(sf::Texture *piecesTexture, sf::Sprite *piecesSprites, Chess::Color result,
                  const Chess::Board &mainBoard, sf::Vector2i mousePositionOnBoard, Chess::Type ch);

sf::Vector2i buttonPressedAction(sf::RenderWindow &window, const Chess::Board &mainBoard, sf::Vector2f tileDim,
                                 sf::Sprite *piecesSprites, bool &movingAPiece, sf::Vector2i &pieceLastPosition);

sf::Vector2i buttonUnPressedAction(sf::RenderWindow &window, Chess::Board &mainBoard, sf::Vector2f tileDim,
                                   sf::Sprite *piecesSprites, bool &movingAPiece,
                                   sf::Vector2i &pieceLastPosition, bool &canPromote);

void promote(Chess::Color result, sf::Texture *piecesTexture, sf::Sprite *piecesSprites, Chess::Board &mainBoard,
             sf::Vector2i mousePositionOnBoard);

bool checkForChecks(const Chess::Board &mainBoard, std::pair<int, int> &kingCoordinates);

#endif //WINDOWMANAGER_H
