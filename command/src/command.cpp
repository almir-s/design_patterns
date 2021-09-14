#include <iostream>
#include <memory>

class GameActor {
  public:
  void jump() { std::cout << "Actor jumping.." << std::endl; }
  void fire() { std::cout << "Actor firing.." << std::endl; }
  void run() { std::cout << "Actor running.." << std::endl; }
};

class Command {
  public:
  virtual ~Command() {}
  virtual void execute(GameActor&) = 0;
};

class JumpCommand : public Command {
  public:
  virtual void execute(GameActor& actor) { actor.jump(); }
};

class FireCommand : public Command {
  public:
  virtual void execute(GameActor& actor) { actor.fire(); }
};

class RunCommand : public Command {
  public:
  virtual void execute(GameActor& actor) { actor.run(); }
};

class InputHandler {
  public:
  ~InputHandler() {
  }

  std::unique_ptr<Command> handleInput(int input) {
    if (input == BUTTON_X)
      return std::move(buttonX_);
    else if (input == BUTTON_Y)
      return std::move(buttonY_);
    else if (input == BUTTON_Z)
      return std::move(buttonZ_);
    return nullptr;
  }

  private:
  int BUTTON_X = 0;
  int BUTTON_Y = 1;
  int BUTTON_Z = 2;
  std::unique_ptr<Command> buttonX_ = std::make_unique<JumpCommand>();
  std::unique_ptr<Command> buttonY_ = std::make_unique<FireCommand>();
  std::unique_ptr<Command> buttonZ_ = std::make_unique<RunCommand>();
};

int main() {
  std::cout << "Command pattern" << std::endl;
  GameActor gameActor;
  InputHandler inputHandler;
  std::unique_ptr<Command> command = inputHandler.handleInput(1);
  if (command) command->execute(gameActor);
  return 0;
}
