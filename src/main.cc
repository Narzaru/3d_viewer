// Temporary and lazy includes. Like whole project.
#include <gtkmm-3.0/gtkmm.h>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>
#include <gtkmm-3.0/gtkmm/glarea.h>
#include <memory>

#include "engine/renderer/renderer.h"
#include "engine/renderer/shader.h"
#include "engine/object/object.h"
#include "gl.h"

class OpenGl : public Gtk::GLArea {
 public:
  OpenGl() {
    signal_render().connect(sigc::mem_fun(*this, &OpenGl::render), false);
    signal_realize().connect(sigc::mem_fun(*this, &OpenGl::init), false);
  }

  void init() {
    make_current();

    shader = new ShaderProgram("./shaders/base_vertex.glsl",
                               "./shaders/base_fragment.glsl");
    shader->Complete();

    depth = new ShaderProgram("./shaders/base_vertex.glsl",
                              "./shaders/depth_test_fragment.glsl");
    depth->Complete();

    obj = new s21::Object(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f), "../models/cube.obj");
    axes.Axes();
    glClearColor(0.2, 0.2, 0.2, 1);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }

  bool render(const Glib::RefPtr<Gdk::GLContext> &context) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    projection = glm::mat4(1.f);
    view = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 0.0f, -5.0f));

    float w = (float)get_allocation().get_width();
    float h = (float)get_allocation().get_height();
    float aspect = w / h;
    if (perspective) {
      projection = glm::perspective(glm::radians(45.f), aspect, 0.1f, 10000.f);
    } else {
      projection = glm::ortho(-aspect, aspect, -1.f, 1.f, 0.1f, 10000.f);
    }

    shader->Use();
    shader->UniformMatrix4fv("view", view);
    shader->UniformMatrix4fv("projection", projection);
    shader->UniformMatrix4fv("transform", transform);
//    object.DrawMeshes(Renderer::VertexConnectionType::kTriangles);
    obj->Draw();
#ifdef AXES
    shader->Use();
    shader->UniformMatrix4fv("view", view);
    shader->UniformMatrix4fv("projection", projection);
    shader->UniformMatrix4fv("transform", transform);
    glDisable(GL_DEPTH_TEST);
    axes.DrawMeshes(Renderer::VertexConnectionType::kLines);
    glEnable(GL_DEPTH_TEST);
#endif  // AXES
    queue_draw();
    return true;
  }

  bool KeyHandler(GdkEventKey *event) {
    uint key_val = event->keyval;
    if (key_val == 'a' || key_val == 'A') {
      translate = glm::translate(translate, glm::vec3(-0.1f, 0.0f, 0.0f));
    } else if (key_val == 'd' || key_val == 'D') {
      translate = glm::translate(translate, glm::vec3(0.1f, 0.0f, 0.0f));
    } else if (key_val == 'w' || key_val == 'W') {
      translate = glm::translate(translate, glm::vec3(0.0f, 0.0f, -0.1f));
    } else if (key_val == 's' || key_val == 'S') {
      translate = glm::translate(translate, glm::vec3(0.0f, 0.0f, 0.1f));
    } else if (key_val == 'q' || key_val == 'Q') {
      rotate = glm::rotate(rotate, glm::radians(15.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    } else if (key_val == 'e' || key_val == 'E') {
      rotate = glm::rotate(rotate,glm::radians(-15.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    } else if (key_val == 'r' || key_val == 'R') {
      rotate = glm::rotate(rotate, glm::radians(-15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    } else if (key_val == 't' || key_val == 'T') {
      rotate = glm::rotate(rotate, glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    } else if (key_val == 'f' || key_val == 'F') {
      rotate = glm::rotate(rotate, glm::radians(-15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    } else if (key_val == 'g' || key_val == 'G') {
      rotate = glm::rotate(rotate, glm::radians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    } else if (key_val == 'z' || key_val == 'Z') {
      translate = glm::translate(translate, glm::vec3(0.0f, 0.1f, 0.0f));
    } else if (key_val == 'c' || key_val == 'C') {
      translate = glm::translate(translate, glm::vec3(0.0f, -0.1f, 0.0f));
    } else if (key_val == 'v' || key_val == 'V') {
      kScale -= .10f;
      scale = glm::scale(glm::mat4{1.f}, glm::vec3(kScale, kScale, kScale));
    } else if (key_val == 'b' || key_val == 'B') {
      kScale += .10f;
      scale = glm::scale(glm::mat4{1.f}, glm::vec3(kScale, kScale, kScale));
    } else if (key_val == 'x' || key_val == 'X') {
      perspective ^= 1;
    } else if (key_val == 'p' || key_val == 'P') {
      translate = glm::mat4(1.0f);
      rotate = glm::mat4(1.0f);
      scale = glm::mat4(1.0f);
      perspective = 1;
    }

    transform = translate * scale * rotate;

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
  ShaderProgram *shader;
  ShaderProgram *depth;
  s21::Object *obj;
  Renderer axes;
};

int main(int argc, char *argv[]) {
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
  Gtk::Window window;
  OpenGl area;
  area.property_has_depth_buffer() = true;
  window.signal_key_press_event()
      .connect(sigc::mem_fun(area, &OpenGl::KeyHandler), false);
  window.add(area);

  window.show_all();
  return app->run(window);
}
