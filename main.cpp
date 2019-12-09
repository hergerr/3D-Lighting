#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <iostream>

typedef float point3[3];

using namespace std;


int getRand(int a, int b)
{
    return a + rand() % (b - a);
}

struct Point
{
    float x, y, z;
    int a, b, c;
};

const int N = 21;
vector<vector<Point>> points;

void resizeVectors()
{
    points.resize(N);
    for (int i = 0; i < N; i++)
    {
        points[i].resize(N);
    }
}

float calcX(float u, float v)
{
    return (-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u) * cos(M_PI * v);
}

float calcY(float u, float v)
{
    return 160 * pow(u, 4) - 320 * pow(u, 3) + 160 * pow(u, 2) - 5;
}

float calcZ(float u, float v)
{
    return (-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u) * sin(M_PI * v);
}

void calculatePoints()
{

    float u, v;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            u = float(i) / (N - 1);
            v = float(j) / (N - 1);

            points[i][j].x = calcX(u, v);
            points[i][j].y = calcY(u, v);
            points[i][j].z = calcZ(u, v);

            points[i][j].a = getRand(0, 255);
            points[i][j].b = getRand(0, 255);
            points[i][j].c = getRand(0, 255);
        }
    }
}

void printTriangles()
{
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - 1; j++)
        {
            if (points[i][j].z > 0)
            {
                glBegin(GL_TRIANGLES);

                glColor3ub(points[i][j].a, points[i][j].b, points[i][j].c);
                glVertex3f(points[i][j].x, points[i][j].y, points[i][j].z);

                glColor3ub(points[i][j + 1].a, points[i][j + 1].b, points[i][j + 1].c);
                glVertex3f(points[i][j + 1].x, points[i][j + 1].y, points[i][j + 1].z);

                glColor3ub(points[i + 1][j].a, points[i + 1][j].b, points[i + 1][j].c);
                glVertex3f(points[i + 1][j].x, points[i + 1][j].y, points[i + 1][j].z);

                glEnd();

                glBegin(GL_TRIANGLES);

                glColor3ub(points[i + 1][j].a, points[i + 1][j].b, points[i + 1][j].c);
                glVertex3f(points[i + 1][j].x, points[i + 1][j].y, points[i + 1][j].z);

                glColor3ub(points[i + 1][j + 1].a, points[i + 1][j + 1].b, points[i + 1][j + 1].c);
                glVertex3f(points[i + 1][j + 1].x, points[i + 1][j + 1].y, points[i + 1][j + 1].z);

                glColor3ub(points[i][j + 1].a, points[i][j + 1].b, points[i][j + 1].c);
                glVertex3f(points[i][j + 1].x, points[i][j + 1].y, points[i][j + 1].z);

                glEnd();
            }
            else
            {
                glBegin(GL_TRIANGLES);

                glColor3ub(points[i][j].a, points[i][j].b, points[i][j].c);
                glVertex3f(points[i][j].x, points[i][j].y, points[i][j].z);

                glColor3ub(points[i][j + 1].a, points[i][j + 1].b, points[i][j + 1].c);
                glVertex3f(points[i][j + 1].x, points[i][j + 1].y, points[i][j + 1].z);

                glColor3ub(points[i + 1][j].a, points[i + 1][j].b, points[i + 1][j].c);
                glVertex3f(points[i + 1][j].x, points[i + 1][j].y, points[i + 1][j].z);

                glEnd();

                glBegin(GL_TRIANGLES);

                glColor3ub(points[i + 1][j].a, points[i + 1][j].b, points[i + 1][j].c);
                glVertex3f(points[i + 1][j].x, points[i + 1][j].y, points[i + 1][j].z);

                glColor3ub(points[i + 1][j + 1].a, points[i + 1][j + 1].b, points[i + 1][j + 1].c);
                glVertex3f(points[i + 1][j + 1].x, points[i + 1][j + 1].y, points[i + 1][j + 1].z);

                glColor3ub(points[i][j + 1].a, points[i][j + 1].b, points[i][j + 1].c);
                glVertex3f(points[i][j + 1].x, points[i][j + 1].y, points[i][j + 1].z);

                glEnd();
            }
        }
    }
}

void Egg()
{
    printTriangles();
}

// ----------------KONIEC WKLEJKI-------------------------

static GLfloat viewer[] = {3.0, 3.0, 10.0};

float up = 0.0;
float side = 0.0;
float r = 10.0;
bool mode = true;

static GLfloat theta = 0.0; // kąt obrotu obiektu
static GLfloat alfa = 0.0;  // kąt obrotu obiektu
static GLfloat pix2angle;   // przelicznik pikseli na stopnie

static GLint status = 0; // stan klawiszy myszy
                         // 0 - nie naciśnięto żadnego klawisza
                         // 1 - naciśnięty zostać lewy klawisz

static int x_pos_old = 0; // poprzednia pozycja kursora myszy
static int y_pos_old = 0;

static int delta_x = 0; // różnica pomiędzy pozycją bieżącą
                        // i poprzednią kursora myszy

static int delta_y = 0;

void Mouse(int btn, int state, int x, int y)
{

    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        x_pos_old = x; // przypisanie aktualnie odczytanej pozycji kursora
                       // jako pozycji poprzedniej
        y_pos_old = y;
        status = 1; // wcięnięty został lewy klawisz myszy
    }
    else

        status = 0; // nie został wcięnięty żaden klawisz
}

void Motion(GLsizei x, GLsizei y)
{

    delta_x = x - x_pos_old; // obliczenie różnicy położenia kursora myszy
    delta_y = y - y_pos_old;

    x_pos_old = x; // podstawienie bieżącego położenia jako poprzednie
    y_pos_old = y;
    glutPostRedisplay(); // przerysowanie obrazu sceny
}

void Axes(void)
{

    point3 x_min = {-5.0, 0.0, 0.0};
    point3 x_max = {5.0, 0.0, 0.0};

    point3 y_min = {0.0, -5.0, 0.0};
    point3 y_max = {0.0, 5.0, 0.0};

    point3 z_min = {0.0, 0.0, -5.0};
    point3 z_max = {0.0, 0.0, 5.0};
    glColor3f(1.0f, 0.0f, 0.0f); // kolor rysowania osi - czerwony
    glBegin(GL_LINES);           // rysowanie osi x
    glVertex3fv(x_min);
    glVertex3fv(x_max);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f); // kolor rysowania - zielony
    glBegin(GL_LINES);           // rysowanie osi y

    glVertex3fv(y_min);
    glVertex3fv(y_max);
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f); // kolor rysowania - niebieski
    glBegin(GL_LINES);           // rysowanie osi z

    glVertex3fv(z_min);
    glVertex3fv(z_max);
    glEnd();
}

// Funkcja określająca co ma być rysowane (zawsze wywoływana, gdy trzeba przerysować scenę)
void RenderScene(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Zdefiniowanie położenia obserwatora

    // Narysowanie osi przy pomocy funkcji zdefiniowanej powyżej

    if (status == 1) // jeśli lewy klawisz myszy wcięnięty
    {
        theta += delta_x * pix2angle; // modyfikacja kąta obrotu o kat proporcjonalny
        alfa += delta_y * pix2angle;
    }
    if (mode)
    {
        Axes();
        gluLookAt(r * cos(2 * M_PI * side) * cos(2 * M_PI * up), r * sin(2 * M_PI * up), r * sin(2 * M_PI * side) * cos(2 * M_PI * up), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    }
    else
    {
        Axes();
        gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glRotatef(theta, 0.0, 1.0, 0.0); //obrót obiektu o nowy kąt
        glRotatef(alfa, 1.0, 0.0, 0.0);
        // glScalef(1.0 + status, 1.0, 1.0);
    }

    glColor3f(1.0f, 1.0f, 1.0f);

    Egg();
    // glutSolidTeapot(3.0);
    glFlush();
    glutSwapBuffers();
}

void keys(unsigned char key, int x, int y)
{
    if (key == 'z')
        up += 0.01;
    if (key == 'x')
        side += 0.01;
    if (key == 'v')
        r--;
    if (key == 'm')
        mode = !mode;
    if (key == 'c')
    {
        r++;
        if (r >= 25.0)
        {
            r = 10.0;
        }
    }

    RenderScene(); // przerysowanie obrazu sceny
}

void MyInit(void)
{
    resizeVectors();
    calculatePoints();

    GLfloat mat_ambient[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess = {20.0};
    GLfloat light_position[] = {0.0, 0.0, 10.0, 1.0};
    GLfloat light_ambient[] = {0.1, 0.0, 0.0, 1.0};
    GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};
    GLfloat light_specular[] = {1.0, 0.0, 0.0, 1.0};
    GLfloat att_constant = {1.0};
    GLfloat att_linear = {0.05};
    GLfloat att_quadratic = {0.001};

    GLfloat light1_position[] = {0.0, 0.0, -10.0, 1.0}; 
    GLfloat light1_ambient[] = {0.1, 0.0, 0.1, 1.0};
    GLfloat light1_diffuse[] = {0.0, 0.0, 1.0, 1.0};
    GLfloat light1_specular[] = {0.0, 0.0, 1.0, 1.0};

    // Ustawienie patrametrów materiału
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

    // Ustawienie parametrów źródła
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic);

    // Ustawienie parametrów źródła
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, att_constant);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, att_linear);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, att_quadratic);

    // Ustawienie opcji systemu oświetlania sceny
    glShadeModel(GL_SMOOTH); // właczenie łagodnego cieniowania
    glEnable(GL_LIGHTING);   // właczenie systemu oświetlenia sceny
    glEnable(GL_LIGHT0);     // włączenie źródła o numerze 0
    glEnable(GL_LIGHT1);     // włączenie źródła o numerze 0
    glEnable(GL_DEPTH_TEST); // włączenie mechanizmu z-bufora
}

void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
    pix2angle = 360.0 / (float)horizontal; // przeliczenie pikseli na stopnie
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Ustawienie parametrów dla rzutu perspektywicznego
    gluPerspective(70, 1.0, 1.0, 30.0);

    if (horizontal <= vertical)
        glViewport(0, (vertical - horizontal) / 2, horizontal, horizontal);

    else
        glViewport((horizontal - vertical) / 2, 0, vertical, vertical);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char *argv[])
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(300, 300);
    glutInit(&argc, argv);
    glutCreateWindow("Rzutowanie perspektywiczne");
    glutKeyboardFunc(keys);
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutMouseFunc(Mouse);
    // Ustala funkcję zwrotną odpowiedzialną za badanie stanu myszy

    glutMotionFunc(Motion);
    // Ustala funkcję zwrotną odpowiedzialną za badanie ruchu myszy
    MyInit();
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();

    return 0;
}