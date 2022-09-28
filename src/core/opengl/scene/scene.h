// ! Class is not implemented

#ifndef SRC_ENGINE_SCENE_SCENE_H_
#define SRC_ENGINE_SCENE_SCENE_H_

#include "camera.h"
#include "core/opengl/renderer/renderer.h"
#include "light_source.h"

struct Scene {
  Camera camera;
  Renderer object;
  LightSource sources;
};

#endif // SRC_ENGINE_SCENE_SCENE_H_
