#include "windowManager.h"

void windowManager() {
    sf::RenderWindow window(sf::VideoMode(MAIN_WINDOW_SIZE, MAIN_WINDOW_SIZE), "Chess game", sf::Style::Close);
    sf::Sprite piecesSprites[32];
    sf::Texture PiecesTextures[12];
    sf::Vector2f tileDim(window.getSize().x / 8.0, window.getSize().y / 8.0);
    sf::Image icon;
    
    icon.loadFromFile("Sprites/icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    
    loadSprites(piecesSprites, PiecesTextures, tileDim);
    
    windowCycle(window, piecesSprites, PiecesTextures, tileDim);
}

void windowCycle(sf::RenderWindow &window, sf::Sprite *piecesSprites, sf::Texture *piecesTexture,
                 sf::Vector2f tileDim) {
    
    Chess::Board mainBoard;
    bool movingAPiece = false;
    sf::Vector2i pieceLastPosition;
    int alpha = 255;
    bool canPromote = false;
    sf::Vector2<int> mousePositionOnBoard;
    sf::Clock deltaClock;
    sf::Time dt = deltaClock.restart();
    
    
    while (window.isOpen()) {
        
        sf::Event event{};
        
        while (window.pollEvent(event)) {
            
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (canPromote) {
                promote(mainBoard.checkForPromotion(), piecesTexture, piecesSprites, mainBoard, mousePositionOnBoard);
                canPromote = false;
            }
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && window.hasFocus()) {
                buttonPressedAction(window, mainBoard, tileDim, piecesSprites, movingAPiece, pieceLastPosition);
            }
            
            if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && window.hasFocus() && movingAPiece) {
                mousePositionOnBoard = buttonUnPressedAction(window, mainBoard, tileDim, piecesSprites, movingAPiece,
                                                             pieceLastPosition, canPromote);
            }
        }
        
        window.clear(sf::Color::Black);
        
        drawTiles(window, tileDim);
        
        
        std::pair<int, int> kingCoordinates;
        
        if (checkForChecks(mainBoard, kingCoordinates)) {
            drawCheckFadeEffect(window, tileDim, kingCoordinates, alpha);
            alpha += -1 * dt.asSeconds();
        }
        else {
            alpha = 255;
        }
        
        drawBoardPieces(window, piecesSprites, mainBoard);
        
        window.display();
        dt = deltaClock.restart();
    }
    
}

void loadSprites(sf::Sprite *piecesSprites, sf::Texture *piecesTexture, sf::Vector2f tileDim) {
    
    //load textures
    for (int i = 0; i < 12; i++) {
        piecesTexture[i].loadFromFile("Sprites/tile" + std::to_string(i) + ".png");
        piecesTexture[i].setSmooth(true);
    }
    
    //black pieces
    
    //rook
    piecesSprites[0].setTexture(piecesTexture[0]);
    piecesSprites[0].setPosition(sf::Vector2f(tileDim.x * 0, 0.f));
    
    //horse
    piecesSprites[1].setTexture(piecesTexture[1]);
    piecesSprites[1].setPosition(sf::Vector2f(tileDim.x * 1, 0.f));
    
    //bishop
    piecesSprites[2].setTexture(piecesTexture[2]);
    piecesSprites[2].setPosition(sf::Vector2f(tileDim.x * 2, 0.f));
    
    //queen
    piecesSprites[3].setTexture(piecesTexture[3]);
    piecesSprites[3].setPosition(sf::Vector2f(tileDim.x * 3, 0.f));
    
    //king
    piecesSprites[4].setTexture(piecesTexture[4]);
    piecesSprites[4].setPosition(sf::Vector2f(tileDim.x * 4, 0.f));
    
    //bishop
    piecesSprites[5].setTexture(piecesTexture[2]);
    piecesSprites[5].setPosition(sf::Vector2f(tileDim.x * 5, 0.f));
    
    //horse
    piecesSprites[6].setTexture(piecesTexture[1]);
    piecesSprites[6].setPosition(sf::Vector2f(tileDim.x * 6, 0.f));
    
    //rook
    piecesSprites[7].setTexture(piecesTexture[0]);
    piecesSprites[7].setPosition(sf::Vector2f(tileDim.x * 7, 0.f));
    
    //pawns
    for (int i = 0; i < 8; i++) {
        piecesSprites[8 + i].setTexture(piecesTexture[5]);
        piecesSprites[8 + i].setPosition(sf::Vector2f(tileDim.x * (float) i, tileDim.y));
    }
    
    
    //white pieces
    
    //rook
    piecesSprites[16].setTexture(piecesTexture[6]);
    piecesSprites[16].setPosition(sf::Vector2f(tileDim.x * 0, tileDim.y * 7));
    
    //horse
    piecesSprites[17].setTexture(piecesTexture[7]);
    piecesSprites[17].setPosition(sf::Vector2f(tileDim.x * 1, tileDim.y * 7));
    
    //bishop
    piecesSprites[18].setTexture(piecesTexture[8]);
    piecesSprites[18].setPosition(sf::Vector2f(tileDim.x * 2, tileDim.y * 7));
    
    //queen
    piecesSprites[19].setTexture(piecesTexture[9]);
    piecesSprites[19].setPosition(sf::Vector2f(tileDim.x * 3, tileDim.y * 7));
    
    //king
    piecesSprites[20].setTexture(piecesTexture[10]);
    piecesSprites[20].setPosition(sf::Vector2f(tileDim.x * 4, tileDim.y * 7));
    
    //bishop
    piecesSprites[21].setTexture(piecesTexture[8]);
    piecesSprites[21].setPosition(sf::Vector2f(tileDim.x * 5, tileDim.y * 7));
    
    //horse
    piecesSprites[22].setTexture(piecesTexture[7]);
    piecesSprites[22].setPosition(sf::Vector2f(tileDim.x * 6, tileDim.y * 7));
    
    //rook
    piecesSprites[23].setTexture(piecesTexture[6]);
    piecesSprites[23].setPosition(sf::Vector2f(tileDim.x * 7, tileDim.y * 7));
    
    //pawns
    for (int i = 0; i < 8; i++) {
        piecesSprites[24 + i].setTexture(piecesTexture[11]);
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

void
drawCheckFadeEffect(sf::RenderWindow &window, sf::Vector2f tileDim, std::pair<int, int> kingCoordinates, int &alpha) {
    if (alpha >= 0) {
        sf::RectangleShape squareRed(sf::Vector2f(tileDim.x, tileDim.y));
        squareRed.setFillColor(sf::Color(238, 0, 0, alpha));
        squareRed.setPosition(sf::Vector2f(tileDim.x * kingCoordinates.second, tileDim.y * kingCoordinates.first));
        window.draw(squareRed);
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

void changeSprite(sf::Texture *piecesTexture, sf::Sprite *piecesSprites, Chess::Color result,
                  const Chess::Board &mainBoard, sf::Vector2i mousePositionOnBoard, Chess::Type ch) {
    
    int index = mainBoard.getNumOfSprite(mousePositionOnBoard.y, mousePositionOnBoard.x);
    int colorIndex = result == Chess::Color::Black ? 0 : 6;
    
    switch (ch) {
        case Chess::Type::Rook: {
            piecesSprites[index].setTexture(piecesTexture[0 + colorIndex]);
            break;
        }
        case Chess::Type::Horse: {
            piecesSprites[index].setTexture(piecesTexture[1 + colorIndex]);
            break;
        }
        case Chess::Type::Bishop: {
            piecesSprites[index].setTexture(piecesTexture[2 + colorIndex]);
            break;
        }
        case Chess::Type::Queen: {
            piecesSprites[index].setTexture(piecesTexture[3 + colorIndex]);
            break;
        }
        default: {
        
        }
    }
}

sf::Vector2i buttonPressedAction(sf::RenderWindow &window, const Chess::Board &mainBoard, sf::Vector2f tileDim,
                                 sf::Sprite *piecesSprites, bool &movingAPiece, sf::Vector2i &pieceLastPosition) {
    
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2i mousePositionOnBoard(mousePosition.x / ((int) tileDim.x),
                                      mousePosition.y / ((int) tileDim.y));
    
    if (!mainBoard.isEmpty(mousePositionOnBoard.y, mousePositionOnBoard.x)) {
        if (checkTurn(mainBoard, mousePositionOnBoard)) {
            if (!movingAPiece) {
                movingAPiece = true;
                pieceLastPosition = mousePositionOnBoard;
            }
        }
    }
    
    if (movingAPiece) {
        //drag piece with cursor
        int index = mainBoard.getNumOfSprite(pieceLastPosition.y, pieceLastPosition.x);
        float newX = mousePosition.x - tileDim.x / 2;
        float newY = mousePosition.y - tileDim.y / 2;
        piecesSprites[index].setPosition(newX, newY);
    }
    return mousePositionOnBoard;
}

sf::Vector2i buttonUnPressedAction(sf::RenderWindow &window, Chess::Board &mainBoard, sf::Vector2f tileDim,
                                   sf::Sprite *piecesSprites, bool &movingAPiece, sf::Vector2i &pieceLastPosition,
                                   bool &canPromote) {
    
    movingAPiece = false;
    
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2i mousePositionOnBoard(mousePosition.x / ((int) tileDim.x),
                                      mousePosition.y / ((int) tileDim.y));
    
    if (checkBounds(mousePositionOnBoard)) {
        
        if (mainBoard.move(pieceLastPosition.y, pieceLastPosition.x, mousePositionOnBoard.y,
                           mousePositionOnBoard.x)) {
            
            setNewPosition(piecesSprites, mainBoard, mousePositionOnBoard, mousePosition, tileDim);
            
            Chess::Color result = mainBoard.checkForPromotion();
            
            if (result == Chess::Color::Black || result == Chess::Color::White) {
                canPromote = true;
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
    return mousePositionOnBoard;
}


void promote(Chess::Color result, sf::Texture *piecesTexture, sf::Sprite *piecesSprites, Chess::Board &mainBoard,
             sf::Vector2i mousePositionOnBoard) {
    Chess::Type ch = getAChoiceWindow(piecesTexture, result);
    
    changeSprite(piecesTexture, piecesSprites, result, mainBoard, mousePositionOnBoard,
                 ch);
    
    int col = mousePositionOnBoard.y;
    int row = mousePositionOnBoard.x;
    mainBoard.promote({col, row}, ch);
}

bool checkForChecks(const Chess::Board &mainBoard, std::pair<int, int> &kingCoordinates) {
    return mainBoard.checkingForChecks(Chess::Color::White, kingCoordinates) ||
           mainBoard.checkingForChecks(Chess::Color::Black, kingCoordinates);
}
