
int max(int a, int b, int c)
{
  if(a > b && a > c)
    return a;
  if(b > c)
    return b;
  return c;
}

