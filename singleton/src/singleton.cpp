#include <iostream>

using namespace std;

class Singleton {
  static Singleton *instance;
  int data;

  Singleton() { data = 0; }

  public:
  static Singleton *getInstance() {
    if (!instance) instance = new Singleton;
    return instance;
  }

  int getData() { return this->data; }

  void setData(int data) { this->data = data; }
};

Singleton *Singleton::instance = nullptr;

int main() {
  Singleton *singleton = singleton->getInstance();
  Singleton *singleton2 = singleton2->getInstance();
  singleton->setData(100);
  singleton2->setData(200);
  cout << singleton->getData() << endl;
  cout << singleton2->getData() << endl;  // Shoud be the same as singleton
  return 0;
}
