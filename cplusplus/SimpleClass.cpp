//
//  SimpleClass.cpp
//  cplusplus
//
//  Created by Александр on 29.03.2018.
//  Copyright © 2018 Александр. All rights reserved.
//

#include "SimpleClass.hpp"

// инит со стороной
Field::Field(int s, int mB) {
    side = s;
    allSquares = s * s;
    maxBlocksCount = mB > 0? mB : s * s - 1;
}

// найти все варианты блоков для поля
void Field::calculateBlocksCount() {
    createField();
    for (int i = 0; i < maxBlocksCount; i++) {
        combinationCount = 0;
        vector<int> blocksIndexes;
        setPosition(0, i, blocksIndexes);
        cout << "count of combination: " << combinationCount << " for side: " << side << " and blocks count: " << i + 1 << endl;
    }
}

void Field::setPosition(int position, int nextBlocksCount, vector<int> blocksIndexes) {
    for (int i = position; i < allSquares - nextBlocksCount; i++) {
        vector<int> newIndexes = blocksIndexes;
        newIndexes.push_back(i);
        if (nextBlocksCount > 0) {
            setPosition(i + 1, nextBlocksCount - 1, newIndexes);
        } else {
//            combinationCount++;
            
//            cout << "block combination: ";
//            for (int i = 0; i < newIndexes.size(); i++) {
//                cout << newIndexes[i] << ", ";
//            }
//            cout << endl;
            
            prepareField();
            setBlocks(newIndexes);
            searchPath();
        }
    }
}

void Field::createField() {
    for (int i = 0; i < allSquares; i++) {
        Square *square = new Square();
        square->setCoordinate(i, side);
        squares.push_back(square);
    }
}

void Field::prepareField() {
    for (int i = 0; i < allSquares; i++) {
        Square *square = squares[i];
        square->clear();
    }
}

void Field::setBlocks(vector<int> blocks) {
    for (int i = 0; i < blocks.size(); i++) {
        Square *square = squares[blocks[i]];
        square->isBlock = true;
    }
}

bool Field::checkField() {
    for (int i = 0; i < allSquares; i++) {
        Square *square = squares[i];
        if (!square->isSelected && !square->isBlock) {
            return false;
        }
    }
    return true;
}

void setSelected(vector<Square *> squares, bool s) {
    for (int i = 0; i < squares.size(); i++) {
        Square *square = squares[i];
        square->isSelected = s;
    }
}

void Field::searchPath() {
    for (int i = 0; i < allSquares; i++) {
        
        setSelected(squares, false);
        
        Square *square = squares[i];
        square->isSelected = true;
        if (!square->isBlock) {
            // ищем от этой ячейки
            vector<Square *> path = searchPathFor(square);
            if (path[0] != nullptr) {
                
                combinationCount++;
                
//                path.insert(path.begin(), square);
//                path.pop_back();
//                for (int j = 0; j < path.size(); j++) {
//                    cout << path[j]->coordinate.index << ", ";
//                }
//                cout << endl;
                
                break;
            }
        }
    }
}



vector<Square *> Field::searchPathFor(Square *square) {
    vector<Square *> newSquares;
    
    // вправо
    if (square->coordinate.x < side - 1) {
        // индекс для следующего
        int index = square->coordinate.index + 1;
        while (index < allSquares) {
            // находим следующий
            Square *nextSquare = squares[index];
            // ячейка не блок и не выбрана
            bool b = !nextSquare->isBlock && !nextSquare->isSelected;
            // находится в том же ряду, что и начальная ячейка
            bool c = nextSquare->coordinate.y == square->coordinate.y;
            if (b && c) {
                nextSquare->isSelected = true;
                newSquares.push_back(nextSquare);
            } else {
                break;
            }
            index++;
        }
        
        newSquares = downSquares(newSquares);
        if (!newSquares.empty()) {
            return newSquares;
        }
    }

    
    // вниз
    if (square->coordinate.y < side - 1) {
        // индекс для следующего
        int index = square->coordinate.index + side;
        while (index < allSquares) {
            // находим следующий
            Square *nextSquare = squares[index];
            // ячейка не блок и не выбрана
            bool b = !nextSquare->isBlock && !nextSquare->isSelected;
            // находится в том же ряду, что и начальная ячейка
            bool c = nextSquare->coordinate.x == square->coordinate.x;
            if (b && c) {
                nextSquare->isSelected = true;
                newSquares.push_back(nextSquare);
            } else {
                break;
            }
            index+=side;
        }
        
        newSquares = downSquares(newSquares);
        if (!newSquares.empty()) {
            return newSquares;
        }
    }
    
    
    // влево
    if (square->coordinate.x > 0) {
        // индекс для следующего
        int index = square->coordinate.index - 1;
        while (index >= 0) {
            // находим следующий
            Square *nextSquare = squares[index];
            // ячейка не блок и не выбрана
            bool b = !nextSquare->isBlock && !nextSquare->isSelected;
            // находится в том же ряду, что и начальная ячейка
            bool c = nextSquare->coordinate.y == square->coordinate.y;
            if (b && c) {
                nextSquare->isSelected = true;
                newSquares.push_back(nextSquare);
            } else {
                break;
            }
            index--;
        }
        
        newSquares = downSquares(newSquares);
        if (!newSquares.empty()) {
            return newSquares;
        }
    }
    
    
    // вверх
    if (square->coordinate.y > 0) {
        // индекс для следующего
        int index = square->coordinate.index - side;
        while (index >= 0) {
            // находим следующий
            Square *nextSquare = squares[index];
            // ячейка не блок и не выбрана
            bool b = !nextSquare->isBlock && !nextSquare->isSelected;
            // находится в том же ряду, что и начальная ячейка
            bool c = nextSquare->coordinate.x == square->coordinate.x;
            if (b && c) {
                nextSquare->isSelected = true;
                newSquares.push_back(nextSquare);
            } else {
                break;
            }
            index-=side;
        }
        
        newSquares = downSquares(newSquares);
        if (!newSquares.empty()) {
            return newSquares;
        }
    }
    newSquares.clear();
    if (checkField()) {
        newSquares.push_back(square);
    } else {
        newSquares.push_back(nullptr);
    }
    return newSquares;
}



vector<Square *> Field::downSquares(vector<Square *> upSquares) {
    if (!upSquares.empty()) {
        Square *lastSquare = upSquares.back();
        vector<Square *> downSquares = searchPathFor(lastSquare);
        if (downSquares[0] != nullptr) {
            upSquares.insert(upSquares.end(), downSquares.begin(), downSquares.end());
            return upSquares;
        } else {
            setSelected(upSquares, false);
            upSquares.clear();
        }
    }
    return upSquares;
}




