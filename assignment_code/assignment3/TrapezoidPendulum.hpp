#ifndef TRAPEZOID_PENDULUM_H_
#define TRAPEZOID_PENDULUM_H_

#include "gloo/SceneNode.hpp"
#include "ForwardTrapezoidIntegrator.hpp"
#include "PendulumSystem.hpp"
#include "ParticleState.hpp"
#include "gloo/VertexObject.hpp"
#include "gloo/shaders/ShaderProgram.hpp"
#include "gloo/shaders/PhongShader.hpp"
#include "gloo/components/ShadingComponent.hpp"
#include "gloo/components/RenderingComponent.hpp"

namespace GLOO {

class TrapezoidPendulum : public SceneNode {
 public:
  TrapezoidPendulum(float integration_step);
  void Update(double delta_time) override;

 private:
     ForwardTrapezoidIntegrator<PendulumSystem, ParticleState> trapezoid_integrator_;
     PendulumSystem system_;
     float integration_step_;
     float time_;
     std::shared_ptr<PhongShader> shader_;
     std::shared_ptr<VertexObject> sphere_mesh_;
     std::vector<SceneNode*> sphere_ptrs_;
};
}  // namespace GLOO

#endif