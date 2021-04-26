#include <iostream>
#include <utility>

enum Direction { up = 0, right = 1, down = 2, left = 3 };

class FrogActor {
  FrogActor() {
    x_ = 0;
    y_ = 0;
  }

  public:
  void moveRight(int offset) {
    std::cout << "Move right call " << std::endl;
    switch (direction_) {
      case Direction::up:
        x_ += offset;
        direction_ = Direction::right;
        break;
      case Direction::right:
        y_ -= offset;
        direction_ = Direction::down;
        break;
      case Direction::down:
        x_ -= offset;
        direction_ = Direction::left;
        break;
      case Direction::left:
        y_ += offset;
        direction_ = Direction::up;
        break;
    }
  }

  void moveForward(int offset) {
    std::cout << "Move forward call " << std::endl;
    switch (direction_) {
      case Direction::up:
        y_ += offset;
        break;
      case Direction::right:
        x_ += offset;
        break;
      case Direction::down:
        y_ -= offset;
        break;
      case Direction::left:
        x_ -= offset;
        break;
    }
  }

  std::pair<int, int> getPosition() const {
    return std::make_pair(x_, y_);
  }

  private:
  int x_;
  int y_;
  Direction direction_ = Direction::up;
};

class Command {
  public:
  virtual ~Command();
  virtual void execute(FrogActor&) = 0;
};

class MoveRightCommand : public Command {
  void execute(FrogActor& frogActor) { frogActor.moveRight(20); }
};

class MoveForwardCommand : public Command {
  void execute(FrogActor& frogActor) { frogActor.moveForward(20); }
};

class GetPositionCommand : public Command {
  void execute(FrogActor& frogActor) { frogActor.getPosition(); }
};

int main() {
  std::cout << "Frogyy started..." << std::endl;
  std::cout << "Frogyy position: " << std::endl;
  return 0;
}
