
#include <iostream>
#include "Bottom.h"

Bottom::Bottom(int gridWidth, int gridHeight)
    : _gridHeight(gridHeight), _gridWidth(gridWidth) {

        auto c = Cell{false, Color(255,255,255)};
        _cells = std::vector<Cell>(_gridHeight*_gridWidth, c);
    }

//check if there is an intersection
Intersection Bottom::CheckIntersection(Tetrom* tetrom){
    Intersection ret{false, false, false};
    for(auto p:tetrom->GetCurrPoints()){
        //std::cout<<"Check point ("<<p.x<<","<<p.y<<") against";
        if(((p.y + 1) < _gridHeight) && cell(p.x, (p.y + 1)).filled){ret.Down |= true;}
        if(((p.x - 1) > 0)           && cell((p.x - 1), p.y).filled){ret.Left |= true;}
        if(((p.x + 1) < _gridWidth)  && cell((p.x + 1), p.y).filled){ret.Right |= true;}
    }
    
    return ret;
}

//Add tatrom to bottom
bool Bottom::Add(Tetrom *tetrom){
    Color tc(255,255,255);

    //Add all points to bottom
    for(auto p:tetrom->GetCurrPoints()){
        cell(p.x, p.y).filled = true;
        cell(p.x, p.y).color = Color::GetTetromColor(tetrom->type);
    }    
}