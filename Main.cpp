#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>

void windowManager();
void loadSprites(sf::Sprite*, sf::Texture*, const sf::Vector2f);
void windowCycle(sf::RenderWindow&, sf::Sprite*, sf::Texture*, const sf::Vector2f);


int main(int argc, char** argv) {

	windowManager();
	return 0;
}

void windowManager() {
	sf::RenderWindow  window(sf::VideoMode(900, 900), "Chess game");
	sf::Sprite piecesSprites[32];
	sf::Texture PiecesTextures[12];
	sf::Vector2f tileDim(window.getSize().x / 8.0, window.getSize().y / 8.0);
	Chess::Board mainBoard;


	loadSprites(piecesSprites, PiecesTextures, tileDim);

	windowCycle(window, piecesSprites, PiecesTextures, tileDim);

}

void windowCycle(sf::RenderWindow& window, sf::Sprite* piecesSprites, sf::Texture* chessPiecesTexture, sf::Vector2f tileDim) {
	Chess::Board mainBoard;
	bool isMoving = false;
	sf::RectangleShape square(sf::Vector2f(tileDim.x, tileDim.y));
	sf::Vector2f InitTileDimension = tileDim;
	sf::Vector2i latestTile;

	while (window.isOpen()) {

		sf::Event event;

		while (window.pollEvent(event)) {


			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::Resized) {
				InitTileDimension.x = window.getSize().x / 8.0;
				InitTileDimension.y = window.getSize().y / 8.0;
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && window.hasFocus()) {

				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				sf::Vector2i mousePositionOnBoard(mousePosition.x / ((int)tileDim.x), mousePosition.y / ((int)tileDim.y));

				//if the tile has a piece on it, or you have already a piece picked up
				if (!mainBoard.isEmpty(mousePositionOnBoard.y,mousePositionOnBoard.x) || isMoving) {
					//if you have not picked up a piece
					if (!isMoving) {
						//then change isMoving
						isMoving = true;
						//save the last cordinates of the piece you picked up
						latestTile = mousePositionOnBoard;
					}
					//sprite follow the cursor
					int index = mainBoard.board[latestTile.y][latestTile.x]->getNumOfSprite();
					piecesSprites[index].setPosition((mousePosition.x - InitTileDimension.x / 2),
						(mousePosition.y - InitTileDimension.y / 2));
				}
			}

			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && window.hasFocus() && isMoving) {
				//when you leave a piece change isMoving
				isMoving = false;


				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

				sf::Vector2i mousePositionOnBoard(mousePosition.x / ((int)tileDim.x), mousePosition.y / ((int)tileDim.y));

				//if the cordinates are not out of borders
				if (mousePositionOnBoard.x >= 0 && mousePositionOnBoard.x < 8 && mousePositionOnBoard.y >= 0 && mousePositionOnBoard.y < 8) {

					if (mainBoard.isEmpty(mousePositionOnBoard.y, mousePositionOnBoard.x)) {
						//set the tile centered in the tile the user choose
						piecesSprites[mainBoard.board[latestTile.y][latestTile.x]->getNumOfSprite()].setPosition((mousePosition.x / ((int)tileDim.x)) * tileDim.x,
							(mousePosition.y / ((int)tileDim.y)) * tileDim.y);

						//update board
						mainBoard.board[mousePositionOnBoard.y][mousePositionOnBoard.x] = std::move(mainBoard.board[latestTile.y][latestTile.x]);

						mainBoard.board[mousePositionOnBoard.y][mousePositionOnBoard.x]->setCurrentCol(mousePositionOnBoard.x);
						mainBoard.board[mousePositionOnBoard.y][mousePositionOnBoard.x]->setCurrentRow(mousePositionOnBoard.y);
					}
					else {
						piecesSprites[mainBoard.board[latestTile.y][latestTile.x]->getNumOfSprite()].setPosition(latestTile.x * tileDim.x, latestTile.y* tileDim.y);
					}
				}
				else {
					//if the user tried to place a piece out of order, return it to its original potition
					//not working :p
					piecesSprites[mainBoard.board[latestTile.y][latestTile.x]->getNumOfSprite()].setPosition(latestTile.x * tileDim.x, latestTile.y * tileDim.y);
				}
			}
		}

		//clear previous frame
		window.clear(sf::Color::Black);

		//draw new frame
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
		for (int i = 0; i < 32; i++) {
			window.draw(piecesSprites[i]);
		}

		//display new frame
		window.display();
	}
}

void loadSprites(sf::Sprite* piecesSprites, sf::Texture* chessPiecesTexture, sf::Vector2f tileDim) {

	//load textures
	for (int i = 0; i < 12; i++) {
		chessPiecesTexture[i].loadFromFile("Sprites/tile" + std::to_string(i) + ".png");
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
		piecesSprites[8 + i].setPosition(sf::Vector2f(tileDim.x * i, tileDim.y));
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
}