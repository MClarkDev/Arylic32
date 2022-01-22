#include "Commander.h"

Commander::Commander(Config* cfgMgr) {
  this->cfgMgr = cfgMgr;

  encMgr = new Wheel();
  btnMgr = new Buttons();

  apiMgr = new ArylicHTTP(cfgMgr->getTargetIP());
}

int Commander::getButtonCommand() {

  // load button values
  int btn = btnMgr->processButtons();
  int dir = encMgr->getDirection();

  // jog if action present, else button
  return (dir != 0) ? 98 + dir : btn;
}

boolean Commander::executeCommand(int cmd) {
  ESP_LOGD(A32, "Running command: %d", cmd);

  switch (cmd) {
    case 1: // N
      apiMgr->preset(1);
      break;
    case 2: // E
      apiMgr->playbackNext();
      break;
    case 3: // NE
      break;
    case 4: // S
      apiMgr->groupLeave();
      break;
    case 6: // SE
      break;
    case 8: // W
      apiMgr->playbackPrev();
      break;
    case 9: // NW
      break;
    case 12: // SW
      break;
    case 16: // C
      apiMgr->playbackTogglePlay();
      break;
    case 97: // Jog Down
      apiMgr->setVolumeStepDown();
      break;
    case 99: // Jog Up
      apiMgr->setVolumeStepDown();
      break;
    default:
      return false;
      break;
  }

  btnMgr->clearButtons();
  return true;
}
