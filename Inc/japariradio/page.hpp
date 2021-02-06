#ifndef __PAGE_H
#define __PAGE_H

#include <stdio.h>

class Page {
 public:
  virtual ~Page() {}

  void initialize();
  bool update();

  virtual bool onPressButtonA() {
    return true;
  }

  virtual bool onPressButtonB() {
    return true;
  }

  virtual bool onLongPressButtonA() {
    return true;
  }

  virtual bool onLongPressButtonB() {
    return true;
  }

 protected:
  virtual void drawWholeScreen() = 0;
  virtual bool draw()            = 0;
};

class TuningPage : public Page {
 public:
  bool onPressButtonA();
  bool onPressButtonB();
  bool onLongPressButtonA();
  bool onLongPressButtonB();

 protected:
  void drawWholeScreen();
  bool draw();
};

#endif
