// Temporary and lazy includes. Like whole project.
#include <gtkmm-3.0/gtkmm.h>
#include <gtkmm-3.0/gtkmm/glarea.h>

#include <ctime>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <memory>

#include "core/opengl/shader/shader_program.h"
#include "core/opengl/shader/shader_program_builder.h"
#include "gl.h"
#include "object/object.h"

class OpenGl : public Gtk::GLArea {
 public:
  OpenGl() {
    signal_render().connect(sigc::mem_fun(*this, &OpenGl::render), false);
    signal_realize().connect(sigc::mem_fun(*this, &OpenGl::init), false);
  }

  void init() {
    make_current();

    s21::shaders::ShaderProgramBuilder builder;

    base = builder.AddVertexShaderFromFile("./shaders/base_vertex.glsl")
                 .AddFragmentShaderFromFile("./shaders/base_fragment.glsl")
                 .Build();

    vertex = builder.AddVertexShaderFromFile("./shaders/base_vertex.glsl")
                .AddFragmentShaderFromFile("./shaders/base_fragment.glsl")
                .AddGeometryShaderFromFile("./shaders/geometry_shader.glsl")
                .Build();

    obj = new s21::Object();
    obj->LoadMeshesFromFile("../models/bugatti.obj");

    glClearColor(0.2, 0.2, 0.2, 1);
    glEnable(GL_DEPTH_TEST);
  }

  bool render(const Glib::RefPtr<Gdk::GLContext> &context) {
    std::cerr << "Draw" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    projection = glm::mat4(1.f);
    view = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 0.0f, -5.0f));

    float w = (float)get_allocation().get_width();
    float h = (float)get_allocation().get_height();
    float aspect = w / h;
    if (perspective) {
      projection = glm::perspective(glm::radians(90.f), aspect, 0.1f, 10000.f);
    } else {
      projection = glm::ortho(-aspect, aspect, -1.f, 1.f, 0.1f, 10000.f);
    }

    glm::mat4 test = obj->GetResultMatrix();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    base.Use();
    base.SetUniformMatrix4f("view", view);
    base.SetUniformMatrix4f("projection", projection);
    base.SetUniformMatrix4f("transform", obj->GetResultMatrix());
    obj->Draw();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    vertex.Use();
    vertex.SetUniformMatrix4f("view", view);
    vertex.SetUniformMatrix4f("projection", projection);
    vertex.SetUniformMatrix4f("transform", obj->GetResultMatrix());
    vertex.SetUniformVector2f("ScreenSize", glm::vec2(w, h));
    vertex.SetUniformInteger("DrawType", 1);
    obj->Draw();
    return true;
  }

  bool KeyHandler(GdkEventKey *event) {
    uint key_val = event->keyval;
    if (key_val == 'a' || key_val == 'A') {
      obj->Transform().position.x -= 0.1f;
    } else if (key_val == 'd' || key_val == 'D') {
      obj->Transform().position.x += 0.1f;
    } else if (key_val == 'w' || key_val == 'W') {
      obj->Transform().position.z -= 0.1f;
    } else if (key_val == 's' || key_val == 'S') {
      obj->Transform().position.z += 0.1f;
    } else if (key_val == 'q' || key_val == 'Q') {
      obj->Transform().rotation.z += 15.0f;
    } else if (key_val == 'e' || key_val == 'E') {
      obj->Transform().rotation.z -= 15.1f;
    } else if (key_val == 'r' || key_val == 'R') {
      obj->Transform().rotation.y -= 15.0f;
    } else if (key_val == 't' || key_val == 'T') {
      obj->Transform().rotation.y += 15.0f;
    } else if (key_val == 'f' || key_val == 'F') {
      obj->Transform().rotation.x -= 15.0f;
    } else if (key_val == 'g' || key_val == 'G') {
      obj->Transform().rotation.x += 15.0f;
    } else if (key_val == 'z' || key_val == 'Z') {
      obj->Transform().position.y += 0.1f;
    } else if (key_val == 'c' || key_val == 'C') {
      obj->Transform().position.y -= 0.1f;
    } else if (key_val == 'v' || key_val == 'V') {
      kScale -= 0.1f;
      obj->Transform().scale = glm::vec3(kScale);
    } else if (key_val == 'b' || key_val == 'B') {
      kScale += 0.1f;
      obj->Transform().scale = glm::vec3(kScale);
    } else if (key_val == 'x' || key_val == 'X') {
      perspective ^= 1;
    } else if (key_val == 'p' || key_val == 'P') {
      translate = glm::mat4(1.0f);
      rotate = glm::mat4(1.0f);
      scale = glm::mat4(1.0f);
      perspective = 1;
    }
    std::cerr << kScale << std::endl;

    transform = translate * scale * rotate;
    queue_draw();
    return false;
  }

  glm::mat4 translate{1.f};
  glm::mat4 scale{1.f};
  glm::mat4 rotate{1.f};

  float kScale{1.0f};
  int perspective = 1;
  glm::mat4 view{1.f};
  glm::mat4 projection{1.f};
  glm::mat4 transform{1.f};
  s21::shaders::ShaderProgram vertex;
  s21::shaders::ShaderProgram base;
  s21::Object *obj;
  clock_t start_time;
  clock_t end_time;
};

int main(int argc, char *argv[]) {
  auto app = Gtk::Application::create(argc, argv);
  Gtk::Window window;
  OpenGl area;
  area.property_has_depth_buffer() = true;
  window.signal_key_press_event().connect(
      sigc::mem_fun(area, &OpenGl::KeyHandler), false);
  window.add(area);

  window.show_all();
  return app->run(window);
}
