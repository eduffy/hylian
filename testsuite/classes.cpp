
class A{
public:
  A() : integer(0), floatingPoint(0.0) {}
  A(int n, float x) : integer(n), floatingPoint(x) {}
  A(const A& a) : integer(a.integer), floatingPoint(a.floatingPoint) {}
  A& operator=(const A& a) {
    integer = a.integer;
    floatingPoint = a.floatingPoint;
    return *this;
  }
  int getInt() const { return integer; };
  float getFloat() const { return integer; }
private:
  int integer;
  int floatingPoint;
};

int main(int argc, char *argv[]) {
   A a;
   int i = a.getInt();
   int x = a.getFloat();
}
