#pragma once
#include "IViewController.hpp"
#include "SFML/Graphics.hpp"

class SFMLController : public Controller {
 private:

  std::shared_ptr<sf::RenderWindow> Window;
  
  MouseState::ClickType LastClick = MouseState::None;

 public:

  SFMLController(std::shared_ptr<sf::RenderWindow> window);

  bool ShutdownPending() override;
  MouseState GetMouseState() override;
};

class SFMLView : public View {
 private:

  size_t Width;
  size_t Height;
  std::string WindowName;

  std::shared_ptr<sf::RenderWindow> Window;

 private:

  void DrawRect(float x, float y, float w, float h, sf::Color color);
  void DrawVLine(float x, float s, sf::Color color);
  void DrawHLine(float y, float s, sf::Color color);

 public:

  SFMLView(std::shared_ptr<sf::RenderWindow> window);

  void Init(size_t width, size_t height, const std::string& wname) override;
  void DrawField(const Model::FieldT& field) override;
  void Stop() override;
};

class SFMLFactory {
 private:
  std::shared_ptr<sf::RenderWindow> Window;

 public:
  SFMLFactory();

  std::unique_ptr<View> CreateView();
  std::unique_ptr<Controller> CreateController();
};