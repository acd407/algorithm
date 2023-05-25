#include <assert.h>
#include <corecrt.h>
#include <cwchar>
#include <vector>
using std::vector;
#include <cstdio>
#include <memory>
using std::make_shared, std::shared_ptr;
using std::make_unique, std::unique_ptr;

template <typename T>
class List {
    T *_data;
    size_t _length;
    size_t _size;
    void extend_memory (size_t msize) {
        assert (msize > _size);
        T *newdata = new T[msize];
        auto ret = memcpy (newdata, _data, sizeof (T) * _length);
        assert (ret == newdata);
        delete[] _data;
        _data = newdata;
        _size = msize;
        //printf("mem: %d\n",msize);
    }
    void extend_memory() { extend_memory (_length * 2); }

  public:
    List() {
        _size = 16;
        _length = 0;
        _data = new T[_size];
    }
    List (std::initializer_list<T> list) {
        _size = 16;
        _length = 0;
        _data = new T[_size];
        // List(); 为什么不行？
        this->push_back (list);
    }

    ~List() { delete[] _data; }
    void clear() { _length = 0; }
    bool emptyQ() { return _length == 0; }
    size_t length() { return _length; }
    size_t size() { return _size; }
    T *data() { return _data; }
    T &operator[] (size_t i) {
        assert (i < _length);
        return _data[i];
    }
    size_t locate (T e) {
        for (size_t i = 0; i < _length; i++) {
            if (_data[i] == e) {
                return i;
            }
        }
        assert (1 == 0);
    }
    T &pred (T e) {
        auto i = locate (e);
        assert (i > 0);
        return _data[i - 1];
    }
    T &succ (T e) {
        auto i = locate (e);
        assert (i + 1 < _length);
        return _data[i + 1];
    }
    List<T> &push_back (T e) {
        if (_length >= _size) {
            extend_memory();
        }
        _data[_length++] = e;
        return *this;
    }
    List<T> &push_back (std::initializer_list<T> list) {
        for (auto i : list)
            push_back (i);
        return *this;
    }
    T &pop() {
        assert (_length > 0);
        return _data[--_length];
    }
    List<T> &insert (size_t pos, T val) {
        if (_length >= _size) {
            extend_memory();
        }
        for (int c = _length - 1; c >= pos; c--)
            _data[c + 1] = _data[c];
        _data[pos] = val;
        _length++;
        return *this;
    }
    List<T> &rm (size_t pos) {
        assert (pos < _length && pos >= 0);
        for (int c = pos + 1; c < _length; c++) {
            _data[c - 1] = _data[c];
        }
        _length--;
        return *this;
    }
    List<T> &rm () {
        assert (_length > 0);
        return rm(_length - 1);
    }
    List<T> &traverse (void (*f) (T &)) {
        for (int i = 0; i < _length; i++) {
            f (_data[i]);
        }
        return *this;
    }
    template <typename R>
    shared_ptr<vector<R>> straverse (R (*f) (T &)) {
        shared_ptr<vector<R>> val = make_shared<vector<R>>();
        for (int i = 0; i < _length; i++) {
            val->push_back (f (_data[i]));
        }
        return val;
    }
    template <typename R>
    vector<R> traverse (R (*f) (T &)) { // 在栈增长之前，要立刻复制
        vector<R> val = vector<R>();    // 局部变量
        for (int i = 0; i < _length; i++) {
            val.push_back (f (_data[i]));
        }
        return val;
    }
};
