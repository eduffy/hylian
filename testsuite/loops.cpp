
int fib_for(int count) {
   int a, b;

   a = 0;
   b = 1;
   for(int i = 0; i < count; i++) {
      int sum = a + b;
      a = b;
      b = sum;
   }
   return b;
}
