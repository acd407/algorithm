#include <assert.h>
#include <corecrt.h>
#include <cwchar>
#include <vector>
using std::vector;
#include <memory>
using std::make_shared, std::shared_ptr;
using std::make_unique, std::unique_ptr;

enum Result { OK, FAILED };

template <typename T>
class List {
  public:
    T *data;
    size_t length;
    size_t size;
    Result result;

  public:
    List() {
        size = 16;
        length = 0;
        data = new T[size];
        result = OK;
    }
    List (std::initializer_list<int> list) {
        size = 16;
        length = 0;
        data = new T[size];
        result = OK;
        // List(); 为什么不行？
        this->push_back (list);
    }
    // 从1开始索引
    ~List() { delete[] data; }
    Result getLastError() { return result; }
    void clearList() { length = 0; }
    bool listEmpty() { return length == 0; }
    size_t listLength() { return length; }
    T &operator[] (size_t i) {
        assert (i < length);
        return data[i];
    }
    T &getElem (size_t i) {
        assert (i > 0 && i <= length);
        return data[i - 1];
    }
    size_t locateElem (T e) {
        for (size_t i = 0; i < length; i++) {
            if (data[i] == e) {
                return i + 1;
            }
        }
        return 0;
    }
    T &priorElem (T e) {
        auto i = locateElem (e) - 1;
        if (i - 1 >= 0) {
            return data[i - 1];
        }
        result = FAILED;
        return nullptr;
    }
    T &nextElem (T e) {
        auto i = locateElem (e) - 1;
        if (i + 1 < length) {
            return data[i + 1];
        }
        result = FAILED;
        return nullptr;
    }
    List<T> &push_back (T e) {
        if (length >= size) {
            extendMem();
        }
        data[length++] = e;
        return *this;
    }
    List<T> &push_back (std::initializer_list<int> list) {
        for (auto it = list.begin(); it != list.end(); ++it) {
            this->push_back (*it);
        }
        return *this;
    }
    T &pop() {
        if (length > 0)
            return data[length--];
        return nullptr;
    }
    List<T> &insert (T e, size_t i) {
        if (length >= size) {
            extendMem();
        }
        for (int c = length - 1; c >= i - 1; c--)
            data[c + 1] = data[c];
        data[i - 1] = e;
        return *this;
    }
    T del (size_t i) {
        assert (i <= length && i > 0);
        T ret = data[i - 1];
        for (int c = i; c < length; c++) {
            data[c - 1] = data[c];
        }
        length--;
        return ret;
    }
    List<T> &rm (size_t i) {
        assert (i <= length && i > 0);
        for (int c = i; c < length; c++) {
            data[c - 1] = data[c];
        }
        length--;
        return *this;
    }
    void extendMem (size_t msize) {
        assert (msize > size);
        T *newdata = new T[msize];
        auto ret = memcpy (newdata, data, sizeof (T) * length);
        assert (ret == newdata);
        delete[] data;
        data = newdata;
        size = msize;
    }
    void extendMem() { extendMem (length * 2); }
    List<T> &traverse (void (*f) (T &)) {
        for (int i = 0; i < length; i++) {
            f (data[i]);
        }
        return *this;
    }
    template <typename R>
    shared_ptr<vector<R>> ptraverse (R (*f) (T &)) {
        shared_ptr<vector<R>> ret = make_shared<vector<R>>();
        for (int i = 0; i < length; i++) {
            ret->push_back (f (data[i]));
        }
        return ret;
    }
    template <typename R>
    vector<R> traverse (R (*f) (T &)) { // 在栈增长之前，要立刻复制
        vector<R> ret = vector<R>();    // 局部变量
        for (int i = 0; i < length; i++) {
            ret.push_back (f (data[i]));
        }
        return ret;
    }
};
