#include <iostream>

class Array {
public:
    Array(std::ostream& ostream);
    Array(const Array& array);
    Array(size_t size, std::ostream& ostream = std::cout, int defaultValue = 0);
    ~Array();

    size_t Size() const;
    size_t Capacity() const;
    void Reserve(size_t newCapacity);
    void Resize(size_t newSize);
    void PushBack(int value = 0);
    void PopBack();

    int& operator [](const size_t& i);
    explicit operator bool() const;

    bool operator <(const Array& it) const;
    bool operator >(const Array& it) const;
    bool operator !=(const Array& it) const;
    bool operator ==(const Array& it) const;
    bool operator <=(const Array& it) const;
    bool operator >=(const Array& it) const;

    Array& operator <<(const int& value);
    Array& operator <<(const Array& it);

    friend std::ostream& operator <<(std::ostream& ostream, const Array& array);

private:
    int* Elements_;
    size_t Size_;
    size_t Capacity_;
    std::ostream& Ostream_;
};


Array::~Array(){
    delete[] Elements_;
    Ostream_ << "Destructed " << Size_ << "\n";
}

Array::Array(std::ostream& ostream) : Ostream_(ostream){
    Elements_ = new int[2];
    Size_ = 0;
    Capacity_ = 2;
    Ostream_ << "Constructed. " << *this << "\n";
}

Array::Array(const Array& array) : Ostream_(array.Ostream_){
    Size_ = array.Size();
    Capacity_ = array.Capacity();
    Elements_ = new int[Capacity()];
    for (size_t i = 0; i < Size(); ++i){
        Elements_[i] = array.Elements_[i];
    }
    Ostream_ << "Constructed from another Array. " << *this << "\n";//!
}

Array::Array(size_t size, std::ostream& ostream, int defaultValue) : Ostream_(ostream) {
    Size_ = size;
    Capacity_ = 2 * size;
    Elements_ = new int[Capacity()];
    for (size_t i = 0; i < size; ++i){
        Elements_[i] = defaultValue;
    }
    Ostream_ << "Constructed with default. "<< *this << "\n";//!
}

size_t Array::Size() const {
    return Size_;
}

size_t Array::Capacity() const{
    return Capacity_;
}

void Array::Reserve(size_t newCapacity){
    if (newCapacity > Capacity()){
        int* Elems_ = new int[newCapacity];
        for (size_t i = 0; i < Size(); ++i){
            Elems_[i] = Elements_[i];
        }
        delete[] Elements_;
        Elements_ = Elems_;
        Capacity_ = newCapacity;
    }
}

void Array::Resize(size_t newSize){
    if (newSize > Capacity()){
        Array::Reserve(newSize);
    }
    Size_ = newSize;
}

void Array::PushBack(int value){
    if (Size() == Capacity()){
        Array::Reserve(Capacity() * 2);
    }
    *(Elements_ + int(Size())) = value;
    Size_++;

}

void Array::PopBack(){
    Size_--;
}

int& Array::operator [](const size_t& i){
    return *(Elements_ + i);
}

Array::operator bool() const{
    return Size() != 0;
}


bool Array::operator <(const Array& it) const{
    for (size_t i = 0; i < std::min(Size(), it.Size()); ++i){
        if(Elements_[i] > it.Elements_[i]){
            return false;
        }else if(Elements_[i] < it.Elements_ [i])
            return true;
    }
    return false;
}

bool Array::operator >(const Array& it) const{
    return !Array::operator<(it);
}

bool Array::operator !=(const Array& it) const{
    for (size_t i = 0; i < std::min(Size(), it.Size()); ++i){
        if (Elements_[i] != it.Elements_ [i]){
            return true;
        }
    }
    return false;
}

bool Array::operator ==(const Array& it) const{
    return !Array::operator!=(it);
}

bool Array::operator <=(const Array& it) const{
    for (size_t i = 0; i < std::min(Size(), it.Size()); ++i){
        if (Elements_[i] > it.Elements_[i]){
            return false;
        }else if(Elements_[i] < it.Elements_[i])
            return true;
    }
    return true;
}

bool Array::operator >=(const Array& it) const{
    return !Array::operator<=(it);
}

Array& Array::operator <<(const int& value){
    PushBack(value);
    return *this;
}

Array& Array::operator <<(const Array& it){
    for (size_t i = 0; i < it.Size(); ++i){
        PushBack(it.Elements_[i]);
    }
    return *this;
}

std::ostream& operator <<(std::ostream& ostream, const Array& array){
    if (array.Size() == 0){
        ostream << "Result Array's capacity is " << array.Capacity() << " and size is " << 0;
    }else{
        ostream << "Result Array's capacity is " << array.Capacity() << " and size is " << array.Size()
                << ", elements are: ";
        for (size_t i = 0; i < array.Size() - 1; ++i){
            ostream << *(array.Elements_ + i) << ", ";
        }
        ostream << *(array.Elements_ + array.Size() - 1);
    }
    return ostream;
}