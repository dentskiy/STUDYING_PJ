#include <math.h>

#include "s21_calc.h"

#define ONE_MONTH 1
#define THREE_MONTH 2
#define HALF_YEAR 3
#define YEAR 4
#define NO_TAX 160000.

int s21_creditA(long double credit, int month, int procent) {
  long double result = 0.;
  double stavka = procent;
  stavka /= (12. * 100.);
  result = credit * stavka / (1 - pow(1 + stavka, -month));
  return (int)round(result);
}

int s21_creditDif(long double credit, int month, int procent) {
  long double res = 0, tmp = credit / (double)month, copy = credit;
  for (int i = 0; i < month; i++) {
    res += (credit * (double)procent / 12. / 100.);
    credit -= tmp;
  }
  res += copy;
  return (int)round(res);
}

void setPeriod(int *per, int month);

void s21_deposit(deposit *var) {
  if (!var) return;
  long double step = 0;
  long double buff = 0;
  if (var->kflag) var->period++;
  setPeriod(&(var->period), var->month);
  setPeriod(&(var->perup), var->month);
  for (int i = 1; i <= var->month; i++) {
    if (!(i % var->perup)) {
      var->sum += var->sumup;
      var->result += var->sumup;
    }
    if (var->kflag)
      step += var->result * var->pc / 100. / 12.;
    else
      step += var->sum * var->pc / 100. / 12.;
    if (!(i % var->period)) {
      buff += step;
      var->result += step;
      step = 0.;
    }
    if (!((i - 1) % 12) && i) {
      if (buff > NO_TAX) var->tax += (buff - NO_TAX) * var->pn / 100.;
      buff = 0.;
    }
  }
  if (buff || step) {
    buff += step;
    var->result += step;
    if (buff > NO_TAX) var->tax += (buff - NO_TAX) * var->pn / 100.;
  }
}

void setPeriod(int *per, int month) {
  switch (*per) {
    case ONE_MONTH:
      *per = 1;
      break;
    case THREE_MONTH:
      *per = 3;
      break;
    case HALF_YEAR:
      *per = 6;
      break;
    case YEAR:
      *per = 12;
      break;
    default:
      *per = month;
      break;
  }
}