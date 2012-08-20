#pragma once

#include <boost/utility.hpp>

class World;

class System : boost::noncopyable {
    // Currently unused, will later be responsible for
    // the event queue.
    World* world_;
  private:
    virtual void do_update(int deltat) = 0;
  public:
    System(World&);
    void update(int deltat);
    World& get_world();
    virtual ~System();
};
 
