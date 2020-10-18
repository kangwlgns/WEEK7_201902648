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
/* (실습 1-1) 분석결과 : main에서 funcA()에 진입하여 Test타입의 r객체를 만들고, funcB()에 진입하여 또 객체를 만든 후에, Executed in B라는 문구를 출력하고 return 합니다. 다시 fundA()로 돌아와서 Executed in A를 출력하고, 다시 main으로 돌아와서 프로그램이 종료됩니다. 이 때, 객체를 생성했으므로 함수가 종료함에 따라 소멸자에 의해 객체에 전달했던 'A', 'B'에 대한 정보와 함께 객체가 삭제됨을 알립니다.
  try catch로 예외처리를 해준 코드이나, 예외가 발생하지 않아 아무 이상없이 코드가 종료되었습니다.
*/

/* (실습 1-2) 분석결과 : 위와 같은 코드이나 안내문이 출력되지 않았습니다.
  funcB()에서 예외를 throw해주었으므로 Stack unwinding이 일어나 catch를 만나기 전까지 함수를 종료하여 이런 현상이 발생하였습니다. 그러나 함수가 종료되면서 객체는 사라지므로 소멸자에 존재하는 안내문만큼은 출력되었습니다. 그리고 main에 존재하는 catch에 도달하여 어느 함수에서 예외가 발생했는지를 반환합니다.
*/