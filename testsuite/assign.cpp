void globalFunction(int x, float y) {}
typedef int f;

namespace NamespaceA{
  void functionInNamespaceA() {}
}

class A{
public:
  A() : integer(0), floatingPoint(0.0) {}
  A(int n, float x) : integer(n), floatingPoint(x) {}
  A(const A& a) : integer(a.integer), floatingPoint(a.floatingPoint) {}
  A& operator=(const A& a);
  int getInt() const;
  float getFloat() const { return integer; }
  void useNamespace() const;
private:
  int integer;
  int floatingPoint;
};

A& A::operator=(const A& a) {
  integer = a.integer;
  floatingPoint = a.floatingPoint;
  return *this;
}

int A::getInt() const { return integer; };
void A::useNamespace() const { NamespaceA::functionInNamespaceA(); }
int getX() { return 1138; }

int main(int argc, char *argv[]) {
   A a;
   int i = a.getInt();
   int x = a.getFloat();
}
