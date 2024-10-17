#include <stdio.h>
#include <stdlib.h>

#define ADD 0
#define SUB 1
#define MUL 2
#define DIV 3
#define FF fflush(stdout);
void addition(int *result, int a, int b){ *result = a+b; return ;}
void division(int *result, int a, int b){ if(b==0){ printf("Invalid Denominator"); return;} *result = a/b; return ;  }
void subtraction(int *result, int a, int b){ *result = a-b; return ;  }
void multiplication(int *result,int a, int b){ *result=a*b; return ; }


void wrapper(void(*fun)()){fun();}

int main(int argc, char *argv[])
{
  int result,a,b;
  int op;
  void (*fp)(int*, int, int);
  
  scanf("%d",&op);
  scanf("%d %d",&a,&b);
  


  switch (op) {
    case ADD:
    fp = addition;
    break;

    case SUB:
    fp = subtraction;
    break;

    case MUL:
    fp = multiplication;
    break;

    case DIV:
    fp = division;
    break;

    default:
      return 0;
  }

  // fp = addition;
  fp(&result, a,b);
  
  printf("%d\n",result);
  return 0;
}
