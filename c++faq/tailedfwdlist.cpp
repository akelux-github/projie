/*
 * tailedfwdlist.cpp
 *
 *  Created on: Nov 29, 2013
 *      Author: rong
 */
#include <forward_list>
#include <queue>
#include <string>
#include <iostream>
#include <iterator>
using std::string;
using std::cout;
using std::endl;

using std::forward_list;
using std::queue;

template <class T> class TailedFwdList {
public:
  typedef typename forward_list<T>::size_type size_type;
  typedef typename forward_list<T>::value_type value_type;
  typedef typename forward_list<T>::reference reference;
  typedef typename forward_list<T>::const_reference const_reference;
private:
  /*
  front
  back
  push_back
  pop_front
   */
  forward_list<T> _data{};
  typename forward_list<T>::iterator _last;
  size_type _size{0};
public:


  // using forward_list::forward_list;  // not necessary?
  inline TailedFwdList() {
    _last = _data.before_begin();
  }

  inline reference back() { return *_last; }
  // const_reference back() const { return *_last; }
  inline void push_back (const_reference val) { _last = _data.insert_after(_last, val); ++_size; }
  inline void push_back (value_type&& val) { _last = _data.insert_after(_last, val); ++_size;}
  inline void pop_front () {
    if (_last == _data.begin() ) {
      _last = _data.before_begin();
    }
    _data.pop_front();
    --_size;
  }

  size_type size() const { return _size; }
  inline reference front() { return _data.front(); }
  inline bool empty() const { return _data.empty(); }
  // const_reference front() const { return _data.front(); }
  /*
  iterator begin() {
    return _data.begin();
  }

  const_iterator begin() const{
    return _data.cbegin();
  }

  iterator end() {
    return _data.end();
  }

  const_iterator end() const{
    return _data.cend();
  }*/

};


int main(void) {
  forward_list<int> l{1,2,3,4};

  for (auto x : l) {
    cout << ' ' << x;
  }

  cout << endl;

  queue<int, TailedFwdList<int>> q;
  q.push(1);
  q.push(2);
  q.push(3);
  cout << q.front() << endl;
  cout << q.back() << endl;
  q.pop();
  cout << q.front() << endl;
  cout << q.back() << endl;

  q.push(5);
  cout << "size: " << q.size() << endl;
  while (!q.empty()) {
    cout <<  ' ' << q.front();
    q.pop();
  }
  cout << endl;

  return 0;
}


