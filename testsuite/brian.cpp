
#include <cstdlib>
#include <iostream>

namespace NamespaceA{
  void functionInNamespaceA() {}
}

class A{
public:
  void functionByBrian();
};
void A::functionByBrian() { int x; };

int getX() {
  return 1138;
}

int main(int argc, char *argv[])
{
   std::cout << "Hello, World!" << std::endl;
   return EXIT_SUCCESS;
}
