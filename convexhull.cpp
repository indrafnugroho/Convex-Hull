//Indra Febrio Nugroho
//13518016
//20 Januari 2020
//Convex Hull

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <vector>
// #include <chrono>
using namespace std;
// using namespace std::chrono;

struct point {
    int x;
    int y;
} ;

int main () {
    int N;
    cout << "Input N : ";
    cin >> N;
    cout << endl;

    point P;
    point SetOfPoint[N];

    srand(time(NULL));
    for (int i=0; i<N; i++) {
        P.x = rand() % 100;
        P.y = rand() % 100;
        SetOfPoint[i] = P;
    }

    /*
    SetOfPoint[0].x = 10;
    SetOfPoint[0].y = 30;
    SetOfPoint[1].x = 12;
    SetOfPoint[1].y = 32;
    SetOfPoint[2].x = 45;
    SetOfPoint[2].y = 98;
    SetOfPoint[3].x = 65;
    SetOfPoint[3].y = 12;
    SetOfPoint[4].x = 5;
    SetOfPoint[4].y = 80;
    */

    vector<point> ListOfConvex;

    clock_t begin = clock();
    //Find the leftmost point in set of points
    point LeftMost = SetOfPoint[0];
    int IdxLM = 0;
    for (int i=1; i<N; i++) {
        if (SetOfPoint[i].x < LeftMost.x) {
            LeftMost = SetOfPoint[i];
            IdxLM = i;
        }
    }

    if (N==2) {
        ListOfConvex.push_back(LeftMost);
        for (int i=0; i<N; i++) {
            if (SetOfPoint[i].x == LeftMost.x && SetOfPoint[i].y == LeftMost.y && i==0) {
                continue;
            } else if (SetOfPoint[i].x == LeftMost.x && SetOfPoint[i].y == LeftMost.y && i==1) {
                break;
            } else {
                ListOfConvex.push_back(SetOfPoint[i]);
            }
        }
    } else {
        ListOfConvex.push_back(LeftMost);
        point CurrentPoint = SetOfPoint[IdxLM];
        int IdxCurrent = IdxLM;
        int IdxPrev = IdxLM;
        bool iLoop = true;

        while (iLoop) {
            int j=0;
            bool convexFound=false;
            while (j<N && !convexFound) {
                if (j==IdxCurrent || j==IdxPrev) {
                    j++;
                } else {
                    int a = SetOfPoint[j].y - CurrentPoint.y;
                    int b = SetOfPoint[j].x - CurrentPoint.x;
                    int c = (CurrentPoint.x * SetOfPoint[j].y) - (CurrentPoint.y * SetOfPoint[j].x);

                    int k=0;
                    int LSide=0, RSide=0;
                    bool found = false;
                    while (k<N && !found) {
                        if (k==IdxCurrent || k==j) {
                            k++;
                        } else {
                            int CheckVal = (a * SetOfPoint[k].x) - (b * SetOfPoint[k].y) - c;

                            if (CheckVal < 0) {
                                LSide++;
                            } else if (CheckVal > 0) {
                                RSide++;
                            }

                            if (LSide>0 && RSide>0) {
                                found=true;
                            }
                            k++;
                        }
                    }
                    if (!found) {
                        IdxPrev = IdxCurrent;
                        IdxCurrent = j;
                        CurrentPoint = SetOfPoint[j];
                        ListOfConvex.push_back(SetOfPoint[j]);
                        convexFound = true;
                    }
                    j++;
                }
            }
            if (CurrentPoint.x == LeftMost.x && CurrentPoint.y == LeftMost.y) {
                iLoop = false;
                //ListOfConvex.push_back(CurrentPoint);
            }
        }
    }
    clock_t end = clock();

    //Output Program
    cout << "Set of Points that shapes the convex hull is\n";
    cout << '[';
    for (auto i = ListOfConvex.begin(); i != ListOfConvex.end(); i++) {
        cout << '(' << (*i).x << ',' << (*i).y << ")";
    }
    cout << "]\n\n";

    cout << "Execution time: ";
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << elapsed_secs << " seconds" << endl << endl;

    cout << "This program is executed in a computer with spesification below\n" ;
    cout << "Processor: AMD E-300 APU with Radeon HD Graphics 1.30 GHz\n";
    cout << "RAM: 2GB\n";
    cout << "Operating system: Windows 10 64bit\n";
    return 0;
}