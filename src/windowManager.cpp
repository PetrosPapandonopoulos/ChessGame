#include "windowManager.h"

void windowManager() {
    sf::RenderWindow window(sf::VideoMode(MAIN_WINDOW_SIZE, MAIN_WINDOW_SIZE), "Chess game", sf::Style::Close);
    sf::Sprite piecesSprites[32];
    sf::Texture PiecesTextures[12];
    sf::Text cordTipsSprites[16];
    sf::Vector2f tileDim(window.getSize().x / (float) BOARD_SIZE, window.getSize().y / (float) BOARD_SIZE);
    sf::Image icon;
    sf::Font font;
    sf::SoundBuffer buffer;
    sf::Sound moveSound;
    
    
    buffer.loadFromFile("Resources/PieceAudio.wav");
    font.loadFromFile("Resources/RobotoMono-Regular.ttf");
    icon.loadFromFile("Sprites/icon.png");
    
    
    window.setVerticalSyncEnabled(true);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    loadSprites(piecesSprites, PiecesTextures, tileDim);
    loadCordTips(cordTipsSprites, tileDim, font);
    moveSound.setBuffer(buffer);
    
    windowCycle(window, piecesSprites, PiecesTextures, tileDim, cordTipsSprites, moveSound);
}

void windowCycle(sf::RenderWindow &window, sf::Sprite *piecesSprites, sf::Texture *piecesTexture,
                 sf::Vector2f tileDim, sf::Text *cordTipsSprites, sf::Sound &moveSound) {
    
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

void
renderFrame(sf::RenderWindow &window, const Chess::Board &mainBoard, sf::Vector2f tileDim, sf::Sprite *piecesSprites,
            sf::Text *cordTipsSprites, int &fadeTransparency, sf::Time dt, bool someoneLost) {
    window.clear(sf::Color::Black);
    
    drawTiles(window, tileDim, {BOARD_SIZE, BOARD_SIZE});
    
    drawCordTips(window, cordTipsSprites);
    
    checkAndDrawFadeEffect(window, mainBoard, tileDim, dt, fadeTransparency);
    
    if (someoneLost) {
        findAndIndicateKing(window, mainBoard, tileDim);
    }
    
    drawBoardPieces(window, piecesSprites, mainBoard);
    
    window.display();
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

void loadCordTips(sf::Text *cordTipsSprites, sf::Vector2f tileDim, const sf::Font &font) {
    
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

void drawTiles(sf::RenderWindow &window, sf::Vector2f tileDim, std::pair<int, int> dimOnWindow) {
    
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
            window.draw(square);
        }
    }
}

void drawATileRed(sf::RenderWindow &window, sf::Vector2f tileDim, std::pair<int, int> tileCoordinates) {
    sf::RectangleShape square(sf::Vector2f(tileDim.x, tileDim.y));
    square.setFillColor(sf::Color::Red);
    square.setPosition(sf::Vector2f(tileDim.x * tileCoordinates.second, tileDim.y * tileCoordinates.first));
    window.draw(square);
}

void drawCordTips(sf::RenderWindow &window, sf::Text *cordTipsSprites) {
    for (int i = 0; i < 16; i++) {
        window.draw(cordTipsSprites[i]);
    }
}

void drawBoardPieces(sf::RenderWindow &window, sf::Sprite *piecesSprites, const Chess::Board &mainBoard) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (!mainBoard.isEmpty(i, j)) {
                window.draw(piecesSprites[mainBoard.getNumOfSprite(i, j)]);
            }
        }
    }
}

void
drawFadeEffect(sf::RenderWindow &window, sf::Vector2f tileDim, std::pair<int, int> kingCoordinates,
               int &fadeTransparency) {
    
    if (fadeTransparency >= 0) {
        sf::RectangleShape squareRed(sf::Vector2f(tileDim.x, tileDim.y));
        squareRed.setFillColor(sf::Color(238, 0, 0, fadeTransparency));
        squareRed.setPosition(sf::Vector2f(tileDim.x * kingCoordinates.second, tileDim.y * kingCoordinates.first));
        window.draw(squareRed);
    }
}

void checkAndDrawFadeEffect(sf::RenderWindow &window, const Chess::Board &mainBoard, sf::Vector2f tileDim, sf::Time dt,
                            int &fadeTransparency) {
    
    std::pair<int, int> kingCoordinates;
    
    if (checkForChecks(mainBoard, kingCoordinates)) {
        drawFadeEffect(window, tileDim, kingCoordinates, fadeTransparency);
        fadeTransparency += -1 * dt.asSeconds();
    }
    else {
        fadeTransparency = 255;
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

void setNewPositionStatic(sf::Sprite *piecesSprites, const Chess::Board &mainBoard, sf::Vector2i newPosition, sf::Vector2f tileDim) {
    
    int index = mainBoard.getNumOfSprite(newPosition.x, newPosition.y);
    float newX = newPosition.x * tileDim.x;
    float newY = newPosition.y * tileDim.y;
    piecesSprites[index].setPosition(newY, newX);
    
}

bool checkBounds(sf::Vector2i mousePositionOnBoard) {
    return mousePositionOnBoard.x >= 0 && mousePositionOnBoard.x < 8 && mousePositionOnBoard.y >= 0 &&
           mousePositionOnBoard.y < 8;
}

bool checkTurn(const Chess::Board &mainBoard, sf::Vector2i mousePositionOnBoard) {
    return mainBoard.getColor(mousePositionOnBoard.y, mousePositionOnBoard.x) == mainBoard.getWhoseTurn();
}

// break this shit, too big
Chess::Type choiceWindow(sf::Vector2i mainWindowCoordinates, sf::Texture *PiecesTextures, Chess::Color color) {
    
    sf::RenderWindow subWindow(sf::VideoMode(SPRITE_SIZE * 4, SPRITE_SIZE),
                               "Choose a Piece", sf::Style::Close);
    //spawn subWindow on top of the main
    mainWindowCoordinates.x += MAIN_WINDOW_SIZE / 2 - subWindow.getSize().x / 2;
    mainWindowCoordinates.y += MAIN_WINDOW_SIZE / 2 - subWindow.getSize().y / 2;
    subWindow.setPosition(mainWindowCoordinates);
    
    sf::Vector2f tileDim(subWindow.getSize().y, subWindow.getSize().y);
    sf::RectangleShape square(sf::Vector2f(tileDim.x, tileDim.y));
    sf::Sprite piecesSprites[4];
    int offSetBasedOnColor = color == Chess::Color::Black ? 0 : 6;
    
    sf::Image icon;
    icon.loadFromFile("Sprites/icon.png");
    subWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    
    for (int i = 0; i < 4; i++) {
        piecesSprites[i].setTexture(PiecesTextures[i + offSetBasedOnColor]);
        piecesSprites[i].setPosition(sf::Vector2f(tileDim.x * i, 0.f));
    }
    
    for (auto &piecesSprite : piecesSprites) {
        piecesSprite.setScale(sf::Vector2f(tileDim.x / piecesSprite.getLocalBounds().width,
                                           tileDim.y / piecesSprite.getLocalBounds().height));
    }
    
    while (subWindow.isOpen()) {
        
        sf::Event event{};
        
        while (subWindow.pollEvent(event)) {
            
            if (event.type == sf::Event::Closed) {
            }
            
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && subWindow.hasFocus()) {
                
                sf::Vector2i mousePosition = sf::Mouse::getPosition(subWindow);
                sf::Vector2i mousePositionOnBoard(mousePosition.x / ((int) tileDim.x),
                                                  mousePosition.y / ((int) tileDim.y));
                
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
        
        drawTiles(subWindow, tileDim, {4, 1});
        
        for (const auto &piecesSprite : piecesSprites) {
            subWindow.draw(piecesSprite);
        }
        
        subWindow.display();
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
                                 sf::Sprite *piecesSprites, bool &movingAPiece, sf::Vector2i &pieceLastPosition,
                                 bool someoneLost) {
    
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2i mousePositionOnBoard(mousePosition.x / ((int) tileDim.x),
                                      mousePosition.y / ((int) tileDim.y));
    
    if (!someoneLost) {
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
    }
    
    return mousePositionOnBoard;
}

sf::Vector2i buttonUnPressedAction(sf::RenderWindow &window, Chess::Board &mainBoard, sf::Vector2f tileDim,
                                   sf::Sprite *piecesSprites, bool &movingAPiece, sf::Vector2i &pieceLastPosition,
                                   bool &canPromote, sf::Sound &moveSound) {
    
    movingAPiece = false;
    
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2i mousePositionOnBoard(mousePosition.x / ((int) tileDim.x),
                                      mousePosition.y / ((int) tileDim.y));
    
    if (checkBounds(mousePositionOnBoard)) {
        Chess::MoveResponse movedResult = mainBoard.move(pieceLastPosition.y, pieceLastPosition.x,
                                                         mousePositionOnBoard.y,
                                                         mousePositionOnBoard.x, false);
        
        if (movedResult != Chess::MoveResponse::Failed) {
            
            setNewPosition(piecesSprites, mainBoard, mousePositionOnBoard, mousePosition, tileDim);
            
            moveSound.play();
            
            if (movedResult == Chess::MoveResponse::QueenSideCastling) {
                int ColBasedOnColor = mainBoard.getWhoseTurn() == Chess::Color::Black ? 0 : 7;
                setNewPositionStatic(piecesSprites, mainBoard, {ColBasedOnColor, 3}, tileDim);
            }
            else if (movedResult == Chess::MoveResponse::KingSideCastling) {
                int ColBasedOnColor = mainBoard.getWhoseTurn() == Chess::Color::Black ? 0 : 7;
                setNewPositionStatic(piecesSprites, mainBoard, {ColBasedOnColor, 5}, tileDim);
            }
            
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
             sf::Vector2i mousePositionOnBoard, sf::Vector2i mainWindowCoordinates) {
    
    Chess::Type ch = choiceWindow(mainWindowCoordinates, piecesTexture, result);
    
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

bool checkForCheckMate(Chess::Board &mainBoard, Chess::Color color) {
    std::pair<int, int> kingCoordinates;
    if (mainBoard.checkingForChecks(color, kingCoordinates)) {
        if (mainBoard.checkForCheckmate(color)) {
            return true;
        }
    }
    return false;
}

void findAndIndicateKing(sf::RenderWindow &window, const Chess::Board &mainBoard, sf::Vector2f tileDim) {
    
    std::pair<int, int> kingCoordinates;
    
    if (mainBoard.checkingForChecks(Chess::Color::White, kingCoordinates)) {
        drawATileRed(window, tileDim, kingCoordinates);
    }
    else if (mainBoard.checkingForChecks(Chess::Color::Black, kingCoordinates)) {
        drawATileRed(window, tileDim, kingCoordinates);
    }
}