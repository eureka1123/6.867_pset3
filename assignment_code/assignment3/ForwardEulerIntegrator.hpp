#ifndef FORWARD_EULER_INTEGRATOR_H_
#define FORWARD_EULER_INTEGRATOR_H_

#include "IntegratorBase.hpp"
#include "glm/gtx/string_cast.hpp"

namespace GLOO {
template <class TSystem, class TState>
class ForwardEulerIntegrator : public IntegratorBase<TSystem, TState> {
  public:
	  TState Integrate(const TSystem& system,
	                   const TState& state,
	                   float start_time,
	                   float dt) const override {
	    // TODO: Here we are returning the state at time t (which is NOT what we
	    // want). Please replace the line below by the state at time t + dt using
	    // forward Euler integration.
	    auto f_x = system.ComputeTimeDerivative(state, start_time);
	    return state + dt * f_x;
	  }
};
}  // namespace GLOO

#endif
