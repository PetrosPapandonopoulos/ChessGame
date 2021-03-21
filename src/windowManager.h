#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H
#define MAIN_WINDOW_SIZE        900
#define CHOICE_WINDOW_SIZE      400
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include <string>
#include <iostream>

void windowManager();

void windowCycle(sf::RenderWindow &window, sf::Sprite *piecesSprites, sf::Texture *piecesTexture,
                 sf::Vector2f tileDim);

void loadSprites(sf::Sprite *piecesSprites, sf::Texture *piecesTexture, sf::Vector2f tileDim);

void drawTiles(sf::RenderWindow &window, sf::Vector2f tileDim);

void drawBoardPieces(sf::RenderWindow &window, sf::Sprite *piecesSprites, const Chess::Board &mainBoard);

void drawCheckFadeEffect(sf::RenderWindow &window, sf::Vector2f tileDim, std::pair<int, int> kingCoordinates, int &alpha);

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
                           sf::Sprite *piecesSprites, sf::Texture *piecesTexture, bool &movingAPiece,
                           sf::Vector2i &pieceLastPosition, bool& canPromote);

void promote(Chess::Color result, sf::Texture *piecesTexture, sf::Sprite *piecesSprites, Chess::Board &mainBoard,
             sf::Vector2i mousePositionOnBoard);

bool checkForChecks(const Chess::Board& mainBoard, std::pair<int, int>& kingCoordinates);

#endif //WINDOWMANAGER_H
