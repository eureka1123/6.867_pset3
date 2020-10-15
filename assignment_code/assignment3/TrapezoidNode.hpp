#ifndef TRAPEZOID_NODE_H_
#define TRAPEZOID_NODE_H_

#include "gloo/SceneNode.hpp"
#include "ForwardTrapezoidIntegrator.hpp"
#include "SingleParticleSystem.hpp"
#include "ParticleState.hpp"
#include "gloo/VertexObject.hpp"
#include "gloo/shaders/ShaderProgram.hpp"
#include "gloo/shaders/PhongShader.hpp"
#include "gloo/components/ShadingComponent.hpp"
#include "gloo/components/RenderingComponent.hpp"

namespace GLOO {

class TrapezoidNode : public SceneNode {
 public:
  TrapezoidNode(float integration_step);
  void Update(double delta_time) override;

 private:
     ForwardTrapezoidIntegrator<SingleParticleSystem, ParticleState> trapezoid_integrator_;
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