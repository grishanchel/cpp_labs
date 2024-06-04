#include <vector>
#include <memory>
#include <string>
#include <map>

using namespace std;

template<class InputIterator, class T>
InputIterator find (InputIterator first, InputIterator last, const T& val)
{
    while (first!=last) {
        if (*first==val) return first;
        ++first;
    }
    return last;
}

vector<shared_ptr<string>> DeDuplicate(const vector<unique_ptr<string>> &in) {

    vector<shared_ptr<string>> out;
    map<string, shared_ptr<string>> mappa;
    for (auto &it: in) {
        if (mappa.find(*it) == mappa.end()) {
            shared_ptr<string> i = make_shared<string>(*it);
            mappa.insert(make_pair(*it, i));
            out.push_back(i);
        } else {
            out.push_back(mappa.at(*it));
        }
    }
    return out;
}

vector<unique_ptr<string>> Duplicate(const vector<shared_ptr<string>> &out) {

    vector<unique_ptr<string>> in;
    for (auto &it: out) {
        in.push_back(make_unique<string>(*it));
    }
    return in;
}































