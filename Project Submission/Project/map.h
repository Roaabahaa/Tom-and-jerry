#ifndef MAP_H
#define MAP_H

#include <QVector>

class Map
{
public:
    Map(int **boardData);
    QVector<int> calculateShortestPath(int startVertex, int endVertex);

private:
    int matrix[126][126];
};

#endif // MAP_H
