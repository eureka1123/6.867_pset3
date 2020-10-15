#ifndef SINGLE_PARTICLE_SYSTEM_H_
#define SINGLE_PARTICLE_SYSTEM_H_

#include "ParticleSystemBase.hpp"

namespace GLOO {
class SingleParticleSystem : public ParticleSystemBase {
  public:
    ParticleState ComputeTimeDerivative(const ParticleState& state,
                                              float time) const override {
        auto positions = state.positions[0];
        std::vector<glm::vec3> time_derivative = {glm::vec3(-positions[1], positions[0], 0.f)};
        ParticleState derivative_state;
        derivative_state.positions = time_derivative;
        //velocities are never used for single particle
        derivative_state.velocities = time_derivative;
        return derivative_state;
    };
};
}  // namespace GLOO

#endif
