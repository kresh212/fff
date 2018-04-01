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

void calcFields(vector<int> sides) {
    for (int i = 0; i < sides.size(); i++) {
        
        int side = sides[i];
//        cout << "-------------------------------------------------------" << endl;
//        cout << "-------------------" << "Square side: " << i << "----------------------" << endl;
//        cout << "-------------------------------------------------------" << endl;
        
        int blocksCount = 6;
        switch (side) {
            case 3: {
                blocksCount = 3;
                break;
            }
            case 4: {
                blocksCount = 5;
                break;
            }
            case 5:
            case 6: {
                blocksCount = 6;
                break;
            }
            case 7: {
                blocksCount = 6;
                break;
            }
            case 8: {
                blocksCount = 6;
                break;
            }
            case 9: {
                blocksCount = 6;
                break;
            }
            case 10: {
                blocksCount = 6;
                break;
            }
        }

        Field field(side, blocksCount);
        field.calculateBlocksCount();
    }
}


int main (int argc, const char * argv[]) {

    int firstArr[] = {3,4,5,6};
    vector<int> firstV(firstArr, firstArr + sizeof(firstArr) / sizeof(int));

    int secondArr[] = {7};
    vector<int> secondV(secondArr, secondArr + sizeof(secondArr) / sizeof(int));

    int thridArr[] = {8};
    vector<int> thridV(thridArr, thridArr + sizeof(thridArr) / sizeof(int));

    int fourthArr[] = {9};
    vector<int> fourthV(fourthArr, fourthArr + sizeof(fourthArr) / sizeof(int));

    thread first(calcFields, firstV);
    thread second(calcFields, secondV);
    thread thrid(calcFields, thridV);
    thread fourth(calcFields, fourthV);
    
    first.join();
    second.join();
    thrid.join();
    fourth.join();
    
    return 0;
}
