#include <iostream>
#include "deque.h"
#include "eratosphen.cpp"
#include "eratosphen.h"
#include <cassert>
#include <vector>

using namespace std;

void sieve_of_eratosthenes(int n) {
    vector<bool> primes(n + 1, true);
    primes[0] = primes[1] = false;

    for (int i = 2; i * i <= n; i++) {
        if (primes[i]) {
            for (int j = i * i; j <= n; j += i) {
                primes[j] = false;
            }
        }
    }

    for (int i = 2; i <= n; i++) {
        if (primes[i]) {
            cout << i << " ";
        }
    }
}

void print_menu() {
    std::cout << "Menu:\n";
    std::cout << "1. Look at the deque\n";
    std::cout << "2. Add smth\n";
    std::cout << "3. Exit\n";
}

void test() {


}
//
//
//int negate(int value) { //Функция для отображения элементов (умножение на -1)
//    return value * -1;
//}
//
//bool is_even(int value) { //Предикат для отбора четных элементов
//    return value % 2 == 0;
//}
//
//int sum(int value1, int value2) { //Функция для операции свертки (сумма элементов)
//    return value1 + value2;
//}
//
//
//int main() {
//
//    Deque<int, 1000> deque = Deque<int, 1000>(10, 4); //Создаем очередь
//    deque.enqueue_front(1);
//    deque.enqueue_front(2);
//    deque.enqueue_back(3);
//    deque.enqueue_back(4);
//    deque.enqueue_front(5);
//    deque.enqueue_back(6);
//    deque.enqueue_front(7);
//    deque.enqueue_back(8);
//    deque.enqueue_front(9);
//    deque.enqueue_back(10);
//
//    cout << "Initial deque: " << endl;
//    for(int i = 0; i < deque.get_size(); i++) {
//        cout << deque.get_element(i) << " ";
//    }
//    cout << endl;
//
//    deque.sort();
//    cout<< "Sorted deque: " << endl;
//    for(int i = 0; i < deque.get_size(); i++) {
//        cout << deque.get_element(i) << " ";
//    }
//    cout << endl;
//
////    Deque<int, 1000> deque1 = deque.map(negate);
////    cout << "Mapped deque: " << endl;
////    for(int i = 0; i < deque1.get_size(); i++) {
////        cout << deque1.get_element(i) << " ";
////    }
////    cout << endl;
//
//    Deque<int, 1000> deque2 = deque.where(is_even);
//    cout << "Filtered deque: " << endl;
//    for(int i = 0; i < deque2.get_size(); i++) {
//        cout << deque2.get_element(i) << " ";
//    }
//    cout << endl;
//
//    int summa = deque.reduce(sum, 0);
//    cout << "Reduced deque: " << endl;
//    cout << summa << endl;
//
//    Deque<int, 1000> deque3 = Deque<int, 1000>(5, 5);
//    deque3.enqueue_back(11);
//    deque3.enqueue_back(12);
//    deque.concatenate(deque3);
//    cout << "Concatenated deque: " << endl;
//    for(int i = 0; i < deque.get_size(); i++) {
//        cout << deque.get_element(i) << " ";
//    }
//    cout << endl;
//
//    Deque<int, 1000> deque4 = deque.slice(1, 6);
//    cout << "Sliced deque: " << endl;
//    for(int i = 0; i < deque4.get_size(); i++) {
//        cout << deque4.get_element(i) << " ";
//    }
//    cout << endl;
//
//    Deque<int, 1000> deque5 = Deque<int, 1000>(5, 5);
//    deque5.enqueue_back(2);
//    deque5.enqueue_back(3);
//    cout << "Contains subsequence? " << deque.contains(deque5) << endl;
//
//    deque.clear();
//    cout << "Cleared deque: " << endl;
//    for(int i = 0; i < deque.get_size(); i++) {
//        cout << deque.get_element(i) << " ";
//    }
//
//    test();
//
//    return 0;
//    cout << endl;
//    sieve_of_eratosthenes(100);
//    return 0;


// пример использования базовых функций дека

void example1() {
    std::cout << "test1 are ok" << "\n";
    SegmentedDeque<int> deque;

    deque.push_back(1);
    deque.push_back(2);
    deque.push_front(0);

    for (int i = 0; i < deque.size(); i++) {
        cout << deque[i] << " ";
    }
    cout << endl;

    deque.pop_back();

    deque.push_front(-1);

    while (!deque.empty()) {
        cout << deque.pop_front() << " ";
    }
    cout << endl;

}

// пример использования функций высшего порядка
void example2() {
    std::cout << "test2 are ok" << "\n";
    SegmentedDeque<int> deque;

    deque.push_back(1);
    deque.push_back(2);
    deque.push_back(3);
    deque.push_back(4);
    deque.push_back(5);

    auto squared = deque.map([](int x) {return x * x; });
    for (int i = 0; i < squared.size(); i++) {
        cout << squared[i] << " "; // вывод: 1 4 9 16 25
    }
    cout << endl;

    auto odd = squared.where([](int x) {return x % 2 == 1; });
    for (int i = 0; i < odd.size(); i++) {
        cout << odd[i] << " "; // вывод: 1 9 25
    }
    cout << endl;

    int sum = odd.reduce([](int a, int b) {return a + b; }, 0);
    cout << sum << endl;

}

// пример использования операций конкатенации, извлечения подпоследовательности, поиска на вхождение последовательности и слияние деков
void example3() {
    std::cout << "tests are ok" << "\n";
    SegmentedDeque<int> deque1;
    SegmentedDeque<int> deque2;

    deque1.push_back(1);
    deque1.push_back(2);
    deque1.push_back(3);

    deque2.push_back(4);
    deque2.push_back(5);

    deque1.concatenate(deque2);
    for (int i = 0; i < deque1.size(); i++) {
        cout << deque1[i] << " "; // вывод: 1 2 3 4 5
    }
    cout << endl;

    auto subdeque = deque1.subsequence(1, 4);
    for (int i = 0; i < subdeque.size(); i++) {
        cout << subdeque[i] << " "; // вывод: 2 3 4
    }
    cout << endl;

    SegmentedDeque<int> search_deque;
    search_deque.push_back(1);
    search_deque.push_back(2);
    search_deque.push_back(3);

    cout << deque1.contains(search_deque) << endl; // вывод: 1
    search_deque.push_back(6);
    cout << deque1.contains(search_deque) << endl; // вывод: 0

    SegmentedDeque<int> deque3;
    deque3.push_back(3);
    deque3.push_back(4);
    deque3.push_back(5);
    deque3.push_back(6);

    auto deque4 = deque1.merge(deque3);
    for (int i = 0; i < deque4.size(); i++) {
        cout << deque4[i] << " "; // вывод: 1 2 3 4 5 6
    }
    cout << endl;

}















int main() {

    SegmentedDeque<int> deque;
    test();
    sieve_of_eratosthenes(100);
    cout << endl;
    print_menu();

    example3();
    example2();
    example1();

}