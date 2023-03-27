#ifndef _INTEL4004STACK_H_
#define _INTEL4004STACK_H_

#include "Intel4004Stack.h"
#include <iostream>
using namespace std;

/* 
*   Intel4004 Emulator
*   Gruppe: Tobias Traiser, Kilian Wachter, Pascal Wildermuth, Shaig Rustamov
*   Projektabgabe C 2.Semester - 18.07.2021
*/

void Intel4004Stack::push(const UBankedAddress address)
{
  if (isOverflow()) {WarningCondition(PUSH);}

  stack[current_stack_position] = address;

  if(current_stack_position == 2){ current_stack_position = 0; }
  else { current_stack_position++; }
  pushCount++;
}

UBankedAddress Intel4004Stack::pop()
{
  if (isUnderflow()) {WarningCondition(POP);}
 
  if(current_stack_position == 0){current_stack_position = 2;}
  else { current_stack_position--; }
  
  popCount++;
  return stack[current_stack_position];
}

int Intel4004Stack::getCurrentStackPosition() const { return current_stack_position; }

int Intel4004Stack::getCount() const { return pushCount + popCount; }

bool Intel4004Stack::isOverflow() const { return getCurrentStackPosition() >= STACKSIZE - 1; }

bool Intel4004Stack::isUnderflow() const { return getCurrentStackPosition() == 0; }

void Intel4004Stack::reset()
{
  pushCount = 0;
  popCount = 0;
  for (int i = 0; i < STACKSIZE; i++)
    stack[i] = {};
}

UBankedAddress *Intel4004Stack::getCopyOfStack(UBankedAddress *const ptr) const
{
  for (int i = 0; i < STACKSIZE; i++)
    ptr[i] = stack[i];
  return ptr;
}

void Intel4004Stack::WarningCondition(const EDirection direction)
{
  switch (direction)
  {
  case PUSH:
    cout << "Warning: Overflow detected!" << endl;
    break;
  case POP:
    cout << "Warning: Underflow detected!" << endl;
    break;
  default:
    cout << "Warning: Unkown error detected!" << endl;
  }
}

#endif