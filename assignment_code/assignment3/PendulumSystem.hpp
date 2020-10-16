#ifndef PENDULUM_SYSTEM_H_
#define PENDULUM_SYSTEM_H_

#include "ParticleSystemBase.hpp"
#include <map>

namespace GLOO {
class PendulumSystem : public ParticleSystemBase {
  public:
    PendulumSystem();
    ParticleState ComputeTimeDerivative(const ParticleState& state,
                                              float time) const override;
    void AddParticle(const glm::vec3 particle_position, float mass, bool fix);
    void AddSpring(int particle_1, int particle_2, float rest_length, float spring_constant);
    void ChangeParticleState(int particle_index, bool state);
    ParticleState state_;
  private:
    std::vector<float> masses_;
    std::map<int, std::map<int, std::tuple<float, float>>> springs_;
    std::vector<int> flags_;
};
}  // namespace GLOO

#endif
