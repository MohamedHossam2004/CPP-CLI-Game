//
// Created by Mohammed Hossam on 08/11/2023.
//

#ifndef PROGRAMMING_III_M1_POINT_H
#define PROGRAMMING_III_M1_POINT_H
class Point{
    int x;
    int y;

public:
    Point(int x, int y);

    Point();

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    virtual ~Point();
};
#endif //PROGRAMMING_III_M1_POINT_H
