#ifndef __PAGE_MASTER_H
#define __PAGE_MASTER_H

#include <stdint.h>

#include "japariradio/page.hpp"

enum class PageKind : int8_t {
  none = -1,

  tuning = 0,
};

typedef struct {
  PageKind pressA;
  PageKind pressB;
  PageKind longPressA;
  PageKind longPressB;
  PageKind nextPage;
} PageInfo;

const PageInfo PageStates[] = {
  // 0: tuning
  { PageKind::none, PageKind::none, PageKind::none, PageKind::none, PageKind::none },
};

class PageMaster {
 public:
  void initialize();

  void pressAButton();
  void pressBButton();

  void longPressAButton();
  void longPressBButton();

  void update();

 private:
  PageKind state;
  Page *page;

  void changePage();
};

#endif
