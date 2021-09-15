#include <iostream>

class State;

class AudioPlayer {
  private:
  State* state_;

  public:
  AudioPlayer();
  ~AudioPlayer();
  void changeState(State*);
  void play() ;
  void lock();
  void next();
  void previous();
};

class State {
  protected:
  AudioPlayer* player_;

  public:
  virtual void play() = 0;
  virtual void lock() = 0;
  virtual void next() = 0;
  virtual void previous() = 0;
  virtual ~State() {}
};


class LockState: public State {
  public:
  LockState(AudioPlayer*);
  void play() override ;
  void lock() override ;
  void next() override;
  void previous() override;
};

class PlayingState : public State {
  public:
  PlayingState(AudioPlayer*);
  void play() override;
  void lock() override;
  void next() override;
  void previous() override;
};

class ReadyState : public State {
  public:
  ReadyState(AudioPlayer* player);
  void play() override;
  void lock() override;
  void next() override;
  void previous() override;
};
