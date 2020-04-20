
#include <iostream>
#include "Bottom.h"

Bottom::Bottom(int gridWidth, int gridHeight)
    : _gridHeight(gridHeight), _gridWidth(gridWidth) {}

//check if there is an intersection
Intersection Bottom::CheckIntersection(Tetrom* tetrom){
    Intersection ret{false, false, false};
    for(auto p:tetrom->GetCurrPoints()){
        //std::cout<<"Check point ("<<p.x<<","<<p.y<<") against";
        for(auto c:_cells){
            //std::cout<<" ("<<c.p.x<<","<<c.p.y<<") ";
            ret |= c.p.CheckNeighbour(p);
            if(ret == Intersection{true,true,true}){
                return ret;
            }
        }
    }
    
    return ret;
}

//Add tatrom to bottom
bool Bottom::Add(Tetrom *tetrom){
    Color tc(255,255,255);
    switch(tetrom->type){
        case TetromType::I:{tc = IColor;break;}
        case TetromType::S:{tc = SColor;break;}
        case TetromType::L:{tc = LColor;break;}
        case TetromType::O:{tc = OColor;break;}
        case TetromType::T:{tc = TColor;break;}
    }

    //Add all points to bottom
    for(auto p:tetrom->GetCurrPoints()){
        _cells.emplace_back(Cell{{p.x, p.y}, tc});
    }    
}