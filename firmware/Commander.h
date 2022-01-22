#ifndef Commander_H
#define Commander_H

#define A32 "Arylic32"

#include <Arduino.h>
#include <ArylicHTTP.h>

#include "BLEProps.h"
#include "Config.h"
#include "Wheel.h"
#include "Buttons.h"

class Commander {
  private:
    Config* cfgMgr;
    Wheel* encMgr;
    Buttons* btnMgr;
    ArylicHTTP* apiMgr;

  public:
    Commander(Config* cfgMgr);
    int getButtonCommand();
    boolean executeCommand(int cmd);
};

#endif
