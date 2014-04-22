
int fib(int limit) {
   int a, b;
   int sum(0);

   a = 0;
   b = 1;
   while(b < limit) {
      int next = a + b;
      a = b;
      b = next;
      if(b % 2 == 0)
        sum += b;
   }
   return sum;
}
