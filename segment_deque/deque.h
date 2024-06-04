#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

//using namespace std;
//
//class SegmentBuffer{
//private:
//    int* elements; // Указатель на первый элемент сегмента очереди
//    int size; //Размер буфера
//    int head, tail; //Индекс начала и конца очереди
//public:
//    SegmentBuffer(int buffer_size) { //Конструктор класса
//        size = buffer_size;
//        elements = new int[size];
//        head = 0;
//        tail = 0;
//    }
//
//    void enqueue(int element) { //Добавление элемента в очередь
//        elements[tail] = element;
//        tail = (tail + 1) % size;
//    }
//
//    int dequeue() { //Извлечение элемента из очереди
//        int element = elements[head];
//        head = (head + 1) % size;
//        return element;
//    }
//
//    int get_size() const { //Получение размера очереди
//        return tail - head;
//    }
//
//    int get_element(int index) { //Получение элемента очереди по индексу
//        int element_index = (head + index) % size;
//        return elements[element_index];
//    }
//};
//
//template<typename T, size_t SegmentSize>
//class Deque{
//private:
//    vector<SegmentBuffer*> segments; //Вектор сегментов буфера
//    int buffer_size{}, segment_size{}; //Размер буфера и размер сегмента
//    int head_segment, head, tail_segment, tail; //Индекс начала и конца очереди
//public:
//
//    class iterator
//    {
//    public:
//        // конструкторы
//        iterator() = default;
//        iterator(const iterator&) = default;
//        iterator(iterator&&)  noexcept = default;
//        iterator(Deque<T, SegmentSize>* deque, size_t segment, size_t index);
//
//        // операторы
//        iterator& operator=(const iterator&) = default;
//        iterator& operator=(iterator&&) = default;
//        bool operator==(const iterator& other) const;
//        bool operator!=(const iterator& other) const;
//        iterator& operator++();
//        iterator operator++(int);
//        iterator& operator--();
//        iterator operator--(int);
//        T& operator*() const;
//        T* operator->() const;
//
//    private:
//        Deque<T, SegmentSize>* m_deque;
//        size_t m_segment{};
//        size_t m_index{};
//    };
//
//    class const_iterator
//    {
//    public:
//        // конструкторы
//        const_iterator() = default;
//        const_iterator(const const_iterator&) = default;
//        const_iterator(const_iterator&&) = default;
//        const_iterator(const Deque<T, SegmentSize>* deque, size_t segment, size_t index);
//        const_iterator(iterator other);
//
//        // операторы
//        const_iterator& operator=(const const_iterator&) = default;
//        const_iterator& operator=(const_iterator&&) = default;
//        bool operator==(const const_iterator& other) const;
//        bool operator!=(const const_iterator& other) const;
//        const_iterator& operator++();
//        const_iterator operator++(int);
//        const_iterator& operator--();
//        const_iterator operator--(int);
//        const T& operator*() const;
//        const T* operator->() const;
//
//    private:
//        const Deque<T, SegmentSize>* m_deque;
//        size_t m_segment;
//        size_t m_index;
//    };
//
//    Deque(int buffer_size, int segment_size) { //Конструктор класса
//        this->buffer_size = buffer_size;
//        this->segment_size = segment_size;
//        segments.push_back(new SegmentBuffer(segment_size));
//        head_segment = 0;
//        head = 0;
//        tail_segment = 0;
//        tail = 0;
//    }
//
//    void enqueue_front(int element) { //Добавление элемента в начало очереди
//        if(head == 0) { //Если начало первого сегмента
//            if(head_segment == 0) { // Если это первый сегмент
//                segments.insert(segments.begin(),new SegmentBuffer(segment_size));
//            }
//            head_segment--;
//            head = segment_size - 1;
//            segments[head_segment]->enqueue(element);
//        } else {
//            head--;
//            segments[head_segment]->enqueue(element);
//        }
//    }
//
//    void enqueue_back(int element) { //Добавление элемента в конец очереди
//        if(tail == segment_size - 1) { //Если конец последнего сегмента
//            if(tail_segment == segments.size() - 1) { //Если это последний сегмент
//                segments.push_back(new SegmentBuffer(segment_size));
//            }
//            tail_segment++;
//            tail = 0;
//            segments[tail_segment]->enqueue(element);
//        } else {
//            segments[tail_segment]->enqueue(element);
//            tail++;
//        }
//    }
//
//    int dequeue_front() { //Извлечение элемента из начала очереди
//        int element = segments[head_segment]->dequeue();
//        if(segments[head_segment]->get_size() == 0) { //Если сегмент пустой
//            delete segments[head_segment]; //Удаляем его
//            segments.erase(segments.begin() + head_segment);
//            head_segment++;
//            head = 0;
//        } else {
//            head++;
//        }
//        return element;
//    }
//
//    int dequeue_back() { //Извлечение элемента из конца очереди
//        int element = segments[tail_segment]->dequeue();
//        if(segments[tail_segment]->get_size() == 0) { //Если сегмент пустой
//            delete segments[tail_segment]; //Удаляем его
//            segments.erase(segments.begin() + tail_segment);
//            tail_segment--;
//            tail = segment_size - 1;
//        } else {
//            tail--;
//        }
//        return element;
//    }
//
//    int get_size() { //Получение размера очереди
//        int size = 0;
//        for(int i = 0; i < segments.size(); i++) {
//            size += segments[i]->get_size();
//        }
//        return size;
//    }
//
//    int get_element(int index) { //Получение элемента очереди по индексу
//        int segment_index = head_segment + index / segment_size;
//        int segment_offset = index % segment_size;
//        return segments[segment_index]->get_element(segment_offset);
//    }
//    vector<T> get_deque(Deque<T,SegmentSize> deque){
//        for(int i = 0; i < deque.get_size(); i++){
//            std::cout << deque.get_element(i) << "\n";
//        }
//    }
//
//    void sort() { //Сортировка элементов очереди
//        vector<int> v;
//        for(int i = 0; i < get_size(); i++) {
//            v.push_back(get_element(i));
//        }
//        std::sort(v.begin(), v.end());
//        clear();
//        for(int i = 0; i < v.size(); i++) {
//            enqueue_back(v[i]);
//        }
//    }
//
//    Deque map(int (*func)(int)) { //Применение функции ко всем элементам очереди
//        Deque result = Deque(buffer_size, segment_size);
//        for(int i = 0; i < get_size(); i++) {
//            int element = get_element(i);
//            result.enqueue_back(func(element));
//        }
//        return result;
//    }
//
//    Deque where(bool (*predicate)(int)) { //Отбор элементов по условию
//        Deque result = Deque(buffer_size, segment_size);
//        for(int i = 0; i < get_size(); i++) {
//            int element = get_element(i);
//            if(predicate(element)) {
//                result.enqueue_back(element);
//            }
//        }
//        return result;
//    }
//
//    int reduce(int (*func)(int, int), int initial_value) { //Операция свертки
//        int result = initial_value;
//        for(int i = 0; i < get_size(); i++) {
//            int element = get_element(i);
//            result = func(result, element);
//        }
//        return result;
//    }
//
//    void concatenate(Deque& other) { //Конкатенация очередей
//        for(int i = 0; i < other.get_size(); i++) {
//            enqueue_back(other.get_element(i));
//        }
//    }
//
//    Deque slice(int start, int end) { //Извлечение подпоследовательности по индексам
//        Deque result = Deque(buffer_size, segment_size);
//        for(int i = start; i < end; i++) {
//            result.enqueue_back(get_element(i));
//        }
//        return result;
//    }
//
//    bool contains(Deque& subsequence) { //Поиск подпоследовательности в очереди
//        if(subsequence.get_size() == 0) { //Пустая подпоследовательность в любой очереди
//            return true;
//        }
//        int match_count = 0;
//        for(int i = 0; i < get_size(); i++) {
//            if(get_element(i) == subsequence.get_element(match_count)) {
//                match_count++;
//            } else {
//                match_count = 0;
//            }
//            if(match_count == subsequence.get_size()) {
//                return true;
//            }
//        }
//        return false;
//    }
//
//    void clear() { //Очистка очереди
//        for(int i = 0; i < segments.size(); i++) {
//            delete segments[i];
//        }
//        segments.clear();
//        segments.push_back(new SegmentBuffer(segment_size));
//        head_segment = 0;
//        head = 0;
//        tail_segment = 0;
//        tail = 0;
//    }
//};

using namespace std;

template<class T>
class SegmentedDeque {
private:
    struct Node {
        std::vector<T> data;
        int begin_index;
        int end_index;
        Node(int begin_index, int end_index): data(end_index - begin_index), begin_index(begin_index), end_index(end_index) {}
    };
    vector<Node> segments;
    int front_index;
    int back_index;
    int max_segment_size;
public:
    explicit SegmentedDeque(int max_segment_size = 1024) : front_index(0), back_index(0), max_segment_size(max_segment_size) {}
    // базовые функции дека
    void push_front(T value) {
        if (front_index == 0) {
            insert_new_front_node();
        }
        front_index--;
        segments.back().data[front_index - segments.back().begin_index] = value;
    }
    T pop_front() {
        T result = front();
        front_index++;
        if (front_index == segments[0].end_index) {
            merge_front_nodes();
        }
        return result;
    }
    void push_back(T value) {
        if (back_index == segments.back().end_index) {
            insert_new_back_node();
        }
        segments.back().data[back_index - segments.back().begin_index] = value;
        back_index++;
    }
    T pop_back() {
        T result = back();
        back_index--;
        if (back_index == segments.back().begin_index) {
            merge_back_nodes();
        }
        return result;
    }
    T front() const {
        return segments[0].data[front_index - segments[0].begin_index];
    }
    T back() const {
        return segments.back().data[back_index - segments.back().begin_index - 1];
    }
    int size() const {
        return (back_index - front_index);
    }
    bool empty() const {
        return size() == 0;
    }


    void sort() {
        sort(segments.begin(), segments.end(), [](const Node& a, const Node& b) {return a.begin_index < b.begin_index; });
        for (auto& segment : segments) {
            std::sort(segment.data.begin(), segment.data.end());
        }
        for (int i = 1; i < segments.size(); i++) {
            Node& left = segments[i - 1];
            Node& right = segments[i];
            if (right.begin_index - left.end_index >= max_segment_size) {
                continue;
            }
            vector<T> merged_data;
            merged_data.reserve(right.end_index - left.begin_index);
            std::merge(left.data.begin(), left.data.end(), right.data.begin(), right.data.end(), back_inserter(merged_data));
            Node merged_node(left.begin_index, right.end_index);
            merged_node.data = move(merged_data);
            segments.erase(segments.begin() + i - 1, segments.begin() + i + 1);
            segments.insert(segments.begin() + i - 1, move(merged_node));
            i--;
        }
    }
    // map
    template<class Function>SegmentedDeque<T> map(Function func) {
        SegmentedDeque<T> result;
        for (auto& val : *this) {
            result.push_back(func(val));
        }
        return result;
    }
    // where
    template<class Function>SegmentedDeque<T> where(Function func) {
        SegmentedDeque<T> result;
        for (auto& val : *this) {
            if (func(val)) {
                result.push_back(val);
            }
        }
        return result;
    }
    // reduce
    template<class Function>T reduce(Function func, T initial) {
        for (auto& val : *this) {
            initial = func(initial, val);
        }
        return initial;
    }
    // конкатенация деков (объединяем с помощью push_back)
    void concatenate(SegmentedDeque<T>& other) {
        for (auto& val : other) {
            push_back(val);
        }
    }
    // извлечение подпоследовательности
    SegmentedDeque<T> subsequence(int start_index, int end_index) {
        SegmentedDeque<T> result;
        int index = 0;
        for (auto& val : *this) {
            if (index >= start_index && index < end_index) {
                result.push_back(val);
            }
            index++;
            if (index >= end_index) {
                break;
            }
        }
        return result;
    }
    // поиск на вхождение последовательности
    bool contains(const SegmentedDeque<T>& subseq) {
        if (size() < subseq.size()) {
            return false;
        }
        for (int i = 0; i <= size() - subseq.size(); i++) {
            bool match = true;
            for (int j = 0; j < subseq.size(); j++) {
                if ((*this)[i + j] != subseq[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return true;
            }
        }
        return false;
    }
    // слияние с другим деком
    SegmentedDeque<T> merge(SegmentedDeque<T>& other) {
        SegmentedDeque<T> result(max_segment_size);
        auto i1 = begin();
        auto i2 = other.begin();
        while (i1 != end() && i2 != other.end()) {
            if (*i1 < *i2) {
                result.push_back(*i1++);
            }
            else {
                result.push_back(*i2++);
            }
        }
        while (i1 != end()) {
            result.push_back(*i1++);
        }
        while (i2 != other.end()) {
            result.push_back(*i2++);
        }
        return result;
    }
    // операторы доступа
    T& operator[](int index) {
        int segment_index = get_segment_index(index);
        return segments[segment_index].data[index - segments[segment_index].begin_index];
    }
    const T& operator[](int index) const {
        int segment_index = get_segment_index(index);
        return segments[segment_index].data[index - segments[segment_index].begin_index];
    }
    // итераторы
    struct iterator {
        typename vector<Node>::iterator segment_it;
        typename vector<T>::iterator vector_it;
        int index;
        iterator(typename vector<Node>::iterator segment_it, typename vector<T>::iterator vector_it, int index):
        segment_it(segment_it), vector_it(vector_it), index(index) {}
        bool operator==(const iterator& other) const {
            return segment_it == other.segment_it && vector_it == other.vector_it && index == other.index;
        }
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }
        T& operator*() {
            return *vector_it;
        }
        iterator& operator++() {
            index++;
            vector_it++;
            while (vector_it == segment_it->data.end() && segment_it + 1 != end_it) {
                segment_it++;
                vector_it = segment_it->data.begin();
            }
            return *this;
        }
        iterator operator++(int) {
            iterator result(segment_it, vector_it, index);
            ++(*this);
            return result;
        }
    private:
        typename vector<Node>::iterator end_it;
        iterator(typename vector<Node>::iterator segment_it, typename vector<T>::iterator vector_it, int index, typename vector<Node>::iterator end_it):
        segment_it(segment_it), vector_it(vector_it), index(index), end_it(end_it) {}
        friend class SegmentedDeque<T>;
    };
    iterator begin() {
        if (empty()) {
            return end();
        }
        auto seg_it = segments.begin();
        auto vec_it = seg_it->data.begin() + (front_index - seg_it->begin_index);
        return iterator(seg_it, vec_it, front_index, segments.end());
    }
    iterator end() {
        return iterator(segments.end(), segments.back().data.end(), back_index, segments.end());
    }
private:
    void insert_new_front_node() {
        Node new_node(front_index - max_segment_size, front_index);
        new_node.data.resize(max_segment_size);
        segments.push_back(new_node);
    }
    void insert_new_back_node() {
        Node new_node(back_index, back_index + max_segment_size);
        new_node.data.resize(max_segment_size);
        segments.push_back(new_node);
    }
    void merge_front_nodes() {
        if (segments.size() == 1) {
            return;
        }
        Node& left = segments[segments.size() - 2];
        Node& right = segments.back();
        if (left.end_index - left.begin_index + right.end_index - right.begin_index >= max_segment_size) {
            return;
        }
        vector<T> merged_data;
        merged_data.reserve(left.data.size() + right.data.size());
        std::merge(left.data.begin(), left.data.end(), right.data.begin(), right.data.end(), back_inserter(merged_data));
        left.data = move(merged_data);
        left.end_index = right.end_index;
        segments.pop_back();
        back_index = left.end_index;
    }
    void merge_back_nodes() {
        if (segments.size() == 1) {
            return;
        }
        Node& left = segments[segments.size() - 2];
        Node& right = segments.back();
        if (left.end_index - left.begin_index + right.end_index - right.begin_index >= max_segment_size) {
            return;
        }
        vector<T> merged_data;
        merged_data.reserve(left.data.size() + right.data.size());
        std::merge(left.data.begin(), left.data.end(), right.data.begin(), right.data.end(), back_inserter(merged_data));
        left.data = move(merged_data);
        left.end_index = right.end_index;
        segments.pop_back();
        back_index = left.end_index;
    }
    int get_segment_index(int index) const {
        int index_left = 0;
        int index_right = segments.size() - 1;
        while (index_left < index_right) {
            int index_middle = (index_left + index_right) / 2;
            if (index < segments[index_middle].begin_index) {
                index_right = index_middle - 1;
            }
            else if (index >= segments[index_middle + 1].begin_index) {
                index_left = index_middle + 1;
            }
            else {
                index_left = index_middle;
                break;
            }
        }
        return index_left;
    }
};







