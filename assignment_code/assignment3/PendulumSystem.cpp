#include "PendulumSystem.hpp"
#include "glm/gtx/string_cast.hpp"
#include <iostream>

namespace GLOO {
PendulumSystem::PendulumSystem(){
  state_ = {{},{}};
  masses_ = {};
  springs_ = {};
  flags_ = {};
}

ParticleState PendulumSystem::ComputeTimeDerivative(const ParticleState& state,
                                              float time) const {
  auto positions = state.positions;
  auto velocities = state.velocities;

  std::vector<glm::vec3> derivative_positions;
  std::vector<glm::vec3> derivative_velocities;
  
  glm::vec3 derivative_position;
  glm::vec3 derivative_velocity;
  for (int i = 0; i < state.positions.size(); i++){
    if (flags_[i]){
      derivative_position = glm::vec3(0,0,0);
      derivative_velocity = glm::vec3(0,0,0);
    } else{
      auto position = positions[i];
      auto velocity = velocities[i];

      auto gravity = masses_[i] * glm::vec3(0.f, -9.8f, 0.f);
      auto drag = -.3f * velocity;
      glm::vec3 spring_sum = glm::vec3(0.f, 0.f, 0.f);
      if (springs_.find(i) != springs_.end()) {
        for (auto j : springs_.at(i)){
          auto spring = springs_.at(i).at(j.first);
          auto r = std::get<0>(spring);
          auto k = std::get<1>(spring);
          auto d = position - positions[j.first];
          auto spring_force = -k * (glm::length(d)-r)*(1/glm::length(d))*d;
          spring_sum = spring_sum + spring_force;
        }
      }
      auto acceleration = (1/masses_[i]) * (gravity + drag + spring_sum);
      derivative_position = velocity;
      derivative_velocity = acceleration;
    }
    derivative_positions.push_back(derivative_position);
    derivative_velocities.push_back(derivative_velocity);
  }
  ParticleState derivative_state;
  derivative_state.positions = derivative_positions;
  derivative_state.velocities = derivative_velocities;
  return derivative_state;
};

void PendulumSystem::AddParticle(const glm::vec3 particle_position, float mass, bool fix){
  state_.positions.push_back(particle_position);
  state_.velocities.push_back(glm::vec3(0,0,0));
  masses_.push_back(mass);
  if (fix){
    flags_.push_back(true);
  } else {
    flags_.push_back(false);
  }
}

void PendulumSystem::AddSpring(int particle_1, int particle_2, float rest_length, float spring_constant){
  springs_[particle_1][particle_2] = {rest_length, spring_constant};
  springs_[particle_2][particle_1] = {rest_length, spring_constant};
}

void PendulumSystem::ChangeParticleState(int particle_index, bool state){
  flags_[particle_index] = state;
}

}
