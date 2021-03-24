#include "WindowManager.h"

WindowManager::WindowManager() : window(sf::VideoMode(MAIN_WINDOW_SIZE, MAIN_WINDOW_SIZE), "Chess game",
                                        sf::Style::Close), mainBoard() {
    
    
    piecesTextures = new sf::Texture[12];
    piecesSprites = new sf::Sprite[32];
    cordTipsSprites = new sf::Text[16];
    
    fadeTransparency = 255;
    
    tileDim = {window.getSize().x / (float) BOARD_SIZE, window.getSize().y / (float) BOARD_SIZE};
    
    canPromote = false;
    movingAPiece = false;
    someoneLost = false;
    
    buffer.loadFromFile("Resources/PieceAudio.wav");
    moveSound.setBuffer(buffer);
    
    font.loadFromFile("Resources/RobotoMono-Regular.ttf");
    icon.loadFromFile("Sprites/icon.png");
    
    window.setVerticalSyncEnabled(true);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    loadSprites();
    loadCordTips();
    
    
}

void WindowManager::loadSprites() {
    
    //load textures
    for (int i = 0; i < 12; i++) {
        piecesTextures[i].loadFromFile("Sprites/tile" + std::to_string(i) + ".png");
        piecesTextures[i].setSmooth(true);
    }
    
    //black pieces
    
    //rook
    piecesSprites[0].setTexture(piecesTextures[0]);
    piecesSprites[0].setPosition(sf::Vector2f(tileDim.x * 0, 0.f));
    
    //horse
    piecesSprites[1].setTexture(piecesTextures[1]);
    piecesSprites[1].setPosition(sf::Vector2f(tileDim.x * 1, 0.f));
    
    //bishop
    piecesSprites[2].setTexture(piecesTextures[2]);
    piecesSprites[2].setPosition(sf::Vector2f(tileDim.x * 2, 0.f));
    
    //queen
    piecesSprites[3].setTexture(piecesTextures[3]);
    piecesSprites[3].setPosition(sf::Vector2f(tileDim.x * 3, 0.f));
    
    //king
    piecesSprites[4].setTexture(piecesTextures[4]);
    piecesSprites[4].setPosition(sf::Vector2f(tileDim.x * 4, 0.f));
    
    //bishop
    piecesSprites[5].setTexture(piecesTextures[2]);
    piecesSprites[5].setPosition(sf::Vector2f(tileDim.x * 5, 0.f));
    
    //horse
    piecesSprites[6].setTexture(piecesTextures[1]);
    piecesSprites[6].setPosition(sf::Vector2f(tileDim.x * 6, 0.f));
    
    //rook
    piecesSprites[7].setTexture(piecesTextures[0]);
    piecesSprites[7].setPosition(sf::Vector2f(tileDim.x * 7, 0.f));
    
    //pawns
    for (int i = 0; i < 8; i++) {
        piecesSprites[8 + i].setTexture(piecesTextures[5]);
        piecesSprites[8 + i].setPosition(sf::Vector2f(tileDim.x * (float) i, tileDim.y));
    }
    
    
    //white pieces
    
    //rook
    piecesSprites[16].setTexture(piecesTextures[6]);
    piecesSprites[16].setPosition(sf::Vector2f(tileDim.x * 0, tileDim.y * 7));
    
    //horse
    piecesSprites[17].setTexture(piecesTextures[7]);
    piecesSprites[17].setPosition(sf::Vector2f(tileDim.x * 1, tileDim.y * 7));
    
    //bishop
    piecesSprites[18].setTexture(piecesTextures[8]);
    piecesSprites[18].setPosition(sf::Vector2f(tileDim.x * 2, tileDim.y * 7));
    
    //queen
    piecesSprites[19].setTexture(piecesTextures[9]);
    piecesSprites[19].setPosition(sf::Vector2f(tileDim.x * 3, tileDim.y * 7));
    
    //king
    piecesSprites[20].setTexture(piecesTextures[10]);
    piecesSprites[20].setPosition(sf::Vector2f(tileDim.x * 4, tileDim.y * 7));
    
    //bishop
    piecesSprites[21].setTexture(piecesTextures[8]);
    piecesSprites[21].setPosition(sf::Vector2f(tileDim.x * 5, tileDim.y * 7));
    
    //horse
    piecesSprites[22].setTexture(piecesTextures[7]);
    piecesSprites[22].setPosition(sf::Vector2f(tileDim.x * 6, tileDim.y * 7));
    
    //rook
    piecesSprites[23].setTexture(piecesTextures[6]);
    piecesSprites[23].setPosition(sf::Vector2f(tileDim.x * 7, tileDim.y * 7));
    
    //pawns
    for (int i = 0; i < 8; i++) {
        piecesSprites[24 + i].setTexture(piecesTextures[11]);
        piecesSprites[24 + i].setPosition(sf::Vector2f(tileDim.x * i, tileDim.y * 6));
    }
    
    for (int i = 0; i < 32; i++) {
        piecesSprites[i].setScale(sf::Vector2f(tileDim.x / piecesSprites[i].getLocalBounds().width,
                                               tileDim.y / piecesSprites[i].getLocalBounds().height));
    }
}

void WindowManager::loadCordTips() {
    
    for (int i = 0; i < 8; i++) {
        cordTipsSprites[7 - i].setFont(font);
        cordTipsSprites[8 + i].setFont(font);
        
        cordTipsSprites[7 - i].setString(std::to_string(8 - i));
        cordTipsSprites[8 + i].setString(std::string(1, 'a' + i));
        
        cordTipsSprites[7 - i].setCharacterSize(FONT_SIZE);
        cordTipsSprites[8 + i].setCharacterSize(FONT_SIZE);
        
        if (i % 2 == 0) {
            
            cordTipsSprites[7 - i].setFillColor(BOARD_BLACK);
            cordTipsSprites[8 + i].setFillColor(BOARD_WHITE);
        }
        else {
            
            cordTipsSprites[7 - i].setFillColor(BOARD_WHITE);
            cordTipsSprites[8 + i].setFillColor(BOARD_BLACK);
        }
        cordTipsSprites[7 - i].setPosition(sf::Vector2f(FONT_POS, tileDim.y * i));
        
        cordTipsSprites[8 + i].setPosition(sf::Vector2f(tileDim.x * i + (tileDim.x - FONT_LETTERS_X),
                                                        tileDim.y * 7 + (tileDim.y - FONT_LETTERS_Y)));
    }
}

void WindowManager::renderFrame(sf::Time dt) {
    window.clear(sf::Color::Black);
    
    drawTiles(this->window, {BOARD_SIZE, BOARD_SIZE});
    
    drawCordTips();
    
    checkAndDrawFadeEffect(dt);
    
    if (someoneLost) {
        findAndIndicateKing();
    }
    
    drawBoardPieces();
    
    window.display();
}

void WindowManager::drawTiles(sf::RenderWindow& renderWindow, std::pair<int, int> dimOnWindow) const {
    
    sf::RectangleShape square(sf::Vector2f(tileDim.x, tileDim.y));
    
    for (int i = 0; i < dimOnWindow.first; i++) {
        for (int j = 0; j < dimOnWindow.second; j++) {
            if (i % 2 == j % 2) {
                square.setFillColor(BOARD_WHITE);
            }
            else {
                square.setFillColor(BOARD_BLACK);
            }
            
            square.setPosition(sf::Vector2f(tileDim.x * i, tileDim.y * j));
            renderWindow.draw(square);
        }
    }
}

void WindowManager::drawATileRed(std::pair<int, int> tileCoordinates) {
    sf::RectangleShape square(sf::Vector2f(tileDim.x, tileDim.y));
    square.setFillColor(sf::Color::Red);
    square.setPosition(sf::Vector2f(tileDim.x * tileCoordinates.second, tileDim.y * tileCoordinates.first));
    window.draw(square);
}

void WindowManager::drawCordTips() {
    for (int i = 0; i < 16; i++) {
        window.draw(cordTipsSprites[i]);
    }
}

void WindowManager::drawBoardPieces() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (!mainBoard.isEmpty(i, j)) {
                window.draw(piecesSprites[mainBoard.getNumOfSprite(i, j)]);
            }
        }
    }
}

void WindowManager::drawFadeEffect(std::pair<int, int> tileCoordinates) {
    
    if (fadeTransparency >= 0) {
        sf::RectangleShape squareRed(sf::Vector2f(tileDim.x, tileDim.y));
        squareRed.setFillColor(sf::Color(238, 0, 0, fadeTransparency));
        squareRed.setPosition(sf::Vector2f(tileDim.x * tileCoordinates.second, tileDim.y * tileCoordinates.first));
        window.draw(squareRed);
    }
}

void WindowManager::checkAndDrawFadeEffect(sf::Time dt) {
    
    std::pair<int, int> kingCoordinates;
    
    if (checkForEitherChecks(kingCoordinates)) {
        drawFadeEffect(kingCoordinates);
        this->fadeTransparency += -1 * dt.asSeconds();
    }
    else {
        //reset
        this->fadeTransparency = 255;
    }
}

bool WindowManager::checkForEitherChecks(std::pair<int, int> &kingCoordinates) {
    return mainBoard.checkingForChecks(Chess::Color::White, kingCoordinates) ||
           mainBoard.checkingForChecks(Chess::Color::Black, kingCoordinates);
}

void WindowManager::placeAPieceBack(sf::Vector2i pieceLastPosition) {
    int index = mainBoard.getNumOfSprite(pieceLastPosition.y, pieceLastPosition.x);
    
    float newX = pieceLastPosition.x * tileDim.x;
    float newY = pieceLastPosition.y * tileDim.y;
    
    piecesSprites[index].setPosition(newX, newY);
}

void WindowManager::setNewPosition(sf::Vector2i mousePosition, sf::Vector2i mousePositionOnBoard) {
    
    int index = mainBoard.getNumOfSprite(mousePositionOnBoard.y, mousePositionOnBoard.x);
    float newX = (mousePosition.x / ((int) tileDim.x)) * tileDim.x;
    float newY = (mousePosition.y / ((int) tileDim.y)) * tileDim.y;
    piecesSprites[index].setPosition(newX, newY);
}

void WindowManager::setNewPositionStatic(sf::Vector2i newPosition) {
    
    int index = mainBoard.getNumOfSprite(newPosition.x, newPosition.y);
    float newX = newPosition.x * tileDim.x;
    float newY = newPosition.y * tileDim.y;
    piecesSprites[index].setPosition(newY, newX);
    
}

bool WindowManager::checkBounds(sf::Vector2i mousePositionOnBoard) {
    return mousePositionOnBoard.x >= 0 && mousePositionOnBoard.x < 8 && mousePositionOnBoard.y >= 0 &&
           mousePositionOnBoard.y < 8;
}

bool WindowManager::checkTurn(sf::Vector2i Coordinates) {
    return mainBoard.getColor(Coordinates.y, Coordinates.x) == mainBoard.getWhoseTurn();
}

Chess::Type WindowManager::choiceWindow(Chess::Color color) {
    
    sf::RenderWindow subWindow(sf::VideoMode(SPRITE_SIZE * 4, SPRITE_SIZE),
                               "Choose a Piece", sf::Style::Close);
    sf::Vector2i mainWindowCoordinates(window.getPosition());
    //spawn subWindow on top of the main
    mainWindowCoordinates.x += MAIN_WINDOW_SIZE / 2 - subWindow.getSize().x / 2;
    mainWindowCoordinates.y += MAIN_WINDOW_SIZE / 2 - subWindow.getSize().y / 2;
    subWindow.setPosition(mainWindowCoordinates);
    
    sf::Vector2f subWindowTileDim(subWindow.getSize().y, subWindow.getSize().y);
    sf::RectangleShape square(sf::Vector2f(subWindowTileDim.x, subWindowTileDim.y));
    sf::Sprite subWindowPiecesSprites[4];
    int offSetBasedOnColor = color == Chess::Color::Black ? 0 : 6;
    
    subWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    
    for (int i = 0; i < 4; i++) {
        subWindowPiecesSprites[i].setTexture(piecesTextures[i + offSetBasedOnColor]);
        subWindowPiecesSprites[i].setPosition(sf::Vector2f(subWindowTileDim.x * i, 0.f));
    }
    
    for (auto &piecesSprite : subWindowPiecesSprites) {
        piecesSprite.setScale(sf::Vector2f(subWindowTileDim.x / piecesSprite.getLocalBounds().width,
                                           subWindowTileDim.y / piecesSprite.getLocalBounds().height));
    }
    
    while (subWindow.isOpen()) {
        
        sf::Event event{};
        
        while (subWindow.pollEvent(event)) {
            
            if (event.type == sf::Event::Closed) {
            }
            
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && subWindow.hasFocus()) {
                
                sf::Vector2i mousePosition = sf::Mouse::getPosition(subWindow);
                sf::Vector2i mousePositionOnBoard(mousePosition.x / ((int) subWindowTileDim.x),
                                                  mousePosition.y / ((int) subWindowTileDim.y));
                
                switch (mousePositionOnBoard.x) {
                    case 0: {
                        std::cout << "User choose Rook!" << std::endl;
                        subWindow.close();
                        return Chess::Type::Rook;
                    }
                    case 1: {
                        std::cout << "User choose Horse!" << std::endl;
                        subWindow.close();
                        return Chess::Type::Horse;
                    }
                    case 2: {
                        std::cout << "User choose Bishop!" << std::endl;
                        subWindow.close();
                        return Chess::Type::Bishop;
                    }
                    case 3: {
                        subWindow.close();
                        std::cout << "User choose Queen!" << std::endl;
                        return Chess::Type::Queen;
                    }
                }
            }
        }
        
        subWindow.clear(sf::Color::Black);
        
        drawTiles(subWindow, {4, 1});
        
        for (const auto &piecesSprite : subWindowPiecesSprites) {
            subWindow.draw(piecesSprite);
        }
        
        subWindow.display();
    }
    
    return Chess::Type::Queen;
}

void WindowManager::changeSprite(Chess::Color result, sf::Vector2i spriteIndexCoordinates, Chess::Type ch) {
    
    int index = mainBoard.getNumOfSprite(spriteIndexCoordinates.y, spriteIndexCoordinates.x);
    int colorIndex = result == Chess::Color::Black ? 0 : 6;
    
    switch (ch) {
        case Chess::Type::Rook: {
            piecesSprites[index].setTexture(piecesTextures[0 + colorIndex]);
            break;
        }
        case Chess::Type::Horse: {
            piecesSprites[index].setTexture(piecesTextures[1 + colorIndex]);
            break;
        }
        case Chess::Type::Bishop: {
            piecesSprites[index].setTexture(piecesTextures[2 + colorIndex]);
            break;
        }
        case Chess::Type::Queen: {
            piecesSprites[index].setTexture(piecesTextures[3 + colorIndex]);
            break;
        }
        default: {
        
        }
    }
}

sf::Vector2i WindowManager::buttonPressedAction(sf::Vector2i &pieceLastPosition) {
    
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2i mousePositionOnBoard(mousePosition.x / ((int) tileDim.x),
                                      mousePosition.y / ((int) tileDim.y));
    
    if (!someoneLost) {
        if (!mainBoard.isEmpty(mousePositionOnBoard.y, mousePositionOnBoard.x)) {
            if (checkTurn(mousePositionOnBoard)) {
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
    }
    
    return mousePositionOnBoard;
}

sf::Vector2i WindowManager::buttonUnPressedAction(sf::Vector2i &pieceLastPosition) {
    
    movingAPiece = false;
    
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2i mousePositionOnBoard(mousePosition.x / ((int) tileDim.x),
                                      mousePosition.y / ((int) tileDim.y));
    
    if (checkBounds(mousePositionOnBoard)) {
        Chess::MoveResponse movedResult = mainBoard.move(pieceLastPosition.y, pieceLastPosition.x,
                                                         mousePositionOnBoard.y,
                                                         mousePositionOnBoard.x, false);
        
        if (movedResult != Chess::MoveResponse::Failed) {
            
            setNewPosition(mousePosition, mousePositionOnBoard);
            
            moveSound.play();
            
            if (movedResult == Chess::MoveResponse::QueenSideCastling) {
                int ColBasedOnColor = mainBoard.getWhoseTurn() == Chess::Color::Black ? 0 : 7;
                setNewPositionStatic({ColBasedOnColor, 3});
            }
            else if (movedResult == Chess::MoveResponse::KingSideCastling) {
                int ColBasedOnColor = mainBoard.getWhoseTurn() == Chess::Color::Black ? 0 : 7;
                setNewPositionStatic({ColBasedOnColor, 5});
            }
            
            Chess::Color result = mainBoard.checkForPromotion();
            
            if (result == Chess::Color::Black || result == Chess::Color::White) {
                canPromote = true;
            }
            
            
            mainBoard.nextTurn();
        }
        else {
            placeAPieceBack(pieceLastPosition);
        }
    }
    else {
        placeAPieceBack(pieceLastPosition);
    }
    return mousePositionOnBoard;
}

void  WindowManager::promote(sf::Vector2i mousePositionOnBoard) {
    
    Chess::Color color = mainBoard.checkForPromotion();
    
    Chess::Type ch = choiceWindow(color);
    
    changeSprite(color, mousePositionOnBoard, ch);
    
    int col = mousePositionOnBoard.y;
    int row = mousePositionOnBoard.x;
    mainBoard.promote({col, row}, ch);
}

bool WindowManager::checkForCheckMate(Chess::Color color) {
    std::pair<int, int> kingCoordinates;
    if (mainBoard.checkingForChecks(color, kingCoordinates)) {
        if (mainBoard.checkForCheckmate(color)) {
            return true;
        }
    }
    return false;
}

void WindowManager::findAndIndicateKing() {
    
    std::pair<int, int> kingCoordinates;
    
    if (mainBoard.checkingForChecks(Chess::Color::White, kingCoordinates)) {
        drawATileRed(kingCoordinates);
    }
    else if (mainBoard.checkingForChecks(Chess::Color::Black, kingCoordinates)) {
        drawATileRed(kingCoordinates);
    }
}

bool WindowManager::windowIsOpen() {
    return window.isOpen();
}

bool WindowManager::windowGetPollEvent(sf::Event& event) {
    return window.pollEvent(event);
}

void WindowManager::closeWindow() {
    window.close();
}

bool WindowManager::windowHasFocus() {
    return window.hasFocus();
}

bool WindowManager::isMovingAPiece() const {
    return movingAPiece;
}

bool WindowManager::isCanPromote() const {
    return canPromote;
}

void WindowManager::setCanPromote(bool input) {
    canPromote = input;
}

bool WindowManager::isSomeoneLost() const {
    return someoneLost;
}

void WindowManager::setSomeoneLost(bool input) {
    someoneLost = input;
}
