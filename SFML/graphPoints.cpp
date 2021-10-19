#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "graphPoints.h"

graphPoints::graphPoints() {};
graphPoints::graphPoints(sf::CircleShape _shape) {};

void graphPoints::loadPoints(std::string _fileName) {
    std::ifstream dataStream;
    std::string line;

#pragma region CSV File Reading
    dataStream.open("HeartRate.csv");                                   // open file to a data stream for reading
    if (dataStream.is_open())                                           // check if file is open - e.g. it could be in the wrong folder
    {
        char next = dataStream.peek();                                  // take a peek at the next data character - i.e. only look, don't read
        while (next != EOF)                                             // if the next character is not the end of file then continue to read data
        {
            std::getline(dataStream, line);                             // get a line of text from the file
            std::stringstream lineStream(line);                         // create a line stream                      
            std::string character;
            std::vector<std::string> parsedRow;                         // a 2d vector - many rows of point co-ordinates                        
            while (std::getline(lineStream, character, ','))            // we  read a row at a time and parse it to get rid of the comma
            {
                parsedRow.push_back(character);                         // push a character at a time into the vector row (x and y co-ordinates)
                std::cout << std::stoi(character) << " ";               // print out to check
            }
            std::cout << std::endl;
            cords.push_back(parsedRow);                                 // push the parsed row into the vector list of co-ordinates

            next = dataStream.peek();                                   // take a sneek peek at the next character in case its the end of file character
        }

    }
    dataStream.close();
#pragma endregion

#pragma region Create Graph points 
    // add an SFML circle object (as a graph point) to our points vector list
// set positions of graph points from point co-ordinates loaded in from CSV file
    for (int i = 0; i < cords.size(); ++i) // for number of rows (300 in this example)
    {
        addPoint(sf::Color(255, 0, 0), 1, sf::Vector2u(1, 1), sf::Vector2f(0, 0));
        addLineY(sf::Color(0, 0, 255), 1, sf::Vector2u(0, -25 ), sf::Vector2f(0, 25));
        for (int j = 0; j < cords[j].size(); ++j) // for number of columns (2)
        {
            if (j == 0) points[i].setPosition(sf::Vector2f(float(stoi(cords[i][j])+25), 0)); // x coordinate +++++++++++++++++++++++++++ side note added 25 to cords
            if (j == 1) points[i].setPosition(sf::Vector2f(points[i].getPosition().x + gap * 2, float(stoi(cords[i][j])) -25)); // y coordinate
        
            if (i % 50==0) {
                if (j == 0) lines[i].setPosition(sf::Vector2f(float(stoi(cords[i][j]) + 25), 0)); // x coordinate for lines
                if (j == 1) lines[i].setPosition(sf::Vector2f(lines[i].getPosition().x + gap * 2, float(stoi(cords[0][0])))); // y coordinate for lines
            }
        }
        
    }
#pragma endregion
  
};
void graphPoints::addPoint(sf::Color clr, int radius, sf::Vector2u origin, sf::Vector2f position) {
    sf::CircleShape pt; pt.setFillColor(clr); pt.setRadius(radius); pt.setOrigin(radius, radius); pt.setPosition(position);
    
    points.push_back(pt);
};


void graphPoints::addLineY(sf::Color clr, int radius, sf::Vector2u origin, sf::Vector2f position) {
    sf::RectangleShape pR; pR.setFillColor(clr); pR.setSize(sf::Vector2f(1, 60)); pR.setOrigin(radius, radius); pR.setPosition(position);

    lines.push_back(pR);
};
void graphPoints::setPointColor(int index, sf::Color _color) {};
void graphPoints::clearPointList() {};

void graphPoints::drawPoints(sf::RenderWindow &_win) {
    for (int i = 0; i < points.size(); ++i)
    {
        _win.draw(points[i]);
        _win.draw(lines[i]);
        
    }
};