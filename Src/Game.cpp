#include "Game.hpp"

size_t Game::GetCellI(int y) const { return (float(y) / WSizeY) * Conf.GridH; }

size_t Game::GetCellJ(int x) const { return (float(x) / WSizeX) * Conf.GridW; }

Game::TimePoint Game::GetTime() const {
  return std::chrono::steady_clock::now();
}

long Game::GetTimeDiffMs(TimePoint t2, TimePoint t1) const {
  return std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
}

Game::Game(Config config, std::unique_ptr<View>&& view,
           std::unique_ptr<Controller>&& contr)
    : ViewPtr{std::move(view)}, ContrPtr{std::move(contr)}, Conf{config} {
  ModelPtr = std::make_unique<Model>(config.GridW, config.GridH);
  WSizeX = Conf.CellSizePx * Conf.GridW;
  WSizeY = Conf.CellSizePx * Conf.GridH;
}

void Game::Run() {
  ViewPtr->Init(WSizeX, WSizeY, "Game of Life");

  bool updateFlag = false;
  TimePoint lastUpdated = GetTime();

  while (!ContrPtr->ShutdownPending()) {
    ViewPtr->DrawField(ModelPtr->GetState());

    Controller::MouseState mouse = ContrPtr->GetMouseState();

    if (mouse.ClickUpdated && mouse.Click == mouse.Left) {
      size_t j = GetCellJ(mouse.X);
      size_t i = GetCellI(mouse.Y);

      ModelPtr->ToggleCell(i, j);
    }

    if (mouse.ClickUpdated && mouse.Click == mouse.Right) {
      updateFlag = !updateFlag;
    }

    if (updateFlag) {
      TimePoint now = GetTime();
      long msElapsed = GetTimeDiffMs(now, lastUpdated);

      if (msElapsed >= Conf.UpdatePeriod) {
        lastUpdated = now;
        ModelPtr->Update();
      }
    }
  }
}