#include <iostream>
#include <utility>
#include <memory>
#include <vector>

enum Direction { up = 0, right = 1, down = 2, left = 3 };

class FrogActor {
  public:
  FrogActor() {
    x_ = 0;
    y_ = 0;
  }

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

  void moveLeft(int offset) {
    std::cout << "Move left call " << std::endl;
    switch (direction_) {
      case Direction::up:
        x_ -= offset;
        direction_ = Direction::left;
        break;
      case Direction::right:
        y_ += offset;
        direction_ = Direction::up;
        break;
      case Direction::down:
        x_ += offset;
        direction_ = Direction::right;
        break;
      case Direction::left:
        y_ -= offset;
        direction_ = Direction::down;
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

  std::pair<int, int> getPosition() const { return std::make_pair(x_, y_); }
  Direction getDirection() const { return direction_; }

  private:
  int x_;
  int y_;
  Direction direction_ = Direction::up;
};

class Command {
  public:
  virtual ~Command() {}
  virtual void execute(FrogActor&) = 0;
};

class MoveRightCommand : public Command {
  private:
  int offset_ = 0;

  public:
  MoveRightCommand(){};
  MoveRightCommand(int offset) : offset_{offset} {};
  void execute(FrogActor& frogActor) { frogActor.moveRight(offset_); }
};

class MoveLeftCommand : public Command {
  private:
  int offset_ = 0;

  public:
  MoveLeftCommand(){};
  MoveLeftCommand(int offset) : offset_{offset} {};
  void execute(FrogActor& frogActor) { frogActor.moveLeft(offset_); }
};

class MoveForwardCommand : public Command {
  private:
  int offset_ = 0;

  public:
  MoveForwardCommand(){};
  MoveForwardCommand(int offset) : offset_(offset){};
  void execute(FrogActor& frogActor) { frogActor.moveForward(offset_); }
};

class GetPositionCommand : public Command {
  public:
  void execute(FrogActor& frogActor) {
    auto position = frogActor.getPosition();
    std::cout << "Position: x = " << position.first
              << " y = " << position.second << std::endl;
    std::cout << "Direction: " << frogActor.getDirection() << std::endl;
  }
};

class InputHandler {
  public:
  std::unique_ptr<Command> handleInput(int input, int offset) {
    switch (input) {
      case 1:
        return std::make_unique<GetPositionCommand>();
      case 2:
        return std::make_unique<MoveForwardCommand>(offset);
      case 3:
        return std::make_unique<MoveRightCommand>(offset);
      case 4:
        return std::make_unique<MoveLeftCommand>(offset);
      default:
        return std::make_unique<GetPositionCommand>();
    }
  }

  void collectCommands() {
    std::cout << "Please enter movement commands in following format "
                 "'direction-offset' "
              << std::endl
              << "where direction is on of the following: forward, left, right "
                 "and offset is an arbitrary integer value. "
              << std::endl
              << "Example: forward-50" << std::endl
              << "For terminating input, enter 'end'" << std::endl;

    std::string input;
    while (std::getline(std::cin, input)) {
      if (input.compare("end") == 0) {
        return;
      }
      collectedCommands.push_back(parse(input));
    }
  }

  std::vector<std::unique_ptr<Command>> getCollectedCommands() {
    return std::move(collectedCommands);
  }

  std::unique_ptr<Command> getPositionCommand() { return std::move(position); }

  private:
  std::unique_ptr<Command> position = std::make_unique<GetPositionCommand>();
  std::vector<std::unique_ptr<Command>> collectedCommands;

  std::unique_ptr<Command> parse(std::string input) const {
    std::string delimiter = "-";
    std::string command = input.substr(0, input.find(delimiter));
    std::string offset =
        input.substr(input.find(delimiter) + 1, input.length());

    std::cout << command << " " << offset << std::endl;

    if (command.compare("forward") == 0) {
      return std::make_unique<MoveForwardCommand>(std::stoi(offset));
    } else if (command.compare("left") == 0) {
      return std::make_unique<MoveLeftCommand>(std::stoi(offset));
    } else if (command.compare("right") == 0) {
      return std::make_unique<MoveRightCommand>(std::stoi(offset));
    } else {
      std::cout << "Input error, incorrect format, exiting " << std::endl;
      std::exit(1);
    }
  }
};

int main() {
  FrogActor frogActor;
  InputHandler inputHandler;
  std::cout << "Frogyy started..." << std::endl;
  std::unique_ptr<Command> positionCommand = inputHandler.getPositionCommand();

  std::cout << "===================" << std::endl;
  inputHandler.collectCommands();
  for (auto& command : inputHandler.getCollectedCommands()) {
    command->execute(frogActor);
    positionCommand->execute(frogActor);
  }
  return 0;
}
