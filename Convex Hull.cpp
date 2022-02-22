// Convex Hull.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <random>
#include <string>

using Point = std::pair<int, int>;
using std::vector;

/* Returns the Convex hull of points vector in order as you circle the points,could be slightly faster if unordered, however I felt an ordered list is more useful*/
vector<Point> & convexHull(vector<Point>& pointsVector) {
    vector<Point>* hull = new vector<Point>;
 
    pointsVector.push_back(pointsVector[0]);
    for (auto i = pointsVector.begin(); i < pointsVector.end()-1;i++) {
        for (auto j = pointsVector.begin(); j < pointsVector.end(); j++) {
            float a = j->second - i->second;
            float b = i->first - j->first;
            float c = i->first * j->second - j->first * i ->second;
            
            bool newSegment = true;
            bool sign;
            bool exteriorPoint = true;

            for (auto ptr = pointsVector.begin(); ptr < pointsVector.end(); ptr++) {
                float calc = a * (float)(ptr->first) + b*(float)(ptr->second) - c;          //calculating the sign of the line segment
                if (newSegment == true) {
                    sign = bool(calc > 0);                 //true for pos, false for neg
                    if (calc != 0) {                        //if calc is 0 then you are testing against a point used in the line segment
                        newSegment = false;
                    }
                }
                else {                                                  
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
            
            if (exteriorPoint == true && *i != *j) {                    //prevents the first point from being inserted as it is in the list twice
                hull->push_back(*i);
                j = pointsVector.end() - 1;                             //if it finds an edge solution involving the node i it does not continue the search as the other side will be found later
            }
           
        }
    }
    
    return *hull;
}

/*Not part of the problem but I figured I'd just make the file in this program for testing purposes*/
void RandomPointgenerator(int xMax, int yMax,int count) {
    std::ofstream file;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> randomx (0, xMax);
    std::uniform_int_distribution<int> randomy(0, yMax);
    
    file.open("DummyData.txt");
    
    for (int i = 0; i < count; ++i) {
        file << randomx(mt) << "," << randomy(mt) << std::endl;
    }
}

/* Reads in from a file and turns the file into a vector of points*/
vector<Point> &FileReader(std::string fileName) {
    std::ifstream in;
    vector<Point>* out = new vector<Point>;
    in.open(fileName);
    
    while (!in.eof()) {
        std::string coordinates;
        in >> coordinates;
        int end = coordinates.find(',');
        Point* x = new Point;
        
        if (coordinates != "") {                            //Makes sure coordinates isnt empty, extra endl or line
            x->first = std::stoi(coordinates.substr(0, end));
            x->second = std::stoi(coordinates.substr(end + 1, coordinates.length()));
            out->push_back(*x);
        }
    }
    
    return *out;
}
int main()
{
    RandomPointgenerator(1000, 1000, 100);                          //Generates the random file in case you would like to play around with it
    vector<Point> data = FileReader("DummyData.txt");
    for (auto i = data.begin(); i < data.end(); i++) {                        //prints the sample vector
        std::cout << i->first << "," << i->second << std::endl;
    }
    std::cout << std::endl;
    vector<Point> solutionCurve = convexHull(data);
    for (auto i = solutionCurve.begin(); i < solutionCurve.end(); i++) {
        std::cout << i->first << "," << i->second << std::endl;
    }

}