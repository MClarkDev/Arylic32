#ifndef Commander_H
#define Commander_H

#define A32 "Arylic32"

#include <Arduino.h>
#include <HTTPClient.h>

#include "BLEProps.h"
#include "Config.h"
#include "Wheel.h"
#include "Buttons.h"

class Commander {
  private:
    Config* cfgMgr;
    Wheel* encMgr;
    Buttons* btnMgr;
    String get(String url);

  public:
    Commander(Config* cfgMgr);
    int getButtonCommand();
    boolean executeCommand(int cmd);
};

#endif
