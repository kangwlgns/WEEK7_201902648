#include <iostream>
#include <stdexcept>

class Test {
public:
    Test(char id) : id_(id) {}
    ~Test() {
        std::cout << "Destructor execution: "
            << id_ << std::endl;
    }
private:
    char id_;
};

int funcB() {
    Test r('B');
     throw std::runtime_error("Exception from funcB!\n");
    std::cout << "Executed in B" << std::endl;
    return 0;
}
int funcA() {
    Test r('A');
    funcB();
    std::cout << "Executed in A" << std::endl;
    return 0;
}
int main() {
    try {
        funcA();
    }
    catch (std::exception& e) {
        std::cout << "Exception : " << e.what();
    }
}
/* (�ǽ� 1-1) �м���� : main���� funcA()�� �����Ͽ� TestŸ���� r��ü�� �����, funcB()�� �����Ͽ� �� ��ü�� ���� �Ŀ�, Executed in B��� ������ ����ϰ� return �մϴ�. �ٽ� fundA()�� ���ƿͼ� Executed in A�� ����ϰ�, �ٽ� main���� ���ƿͼ� ���α׷��� ����˴ϴ�. �� ��, ��ü�� ���������Ƿ� �Լ��� �����Կ� ���� �Ҹ��ڿ� ���� ��ü�� �����ߴ� 'A', 'B'�� ���� ������ �Բ� ��ü�� �������� �˸��ϴ�.
  try catch�� ����ó���� ���� �ڵ��̳�, ���ܰ� �߻����� �ʾ� �ƹ� �̻���� �ڵ尡 ����Ǿ����ϴ�.
*/

/* (�ǽ� 1-2) �м���� : ���� ���� �ڵ��̳� �ȳ����� ��µ��� �ʾҽ��ϴ�.
  funcB()���� ���ܸ� throw���־����Ƿ� Stack unwinding�� �Ͼ catch�� ������ ������ �Լ��� �����Ͽ� �̷� ������ �߻��Ͽ����ϴ�. �׷��� �Լ��� ����Ǹ鼭 ��ü�� ������Ƿ� �Ҹ��ڿ� �����ϴ� �ȳ�����ŭ�� ��µǾ����ϴ�. �׸��� main�� �����ϴ� catch�� �����Ͽ� ��� �Լ����� ���ܰ� �߻��ߴ����� ��ȯ�մϴ�.
*/