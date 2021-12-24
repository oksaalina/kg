#include "graphics.h"
#include "Prism.h"
#include "Parallelepiped.h"
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void hud(vector<Figure*>& figures) {
    vector<BaseFigure*> triangles;
    for (int i = 0; i < figures.size(); i++) {
        figures[i]->projection();
        vector<BaseFigure*> tmp = figures[i]->getTriandles();
        for (auto triangle : tmp)
            triangles.push_back(triangle);
    }
    for (int i = 1; i < triangles.size(); i++) {
        for (int j = 0; j < triangles.size() - i; j++)
            if (triangles[j]->getMidZ() < triangles[j + 1]->getMidZ())
                swap(triangles[j], triangles[j + 1]);
    }

    for (int i = 0; i < triangles.size(); i++) {
        triangles[i]->print();
        triangles[i]->painting();
    }
}

void shadow(vector<Figure*>& figures, Point3D l) {
    for (int i = 0; i < figures.size(); i++)
        figures[i]->parintShadow(l);
}

void setMax(vector<Figure*>& figures, int maxX, int maxY) {
    for (int i = 0; i < figures.size(); i++)
        figures[i]->setMax(maxX, maxY);
}

void drowTask(vector<Figure*>& figures, Point3D& l) {
    cleardevice();
    hud(figures);
    shadow(figures, l);
}

void transfer(vector<Figure*>& figures, int number, double dx, double dy, double dz) {
    for (int i = 0; i < figures.size(); i++)
        if (number == 0 || i == number - 1)
            figures[i]->transfer(dx, dy, dz);
}

void scale(vector<Figure*>& figures, int number, double sx, double sy, double sz) {
    for (int i = 0; i < figures.size(); i++)
        if (number == 0 || i == number - 1)
            figures[i]->scale(sx, sy, sz);
}

void rotation(vector<Figure*>& figures, int number, double angle, Axises axis) {
    for (int i = 0; i < figures.size(); i++)
        if (number == 0 || i == number - 1)
            figures[i]->rotation(angle, axis);
}

vector<Figure*> createTask() {
    Parallelepiped* parallelepiped = new Parallelepiped(
        Point3D(50, 50, 100), Point3D(100, 50, 100), Point3D(100, 100, 100), Point3D(50, 100, 100),
        Point3D(50, 50, 200), Point3D(100, 50, 200), Point3D(100, 100, 200), Point3D(50, 100, 200),
        BLUE, GREEN, RED, YELLOW, CYAN, BROWN);
    Prism* prism = new Prism(
        Point3D(200, 225, 100), Point3D(230, 200, 100), Point3D(260, 200, 100), Point3D(290, 225, 100), Point3D(260, 250, 100), Point3D(230, 250, 100),
        Point3D(200, 225, 200), Point3D(230, 200, 200), Point3D(260, 200, 200), Point3D(290, 225, 200), Point3D(260, 250, 200), Point3D(230, 250, 200),
        BLUE, GREEN, RED, YELLOW, CYAN, BROWN, MAGENTA, DARKGRAY);
    vector<Figure*> figures;
    figures.push_back(parallelepiped);
    figures.push_back(prism);
    return figures;
}

int main() {

    //инициализация графического окна
    int gm, gd = DETECT;
    char a[2] = " ";
    initgraph(&gd, &gm, a);
    const int maxX = getmaxx() - 10, maxY = getmaxy() - 10;
    vector<Figure*> figures = createTask();
    setMax(figures, maxX, maxY);
    double range = 10, rel = 1.1, angle = 10;
    Point3D l(0, 0, 0);  //источник света
    drowTask(figures, l);
    bool isExit = false;
    int number = 0;
    while (!isExit)
    {
        //обработка нажатий
        switch (getch())
        {
        case 48: //0
            number = 0;
            break;
        case 49: //1
            number = 1;
            break;
        case 50: //2
            number = 2;
            break;
        case 116: //t
            transfer(figures, number, 0, 0, range);
            drowTask(figures, l);
            break;
        case 103: //g
            transfer(figures, number, 0, 0, -range);
            drowTask(figures, l);
            break;
        case 119: //w
            transfer(figures, number, 0, -range, 0);
            drowTask(figures, l);
            break;
        case 115: //s
            transfer(figures, number, 0, range, 0);
            drowTask(figures, l);
            break;
        case 97: //a
            transfer(figures, number, -range, 0, 0);
            drowTask(figures, l);
            break;
        case 100: //d
            transfer(figures, number, range, 0, 0);
            drowTask(figures, l);
            break;
        case 102: //minus - f
            scale(figures, number, 1.0 / rel, 1.0 / rel, 1.0 / rel);
            drowTask(figures, l);
            break;
        case 114: //plus - r
            scale(figures, number, rel, rel, rel);
            drowTask(figures, l);
            break;
        case 113: //q      
            rotation(figures, number, -angle, Axises::Z);
            drowTask(figures, l);
            break;
        case 101: //e
            rotation(figures, number, angle, Axises::Z);
            drowTask(figures, l);
            break;
        case 72: //Up      
            rotation(figures, number, -angle, Axises::X);
            drowTask(figures, l);
            break;
        case 80: //Down
            rotation(figures, number, angle, Axises::X);
            drowTask(figures, l);
            break;
        case 75: //Left    
            rotation(figures, number, angle, Axises::Y);
            drowTask(figures, l);
            break;
        case 77: //Right
            rotation(figures, number, -angle, Axises::Y);
            drowTask(figures, l);
            break;
        case 27:
            isExit = true;
            break;
        }
    }
    //закрытие графического окна
    closegraph();
}