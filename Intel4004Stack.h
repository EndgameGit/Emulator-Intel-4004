#ifndef _STACK_H_
#define _STACK_H_

#include "MCS4BaseClasses.h"

/* 
*   Intel4004 Emulator
*   Gruppe: Tobias Traiser, Kilian Wachter, Pascal Wildermuth, Shaig Rustamov
*   Projektabgabe C 2.Semester - 18.07.2021
*/

class Intel4004Stack : public Intel4004StackBase {
public:
  enum {
    STACKSIZE = 3 //!< Maximale Größe des Intel 4004 Stacks
  };

  typedef enum {
    PUSH, //!< Hineinspeichern
    POP //!< Herausholen
  } EDirection;

  Intel4004Stack() : pushCount{0}, popCount(0), current_stack_position(0) {}

  virtual void push(const UBankedAddress address);
  virtual UBankedAddress pop();
  virtual void reset();
  virtual int getCurrentStackPosition() const;
  virtual int getCount() const;
  virtual bool isOverflow() const;
  virtual bool isUnderflow() const;
  virtual UBankedAddress *getCopyOfStack(UBankedAddress *const ptr) const;

protected:
  virtual void WarningCondition(const EDirection direction);

private:
  UBankedAddress stack[STACKSIZE];
  int pushCount, popCount;
  int current_stack_position;
};

#endif
