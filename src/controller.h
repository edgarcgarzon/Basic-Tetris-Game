#ifndef CONTROLLER_H
#define CONTROLLER_H

#include<memory>

#include "Tetrom.h"


class Controller {
public:
  void HandleInput(bool &running, Tetrom* tetrom) const;

private:


};

#endif