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

#include <thread>

#include "SimpleClass.hpp"

using namespace std;

void calcFields(int bin) {
    for (int i = 3; i < 9; i++) {
        
        if (i % 2 == bin) {
            continue;
        }
        
//        cout << "-------------------------------------------------------" << endl;
//        cout << "-------------------" << "Square side: " << i << "----------------------" << endl;
//        cout << "-------------------------------------------------------" << endl;
        
        //
        
        Field field(i, 6);
        field.calculateBlocksCount();
    }
}


int main (int argc, const char * argv[]) {

    

    thread even(calcFields, 0);
    thread odd(calcFields, 1);
    
    even.join();
    odd.join();
    
    
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
