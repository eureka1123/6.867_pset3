#include "TrapezoidCloth.hpp"

#include "ForwardTrapezoidIntegrator.hpp"
#include "PendulumSystem.hpp"
#include "ParticleState.hpp"
#include "gloo/debug/PrimitiveFactory.hpp"
#include "gloo/shaders/PhongShader.hpp"
#include "gloo/shaders/SimpleShader.hpp"
#include "glm/gtx/string_cast.hpp"
#include "gloo/InputManager.hpp"



namespace GLOO {
TrapezoidCloth::TrapezoidCloth(float integration_step) {
  integration_step_ = integration_step;
  integrator_ = ForwardTrapezoidIntegrator<PendulumSystem, ParticleState>();
  system_ = PendulumSystem();
  time_ = 0.f;
  sphere_mesh_ = PrimitiveFactory::CreateSphere(0.025f, 25, 25);
  shader_ = std::make_shared<PhongShader>();
  auto line_shader_ = std::make_shared<SimpleShader>();

  start_x = -.2f;
  start_y = 0.f;
  float x = start_x;
  float y = start_y;
  float mass = .3f;
  bool fixed = false;
  size_ = 8;
  r = .2;
  int k = 40;

  for (int i = 0; i<size_; i++){
    for (int j = 0; j<size_; j++){
      if ((i==size_ - 1 && j == size_ - 1) || (i==size_-1 && j == 0)){
        fixed = true;
      }
      system_.AddParticle(glm::vec3(x, y, 0), mass, fixed);
      fixed = false; 
      x = x + r;
      if (i>0){
        auto curr_index = i * size_ + j;
        auto prev_index = (i - 1) * size_ + j;
        system_.AddSpring(curr_index, prev_index, r, k);
        auto line = std::make_shared<VertexObject>();
        auto positions = make_unique<PositionArray>();
        positions -> push_back(system_.state_.positions[prev_index]);
        positions -> push_back(system_.state_.positions[curr_index]);
        auto indices = make_unique<IndexArray>();
        indices->push_back(0);
        indices->push_back(1);
        line ->UpdatePositions(std::move(positions));
        line ->UpdateIndices(std::move(indices));
        auto line_node = make_unique<SceneNode>();
        line_node->CreateComponent<ShadingComponent>(line_shader_);

        auto& rc = line_node->CreateComponent<RenderingComponent>(line);
        rc.SetDrawMode(DrawMode::Lines);
        structural_ptrs_.push_back(line.get());
        AddChild(std::move(line_node));
        if (i>1){
          auto prev_index = (i - 2) * size_ + j;
          system_.AddSpring(curr_index, prev_index, r, k);
        }
        if (j < size_-1) {
          auto diag_index = (i-1) * size_ + (j+1);
          system_.AddSpring(curr_index, diag_index, r, k);
        }
      }
      if (j>0){
        auto curr_index = i * size_ + j;
        auto prev_index = i * size_ + (j-1);
        system_.AddSpring(curr_index, prev_index, r, k);
        auto line = std::make_shared<VertexObject>();
        auto positions = make_unique<PositionArray>();
        positions -> push_back(system_.state_.positions[prev_index]);
        positions -> push_back(system_.state_.positions[curr_index]);
        auto indices = make_unique<IndexArray>();
        indices->push_back(0);
        indices->push_back(1);
        line ->UpdatePositions(std::move(positions));
        line ->UpdateIndices(std::move(indices));
        auto line_node = make_unique<SceneNode>();
        line_node->CreateComponent<ShadingComponent>(line_shader_);

        auto& rc = line_node->CreateComponent<RenderingComponent>(line);
        rc.SetDrawMode(DrawMode::Lines);
        structural_ptrs_.push_back(line.get());
        AddChild(std::move(line_node));
        if (j>1){
          auto prev_index = i * size_ + (j-2);
          system_.AddSpring(curr_index, prev_index, r, k);
        }
        if (i > 0) {
          auto diag_index = (i-1) * size_ + (j-1);
          system_.AddSpring(curr_index, diag_index, r, k);
        }
      }
    }
    x = start_x;
    y = y + r;
  }
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

void TrapezoidCloth::Update(double delta_time) {
  for (float i = 0; i < float(delta_time); i += integration_step_){
    time_ += delta_time;
    auto next_state = integrator_.Integrate(system_,
                   system_.state_,
                   time_,
                   integration_step_);
    system_.state_ = next_state;
  }

  if (InputManager::GetInstance().IsKeyPressed('R')) {
    float x = start_x;
    float y = start_y;
    for (int i = 0; i<size_; i++){
      for (int j = 0; j<size_; j++){
        auto sphere_node = sphere_ptrs_[i*size_+j];
        sphere_node->GetTransform().SetPosition(glm::vec3(x,y,0));
        system_.state_.positions[i*size_+j] = glm::vec3(x,y,0);
        x = x+r;
        system_.ChangeParticleState(i*size_+j, false);
      }
      x = start_x;
      y = y+r;
    }
  }
  else{
    for (int i = 0; i< system_.state_.positions.size(); i++){
      auto sphere_node = sphere_ptrs_[i];
      sphere_node->GetTransform().SetPosition(system_.state_.positions[i]);
    }
  }
  int index = 0;
  for (int i =0; i<size_;i++){
    for (int j=0; j<size_; j++){
      if (i>0){
        auto curr_index = i * size_ + j;
        auto prev_index = (i - 1) * size_ + j;
        auto line = structural_ptrs_[index];

        auto positions = make_unique<PositionArray>();
        positions -> push_back(system_.state_.positions[prev_index]);
        positions -> push_back(system_.state_.positions[curr_index]);
        auto indices = make_unique<IndexArray>();
        indices->push_back(0);
        indices->push_back(1);
        line ->UpdatePositions(std::move(positions));
        line ->UpdateIndices(std::move(indices));
        index = index + 1;
      }
      if (j>0){
        auto curr_index = i * size_ + j;
        auto prev_index = i * size_ + (j-1);
        auto line = structural_ptrs_[index];

        auto positions = make_unique<PositionArray>();
        positions -> push_back(system_.state_.positions[prev_index]);
        positions -> push_back(system_.state_.positions[curr_index]);
        auto indices = make_unique<IndexArray>();
        indices->push_back(0);
        indices->push_back(1);
        line ->UpdatePositions(std::move(positions));
        line ->UpdateIndices(std::move(indices));
        index = index + 1;
      }
    }
  }

}

}
