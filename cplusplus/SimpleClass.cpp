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

        string fileName = to_string(side) + ".txt";
        ofstream sideFile;
        sideFile.open (fileName, fstream::out | fstream::app);
        sideFile << "//" << i + 1 << "//" << endl;
        sideFile.close();


        auto start = chrono::system_clock::now();

        setPosition(0, i, blocksIndexes);
        
        auto end = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end-start;
        time_t end_time = std::chrono::system_clock::to_time_t(end);

        cout << "\nTime : "<< ctime(&end_time) << "time passed from previos: (" << side << " : " << i << ") --- " << elapsed_seconds.count();
        cout << "\ncount : " << combinationCount << " \tside: " << side << " \tblocks : " << i + 1 << endl;

        // auto t = std::time(nullptr);
        // auto tm = *std::localtime(&t);
        // cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << ": " << "count of combination: " << combinationCount << " for side: " << side << " and blocks count: " << i + 1 << endl;

        
    }
}

void Field::setPosition(int position, int nextBlocksCount, vector<int> blocksIndexes) {
    for (int i = position; i < allSquares - nextBlocksCount; i++) {
        vector<int> newIndexes = blocksIndexes;
        newIndexes.push_back(i);
        if (nextBlocksCount > 0) {
            setPosition(i + 1, nextBlocksCount - 1, newIndexes);
        } else {
            // combinationCount++;
            
            // cout << "block combination: -- ";
            // for (int i = 0; i < newIndexes.size(); i++) {
            //    cout << newIndexes[i];
            //    if (i != newIndexes.size() - 1) {
            //         cout << "||";
            //    }

            // }
            // cout << endl;
            
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
                
                path.insert(path.begin(), square);
                path.pop_back();
                printPath(path);
                // cout << "Path for this blocks -- ";
                // for (int j = 0; j < path.size(); j++) {
                //     cout << path[j]->coordinate.index;
                //     if (j != path.size() - 1) {
                //         cout << "::";
                //     }
                // }
                // cout << endl;
                
                break;
            }
        }
    }
}

void Field::printPath(vector<Square *> pathSquares) {
    string fileName = to_string(side) + ".txt";
    ofstream sideFile;
    sideFile.open (fileName, fstream::out | fstream::app);

    for (int i = 0; i < squares.size(); ++i) {   
        auto square = squares[i];
        if (square->isBlock) {
            sideFile << square->coordinate.index << "||";
        }
    }
    sideFile << "&&";
    for (int i = 0; i < pathSquares.size(); ++i) {
        auto square = pathSquares[i];
        sideFile << square->coordinate.index << "::";
    }
    sideFile << endl;

    sideFile.close();
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
        
        newSquares = downSquares(newSquares, true);
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
        
        newSquares = downSquares(newSquares, false);
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
        
        newSquares = downSquares(newSquares, true);
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
        
        newSquares = downSquares(newSquares, false);
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



vector<Square *> Field::downSquares(vector<Square *> upSquares, bool horizontal) {
    if (!upSquares.empty()) {
        Square *lastSquare = upSquares.back();
        if (!checkSquaresInCurrentLine(lastSquare, horizontal)) {
            setSelected(upSquares, false);
            upSquares.clear();
            return upSquares;
        }
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

bool Field::checkSquaresInCurrentLine(Square *square, bool horizontal) {
    if (horizontal) {
        // ищем по горизонтали
        if (square->coordinate.y == 0 || square->coordinate.y == side - 1) {
            return true;
        } else {
            bool upSel = false;
            bool centerSel = false;
            bool downSel = false;

            for (int i = 0; i < allSquares; ++i)
            {
                auto tmpSquare = squares[i];
                if (tmpSquare->isBlock) {
                    continue;
                }
                if (tmpSquare->coordinate.y < square->coordinate.y) {
                    // сверху
                    if (!tmpSquare->isSelected) {
                        upSel = true;
                    }
                } else if (tmpSquare->coordinate.y > square->coordinate.y) {
                    // снизу
                    if (!tmpSquare->isSelected) {
                        downSel = true;
                    }
                } else {
                    // по центру
                    if (!tmpSquare->isSelected) {
                        return true;
                    }
                }
            }
            return !(upSel && downSel);
        }
    } else {
        // ищем по вертикали
         if (square->coordinate.x == 0 || square->coordinate.x == side - 1) {
            return true;
        } else {
            bool leftSel = false;
            bool centerSel = false;
            bool rightSel = false;

            for (int i = 0; i < allSquares; ++i)
            {
                auto tmpSquare = squares[i];
                if (tmpSquare->isBlock) {
                    continue;
                }
                if (tmpSquare->coordinate.x < square->coordinate.x) {
                    // слева
                    if (!tmpSquare->isSelected) {
                        leftSel = true;
                    }
                } else if (tmpSquare->coordinate.x > square->coordinate.x) {
                    // справа
                    if (!tmpSquare->isSelected) {
                        rightSel = true;
                    }
                } else {
                    // по центру
                    if (!tmpSquare->isSelected) {
                        return true;
                    }
                }
            }
            return !(rightSel && leftSel);
        }
    }

    return false;
}


