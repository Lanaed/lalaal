#include "markerarray.h"
#include <cstring>
#include <fstream>

MarkerArray::MarkerArray()
{
    _elementsCount = 0;
    _base = NULL;
}

//создание массива
MarkerArray::MarkerArray(unsigned int elementsCount)
{
    _elementsCount = elementsCount;
    _base = new Marker[elementsCount];
}

//обращение к элементу
Marker MarkerArray::at(unsigned int position)
{
    return _base[position];
}


//установка значений
void MarkerArray::setValue(unsigned int position, Marker value)
{
    _base[position] = value;
}


//изменение размера массива
void MarkerArray::resize(unsigned int size)
{
    Marker* _old_base = _base;
    _base = new Marker[size];
    for (int i = 0; i < size - 1; i++)
        _base[i] = _old_base[i];
    _elementsCount = size;
}

//для удаления элемента
void MarkerArray::remove(unsigned int position)
{
    std::copy(_base + position,
              _base + _elementsCount - 1,
              _base + position - 1);
    _elementsCount--;
}


int MarkerArray::contains(unsigned int value)
{
    int i;
    for (i = 0; i < _elementsCount && _base[i].get_id() !=value; i++);
    if (i>=_elementsCount)
            return -1;
    else
        return i;
}

//для добавления элемента
void MarkerArray::append(Marker value)
{
    int pos = contains(value.get_id());
    if (pos > -1)
        _base[pos].append_track(value.get_track());
    else
    {
        resize(_elementsCount + 1);
        //std::cout << "Adding Value" << std::endl;
        _base[_elementsCount - 1] = value;
    }
}

//проверка на пустоту
bool MarkerArray::isEmpty()
{
    return _elementsCount == 0;
}

//считывание массива из файла
void MarkerArray::getArray(string filepath)
{
    ifstream inputFile;
    _elementsCount = 0;
    inputFile.open(filepath, std::ios::in|ios::binary);
    //inputFile >> _elementsCount;
    //resize(_elementsCount);
    while (true)
    {
        int id;
        int trackSize;
        inputFile >> id >> trackSize;
        if (inputFile.eof())
            break;
        vector<Position> track;
        for (int i = 0; i < trackSize; i++)
        {
            int x,y,z, time;
            bool vis;
            inputFile >> x >> y >> z >> time;// >> vis;

            Position p;
            p.x = x;
            p.y = y;
            p.z = z;
            p.time = time;
            //p.vis = vis;
            track.push_back(p);
        }
        //std::cout << "Here with " << track[0].x << " " << track[0].y << " " << track[0].z << std::endl;
        append(Marker(id, track));
    }
}

//запись массива в файл
void MarkerArray::toFile(string filepath)
{
    ofstream outFile;
    outFile.open(filepath, std::ios::out);
    //outFile << _elementsCount << " ";
    for (int i = 0; i < _elementsCount; i++)
    {
        outFile << at(i).get_id() << " ";
        outFile << at(i).get_track().size() << " ";
        for (int j = 0; j < at(i).get_track().size(); j++)
            outFile << at(i).get_track()[j].x << " " << at(i).get_track()[j].y << " "
                    << at(i).get_track()[j].z << " " << at(i).get_track()[j].time<<" ";
                    //<< " " << at(i).get_track()[j].vis << " ";
    }

}


//определение размера массива
unsigned int MarkerArray::size()
{
    return _elementsCount;
}
