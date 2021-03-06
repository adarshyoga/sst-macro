#include "actor.h"

namespace sstmac {
namespace tutorial {

class christopher_guest :
  public actor
{
  FactoryRegister("guest", actor, christopher_guest,
              "Renowned writer, actor, improvisor of Spinal Tap fame")
 public:
  christopher_guest(sprockit::sim_parameters* params);

  std::string to_string() const override {
    return "count rugen";
  }

  virtual void act() override;

 protected:
  int num_fingers_;

};

}
}
