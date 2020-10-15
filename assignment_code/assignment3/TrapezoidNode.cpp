#include "TrapezoidNode.hpp"

#include "ForwardTrapezoidIntegrator.hpp"
#include "SingleParticleSystem.hpp"
#include "ParticleState.hpp"
#include "gloo/debug/PrimitiveFactory.hpp"
#include "gloo/shaders/PhongShader.hpp"
#include "glm/gtx/string_cast.hpp"


namespace GLOO {
TrapezoidNode::TrapezoidNode(float integration_step) {
  integration_step_ = integration_step;
  trapezoid_integrator_ = ForwardTrapezoidIntegrator<SingleParticleSystem, ParticleState>();
  system_ = SingleParticleSystem();
  time_ = 0.f;
  state_ = {{glm::vec3(-.4,0,0)}, {glm::vec3(0,0,0)}};
  frame_state_ = {{glm::vec3(-1.7,0,0)}, {glm::vec3(0,0,0)}};
  sphere_mesh_ = PrimitiveFactory::CreateSphere(0.1f, 25, 25);
  shader_ = std::make_shared<PhongShader>();
  CreateComponent<ShadingComponent>(shader_);
  CreateComponent<RenderingComponent>(sphere_mesh_);
  GetTransform().SetPosition((state_+frame_state_).positions[0]);
}

void TrapezoidNode::Update(double delta_time) {
  for (float i = 0; i < float(delta_time); i += integration_step_){
    time_ += delta_time;
    auto next_state = trapezoid_integrator_.Integrate(system_,
                   state_,
                   time_,
                   integration_step_);
    state_ = next_state;
  }
  GetTransform().SetPosition((state_+frame_state_).positions[0]);

}

}
