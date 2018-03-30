//
//  SimpleClass.hpp
//  cplusplus
//
//  Created by Александр on 29.03.2018.
//  Copyright © 2018 Александр. All rights reserved.
//

#ifndef SimpleClass_hpp
#define SimpleClass_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "Square.hpp"

#endif /* SimpleClass_hpp */

using namespace std;

class Field {
    // сторона поля
    int side = 1;
    // всего квадратов
    int allSquares = 1;
    // максимальное колличество блоков (ограничение)
    int maxBlocksCount = 0;
    // колличество комбинаций блоков для поля
    int combinationCount = 0;
    // ячейки поля
    vector<Square *> squares;
    
    // новое поле
    void setPosition(int position, int nextBlocksCount, vector<int> blocksIndexes);
    // создаем поле
    void createField();
    // подготовка под новое условие
    void prepareField();
    // проверка выборки
    bool checkField();
    // установка новой комбинации блоков
    void setBlocks(vector<int> blocks);
    
    void searchPath();
    
    vector<Square *> searchPathFor(Square *square);
    vector<Square *> downSquares(vector<Square *> upSquares);
    
public:
    // инит со стороной
    Field(int s, int mB);
    // найти все варианты блоков для поля
    void calculateBlocksCount();
    
    
};










