#include "Game.hpp"
#include "SFMLViewController.hpp"

int main() {
  Game::Config config;

  config.GridW = 40;
  config.GridH = 30;
  config.CellSizePx = 30;

  config.UpdatePeriod = 250; // ms
  
  SFMLFactory sfml;

  Game game {config, sfml.CreateView(), sfml.CreateController()};

  game.Run();
}