#include <iostream>
#include <vector>
#include <memory>
#include "state.hpp"

PlayingState::PlayingState(AudioPlayer* player) { player_ = player; }

void PlayingState::play() {
  std::cout << "PLAYING state, play action performed, stay in PLAYING state"
            << std::endl;
}
void PlayingState::lock() {
  std::cout << "PLAYING state, lock action performed, go to LOCKED state"
            << std::endl;
  player_->changeState(new LockState(player_));
}
void PlayingState::next() {
  std::cout << "PLAYING state, next action performed" << std::endl;
}
void PlayingState::previous() {
  std::cout << "PLAYING state, previous action performed" << std::endl;
}

LockState::LockState(AudioPlayer* player) { player_ = player; }

void LockState::play() {
  std::cout << "LOCKED state, play action performed, go to PLAYING state"
            << std::endl;
  player_->changeState(new PlayingState(player_));
}
void LockState::lock() {
  std::cout << "LOCKED state, lock action performed, go to READY state"
            << std::endl;
  player_->changeState(new ReadyState(player_));
}
void LockState::next() {
  std::cout << "LOCKED state action next, Nothing can be done" << std::endl;
}
void LockState::previous() {
  std::cout << "LOCKED state action previous, Nothing can be done" << std::endl;
}

ReadyState::ReadyState(AudioPlayer* player) { player_ = player; }

void ReadyState::play() {
  std::cout << "READY state, play action performed, go to PLAYING state"
            << std::endl;
  player_->changeState(new PlayingState(player_));
}

void ReadyState::lock() {
  std::cout << "READY state, lock action performed, go to LOCKED state"
            << std::endl;
  player_->changeState(new LockState(player_));
}

void ReadyState::next() {
  std::cout << "READY state action next, Nothing can be done" << std::endl;
}
void ReadyState::previous() {
  std::cout << "READY state action previous, Nothing can be done" << std::endl;
}

AudioPlayer::AudioPlayer() { state_ = new ReadyState(this); }

AudioPlayer::~AudioPlayer() { delete state_; }
void AudioPlayer::changeState(State* state) { state_ = state; }
void AudioPlayer::play() { state_->play(); }
void AudioPlayer::lock() { state_->lock(); }
void AudioPlayer::next() { state_->next(); }
void AudioPlayer::previous() { state_->previous(); }

int main() {
  std::cout << "State pattern" << std::endl;
  AudioPlayer player;
  player.next();
  player.play();
  player.next();
  player.lock();
  player.next();
  player.play();
  player.previous();
  return 0;
}
