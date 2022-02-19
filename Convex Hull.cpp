// Convex Hull.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using Point = std::pair<int, int>;

std::vector<Point> convexHull(std::vector<Point>& pointsVector) {
    std::vector<Point> hull;
 
    pointsVector.push_back(pointsVector[0]);
    for (auto i = pointsVector.begin(); i < pointsVector.end()-1;i++) {
        for (auto j = i+1; j < pointsVector.end(); j++) {
            float a = j->second - i->second;
            float b = i->first - j->first;
            float c = i->first * j->second - j->first * i ->second;
            bool newSegment = true;
            bool sign;
            bool exteriorPoint = true;
            for (auto ptr = pointsVector.begin(); ptr < pointsVector.end(); ptr++) {
                float calc = a * (ptr->first) + b*(ptr->second) - c;
                if (newSegment == true) {
                    sign = bool(calc > 0);                 //true for pos, false for neg, 0 is pos
                    if (calc != 0) {
                        newSegment = false;
                    }
                }
                else {                                                  //End the search on this segment
                    if (sign == 1 && calc < 0) {
                        ptr = pointsVector.end()-1;
                        exteriorPoint = false;
                    }
                    if(sign == 0 && calc > 0){
                        ptr = pointsVector.end()-1;
                        exteriorPoint = false;
                    }
                }
            }
            /* Thought here what if we just push back the starting node and at the start push the first node onto the end of the vector so it checks them all? maybe*/
            if (exteriorPoint == true) {
                if(std::find(hull.begin(),hull.end(),*i) == hull.end())
                    hull.push_back(*i);
            }
           
        }
    }
    //may not need the unique check
    
    //hull.u
    return hull;
}

int main()
{
    std::vector<Point> test = { {4,5},{3,9},{4,13},{7,12},{9,10},{9,5},{7,8},{6,7},{6,12}};
    std::vector<Point> out = convexHull(test);
    for (auto i = out.begin(); i < out.end(); i++) {
        std::cout << i->first << "," << i->second << std::endl;
    }
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
