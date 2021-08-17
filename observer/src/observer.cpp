#include <iostream>
#include <vector>
#include <memory>

struct Entity {
  std::string title;
};

struct Event {
  u_int32_t id;
  std::string title;
};

class Observer {
  private:
  u_int32_t id;

  public:
  virtual void onNotify(Entity entity, Event event) = 0;
  virtual ~Observer() {}
};

class AchievmentObserver : public Observer {
  public:
  void onNotify(Entity entity, Event event) {
    switch (event.id) {
      case 1:
        std::cout << "MonstersKiller bage earned!!" << std::endl;
        break;
    }
  }
  ~AchievmentObserver() {}
};

class SoundObserver : public Observer {
  public:
  void onNotify(Entity entity, Event event) {
    switch (event.id) {
      case 1:
        std::cout << "Apply monster kill sound" << std::endl;
        break;
    }
  }
  ~SoundObserver() {}
};

class Subject {
  private:
  std::vector<std::unique_ptr<Observer>> observers_;

  public:
  void addObserver(std::unique_ptr<Observer> observer) {
    observers_.push_back(std::move(observer));
  }

  void notify(Entity entity, Event event) {
    for (auto& observer : observers_) {
      observer->onNotify(entity, event);
    }
  }
  // void removeObserver(Observer observer) {}
};

class Game {
  private:
  Subject& subject_;

  public:
  Game(Subject& subject) : subject_(subject){};
  void winTrophy(Entity entity, Event event) { subject_.notify(entity, event); }

  void completeLevel(Entity entity, Event event) {
    subject_.notify(entity, event);
  }
  ~Game(){};
};

int main() {
  std::cout << "Observer ..." << std::endl;
  Entity entity;
  Event event{1, "KillMonster"};
  Subject subject;
  subject.addObserver(
      std::make_unique<AchievmentObserver>(AchievmentObserver()));
  subject.addObserver(std::make_unique<SoundObserver>(SoundObserver()));
  Game game(subject);
  game.winTrophy(entity, event);
}
