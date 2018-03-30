//
//  main.cpp
//  cplusplus
//
//  Created by Александр on 29.03.2018.
//  Copyright © 2018 Александр. All rights reserved.
//

#include <iostream>
#include <new>
#include <string>

#include "SimpleClass.hpp"

using namespace std;




int main (int argc, const char * argv[]) {

    
    for (int i = 3; i < 6; i++) {
        
        cout << "-------------------------------------------------------" << endl;
        cout << "-------------------" << "Square side: " << i << "----------------------" << endl;
        cout << "-------------------------------------------------------" << endl;
        
        Field field(i, 0);
        field.calculateBlocksCount();
    }
    
    
    
    
//    vector<int> v;
//    for (int i = 0; i < 100; i++) {
//        v.push_back(i * i);
//    }
//    
//    for (int i = 0; i < 100; i++) {
//        cout << v[i] << endl;
//    }
    
    return 0;
}
