//
//  Square.hpp
//  cplusplus
//
//  Created by Александр on 30.03.2018.
//  Copyright © 2018 Александр. All rights reserved.
//

#ifndef Square_hpp
#define Square_hpp

#include <stdio.h>

#endif /* Square_hpp */

using namespace std;

struct Coordinate {
    int x = 0;
    int y = 0;
    int index = 0;
};


class Square {
    
public:
    Square();
    ~Square();

    int isBlock = false;
    int isSelected = false;
    Coordinate coordinate;
    
    void setCoordinate(int index, int side);
    void clear();
};
