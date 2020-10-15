#ifndef RK4_NODE_H_
#define RK4_NODE_H_

#include "gloo/SceneNode.hpp"
#include "ForwardRK4Integrator.hpp"
#include "SingleParticleSystem.hpp"
#include "ParticleState.hpp"
#include "gloo/VertexObject.hpp"
#include "gloo/shaders/ShaderProgram.hpp"
#include "gloo/shaders/PhongShader.hpp"
#include "gloo/components/ShadingComponent.hpp"
#include "gloo/components/RenderingComponent.hpp"

namespace GLOO {

class RK4Node : public SceneNode {
 public:
  RK4Node(float integration_step);
  void Update(double delta_time) override;

 private:
     ForwardRK4Integrator<SingleParticleSystem, ParticleState> RK4_integrator_;
     SingleParticleSystem system_;
     ParticleState state_;
     ParticleState frame_state_;
     float integration_step_;
     float time_;
     std::shared_ptr<PhongShader> shader_;
     std::shared_ptr<VertexObject> sphere_mesh_;

};
}  // namespace GLOO

#endif