#ifndef CONTROLLER_H
#define CONTROLLER_H

#include<memory>

#include "Tetrom.h"


class Controller {
public:
  void HandleInput(bool &running, std::shared_ptr<Tetrom> tetrom) const;

private:


};

#endif