
#include <cstdlib>
#include <cstdio>
#include <iostream>

namespace NamespaceA{
  void functionInNamespaceA() {}
}

class A{
public:
  A() : integer(0), floatingPoint(0.0) {}
  A(int n, float x) : integer(n), floatingPoint(x) {}
  int getInt() const;
  float getFloat() const { return integer; }
  void useNamespace() const;
  static bool isEven(int number) { return number%2==0; }
private:
  int integer;
  int floatingPoint;
};
int A::getInt() const { return integer; };
void A::useNamespace() const {
  NamespaceA::functionInNamespaceA();
}

int getX(int) {
  return 1138;
}

int main(int argc, char *argv[])
{
   std::cout << "Hello, World!" << std::endl;
   printf("Hello, World\n");
   A a;
   int i = a.getInt();
   int x = a.getFloat();
   bool e = A::isEven(10) || A::isEven(11);
   return EXIT_SUCCESS;
}
