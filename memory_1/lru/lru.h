#include <unordered_map>
#include <list>

using namespace std;

template <typename TestKey, typename TestValue>

class LruCache {
public:
    explicit LruCache(size_t maxi) : max_size(maxi){};
    void Put(const TestKey& key, const TestValue& value) {
        auto it = mappa.find(key);
        if (it == mappa.end()) {
            double_list.push_front(key);
            mappa[key] = { value, double_list.begin() };
            if (mappa.size() > max_size) {
                mappa.erase(double_list.back());
                double_list.pop_back();
            }
        }
        else {
            double_list.erase(it->second.second);
            double_list.push_front(key);
            mappa[key] = { value, double_list.begin() };
        }
    }

    bool Get(const TestKey& key, TestValue* value) {
        auto it = mappa.find(key);
        if (it == mappa.end()) {
            return false;
        }
        double_list.erase(it->second.second);
        double_list.push_front(key);
        mappa[key] = { it->second.first, double_list.begin() };
        auto test = it -> second ;
        *value = test.first;
        return true;
    }
    ~LruCache()= default;
private:
    list<TestKey> double_list;
    unordered_map<TestKey, pair<TestValue, typename list<TestKey>::iterator>> mappa;
    size_t max_size;

};