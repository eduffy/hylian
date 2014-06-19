
int increment(int p) {
  return p+1;
}

int decrement(int p) {
  return p-1;
}

int multiply(int a, int b) {
  return a*b;
}

int factorial(int n) {
  if (n == 0) return 1;
  else return multiply(n, factorial(n-1));
}

int max(int a, int b) {
  return a > b ? a : b;
}

int max(int a, int b, int c) {
  return max(a, max(b, c));
}

int main() {
  int n = factorial(5);
  int m;
  if (n < 100) {
    m = increment(n);
  }
  else m = decrement(n);
  int z = max(5, 2, 3);
}
