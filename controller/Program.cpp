#include "Program.hpp"

Program::Program()
{
  conf.load();
}

void Program::tick()
{
  if (pCurrentActivity)
  {
    if (pauseMenu.isActive())
    {
      pauseMenu.tick();
      if (pauseMenu.didUnpause())
      {
        pCurrentActivity->unpause();
      }
      if (pauseMenu.didQuit())
      {
        pCurrentActivity = nullptr;
      }
    }
    else if (inputs.shouldPause())
    {
      pCurrentActivity->pause();
      pauseMenu.enable();
    }
    else
    {
      pCurrentActivity->tick();
      if (pCurrentActivity->didFinish())
      {
        dataMgr.recordActivity(*pCurrentActivity);
        pCurrentActivity = nullptr;
      }
    }
  }
  else
  {
    mainMenu.tick();
    pCurrentActivity = mainMenu.getActivitySelection();
    if (pCurrentActivity)
    {
      pCurrentActivity->start(conf);
    }
  }
}
