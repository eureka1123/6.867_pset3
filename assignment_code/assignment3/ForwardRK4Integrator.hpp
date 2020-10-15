#ifndef FORWARD_RK4_INTEGRATOR_H_
#define FORWARD_RK4_INTEGRATOR_H_

#include "IntegratorBase.hpp"
#include "glm/gtx/string_cast.hpp"
#include <iostream>

namespace GLOO {
template <class TSystem, class TState>
class ForwardRK4Integrator : public IntegratorBase<TSystem, TState> {
  public:
	  TState Integrate(const TSystem& system,
	                   const TState& state,
	                   float start_time,
	                   float dt) const override {
	    // TODO: Here we are returning the state at time t (which is NOT what we
	    // want). Please replace the line below by the state at time t + dt using
	    // forward Euler integration.
	    auto f_0 = dt * system.ComputeTimeDerivative(state, start_time);
	    auto f_1 = dt * system.ComputeTimeDerivative(state + .5f * f_0, start_time + dt/2.);
	    auto f_2 = dt * system.ComputeTimeDerivative(state + .5f * f_1, start_time + dt/2.);
	    auto f_3 = dt * system.ComputeTimeDerivative(state + f_2, start_time + dt);
	    return state + (1/6.) * (f_0 + 2.f * f_1  + 2.f * f_2 + f_3);
	  }
};
}  // namespace GLOO

#endif
