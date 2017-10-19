#include "marker.h"
#include <math.h>

Marker::Marker(){
    id = 0;
    Position p;
    p.x = 0;
    p.y = 0;
    p.z = 0;
    p.vis = is_visible(0, 0, 0);
    p.time = 0;
    track.push_back(p);
}

Marker::Marker(unsigned int num, double x1, double y1, double z1, unsigned int time) {
    id = num;
    Position p;
    p.x = x1;
    p.y = y1;
    p.z = z1;
    p.vis = is_visible(x1, y1, z1);
    p.time = time;
    track.push_back(p);
}
Marker::Marker(unsigned int num, vector<Position> tr)
{
    id = num;
    for (int i = 0; i < tr.size(); i++)
        tr[i].vis = is_visible(tr[i].x, tr[i].y, tr[i].z);
    track = tr;
}


void Marker::delVec(unsigned int pos)
{
    if (pos>=track.size())
        std::cout<<"Error!"<<std::endl;
    else{

        track.erase(track.begin() + pos);
    }
}


Marker::Marker(const Marker &obj)
{
    id = obj.id;
    track = obj.track;
}

vector<Position> Marker::get_track()
{
    return track;
}

void Marker::show(){
    std::cout << track.size() << std::endl;
    cout <<"ID of marker: "<< id <<endl;
    for (int i = 0; i < track.size(); i++)
    {
        cout <<"Position num. "<<i+1<<endl;
        cout <<"Visibillity: "<<boolalpha <<track[i].vis<<endl;
        if (track[i].vis){
            cout <<"X:"<< track[i].x << endl;
            cout <<"Y:"<< track[i].y << endl;
            cout <<"Z:"<< track[i].z << endl;
            cout <<"T:"<< track[i].time << endl;
        }
    }
}
unsigned int Marker::get_id()
{
    return id;
}

double Marker::get_length()
{
    double res = 0;
    for (int i = 0; i < track.size() - 1; i++)
        res += sqrt(pow(track[i+1].x - track[i].x,2) + pow(track[i+1].y - track[i].y,2) +pow(track[i+1].z - track[i].z,2));
    return res;
}
int Marker::get_time()
{
    int res = 0;
    for(auto n: track)
        res += n.time;
    return res;
}
double Marker::get_av_speed()
{
    return get_length()/get_time();
}
double Marker::get_max_speed()
{
    double res = 0;
    for (int i = 0; i < track.size() - 1; i++)
    {
        double len = sqrt(pow(track[i+1].x - track[i].x,2) + pow(track[i+1].y - track[i].y,2) +pow(track[i+1].z - track[i].z,2));
        int time = track[i+1].time - track[i].time;
        if (len/time > res)
        {
            res = len/time;
        }
    }
    return res;
}
void Marker::append_track(vector<Position> value)
{
    track.insert(std::end(track), std::begin(value), std::end(value));
}

bool Marker::is_visible(double x, double y, double z) {
    return (x >=0 && x <= Mx && y >=0 && y<=My && z >=0 && z<=Mz);
}
