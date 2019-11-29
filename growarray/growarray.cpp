/*
Author: Ethan Jones
Pledge: I pledge my honor that I have abided by the stevens honor system
*/

#include <stdio.h>
#include <stdlib.h>
//#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

class Point
{
public:
  double x, y;
};

template < typename T >
class GrowArray
{
private:
  int capacity;
  int used;
  T *data;

  void grow ()
  {
    T *old = data;
    data = new T[capacity *= 2];
    for (int i = 0; i < used; i++)
      {
	data[i] = old[i];
      }
  }

public:
GrowArray ():capacity (1), used (0), data (new T[capacity])
  {
  }
  GrowArray (int initialSize)
  {
    capacity = initialSize;
    used = 0;
    data = new T[capacity];
  }
  ~GrowArray ()
  {
    delete[]data;
  }
  GrowArray (const GrowArray& orig) = delete;
  GrowArray& operator =(const GrowArray& orig) = delete;


  void addEnd (T v)
  {
    if (used >= capacity)
      grow ();
    data[used++] = v;
  }
  void addStart (T v)
  {
    if (used >= capacity)
      grow ();
    for (int i = used - 1; i >= 0; i--)
      data[i + 1] = data[i];
    data[0] = v;
    used++;
  }
  void insert (int i, T v)
  {
    if (i < 0 || i > used)
      throw "index is not inside the array.";
    if (used >= capacity)
      grow ();
    for (int x = used - 1; x >= i; x--)
      data[x + 1] = data[x];
    data[i] = v;
    used++;
  }
  void removeEnd ()
  {
    if (used < 1)
      throw "there is nothing to remove.";
    used--;
  }
  void removeStart ()
  {
    if (used < 1)
      throw "there is nothing to remove.";
    for (int i = 0; i < used - 1; i++)
      data[i] = data[i + 1];
    used--;
  }
  void remove (int i)
  {
    if (i < 0 || i >= used)
      throw "index is not inside the array.";
    for (int x = i; x < used - 1; x++)
      data[x] = data[x + 1];
    used--;
  }
  int size () const
  {
    return used;
  }
  int get (int i) const
  {
    if (i < 0 || i > used)
      throw "index is not inside the array.";
    return data[i];
  }
};

void read(string filename){
    point input;
    float x, y;
    ifstream f;

    f.open(filename);
    while(f >> x >> y)
    {
        input.x = x;
        input.y = y;
        arr.addEnd(input);
    }
    f.close();
}

void printMinMax(){
    xMax = arr.get(0).x;
    xMin = arr.get(0).x;
    yMax = arr.get(0).y;
    yMax = arr.get(0).y;
    for(int i = 0; i < arr.size(); i++){
                if (arr.get(i).x > xMax) {
            xMax = arr.get(i).x;
        }
        if (arr.get(i).x < xMin) {
            xMin = arr.get(i).x;
        }
        if (arr.get(i).y > yMax) {
            yMax = arr.get(i).y;
        }
        if (arr.get(i).y < yMin) {
            yMin = arr.get(i).y;
        }
    }
    cout << "Min X: " << xMin << ", Max X: " << xMax << ", Min Y: " << yMin << ", Max Y: " << yMax << endl;
}

void makeGrid () {
    int a, b;
    for (int i = 0; i < arr.size(); i++) {
        a = (int) (round((arr.get(i).y - yMin) / (yMax - yMin) * 7));
        b = (int) (round((arr.get(i).x - xMin) / (xMax - xMin) * 7));
        rectangle[a][b].addEnd(arr.get(i));
    }
}

void printGrid () {
    for (int i = 0; i < 8; i++) {
        cout << "Cell: (" << i << ",0):" << endl;
        for (int j = 0; j < rectangle[i][0].size(); j++) {
            cout << "(" << rectangle[i][0].get(j).x << "," << rectangle[i][0].get(j).y << ") ";
        }
        cout << endl;
    }
    for (int i = 1; i < 8; i++) {
        cout << "Cell: (7, " << i << "):" << endl;
        for (int j = 0; j < rectangle[7][i].size(); j++) {
            cout << "(" << rectangle[7][i].get(j).x << "," << rectangle[7][i].get(j).y << ") ";
        }
        cout << endl;
    }
    for (int i = 7; i > 0; i--) {
        cout << "Cell: (" << i-1 << ", 7):" << endl;
        for (int j = 0; j < rectangle[i][7].size(); j++) {
            cout << "(" << rectangle[i][7].get(j).x << "," << rectangle[i][7].get(j).y << ") ";
        }
        cout << endl;
    }
    for (int i = 7; i > 1; i--) {
        cout << "Cell: (0, " << i-1 << "):" << endl;
        for (int j = 0; j < rectangle[0][i].size(); j++) {
            cout << "(" << rectangle[0][i].get(j).x << "," << rectangle[0][i].get(j).y << ") ";
        }
        cout << endl;
    }
}

float xMin, xMAX, yMin, yMax;
GrowArray <point> arr;
GrowArray <point> matrix[8][8];

  int main ()
  {
    read("convexhullpoint.dat");
    printMinMax();
    makeGrid();
    printGrid();
  }
