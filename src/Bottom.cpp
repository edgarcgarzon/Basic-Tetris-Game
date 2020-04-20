
#include "Bottom.h"

Bottom::Bottom(int gridWidth, int gridHeight)
    : _gridHeight(gridHeight), _gridWidth(gridWidth) {}

//check if there is an intersection
bool Bottom::CheckIntersection(std::shared_ptr<Tetrom> tetrom){
    for(auto p:tetrom->GetCurrPoints()){
        for(auto c:_cells){
            if(p.neighbour(c.p)){return true;}
        }
    }
    
    return false;
}

//Add tatrom to bottom
bool Bottom::Add(std::shared_ptr<Tetrom> tetrom){
    Color tc(255,255,255);
    switch(tetrom->type){
        case TetromType::I:{tc = IColor;break;}
        case TetromType::S:{tc = SColor;break;}
        case TetromType::L:{tc = LColor;break;}
        case TetromType::O:{tc = OColor;break;}
        case TetromType::T:{tc = TColor;break;}
    }

    //Add all points to bottom
    for(auto p:tetrom->GetCurrPoints){
        _cells.emplace_back(Cell{{p.x, p.y}, tc});
    }    
}