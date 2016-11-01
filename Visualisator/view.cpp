#include "view.h"
View* view;



View::View(Network *network)
{

    //engine.initEngine();
    visualisator = new Visualisator(network);

    timer.singleShot(visualisator->STEP,this,SLOT(stepTimer()));

    setMouseTracking(true);

    VIRTUAL_HEIGHT = 900;
    VIRTUAL_WIDTH = 1250;
    ASPECT_RATIO = VIRTUAL_WIDTH/VIRTUAL_HEIGHT;
}


void View::stepTimer()
{
    //engine.step();

    this->update();
    timer.singleShot(visualisator->STEP,this,SLOT(stepTimer()));
    //timer.singleShot(1,this,SLOT(stepTimer()));
}



void View::mouseMoveEvent(QMouseEvent* mouseEvent) {
    //visualisator.mousePosOnScreen = QPointF(mouseEvent->pos().x()/scale, mouseEvent->pos().y()/scale);
    //visualisator.mousePos = screen->position+engine.mousePosOnScreen;
}

void View::mousePressEvent(QMouseEvent *mouseEvent)
{
    //engine.humanControl->onMousePress(mouseEvent);

}

void View::keyPressEvent(QKeyEvent * event) {
    //engine.humanControl->onKeyPress(event);


}

void View::keyReleaseEvent(QKeyEvent * event) {
    //engine.humanControl->onKeyRelease(event);

}


void View::initializeGL() {
    //Задаем цвет фона в OpenGL окне
    glClearColor(1,0.9,0.7,0);

    glMatrixMode( GL_PROJECTION );

    glOrtho( 0, 1250, 900, 0, 1.0, -1.0 );


    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();           // загружает единичную матрицу моделирования

    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    visualisator->init();
    //spriteBase.directionSprite = 0;
}

void View::resizeGL(int inWidth, int inHeight)
{
    // Set Viewport to window dimensions
    // calculate new viewport
    aspectRatio = (float)inWidth/(float)inHeight;
    scale = 1;
    float cropX;
    float cropY;

    if(aspectRatio > ASPECT_RATIO)
    {
        scale = (float)inHeight/(float)VIRTUAL_HEIGHT;
        cropX = (inWidth - VIRTUAL_WIDTH*scale)/2;
    }
    else if(aspectRatio < ASPECT_RATIO)
    {
        scale = (float)inWidth/(float)VIRTUAL_WIDTH;
        cropY = (inHeight - VIRTUAL_HEIGHT*scale)/2;
    }
    else
    {
        scale = (float)inWidth/(float)VIRTUAL_WIDTH;
    }

    float w = (float)VIRTUAL_WIDTH*scale;
    float h = (float)VIRTUAL_HEIGHT*scale;
    //viewport = new Rectangle(crop.x, crop.y, w, h);
    glViewport( 0, 0, w, h );
}

void View::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT );

    glColor3f(0,0.4,0);
    glPushMatrix();
    glTranslate(QPointF(100,50));
    //(0,0,0,"test LOL", QFont("verdana"));
    glPopMatrix();
    glColor3f(1,1,1);

    visualisator->draw();
}
