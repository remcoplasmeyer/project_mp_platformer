#pragma once

#include <boost/utility.hpp>

class World;

class ISystem : boost::noncopyable {
    World* world_;
  private:
    //! Called every step with deltat time since last call.
    //!
    //! The time is given in microseconds.
    //!
    //! TODO: Enforce this using chrono?
    virtual void do_update(int deltat) = 0;
  public:
    //! Associate this system with the given world.
    //!
    //! Hm, it would help if we enforced that the world had to create this.
    //! World is becoming a bit of a god class now.
    ISystem(World&);

    //! Forwarding function for do_update.
    //!
    //! Makes sure, amongst other things, that deltat is sane.
    void update(int deltat);

    //! Returns the world this system is operating on.
    World& get_world();

    virtual ~ISystem() = default;
};
 
