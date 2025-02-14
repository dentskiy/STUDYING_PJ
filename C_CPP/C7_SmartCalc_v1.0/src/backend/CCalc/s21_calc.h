#ifndef S21_CALC
#define S21_CALC

typedef enum errorCode { OK, NULLPTR, NO_NULL_LIST, ERROR_ELEM } status;
#define POINTC 100

typedef enum functions {
  NONE,
  SIN,
  COS,
  TAN,
  ASIN,
  ACOS,
  ATAN,
  LOG,
  LOG10,
  SQRT,
  USUM,
  USUB,
  SUM = '+',
  SUB = '-',
  MULT = '*',
  DIV = '/',
  POW = '^',
  MOD = '%',
  OP = '(',
  ED = ')',
  X = -1
} func;

#define FUNC                                                                 \
  {                                                                          \
    SIN, COS, TAN, ASIN, ACOS, ATAN, LOG, LOG10, SQRT, USUM, USUB, SUM, SUB, \
        MULT, DIV, POW, MOD, OP, ED, '\0'                                    \
  }

struct s21_calc {
  func arg;
  double val;
  struct s21_calc* next;
};
typedef struct s21_calc token_node;

int s21_getToken(char* str, token_node** start);

token_node* popNode(token_node** stack);
void pushNode(token_node** stack, token_node* elem);
void setNode(token_node** stack, token_node* elem);
void removeList(token_node** list);

int s21_sortStation(token_node** list);
int s21_SmartCalc(char* str, char* res, double* x, double* y, double point);

int s21_creditA(long double credit, int month, int procent);
int s21_creditDif(long double credit, int month, int procent);

typedef struct s21_deposit_data {
  long double sum;
  float pc;
  float pn;
  int month;
  int kflag;
  int period;
  int perup;
  long double sumup;
  long double result;
  long double tax;
} deposit;

void s21_deposit(deposit* var);

#endif