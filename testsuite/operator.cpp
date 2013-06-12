
class array {
public:
  explicit array(int n) { 
    data = new int[n];
  }
  ~array() { delete[] data; }
  int &operator[](int index) {
    return data[index];
  }
private:
  int *data;
};

int main(int argc, char *argv[])
{

   array A(100);
   A[0] = 1138;
}
