//
//  Square.cpp
//  cplusplus
//
//  Created by Александр on 30.03.2018.
//  Copyright © 2018 Александр. All rights reserved.
//

#include "Square.hpp"

Square::Square() {
    
}
Square::~Square() {
    
}

void Square::setCoordinate(int index, int side) {
    coordinate.x = index % side;
    coordinate.y = index / side;
    coordinate.index = index;
}

void Square::clear() {
    isBlock = false;
    isSelected = false;
}
