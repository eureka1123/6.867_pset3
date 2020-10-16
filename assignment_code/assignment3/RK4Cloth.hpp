#ifndef RK4_CLOTH_H_
#define RK4_CLOTH_H_

#include "gloo/SceneNode.hpp"
#include "ForwardRK4Integrator.hpp"
#include "PendulumSystem.hpp"
#include "ParticleState.hpp"
#include "gloo/VertexObject.hpp"
#include "gloo/shaders/ShaderProgram.hpp"
#include "gloo/shaders/PhongShader.hpp"
#include "gloo/shaders/SimpleShader.hpp"
#include "gloo/components/ShadingComponent.hpp"
#include "gloo/components/RenderingComponent.hpp"

namespace GLOO {

class RK4Cloth : public SceneNode {
 public:
  RK4Cloth(float integration_step);
  void Update(double delta_time) override;

 private:
     ForwardRK4Integrator<PendulumSystem, ParticleState> RK4_integrator_;
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