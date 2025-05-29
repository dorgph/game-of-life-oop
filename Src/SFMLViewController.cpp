#include <SFMLViewController.hpp>

SFMLController::SFMLController(std::shared_ptr<sf::RenderWindow> window)
    : Window{window} {}

bool SFMLController::ShutdownPending() {
  while (std::optional event = Window->pollEvent())
    if (event->is<sf::Event::Closed>()) return true;

  return false;
}

SFMLController::MouseState SFMLController::GetMouseState() {
  auto pos = sf::Mouse::getPosition(*Window);

  MouseState state{MouseState::None, false, pos.x, pos.y};

  if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    state.Click = MouseState::Left;

  if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
    state.Click = MouseState::Right;

  if (state.Click != LastClick) {
    state.ClickUpdated = true;
    LastClick = state.Click;
  }

  return state;
}

void SFMLView::DrawRect(float x, float y, float w, float h, sf::Color color) {
  sf::RectangleShape rect({w, h});
  rect.setPosition({x, y});
  rect.setFillColor(color);

  Window->draw(rect);
}

void SFMLView::DrawVLine(float x, float s, sf::Color color) {
  sf::RectangleShape rect({s, float(Height)});
  rect.setPosition({x, 0});
  rect.setFillColor(color);

  Window->draw(rect);
}

void SFMLView::DrawHLine(float y, float s, sf::Color color) {
  sf::RectangleShape rect({float(Width), s});
  rect.setPosition({0, y});
  rect.setFillColor(color);

  Window->draw(rect);
}

SFMLView::SFMLView(std::shared_ptr<sf::RenderWindow> window)
    : View{}, Window{window} {}

void SFMLView::Init(size_t width, size_t height, const std::string& wname) {
  Width = width;
  Height = height;
  WindowName = wname;

  unsigned int uwidth = width;
  unsigned int uheight = height;

  *Window = sf::RenderWindow(sf::VideoMode({uwidth, uheight}), wname);
}

void SFMLView::DrawField(const Model::FieldT& field) {
  size_t fHeight = field.size();
  size_t fWidth = field[0].size();

  float cellWidthPx = float(Width) / fWidth;
  float cellHeightPx = float(Height) / fHeight;

  Window->clear(sf::Color::White);

  float lineWidth = 1;
  sf::Color grey{100, 100, 100};

  for (int i = 1; i < fHeight; ++i)
    DrawHLine(i * cellHeightPx, lineWidth, grey);

  for (int j = 1; j < fWidth; ++j) DrawVLine(j * cellWidthPx, lineWidth, grey);

  for (int i = 0; i < fHeight; ++i)
    for (int j = 0; j < fWidth; ++j)
      if (field[i][j])
        DrawRect(j * cellWidthPx, i * cellHeightPx, cellWidthPx, cellHeightPx,
                 sf::Color::Black);

  Window->display();
}

void SFMLView::Stop() { Window->close(); }

SFMLFactory::SFMLFactory() : Window{std::make_shared<sf::RenderWindow>()} {}

std::unique_ptr<IView> SFMLFactory::CreateView() {
  return std::make_unique<SFMLView>(Window);
}

std::unique_ptr<Controller> SFMLFactory::CreateController() {
  return std::make_unique<SFMLController>(Window);
}