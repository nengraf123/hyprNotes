#include <GLFW/glfw3.h>
#include "texture.h"
#include <iostream>
#include <string>
#include <cmath>

#define c std::cout
#define f std::flush;

void Init () {
  if (!glfwInit()) {
    std::cerr << "Не удалось инициализировать GLFW\n";
  }
  glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE); // говорим что есть АЛЬФА канал
  glfwWindowHintString(GLFW_WAYLAND_APP_ID, "float"); // даем ему класс
}

void Close (GLFWwindow* win) {
  glfwDestroyWindow(win); // убиваем
  glfwTerminate(); // умираем
}

void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height); // каждый раз выставляем вьюпорт под актуальный размер
}


int main() {
  Init();

  GLFWwindow* window = glfwCreateWindow(300, 300, "app", nullptr, nullptr);
  if (!window) {std::cerr << "Не удалось создать окно\n"; glfwTerminate(); return -1;}

  glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

  glEnable(GL_BLEND);
  glEnable(GL_TEXTURE_2D); // добавить рядом с glEnable(GL_BLEND)
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // включаем прозрачность для фигур

  GLuint TextureBlik = loadTexture("/home/graf/Downloads/vecteezy_white-glass-transparent-frame_11015858.png");

  while (!glfwWindowShouldClose(window)) {
      glClearColor(0.3f, 0.0f, 0.3f, 0.1f); glClear(GL_COLOR_BUFFER_BIT);


      glBindTexture(GL_TEXTURE_2D, TextureBlik);
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
      glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, -1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( 1.0f, -1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( 1.0f,  1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f,  1.0f);
      glEnd();


      glfwSwapBuffers(window);
      glfwPollEvents();
  }

  Close(window);
  return 0;
}
