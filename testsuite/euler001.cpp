
int find_sum(int n) {
  int sum = 0;
  for(int i = 0; i < n; i++) {
    if(i % 15 == 0)
      sum += i;
  }
  return sum;
}
