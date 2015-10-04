
#include <stdio.h>
int n;

int main(void)
{
   // Disable STDOUT buffering. Otherwise nothing will be printed
   // before a newline character or when the buffer is flushed.
   // This MUST be done before any writes to STDOUT to have any effect...
   //setbuf(stdout,NULL);
   printf("Hello begin world\r\n");
   //fflush(stdin);
   scanf("%d",&n); // n=getchar();
   printf("The number type is %d\n",n);
   printf("Hello end world\r\n");
   //for (;;) ;
   return 0;
}
