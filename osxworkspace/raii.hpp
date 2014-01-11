/*
 * raii.hpp
 *
 *  Created on: Dec 6, 2013
 *      Author: Rong
 */

#ifndef RAII_HPP_
#define RAII_HPP_


template <class Resource, class ConstructorArgument, Resource (*aquire)(ConstructorArgument),  void (*release)(Resource)> class RAII {
  Resource _handler;
public:
  RAII(ConstructorArgument arg) {
    _handler = aquire(arg);
  }

  ~RAII() {
    release(_handler);
  }

  operator Resource() {
     return _handler;
   }
};

template <class Resource, class ConstructorArgument, Resource (*aquire)(ConstructorArgument),  void (*release)(Resource)> class RAII {
  Resource _handler;
public:
  RAII(ConstructorArgument arg) {
    _handler = aquire(arg);
  }

  ~RAII() {
    release(_handler);
  }

  operator Resource() {
     return _handler;
   }
};

#endif /* RAII_HPP_ */
