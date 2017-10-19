#ifndef MARKER_H
#define MARKER_H


#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <string>

using namespace std;


const double Mx = 1000, My = 1000, Mz = 1000;

struct Position{
    double x, y, z;
    int time;
    bool vis;
};

class Marker{
public:
    Marker(unsigned int num, double x1, double y1, double z1, unsigned int time);
    Marker(unsigned int num, vector<Position> tr);
    Marker();
    Marker(const Marker &obj);
    //~Marker ();

    vector<Position> get_track();
    unsigned int get_id();

    void show();
    bool contain(unsigned int m_f_check);
    double get_length();
    void append_track(vector<Position> value);
    int get_time();
    double get_av_speed();
    double get_max_speed();
    void delVec(unsigned int pos);

private:
    unsigned int id;
    vector<Position> track;
    bool is_visible(double x, double y, double z);
};



#endif // MARKER_H
