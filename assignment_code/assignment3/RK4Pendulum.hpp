#ifndef RK4_PENDULUM_H_
#define RK4_PENDULUM_H_

#include "gloo/SceneNode.hpp"
#include "ForwardRK4Integrator.hpp"
#include "PendulumSystem.hpp"
#include "ParticleState.hpp"
#include "gloo/VertexObject.hpp"
#include "gloo/shaders/ShaderProgram.hpp"
#include "gloo/shaders/PhongShader.hpp"
#include "gloo/components/ShadingComponent.hpp"
#include "gloo/components/RenderingComponent.hpp"

namespace GLOO {

class RK4Pendulum : public SceneNode {
 public:
  RK4Pendulum(float integration_step);
  void Update(double delta_time) override;

 private:
     ForwardRK4Integrator<PendulumSystem, ParticleState> RK4_integrator_;
     PendulumSystem system_;
     float integration_step_;
     float time_;
     std::shared_ptr<PhongShader> shader_;
     std::shared_ptr<VertexObject> sphere_mesh_;
     std::vector<SceneNode*> sphere_ptrs_;
};
}  // namespace GLOO

#endif