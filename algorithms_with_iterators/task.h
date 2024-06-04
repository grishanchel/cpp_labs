#include <cstdlib>
#include <iterator>
#include <vector>
#include <random>
#include <functional>


/*
 * Нужно написать функцию, которая принимает на вход диапазон, применяет к каждому элементу данную операцию и затем складывает результат применения операции в новый диапазон
 * Входной диапазон задан итераторами [firstIn; lastIn)
 * Выходной диапазон начинается с firstOut и имеет такую же длину как входной диапазон
 * Операция является функцией с одним аргументом (унарная функция), возвращающая результат такого типа, который можно положить в OutputIt
 */

template<class InputIt, class OutputIt, class UnaryOperation>
void Transform(InputIt firstIn, InputIt lastIn, OutputIt firstOut, UnaryOperation op) {

    while (firstIn!=lastIn){
        *firstOut++ = op(*firstIn++);
    }

}

/*
 * Нужно написать функцию, которая принимает на вход диапазон и переставляет элементы в нем таким образом, чтобы элементы,
 * которые удовлетворяют условию p, находились ближе к началу диапазона, чем остальные элементы.
 * Входной диапазон задан итераторами [first; last)
 * p является функцией с одним аргументом (унарная функция), возвращающая результат типа bool
 */

template<class BidirIt, class UnaryPredicate>
BidirIt find_no(BidirIt first, BidirIt last, UnaryPredicate p)
{
    while (first!=last) {
        if (!p(*first)) return first;
        ++first;
    }
    return last;
}

template<class BidirIt, class UnaryPredicate>
void Partition(BidirIt first, BidirIt last, UnaryPredicate p) {

    first=find_no(first, last, p);

    for (auto i=std::next(first); i!=last; ++i) {
        if (p(*i)) {
            std::iter_swap(i, first);
            ++first;
        }
    }
}

/*
 * Нужно написать функцию, которая принимает на вход два отстотированных диапазона и объединяет их в новый отсортированный диапазон, содержащий все элементы обоих входных диапазонов.
 */
template<class InputIt1, class InputIt2, class OutputIt>
void Merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt firstOut) {

    for (;first1!=last1; ++firstOut) {
        if (first2 == last2) {
            std::copy(first1, last1, firstOut);
        }
        if (*first2<*first1) {
            *firstOut=*first2;
            ++first2;

        } else {
            *firstOut=*first1;
            ++first1;
        }
    }

}


/*
 * Напишите класс "диапазон чисел Фибоначчи"
 * Экземпляр класса представляет из себя диапазон от первого до N-го числа Фибоначчи (1, 2, 3, 5, 8, 13 и т.д.)
 * С помощью функций begin и end можно получить итераторы и пробежать по диапазону или передать их в STL-алгоритмы
 */
class FibonacciRange {
public:
    class Iterator {
        friend class FibonacciRange;
    public:
        using value_type = uint64_t;
        using difference_type = ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category = std::input_iterator_tag;

        explicit Iterator(uint64_t* it): it(it) {}

        value_type operator*() const {
            return *it;
        }

        Iterator &operator++() {
            it++;
            return *this;
        }

        Iterator operator++(int) {
            Iterator copy(*this);
            *this->operator++();
            return copy;
        }

        bool operator==(const Iterator &rhs) const {
            return it==rhs.it;
        }
        bool operator!=(const Iterator &rhs) const {
            return it!=rhs.it;
        }
        bool operator<(const Iterator &rhs) const {
            return it<rhs.it;
        }

    private:
        uint64_t it;
    };

    FibonacciRange(size_t amount) : array(new uint64_t[amount]), amount(amount)
    {
        array[0]=1;
        array[1]=array[0]+1
        for(size_t i=2; i<amount; ++i){
            array[i]=array[i-1]+array[i-2];
        }
    }

    Iterator begin() const {
        return Iterator(&array[0]);
    }

    Iterator end() const {
        return Iterator(&array[amount-1]+1);
    }
    size_t size() const {
        return amount;
    }
private:
    uint64_t* array;
    size_t amount;
};