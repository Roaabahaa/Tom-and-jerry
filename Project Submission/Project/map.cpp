#include "map.h"
#include <QString>
#include <QDebug>
#include <iostream>
#include <QFile>
#include <QTextStream>

const int INF = 99999;

Map::Map(int **boardData)
{
    // initlize the 2D array to zeros
    for(int i=0; i<122; i++)
        for(int j=0; j<122; j++)
            matrix[i][j] = 0;

    // populate the adjacency matrix with edges
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (boardData[i][j] >= 0)
            {
                // check if upper node is not a wall
                if (boardData[i-1][j] >= 0)
                {
                    matrix[boardData[i][j]][boardData[i - 1][j]] = 1;
                }

                // check if lower node is not a wall
                if (boardData[i+1][j] >= 0)
                {
                    matrix[boardData[i][j]][boardData[i + 1][j]] = 1;
                }

                // check if left node is not a wall
                if (boardData[i][j-1] >= 0)
                {
                    matrix[boardData[i][j]][boardData[i][j-1]] = 1;
                }

                // check if right node is not a wall
                if (boardData[i][j+1] >= 0)
                {
                    matrix[boardData[i][j]][boardData[i][j+1]] = 1;
                }
            }
        }
    }


    QFile file("C:/Users/moham/Desktop/Fall 2021/CS2/GameImages/test.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      // We're going to streaming text to the file
      QTextStream stream(&file);
      for(int i=0; i<122; i++)
      {
          for(int j=0; j<122; j++)
              stream << QString::number(matrix[i][j]) + " ";
          stream << "\n\r";
      }
      file.close();
      qDebug() << "Writing finished";
    }

}

QVector<int> Map::calculateShortestPath(int startVertex, int endVertex)
{
    QVector<int> path;
    if(endVertex < 0)
    {
        // return empty path to make the characters stay still
        return path;
    }
    bool done[122];
    int previous[122];
    double cost[122];

    double temp[122][122];
    for (int i = 0; i < 122; i++)
        for (int j = 0; j < 122; j++)
            if (matrix[i][j] == 0)
                temp[i][j] = INF;
            else
                temp[i][j] = matrix[i][j];

    for (int i = 0; i < 122; i++)
    {
        if (i == startVertex)
        {
            done[i] = true;
            previous[i] = -1;
            cost[i] = 0;
        }
        else
        {
            done[i] = false;
            previous[i] = startVertex;
            cost[i] = temp[startVertex][i];
        }
    }

    int count = 1;

    while (count < 122)
    {
        // Which vertex is done?
        // Vertex with the lowest cost.
        double minimum = INF;
        int currentVertex;
        for (int i = 0; i < 122; i++)
        {
            if (done[i] == false && cost[i] < minimum)
            {
                minimum = cost[i];
                currentVertex = i;
            }
        }
        done[currentVertex] = true;
        //
        for (int i = 0; i < 122; i++)
        {
            if (done[i] == false)
            {
                double value = cost[currentVertex] + temp[currentVertex][i];
                if (value < cost[i])
                {
                    cost[i] = value;
                    previous[i] = currentVertex;
                }
            }
        }
        count++;
    }
    int j;
    path.push_back(endVertex);
    j = endVertex;// to return only the path we were interested in
    while (j != startVertex)
    {
        path.insert(path.begin(), previous[j]);
        j = previous[j];
    }
    path.removeAt(0);
    return path;
}
