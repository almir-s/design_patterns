#include <iostream>
#include <utility>
#include <memory>
#include <vector>

enum Direction { up = 0, right = 1, down = 2, left = 3 };

struct FrogActor {
  int x_ = 0;
  int y_ = 0;
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
  MoveRightCommand(int offset) : offset_{offset} {};

  void execute(FrogActor& frogActor) {
    std::cout << "Move right call " << std::endl;
    switch (frogActor.direction_) {
      case Direction::up:
        frogActor.x_ += offset_;
        frogActor.direction_ = Direction::right;
        break;
      case Direction::right:
        frogActor.y_ -= offset_;
        frogActor.direction_ = Direction::down;
        break;
      case Direction::down:
        frogActor.x_ -= offset_;
        frogActor.direction_ = Direction::left;
        break;
      case Direction::left:
        frogActor.y_ += offset_;
        frogActor.direction_ = Direction::up;
        break;
    }
  }
};

class MoveLeftCommand : public Command {
  private:
  int offset_ = 0;

  public:
  MoveLeftCommand(int offset) : offset_{offset} {};

  void execute(FrogActor& frogActor) {
    std::cout << "Move left call " << std::endl;
    switch (frogActor.direction_) {
      case Direction::up:
        frogActor.x_ -= offset_;
        frogActor.direction_ = Direction::left;
        break;
      case Direction::right:
        frogActor.y_ += offset_;
        frogActor.direction_ = Direction::up;
        break;
      case Direction::down:
        frogActor.x_ += offset_;
        frogActor.direction_ = Direction::right;
        break;
      case Direction::left:
        frogActor.y_ -= offset_;
        frogActor.direction_ = Direction::down;
        break;
    }
  }

};

class MoveForwardCommand : public Command {
  private:
  int offset_ = 0;

  public:
  MoveForwardCommand(int offset) : offset_(offset){};

  void execute(FrogActor& frogActor) {
    std::cout << "Move forward call " << std::endl;
    switch (frogActor.direction_) {
      case Direction::up:
        frogActor.y_ += offset_;
        break;
      case Direction::right:
        frogActor.x_ += offset_;
        break;
      case Direction::down:
        frogActor.y_ -= offset_;
        break;
      case Direction::left:
        frogActor.x_ -= offset_;
        break;
    }
  }
};

class GetPositionCommand : public Command {
  public:
  void execute(FrogActor& frogActor) {
    auto position = std::make_pair(frogActor.x_, frogActor.y_);
    std::cout << "Position: " << std::endl
              << "x = " << position.first << " y = " << position.second
              << std::endl;
    std::cout << "Direction: " << frogActor.direction_<< std::endl;
    std::cout << "==================" << std::endl;
  }
};

class Runner {
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

  void executeCollectedCommadns(FrogActor& frogActor) {
    for (auto& command : collectedCommands) {
      command->execute(frogActor);
      position->execute(frogActor);
    }
  }

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
  Runner runner;
  std::cout << "Frogyy started..." << std::endl;
  std::cout << "===================" << std::endl;
  runner.collectCommands();
  runner.executeCollectedCommadns(frogActor);
  return 0;
}
