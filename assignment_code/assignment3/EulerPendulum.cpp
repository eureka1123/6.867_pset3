#include "EulerPendulum.hpp"

#include "ForwardEulerIntegrator.hpp"
#include "PendulumSystem.hpp"
#include "ParticleState.hpp"
#include "gloo/debug/PrimitiveFactory.hpp"
#include "gloo/shaders/PhongShader.hpp"
#include "glm/gtx/string_cast.hpp"


namespace GLOO {
EulerPendulum::EulerPendulum(float integration_step) {
  integration_step_ = integration_step;
  euler_integrator_ = ForwardEulerIntegrator<PendulumSystem, ParticleState>();
  system_ = PendulumSystem();
  time_ = 0.f;
  system_.AddParticle(glm::vec3(-.7f, 1.f, 0), .5f, true);
  system_.AddParticle(glm::vec3(-.6f, .8f, 0), .5f, false);
  system_.AddParticle(glm::vec3(-.8f, .6f, 0), .5f, false);
  system_.AddParticle(glm::vec3(-.6f, .4f, 0), .5f, false);
  system_.AddParticle(glm::vec3(-.8f, .2f, 0), .5f, false);
  system_.AddSpring(0, 1, .15, 32);
  system_.AddSpring(1, 2, .15, 32);
  system_.AddSpring(2, 3, .15, 32);
  system_.AddSpring(3, 4, .15, 32);



  sphere_mesh_ = PrimitiveFactory::CreateSphere(0.025f, 25, 25);
  shader_ = std::make_shared<PhongShader>();
  //TODO make node for each
  for (auto position : system_.state_.positions){
    auto sphere_node = make_unique<SceneNode>();
    sphere_node->CreateComponent<ShadingComponent>(shader_);
    sphere_node->CreateComponent<RenderingComponent>(sphere_mesh_);
    sphere_node->GetTransform().SetPosition(position);
    sphere_ptrs_.push_back(sphere_node.get());
    AddChild(std::move(sphere_node));
  }
  
}

void EulerPendulum::Update(double delta_time) {
  for (float i = 0; i < float(delta_time); i += integration_step_){
    time_ += delta_time;
    auto next_state = euler_integrator_.Integrate(system_,
                   system_.state_,
                   time_,
                   integration_step_);
    system_.state_ = next_state;
  }
  for (int i = 0; i< system_.state_.positions.size(); i++){
    auto sphere_node = sphere_ptrs_[i];
    sphere_node->GetTransform().SetPosition(system_.state_.positions[i]);
  }

}

}
