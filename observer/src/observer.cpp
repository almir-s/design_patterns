#include <iostream>
#include <vector>
#include <memory>

#define MONSTER_KILLED 1

struct Entity {
  std::string title;
};

struct Event {
  uint32_t id;
  std::string title;
};

class Observer {
  private:
  uint32_t id;

  public:
  virtual void onNotify(Entity entity, Event event) = 0;
  virtual ~Observer() = default;
};

class AchievmentObserver : public Observer {
  public:
  void onNotify(Entity entity, Event event) override {
    switch (event.id) {
      case MONSTER_KILLED:
        std::cout << "MonstersKiller badge earned!!" << std::endl;
        break;
    }
  }
  ~AchievmentObserver() {}
};

class SoundObserver : public Observer {
  public:
  void onNotify(Entity entity, Event event) override {
    switch (event.id) {
      case MONSTER_KILLED:
        std::cout << "Apply monster kill sound" << std::endl;
        break;
    }
  }
  ~SoundObserver() {}
};

class Subject {
  private:
  std::vector<Observer*> observers_;

  public:
  void addObserver(Observer* observer) { observers_.push_back(observer); }

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
  void killMonster(Entity entity, Event event) {
    subject_.notify(entity, event);
  }

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
  AchievmentObserver achievement;
  SoundObserver sound;
  subject.addObserver(&achievement);
  subject.addObserver(&sound);
  Game game(subject);
  game.killMonster(entity, event);
}
