#include <iostream>
#include <memory>

class Unit {
  public:
  void moveTo(int x, int y) {
    x_ = x;
    y_ = y;
    std::cout << "Current position is: x: " << x_ << " y:" << y_ << std::endl;
  }
  int x() { return x_; }
  int y() { return y_; }

  private:
  int x_ = 0, y_ = 0;
};

class Command {
  public:
  virtual ~Command() {}
  virtual void execute() = 0;
  virtual void undo() = 0;
};

class MoveUnitCommand : public Command {
  public:
  MoveUnitCommand(const Unit& unit, int x, int y)
      : unit_(unit), x_(x), y_(y), xBefore_(0), yBefore_(0) {}
  virtual void execute() {
    xBefore_ = unit_.x();
    yBefore_ = unit_.y();
    unit_.moveTo(x_, y_);
  }

  virtual void undo() { unit_.moveTo(xBefore_, yBefore_); }

  private:
  Unit unit_;
  int x_, y_, xBefore_, yBefore_;
};

class InputHandler {
  public:
  ~InputHandler() {}

  std::unique_ptr<Command> handleInput(int input) {
    Unit unit;
    if (input == BUTTON_UP)
      return std::make_unique<MoveUnitCommand>(unit, unit.x(), unit.y() - 1);
    else if (input == BUTTON_DOWN)
      return std::make_unique<MoveUnitCommand>(unit, unit.x(), unit.y() + 1);
    return nullptr;
  }

  private:
  int BUTTON_UP = 0;
  int BUTTON_DOWN = 1;
};

int main() {
  std::cout << "Command pattern: Undo & Redo example" << std::endl;
  InputHandler inputHandler;
  std::unique_ptr<Command> command = inputHandler.handleInput(1);
  if (command) {
    command->execute();
    command->undo();
  }
  return 0;
}
