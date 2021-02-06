#include "japariradio/page_master.hpp"

void PageMaster::initialize() {
  this->state = PageKind::tuning;
  this->changePage();
}

void PageMaster::pressAButton() {
  if (this->page->onPressButtonA()) {
    int8_t stateIndex = static_cast<int8_t>(this->state);
    PageKind nextKind = PageStates[stateIndex].pressA;

    if (nextKind != PageKind::none) {
      this->state = nextKind;
      this->changePage();
    }
  }
}

void PageMaster::pressBButton() {
  if (this->page->onPressButtonB()) {
    int8_t stateIndex = static_cast<int8_t>(this->state);
    PageKind nextKind = PageStates[stateIndex].pressB;

    if (nextKind != PageKind::none) {
      this->state = nextKind;
      this->changePage();
    }
  }
}

void PageMaster::longPressAButton() {
  if (this->page->onLongPressButtonA()) {
    int8_t stateIndex = static_cast<int8_t>(this->state);
    PageKind nextKind = PageStates[stateIndex].longPressA;

    if (nextKind != PageKind::none) {
      this->state = nextKind;
      this->changePage();
    }
  }
}

void PageMaster::longPressBButton() {
  if (this->page->onLongPressButtonB()) {
    int8_t stateIndex = static_cast<int8_t>(this->state);
    PageKind nextKind = PageStates[stateIndex].longPressB;

    if (nextKind != PageKind::none) {
      this->state = nextKind;
      this->changePage();
    }
  }
}

void PageMaster::update() {
  if (this->page->update()) {
    int8_t stateIndex = static_cast<int8_t>(this->state);
    PageKind nextKind = PageStates[stateIndex].nextPage;

    if (nextKind != PageKind::none) {
      this->state = nextKind;
      this->changePage();
    }
  }
}

void PageMaster::changePage() {
  delete this->page;

  switch (this->state) {
    case PageKind::tuning:
      this->page = new TuningPage();
      break;

    default:
      break;
  }

  this->page->initialize();
}
