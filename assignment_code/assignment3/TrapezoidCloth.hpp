#ifndef TRAPEZOID_CLOTH_H_
#define TRAPEZOID_CLOTH_H_

#include "gloo/SceneNode.hpp"
#include "ForwardTrapezoidIntegrator.hpp"
#include "PendulumSystem.hpp"
#include "ParticleState.hpp"
#include "gloo/VertexObject.hpp"
#include "gloo/shaders/ShaderProgram.hpp"
#include "gloo/shaders/PhongShader.hpp"
#include "gloo/shaders/SimpleShader.hpp"
#include "gloo/components/ShadingComponent.hpp"
#include "gloo/components/RenderingComponent.hpp"

namespace GLOO {

class TrapezoidCloth : public SceneNode {
 public:
  TrapezoidCloth(float integration_step);
  void Update(double delta_time) override;

 private:
     ForwardTrapezoidIntegrator<PendulumSystem, ParticleState> integrator_;
     PendulumSystem system_;
     float integration_step_;
     float time_;
     int size_;
     float start_x;
     float start_y;
     float r;
     std::shared_ptr<PhongShader> shader_;
     std::shared_ptr<SimpleShader> line_shader_;
     std::shared_ptr<VertexObject> sphere_mesh_;
     std::vector<SceneNode*> sphere_ptrs_;
     std::vector<VertexObject*> structural_ptrs_;
};
}  // namespace GLOO

#endif