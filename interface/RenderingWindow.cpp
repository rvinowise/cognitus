#include "RenderingWindow.h"

#include <QDebug>
#include <QString>


RenderingWindow::RenderingWindow()
{
    resize(640, 480);
}

RenderingWindow::~RenderingWindow()
{

}


void RenderingWindow::initializeGL()
{
  // Initialize OpenGL Backend
  initializeOpenGLFunctions();
  printContextInformation();

  // Set global information

  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void RenderingWindow::resizeGL(int width, int height)
{
  // Currently we are not handling width/height changes
  (void)width;
  (void)height;
}

void RenderingWindow::paintGL()
{
  // Clear
  glClear(GL_COLOR_BUFFER_BIT);
}



/*******************************************************************************
 * Private Helpers
 ******************************************************************************/

void RenderingWindow::printContextInformation()
{
  QString glType;
  QString glVersion;
  QString glProfile;

  // Get Version Information
  glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
  glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

  // Get Profile Information
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
  switch (format().profile())
  {
    CASE(NoProfile);
    CASE(CoreProfile);
    CASE(CompatibilityProfile);
  }
#undef CASE

  // qPrintable() will print our QString w/o quotes around it.
  qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
}
