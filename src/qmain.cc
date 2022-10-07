#include <QApplication>
#include <QGLFormat>
#include <QKeyEvent>
#include <QOpenGLFunctions>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QThread>
#include <QWindow>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>

#include "core/opengl/shader/shader_program.h"
#include "core/opengl/shader/shader_program_builder.h"
#include "object/object.h"

class OpenGLWindow : public QWindow, protected QOpenGLFunctions {
//    Q_OBJECT
 public:
  explicit OpenGLWindow(QWindow *parent = nullptr);

  virtual void render(QPainter *painter);
  virtual void render();

  virtual void initialize();

  void setAnimating(bool animating);

 public slots:
  void renderLater();
  void renderNow();

 protected:
  bool event(QEvent *event) override;

  void exposeEvent(QExposeEvent *event) override;

 private:
  bool m_animating = false;

  QOpenGLContext *m_context = nullptr;
  QOpenGLPaintDevice *m_device = nullptr;
};

OpenGLWindow::OpenGLWindow(QWindow *parent) : QWindow(parent) {
  setSurfaceType(QWindow::OpenGLSurface);
}

void OpenGLWindow::render(QPainter *painter) { Q_UNUSED(painter); }

void OpenGLWindow::initialize() {}

void OpenGLWindow::render() {
  if (!m_device) m_device = new QOpenGLPaintDevice;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  m_device->setSize(size() * devicePixelRatio());
  m_device->setDevicePixelRatio(devicePixelRatio());

  QPainter painter(m_device);
  render(&painter);
}

void OpenGLWindow::renderLater() { requestUpdate(); }

bool OpenGLWindow::event(QEvent *event) {
  switch (event->type()) {
    case QEvent::UpdateRequest:
      renderNow();
      return true;
    default:
      return QWindow::event(event);
  }
}

void OpenGLWindow::exposeEvent(QExposeEvent *event) {
  Q_UNUSED(event);

  if (isExposed()) renderNow();
}

void OpenGLWindow::renderNow() {
  if (!isExposed()) return;

  bool needsInitialize = false;

  if (!m_context) {
    m_context = new QOpenGLContext(this);
    m_context->setFormat(requestedFormat());
    m_context->create();

    needsInitialize = true;
  }

  m_context->makeCurrent(this);

  if (needsInitialize) {
    initializeOpenGLFunctions();
    initialize();
  }

  render();

  m_context->swapBuffers(this);

  if (m_animating) renderLater();
}

void OpenGLWindow::setAnimating(bool animating) {
  m_animating = animating;

  if (animating) renderLater();
}

class ExampleWindow : public OpenGLWindow {
 public:
  using OpenGLWindow::OpenGLWindow;

  void initialize() override {
    s21::shaders::ShaderProgramBuilder builder;
    shader = builder.AddVertexShaderFromFile("./shaders/base_vertex.glsl")
                 .AddFragmentShaderFromFile("./shaders/base_fragment.glsl")
                 .Build();
    obj = new s21::Object(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f),
                          "../models/cube.obj");

    glClearColor(0.2, 0.2, 0.2, 1);
    glEnable(GL_DEPTH_TEST);
  }

  void render() override {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width(), height());

    view = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 0.0f, -5.0f));

    auto w = static_cast<float>(width());
    auto h = static_cast<float>(height());
    std::cerr << w << " " << h << std::endl;
    float aspect = w / h;
    if (perspective) {
      projection = glm::perspective(glm::radians(90.f), aspect, 0.1f, 10000.f);
    } else {
      projection = glm::ortho(-aspect, aspect, -1.f, 1.f, 0.1f, 10000.f);
    }

    shader.Use();
    shader.UniformMatrix4fv("view", view);
    shader.UniformMatrix4fv("projection", projection);
    shader.UniformMatrix4fv("transform", transform);
    obj->Draw();
    ++m_frame;
  }

 private:
  GLint m_posAttr = 0;
  GLint m_colAttr = 0;
  GLint m_matrixUniform = 0;

  int m_frame = 0;

  s21::shaders::ShaderProgram shader;
  s21::Object *obj{nullptr};

  glm::mat4 translate{1.f};
  glm::mat4 scale{1.f};
  glm::mat4 rotate{1.f};

  float kScale{1.0f};
  int perspective = 1;
  glm::mat4 view{1.f};
  glm::mat4 projection{1.f};
  glm::mat4 transform{1.f};
};

int main(int argc, char *argv[]) {
  QApplication application(argc, argv);

  QSurfaceFormat format;
  format.setDepthBufferSize(16);
  format.setSamples(16);

  ExampleWindow window;
  window.setFormat(format);
  window.resize(640, 480);
  window.show();

  return application.exec();
}