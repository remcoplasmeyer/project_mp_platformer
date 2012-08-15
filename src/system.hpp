#pragma once

#include <boost/utility.hpp>

class System : boost::noncopyable {
  private:
    virtual void do_update(int deltat) = 0;
  public:
    void update(int deltat) {
        do_update(deltat);
    }
    virtual ~System() {}
};
 
