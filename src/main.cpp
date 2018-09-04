#include <iostream>

#include "utils.h"
#include "graphics.h"
#include "world.h"
#include "controls.h"

// This is just an example using basic glut functionality.
// If you want specific Apple functionality, look up AGL

double last_update;
double last_check;
unsigned int frames_passed;

gm_engine::Entity player(
    gm_engine::Cube(
        {100.0, 0.0, 100.0},
        {20.0, 40.0, 20.0}
    ),
    {0.7, 0.7, 0.7},
    {0.0, 0.0, 0.0},
    10.0,
    false,
    10.0
);
gm_engine::Entity cube(
    gm_engine::Cube(
        {-100.0, 0.0, 100.0},
        {20.0, 30.0, 20.0}
    ),
    {0.4, 0.4, 0.7},
    {0.0, 0.0, 0.0},
    1.0,
    false
);
gm_engine::Entity cube2(
    gm_engine::Cube(
        {-200.0, 0.0, 100.0},
        {20.0, 30.0, 20.0}
    ),
    {0.4, 0.4, 0.7},
    {100.0, 0.0, 0.0},
    1.0,
    false
);
gm_engine::Entity cube3(
    gm_engine::Cube(
        {-200.0, -20.0, 200.0},
        {20.0, 40.0, 20.0}
    ),
    {0.4, 0.4, 0.7},
    {50.0, 0.0, 0.0},
    1.0,
    true
);
gm_engine::Entity ground(
    gm_engine::Cube(
        {-200.0, -30.0, 0.0},
        {700.0, 10.0, 700.0}
    ),
    {0.9, 0.9, 0.9},
    {0.0, 0.0, 0.0},
    1.0,
    true,
    0.0
);
gm_engine::World world;
gm_engine::Controller controller;

GLuint texture;

gm_engine::Texture* wood;

void init() // Called before main loop to set up the program
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);

    glEnable(GL_ALPHA_TEST); // This thing discards all transparent pixels
    glAlphaFunc(GL_NOTEQUAL, 0.0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    texture = gm_engine::Image("img/cat.png").load_texture();
    
    last_update = gm_engine::current_timestamp();
    last_check = gm_engine::current_timestamp();
    frames_passed = 0;

    world.add_entity(&player);
    world.add_entity(&cube);
    world.add_entity(&cube2);
    world.add_entity(&cube3);
    world.add_entity(&ground);

    wood = new gm_engine::Texture("img/stone2.png");
    wood->get_in_game_size() = {40.0, 40.0, 0.0};

    ground.used_texture = wood;

    // std::cout << player.get_shape().get_point(gm_engine::Cube::LEFT|gm_engine::Cube::BOTTOM|gm_engine::Cube::NEAR) << "\n";
}

// Called at the start of the program, after a glutPostRedisplay() and during idle
// to display a frame
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glLoadIdentity();

    // glColor3f(1.0f, 1.0f, 1.0f); 
    // glBegin(GL_TRIANGLES);
    //     glVertex3f(0.0, 0.0, -10.0);
    //     glVertex3f(100.0, 0.0, -10.0);
    //     glVertex3f(0.0, 100.0, -10.0);
    // glEnd();

    // glColor3f(0.0f, 1.0f, 1.0f); 
    // glBegin(GL_QUADS);
    //     glVertex3f(25.f, 25.f, -20.0);
    //     glVertex3f(200.0f, 50.0f, -20.0);
    //     glVertex3f(200.0f, 150.0f, -20.0);
    //     glVertex3f(50.0f, 150.0f, -20.0);
    // glEnd();

    // glColor3f(0.3f, 0.5f, 1.0f); 
    // glBegin(GL_QUADS);
    //     glVertex3f(50.f, 50.f, 50.0);
    //     glVertex3f(200.0f, 50.0f, 50.0);
    //     glVertex3f(200.0f, 150.0f, 50.0);
    //     glVertex3f(50.0f, 150.0f, 50.0);
    // glEnd();

    world.render();

    glColor3f(1.0f, 0.0f, 0.0f); 
    glBegin(GL_LINES);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(100.0f, 0.0f, 0.0f);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f); 
    glBegin(GL_LINES);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 100.0f, 0.0f);
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f); 
    glBegin(GL_LINES);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture);
    glEnable(GL_TEXTURE_2D);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); 
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(0.0, 300, 0.0);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(100, 300, 0.0);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(100.0, 0.0, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);


    // glColor4f(0.0f, 1.0f, 1.0f, 0.5f); 
    // glBegin(GL_QUADS);
    //     glVertex3f(0.0, 0.0, -10.0);
    //     glVertex3f(0.0, 300, -10.0);
    //     glVertex3f(100, 300, -10.0);
    //     glVertex3f(100.0, 0.0, -10.0);
    // glEnd();

    
    glutSwapBuffers();
    
    

    ++frames_passed;
    double current_update = gm_engine::current_timestamp();
    if (current_update - last_update > 1000)
    {
        last_update = current_update;
        std::cout << frames_passed << " FPS" << std::endl;
        frames_passed = 0;
    }

    world.process_physic((current_update - last_check) / 1000);

    last_check = current_update;

    glMatrixMode(GL_MODELVIEW);

    gm_engine::Entity* standing_on = player.get_collision_from_left_side().y;
    if (standing_on) {
        // player.get_velocity().x = standing_on->get_velocity().x;
        // player.get_velocity().z = standing_on->get_velocity().z;

        // if (controller.is_key_pressed('w')) {
        //     // glTranslatef(0.0f, 0.0f, -2.0f);
        //     // player.get_shape().move({0.0, 0.0, 2.0});
        //     player.get_velocity().z += 100;
        // }
        // if (controller.is_key_pressed('s')) {
        //     // glTranslatef(0.0f, 0.0f, 2.0f);
        //     // player.get_shape().move({0.0, 0.0, -2.0});
        //     player.get_velocity().z -= 100;
        // }
        // if (controller.is_key_pressed('a')) {
        //     // glTranslatef(2.0f, 0.0f, 0.0f);
        //     // player.get_shape().move({-2.0, 0.0, 0.0});
        //     player.get_velocity().x -= 100;
        // }
        // if (controller.is_key_pressed('d')) {
        //     // glTranslatef(-2.0f, 0.0f, 0.0f);
        //     // player.get_shape().move({2.0, 0.0, 0.0});
        //     player.get_velocity().x += 100;
        // }
        if (controller.is_key_pressed(' ')) {
            player.get_velocity().y += 100;
        }
    }
    player.get_move_velocity().z = player.get_move_velocity().x = 0;
    if (controller.is_key_pressed('w')) {
        player.get_move_velocity().z = 100;
    }
    if (controller.is_key_pressed('s')) {
        player.get_move_velocity().z = -100;
    }
    if (controller.is_key_pressed('a')) {
        player.get_move_velocity().x = -100;
    }
    if (controller.is_key_pressed('d')) {
        player.get_move_velocity().x = 100;
    }
    
    
    // std::cerr << player.get_collision() << "\n";

    if (controller.is_key_pressed('e')) {
        glRotatef(1.0f, 0.0f, 1.0f, 0.0f);
    }
    if (controller.is_key_pressed('q')) {
        glRotatef(-1.0f, 0.0f, 1.0f, 0.0f);
    }
    
}

// Called every time a window is resized to resize the projection matrix
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-float(w)/3, float(w), -float(h)/3, float(h), 1000.0f, -1000.0f);
    GLfloat matrixf[16] = {  // Matrix for our projection
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 1, 1, 0,
        0, 0, 0, 1,
    };
    glMultMatrixf(matrixf);
    
    
    // glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    // glFrustum(-0.1, 0.1, -float(h)/(10.0*float(w)), float(h)/(10.0*float(w)), 0.5, 1000.0);

    // glGetFloatv(GL_PROJECTION_MATRIX, matrixf);
    // for (int i = 0; i < 4; ++i) {
    //     std::cout << matrixf[i * 4] << " "
    //         << matrixf[i * 4 + 1] << " "
    //         << matrixf[i * 4 + 2] << " "
    //         << matrixf[i * 4 + 3] << "\n";
    // }

    // std::cout << "\n";
    // glGetFloatv(GL_MODELVIEW_MATRIX, matrixf);
    // for (int i = 0; i < 4; ++i) {
    //     std::cout << matrixf[i * 4] << " "
    //         << matrixf[i * 4 + 1] << " "
    //         << matrixf[i * 4 + 2] << " "
    //         << matrixf[i * 4 + 3] << "\n";
    // }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyPressed(unsigned char key, int x, int y) {
    controller.move_mouse(x, y);
    controller.press_key(key);
}  

void keyUp(unsigned char key, int x, int y) {
    controller.move_mouse(x, y);
    controller.release_key(key);
} 

int main(int argc, char **argv)
{
    glutInit(&argc, argv); // Initializes glut

    // Sets up a double buffer with RGBA components and a depth component
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);

    // Sets the window size to 512*512 square pixels
    glutInitWindowSize(800, 600);

    // Sets the window position to the upper left
    glutInitWindowPosition(0, 0);

    // Creates a window using internal glut functionality
    glutCreateWindow("Hello!");

    // passes reshape and display functions to the OpenGL machine for callback
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);

    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);

    init();

    // Starts the program.
    glutMainLoop();

    delete wood;
   
    return 0;
}
