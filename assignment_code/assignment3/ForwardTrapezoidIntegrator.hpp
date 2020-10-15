#ifndef FORWARD_TRAPEZOID_INTEGRATOR_H_
#define FORWARD_TRAPEZOID_INTEGRATOR_H_

#include "IntegratorBase.hpp"
#include "glm/gtx/string_cast.hpp"

namespace GLOO {
template <class TSystem, class TState>
class ForwardTrapezoidIntegrator : public IntegratorBase<TSystem, TState> {
  public:
	  TState Integrate(const TSystem& system,
	                   const TState& state,
	                   float start_time,
	                   float dt) const override {
	    // TODO: Here we are returning the state at time t (which is NOT what we
	    // want). Please replace the line below by the state at time t + dt using
	    // forward Euler integration.
	    auto f_0 = system.ComputeTimeDerivative(state, start_time);
	    auto f_1 = system.ComputeTimeDerivative(state + dt * f_0, start_time + dt);

	    return state + (dt / 2) * (f_0 + f_1);
	  }
};
}  // namespace GLOO

#endif
