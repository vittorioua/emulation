#include <emulator.h>
#include <QGLWidget>
#include <math.h>

#include <QtOpenGL>
#include <glut.h>
#include <QTimer>
#include <qdebug.h>
#include <place.h>
#include <flight.h>
#include <sstream>

const GLfloat PI180 = M_PI / 180;

int Emulator::flightCounter = 1;

Emulator::Emulator(QWidget *parent): QGLWidget(parent)
{
    glparams = new GLParams(1, 0, 0, 0, -90, 0, 0);
    earth = new Earth(0.6f, 40, 40);
    plane = new Plane(0.04f, Qt::blue);

    //flights.append(new Flight(plane, new Place(1.8, 0.7), new Place(4, 1)));

    for (int i = 0; i < 20; i++) {
        flights.append(new Flight(plane,
                                  new Place(randomFloat(0, M_PI * 2), randomFloat(0, M_PI * 2)),
                                  new Place(randomFloat(0, M_PI * 2), randomFloat(0, M_PI * 2)),
                                  rand() % 1000 +500,flightCounter));
        flightCounter++;

    }
    emit sendFlightData("$FD$ "+QString::number(flights[0]->getFrom().getAngleHor())+
                        ","+QString::number(flights[0]->getFrom().getAngleVer())+
                        " "+QString::number(flights[0]->getTo().getAngleHor())+
                        ","+QString::number(flights[0]->getTo().getAngleHor())+
                        " "+QString::number(flights[0]->getFlightNumber())+
                        " "+QString::number(flights[0]->getTimeFlight()));
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));

    //connect(this,SIGNAL(sendFlightData(QString)),this,SLOT(slotSendToServer(QString)));
    timer->start(30);
}

Emulator::~Emulator() {
    makeCurrent();
    glDeleteTextures(1, textureID);
}

float Emulator::randomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void Emulator::genTextures() {
   QImage image;
   image.load("world_map.jpg");
   //image.load("earth_physical.jpg");

   image = QGLWidget::convertToGLFormat(image);
   glGenTextures(1, textureID);
   glBindTexture(GL_TEXTURE_2D, textureID[0]);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)image.width(), (GLsizei)image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

void Emulator::initializeGL() {
    qglClearColor(Qt::black);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    genTextures();
    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Emulator::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(glparams->getNSca(), glparams->getNSca(), glparams->getNSca());
    glTranslatef(glparams->getXTra(), glparams->getYTra(), glparams->getZTra());
    glRotatef(glparams->getXRot(), 1.0f, 0.0f, 0.0f);
    glRotatef(glparams->getYRot(), 0.0f, 1.0f, 0.0f);
    glRotatef(glparams->getZRot(), 0.0f, 0.0f, 1.0f);

    glEnable(GL_TEXTURE_2D);

    earth->draw();

    glDisable(GL_TEXTURE_2D);

    qglColor(plane->getColor());
    for (int i = 0; i < flights.size(); i++) {
        flights[i]->draw(glparams);

    }

}

void Emulator::resizeGL(int nWidth, int nHeight) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat ratio = (GLfloat)nHeight / (GLfloat)nWidth;
    if (nWidth >= nHeight)
       glOrtho(-1.0/ratio, 1.0/ratio, -1.0, 1.0, -10.0, 10.0);
    else
       glOrtho(-1.0, 1.0, -1.0*ratio, 1.0*ratio, -10.0, 10.0);
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}

void Emulator::mousePressEvent(QMouseEvent* e) {
    ptrMousePosition = e->pos();
}

void Emulator::mouseMoveEvent(QMouseEvent* e) {
    GLfloat xTra = glparams->getXTra();
    GLfloat yTra = glparams->getYTra();
    if (e->buttons() & Qt::MiddleButton) {
        xTra += (GLfloat)(e->pos().x() - ptrMousePosition.x()) / (GLfloat)400;
        yTra -= (GLfloat)(e->pos().y() - ptrMousePosition.y()) / (GLfloat)400;
    }
    glparams->setXTra(xTra);
    glparams->setYTra(yTra);
    GLfloat xRot = glparams->getXRot();
    GLfloat zRot = glparams->getZRot();
    if (e->buttons() & Qt::LeftButton) {
        GLfloat t = xRot + 180 /*/ nSca*/ * (GLfloat)(e->y() - ptrMousePosition.y()) / height();
        xRot = t;
        zRot += 180 /*/ nSca*/ * (GLfloat)(e->x() - ptrMousePosition.x()) / width();
    }
    glparams->setXRot(xRot);
    glparams->setZRot(zRot);
    ptrMousePosition = e->pos();
    updateGL();
}

void Emulator::wheelEvent(QWheelEvent *e) {
    GLfloat nSca = glparams->getNSca();
    e->delta() > 0 ? nSca *= 1.1f : nSca /= 1.1f;
    glparams->setNSca(nSca);
    updateGL();
}

void Emulator::change() {
    updateGL();
}

void Emulator::getFlightData(int flightNumber, Place from, Place to, int timeFlight)
{
    //QMessageBox::critical(0,"Emulator","getflightdata",QMessageBox::Ok);
    std::stringstream sFrom, sTo;
    sFrom<<from.getAngleHor()<<" "<<from.getAngleVer();
    sTo<<to.getAngleHor()<<" "<<to.getAngleVer();
    //emit sendFlightData(flightNumber, sFrom.str().c_str(), sTo.str().c_str(), timeFlight);*/
    std::stringstream sRes;
    sRes<<"FD - "<<flightNumber<<" "<<sFrom.str().c_str()<<": "<<sFrom.str().c_str()<<" "<<timeFlight;
    emit sendFlightData(sRes.str().c_str());
}

void Emulator::start() {
    for (int i = 0; i < flights.size(); i++) {
        flights[i]->start();
    }
}

   /* connect(&timer, SIGNAL(timeout()),this,SLOT(updateGL()));
    timer.start(16);
    earth = new Earth(0.6f, 40, 40);
}

Emulator::~Emulator()
{

}


void Emulator::paintGL()
{
  /*  qDebug()<<"1\n";
    float xRotated = 90.0, yRotated = 0.0, zRotated = 0.0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   // glRotatef(0.5,0,1,0);

    //glutSolidSphere(0.6,36,2);
    glMatrixMode   (GL_MODELVIEW);
    glClear        (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();
    glRotatef(0.5,0,1,0);
    glTranslatef(0.0, 0.0, -15.0);
    drawEarth(0);
    glTranslatef(0.0, 0.0, -15.0);
    drawSatellite(0);




}

void Emulator::initializeGL()
{
    glClearColor(0.2,0.2,0.2,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
}

void Emulator::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h,0.01,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5, 0,0,0, 0,1,0);
}

void Emulator::drawEarth(double rotate=0)
{

    glColor3f (0.8, 0.2, 0.1);              // Red ball displaced to left.
    glPushMatrix ();
       glTranslatef    (-1.5, 0.0, 0.0);
       glRotatef       (60.0, 1,0,0);
       glRotatef       (0.5, 0,1,0);   // Red ball rotates at twice the rate of blue ball.
       glutSolidSphere (2.0, 20, 2/*50*//*);
    glPopMatrix ();
}

void Emulator::drawSatellite(double rotate=0)
{

    glColor3f (0.1, 0.2, 0.8);              // Blue ball displaced to right.
    glPushMatrix ();
       glTranslatef    (2.5, 0.0, 0.0);
       glRotatef       (60.0, 1,0,0);
       glRotatef       (0.5, 1,0,0);
       glutSolidSphere (0.2, 20,  2/*50);
    glPopMatrix ();

}


Earth::Earth(GLfloat x, GLfloat y, GLfloat z,
      GLfloat radius, GLfloat numHSlices, GLfloat numVSlices) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->radius = radius;
    this->numHSlices = numHSlices;
    this->numVSlices = numVSlices;
}

Earth::Earth(GLfloat radius, GLfloat numHSlices, GLfloat numVSlices) {
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->radius = radius;
    this->numHSlices = numHSlices;
    this->numVSlices = numVSlices;
}

void Earth::draw() {
    glBegin(GL_QUADS);
    for (int i = 0; i < numVSlices; i++) {
        for (int j = 0; j < numHSlices; j++) {
            glTexCoord2f(1.0f * j / numHSlices, 1.0f - 1.0f * i / numVSlices);
            glVertex3f(x + radius * qCos(M_PI * j * 2 / numHSlices) * qSin(M_PI * i / numVSlices),
                       y + radius * qSin(M_PI * j * 2 / numHSlices) * qSin(M_PI * i / numVSlices),
                       z + radius * qCos(M_PI * i / numVSlices));
            glTexCoord2f(1.0f * (j + 1) / numHSlices, 1.0f - 1.0f * i / numVSlices);
            glVertex3f(x + radius * qCos(M_PI * (j + 1) * 2 / numHSlices) * qSin(M_PI * i / numVSlices),
                       y + radius * qSin(M_PI * (j + 1) * 2 / numHSlices) * qSin(M_PI * i / numVSlices),
                       z + radius * qCos(M_PI * i / numVSlices));
            glTexCoord2f(1.0f * (j + 1) / numHSlices, 1.0f - 1.0f * (i + 1) / numVSlices);
            glVertex3f(x + radius * qCos(M_PI * (j + 1) * 2 / numHSlices) * qSin(M_PI * (i + 1) / numVSlices),
                       y + radius * qSin(M_PI * (j + 1) * 2 / numHSlices) * qSin(M_PI * (i + 1) / numVSlices),
                       z + radius * qCos(M_PI * (i + 1) / numVSlices));
            glTexCoord2f(1.0f * j / numHSlices, 1.0f - 1.0f * (i + 1) / numVSlices);
            glVertex3f(x + radius * qCos(M_PI * j * 2 / numHSlices) * qSin(M_PI * (i + 1) / numVSlices),
                       y + radius * qSin(M_PI * j * 2 / numHSlices) * qSin(M_PI * (i + 1) / numVSlices),
                       z + radius * qCos(M_PI * (i + 1) / numVSlices));
        }
    }
    glEnd();
}
*/
