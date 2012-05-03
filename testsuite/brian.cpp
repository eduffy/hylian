
#include <cstdlib>
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
private:
  int integer;
  int floatingPoint;
};
int A::getInt() const { return integer; };
void A::useNamespace() const {
  NamespaceA::functionInNamespaceA();
}

int getX() {
  return 1138;
}

int main(int argc, char *argv[])
{
   std::cout << "Hello, World!" << std::endl;
   A a;
   int i = a.getInt();
   int x = a.getFloat();
   return EXIT_SUCCESS;
}
