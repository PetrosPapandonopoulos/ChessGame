#include "Board.h"
#include <string>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#define MAIN_WINDOW_SIZE        900
#define CHOICE_WINDOW_SIZE      400

void windowManager();

void windowCycle(sf::RenderWindow &, sf::Sprite *, sf::Texture *, sf::Vector2f);

void loadSprites(sf::Sprite *, sf::Texture *, sf::Vector2f);

void drawTiles(sf::RenderWindow &, sf::Vector2f);

void drawBoardPieces(sf::RenderWindow &, sf::Sprite *, const Chess::Board &);

void placeAPieceBack(sf::Sprite *, const Chess::Board &, sf::Vector2i, sf::Vector2f);

void setNewPosition(sf::Sprite *, const Chess::Board &, sf::Vector2i, sf::Vector2i, sf::Vector2f);

bool checkBounds(sf::Vector2i);

bool checkTurn(const Chess::Board &, sf::Vector2i);

Chess::Type getAChoiceWindow(sf::Texture *, Chess::Color);

void changeSprite(sf::Texture *, sf::Sprite *, Chess::Color, const Chess::Board &, sf::Vector2i, Chess::Type);

int main() {
    
    windowManager();
    return 0;
}

void windowManager() {
    sf::RenderWindow window(sf::VideoMode(MAIN_WINDOW_SIZE, MAIN_WINDOW_SIZE), "Chess game", sf::Style::Close);
    sf::Sprite piecesSprites[32];
    sf::Texture PiecesTextures[12];
    sf::Vector2f tileDim(window.getSize().x / 8.0, window.getSize().y / 8.0);
    sf::Image icon;
    
    icon.loadFromFile("Sprites/icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    
    loadSprites(piecesSprites, PiecesTextures, tileDim);
    
    windowCycle(window, piecesSprites, PiecesTextures, tileDim);
    
}

void windowCycle(sf::RenderWindow &window, sf::Sprite *piecesSprites, sf::Texture *chessPiecesTexture,
                 sf::Vector2f tileDim) {
    
    Chess::Board mainBoard;
    bool MovingAPiece = false;
    
    sf::Vector2i pieceLastPosition;
    
    
    while (window.isOpen()) {
        
        sf::Event event{};
        
        while (window.pollEvent(event)) {
            
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && window.hasFocus()) {
                
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                sf::Vector2i mousePositionOnBoard(mousePosition.x / ((int) tileDim.x),
                                                  mousePosition.y / ((int) tileDim.y));
                
                if (!mainBoard.isEmpty(mousePositionOnBoard.y, mousePositionOnBoard.x)) {
                    if (checkTurn(mainBoard, mousePositionOnBoard)) {
                        if (!MovingAPiece) {
                            MovingAPiece = true;
                            pieceLastPosition = mousePositionOnBoard;
                        }
                    }
                }
                
                if (MovingAPiece) {
                    //drag piece with cursor
                    int index = mainBoard.getNumOfSprite(pieceLastPosition.y, pieceLastPosition.x);
                    float newX = mousePosition.x - tileDim.x / 2;
                    float newY = mousePosition.y - tileDim.y / 2;
                    piecesSprites[index].setPosition(newX, newY);
                }
            }
            
            if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && window.hasFocus() && MovingAPiece) {
                
                MovingAPiece = false;
                
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                sf::Vector2i mousePositionOnBoard(mousePosition.x / ((int) tileDim.x),
                                                  mousePosition.y / ((int) tileDim.y));
                
                if (checkBounds(mousePositionOnBoard)) {
                    
                    if (mainBoard.move(pieceLastPosition.y, pieceLastPosition.x, mousePositionOnBoard.y,
                                       mousePositionOnBoard.x)) {
                        
                        setNewPosition(piecesSprites, mainBoard, mousePositionOnBoard, mousePosition, tileDim);
                        
                        Chess::Color result = mainBoard.checkForPromotion();
                        
                        if (result == Chess::Color::Black || result == Chess::Color::White) {
                            Chess::Type ch = getAChoiceWindow(chessPiecesTexture, result);
                            changeSprite(chessPiecesTexture, piecesSprites, result, mainBoard, mousePositionOnBoard, ch);
                            mainBoard.promote({mousePositionOnBoard.y, mousePositionOnBoard.x}, ch);
                        }
                        
                        mainBoard.nextTurn();
                    }
                    else {
                        placeAPieceBack(piecesSprites, mainBoard, pieceLastPosition, tileDim);
                    }
                }
                else {
                    placeAPieceBack(piecesSprites, mainBoard, pieceLastPosition, tileDim);
                }
            }
        }
        
        window.clear(sf::Color::Black);
        
        drawTiles(window, tileDim);
        
        drawBoardPieces(window, piecesSprites, mainBoard);
        
        window.display();
    }
    
}

void loadSprites(sf::Sprite *piecesSprites, sf::Texture *chessPiecesTexture, sf::Vector2f tileDim) {
    
    //load textures
    for (int i = 0; i < 12; i++) {
        chessPiecesTexture[i].loadFromFile("Sprites/tile" + std::to_string(i) + ".png");
        chessPiecesTexture[i].setSmooth(true);
    }
    
    //black pieces
    
    //rook
    piecesSprites[0].setTexture(chessPiecesTexture[0]);
    piecesSprites[0].setPosition(sf::Vector2f(tileDim.x * 0, 0.f));
    
    //horse
    piecesSprites[1].setTexture(chessPiecesTexture[1]);
    piecesSprites[1].setPosition(sf::Vector2f(tileDim.x * 1, 0.f));
    
    //bishop
    piecesSprites[2].setTexture(chessPiecesTexture[2]);
    piecesSprites[2].setPosition(sf::Vector2f(tileDim.x * 2, 0.f));
    
    //queen
    piecesSprites[3].setTexture(chessPiecesTexture[3]);
    piecesSprites[3].setPosition(sf::Vector2f(tileDim.x * 3, 0.f));
    
    //king
    piecesSprites[4].setTexture(chessPiecesTexture[4]);
    piecesSprites[4].setPosition(sf::Vector2f(tileDim.x * 4, 0.f));
    
    //bishop
    piecesSprites[5].setTexture(chessPiecesTexture[2]);
    piecesSprites[5].setPosition(sf::Vector2f(tileDim.x * 5, 0.f));
    
    //horse
    piecesSprites[6].setTexture(chessPiecesTexture[1]);
    piecesSprites[6].setPosition(sf::Vector2f(tileDim.x * 6, 0.f));
    
    //rook
    piecesSprites[7].setTexture(chessPiecesTexture[0]);
    piecesSprites[7].setPosition(sf::Vector2f(tileDim.x * 7, 0.f));
    
    //pawns
    for (int i = 0; i < 8; i++) {
        piecesSprites[8 + i].setTexture(chessPiecesTexture[5]);
        piecesSprites[8 + i].setPosition(sf::Vector2f(tileDim.x * (float) i, tileDim.y));
    }
    
    
    //white pieces
    
    //rook
    piecesSprites[16].setTexture(chessPiecesTexture[6]);
    piecesSprites[16].setPosition(sf::Vector2f(tileDim.x * 0, tileDim.y * 7));
    
    //horse
    piecesSprites[17].setTexture(chessPiecesTexture[7]);
    piecesSprites[17].setPosition(sf::Vector2f(tileDim.x * 1, tileDim.y * 7));
    
    //bishop
    piecesSprites[18].setTexture(chessPiecesTexture[8]);
    piecesSprites[18].setPosition(sf::Vector2f(tileDim.x * 2, tileDim.y * 7));
    
    //queen
    piecesSprites[19].setTexture(chessPiecesTexture[9]);
    piecesSprites[19].setPosition(sf::Vector2f(tileDim.x * 3, tileDim.y * 7));
    
    //king
    piecesSprites[20].setTexture(chessPiecesTexture[10]);
    piecesSprites[20].setPosition(sf::Vector2f(tileDim.x * 4, tileDim.y * 7));
    
    //bishop
    piecesSprites[21].setTexture(chessPiecesTexture[8]);
    piecesSprites[21].setPosition(sf::Vector2f(tileDim.x * 5, tileDim.y * 7));
    
    //horse
    piecesSprites[22].setTexture(chessPiecesTexture[7]);
    piecesSprites[22].setPosition(sf::Vector2f(tileDim.x * 6, tileDim.y * 7));
    
    //rook
    piecesSprites[23].setTexture(chessPiecesTexture[6]);
    piecesSprites[23].setPosition(sf::Vector2f(tileDim.x * 7, tileDim.y * 7));
    
    //pawns
    for (int i = 0; i < 8; i++) {
        piecesSprites[24 + i].setTexture(chessPiecesTexture[11]);
        piecesSprites[24 + i].setPosition(sf::Vector2f(tileDim.x * i, tileDim.y * 6));
    }
    
    for (int i = 0; i < 32; i++) {
        piecesSprites[i].setScale(sf::Vector2f(tileDim.x / piecesSprites[i].getLocalBounds().width,
                                               tileDim.y / piecesSprites[i].getLocalBounds().height));
    }
}

void drawTiles(sf::RenderWindow &window, sf::Vector2f tileDim) {
    
    sf::RectangleShape square(sf::Vector2f(tileDim.x, tileDim.y));
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i % 2 == j % 2) {
                square.setFillColor(sf::Color(238, 238, 213));
            }
            else {
                square.setFillColor(sf::Color(148, 118, 93));
            }
            square.setPosition(sf::Vector2f(tileDim.x * i, tileDim.y * j));
            window.draw(square);
        }
    }
}

void drawBoardPieces(sf::RenderWindow &window, sf::Sprite *piecesSprites, const Chess::Board &mainBoard) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (!mainBoard.isEmpty(i, j)) {
                window.draw(piecesSprites[mainBoard.getNumOfSprite(i, j)]);
            }
        }
    }
}

void placeAPieceBack(sf::Sprite *piecesSprites, const Chess::Board &mainBoard, sf::Vector2i pieceLastPosition,
                     sf::Vector2f tileDim) {
    int index = mainBoard.getNumOfSprite(pieceLastPosition.y, pieceLastPosition.x);
    float newX = pieceLastPosition.x * tileDim.x;
    float newY = pieceLastPosition.y * tileDim.y;
    piecesSprites[index].setPosition(newX, newY);
}

void setNewPosition(sf::Sprite *piecesSprites, const Chess::Board &mainBoard, sf::Vector2i mousePositionOnBoard,
                    sf::Vector2i mousePosition, sf::Vector2f tileDim) {
    int index = mainBoard.getNumOfSprite(mousePositionOnBoard.y, mousePositionOnBoard.x);
    float newX = (mousePosition.x / ((int) tileDim.x)) * tileDim.x;
    float newY = (mousePosition.y / ((int) tileDim.y)) * tileDim.y;
    piecesSprites[index].setPosition(newX, newY);
}

bool checkBounds(sf::Vector2i mousePositionOnBoard) {
    return mousePositionOnBoard.x >= 0 && mousePositionOnBoard.x < 8 && mousePositionOnBoard.y >= 0 &&
           mousePositionOnBoard.y < 8;
}

bool checkTurn(const Chess::Board &mainBoard, sf::Vector2i mousePositionOnBoard) {
    return mainBoard.getColor(mousePositionOnBoard.y, mousePositionOnBoard.x) == mainBoard.getWhoseTurn();
}

Chess::Type getAChoiceWindow(sf::Texture *PiecesTextures, Chess::Color color) {
    sf::RenderWindow window(sf::VideoMode(CHOICE_WINDOW_SIZE, 112), "Choose a Piece", sf::Style::Close);
    sf::Vector2f tileDim(window.getSize().x / 4.0, window.getSize().y);
    sf::Sprite piecesSprites[4];
    sf::Image icon;
    icon.loadFromFile("Sprites/icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    if (color == Chess::Color::Black) {
        for (int i = 0; i < 4; i++) {
            piecesSprites[i].setTexture(PiecesTextures[i]);
            piecesSprites[i].setPosition(sf::Vector2f(tileDim.x * i, 0.f));
        }
    }
    else {
        for (int i = 0; i < 4; i++) {
            piecesSprites[i].setTexture(PiecesTextures[i + 6]);
            piecesSprites[i].setPosition(sf::Vector2f(tileDim.x * i, 0.f));
        }
    }
    
    while (window.isOpen()) {
        
        sf::Event event{};
        
        while (window.pollEvent(event)) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && window.hasFocus()) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                sf::Vector2i mousePositionOnBoard(mousePosition.x / ((int) tileDim.x),
                                                  mousePosition.y / ((int) tileDim.y));
                
                std::cout << mousePositionOnBoard.x + 1 << std::endl;
                
                if (mousePositionOnBoard.x == 0) {
                    std::cout << "User choose Rook!" << std::endl;
                    window.close();
                    return Chess::Type::Rook;
                }
                else if (mousePositionOnBoard.x == 1) {
                    std::cout << "User choose Horse!" << std::endl;
                    window.close();
                    return Chess::Type::Horse;
                }
                else if (mousePositionOnBoard.x == 2) {
                    std::cout << "User choose Bishop!" << std::endl;
                    window.close();
                    return Chess::Type::Bishop;
                }
                else if (mousePositionOnBoard.x == 3) {
                    window.close();
                    std::cout << "User choose Queen!" << std::endl;
                    return Chess::Type::Queen;
                }
            }
        }
        
        if (color == Chess::Color::Black) {
            window.clear(sf::Color(238, 238, 213));
        }
        else {
            window.clear(sf::Color(148, 118, 93));
        }
        
        for (const auto &piecesSprite : piecesSprites) {
            window.draw(piecesSprite);
        }
        
        window.display();
    }
    
    return Chess::Type::Queen;
}

void changeSprite(sf::Texture *chessPiecesTexture, sf::Sprite *piecesSprites, Chess::Color result,
                  const Chess::Board &mainBoard, sf::Vector2i mousePositionOnBoard, Chess::Type ch) {
    
    int index = mainBoard.getNumOfSprite(mousePositionOnBoard.y, mousePositionOnBoard.x);
    int colorIndex = result == Chess::Color::Black ? 0 : 6;
    
    switch (ch) {
        case Chess::Type::Rook: {
            piecesSprites[index].setTexture(chessPiecesTexture[0 + colorIndex]);
            break;
        }
        case Chess::Type::Horse: {
            piecesSprites[index].setTexture(chessPiecesTexture[1 + colorIndex]);
            break;
        }
        case Chess::Type::Bishop: {
            piecesSprites[index].setTexture(chessPiecesTexture[2 + colorIndex]);
            break;
        }
        case Chess::Type::Queen: {
            piecesSprites[index].setTexture(chessPiecesTexture[3 + colorIndex]);
            break;
        }
        default: {
        
        }
    }
}