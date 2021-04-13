#include "BSplineCurve.hpp"
#include "Drawing.hpp"
#include "Model.hpp"
#include "Point.hpp"
#include "Transform.hpp"

#include <iostream>
#include <math.h>
#include <stdlib.h>

#include <GL/glut.h>

void changeWindowSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void)
{
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	Point camera = Model::instance()->getCameraPoint();
	Point at = Model::instance()->getAtPoint();
	Vector up = Model::instance()->getUpVector();
	// Set the camera
	gluLookAt(camera.x, camera.y, camera.z,
	          at.x, at.y, at.z,
	          up.x, up.y, up.z);

	// Draw Ground Wireframe
	for(float i = -100.0; i <= 100.0; i += 10.0)
	{
		Line xline = {Point(-100.0, 0.0, i, 1.0), Point(100.0, 0.0, i, 1.0)};
		Line zline = {Point(i, 0.0, -100.0, 1.0), Point(i, 0.0, 100.0, 1.0)};
		drawLine(xline, {0.1, 0.1, 0.1}, 0.5);
		drawLine(zline, {0.1, 0.1, 0.1}, 0.5);
	}

	NurbsSurface* surface = Model::instance()->getSurface();
	drawNurbs(*surface, {1.0, 0.0, 1.0}, 1.0, 20);

	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int xx, int yy)
{
	NurbsSurface* surface = Model::instance()->getSurface();
	if(key == 27) // Escape.
		exit(0);
	else if(key == 9) // Tab.
	{
		if(Model::instance()->knotMode() == "uknots")
		{
			surface->incrementKnotIndex();
			surface->printUKnots();
		}
		else if(Model::instance()->knotMode() == "vknots")
		{
			surface->incrementKnotIndex();
			surface->printVKnots();
		}
		else
			surface->toggleMode();
	}
	else if(key == 'w')
	{
		Point* p = surface->getPoint();
		p->w += 1.0;
		std::cout << "weight: " << p->w << std::endl;
	}
	else if(key == 'W')
	{
		Point* p = surface->getPoint();
		p->w -= 1.0;
		std::cout << "weight: " << p->w << std::endl;
	}
	else if(key == 'i')
	{
		if(surface->getMode() == NurbsSurface::ROW)
			surface->insertRow(true);
		else if(surface->getMode() == NurbsSurface::COLUMN)
			surface->insertColumn(true);
	}
	else if(key == 'I')
	{
		if(surface->getMode() == NurbsSurface::ROW)
			surface->insertRow(false);
		else if(surface->getMode() == NurbsSurface::COLUMN)
			surface->insertColumn(false);
	}
	else if(key == 'd')
	{
		if(surface->getMode() == NurbsSurface::ROW)
			surface->deleteRow();
		else if(surface->getMode() == NurbsSurface::COLUMN)
			surface->deleteColumn();
	}
	else if(key == 'o')
	{
		if(surface->getMode() == NurbsSurface::ROW)
		{
			if(surface->getVOrder() <= surface->getPoints()[0].size() - 1)
				surface->setVOrder(surface->getVOrder() + 1);
			std::cout << "vOrder: " << surface->getVOrder() << std::endl;
		}
		else if(surface->getMode() == NurbsSurface::COLUMN)
		{
			if(surface->getUOrder() <= surface->getPoints().size() - 1)
				surface->setUOrder(surface->getUOrder() + 1);
			std::cout << "uOrder: " << surface->getUOrder() << std::endl;
		}
	}
	else if(key == 'O')
	{
		if(surface->getMode() == NurbsSurface::ROW)
		{
			if(surface->getVOrder() >= 3)
				surface->setVOrder(surface->getVOrder() - 1);
			std::cout << "vOrder: " << surface->getVOrder() << std::endl;
		}
		else if(surface->getMode() == NurbsSurface::COLUMN)
		{
			if(surface->getUOrder() >= 3)
				surface->setUOrder(surface->getUOrder() - 1);
			std::cout << "uOrder: " << surface->getUOrder() << std::endl;
		}
	}
	else if(key == 'k')
	{
		if(Model::instance()->knotMode() == "none")
		{
			Model::instance()->knotMode() = "uknots";
			Model::instance()->getSurface()->printUKnots();
		}
		else
		{
			Model::instance()->knotMode() = "none";
			std::cout << "knot mode ended" << std::endl;
		}
	}
	else if(key == 'K')
	{
		if(Model::instance()->knotMode() != "vknots")
		{
			Model::instance()->knotMode() = "vknots";
			Model::instance()->getSurface()->printVKnots();
		}
	}
}

void pressKey(int key, int xx, int yy)
{
	NurbsSurface* surface = Model::instance()->getSurface();
	int mod = glutGetModifiers();
	if(mod & GLUT_ACTIVE_CTRL) // Ctrl is pressed.
	{
		NurbsSurface::Index index = Model::instance()->getSurface()->getIndexSelected();

		if(key == GLUT_KEY_UP)
			index.i++;
		else if(key == GLUT_KEY_DOWN)
			index.i--;
		else if(key == GLUT_KEY_RIGHT)
			index.j++;
		else if(key == GLUT_KEY_LEFT)
			index.j--;

		Model::instance()->getSurface()->setIndexSelected(index);
	}
	else // Ctrl is not pressed.
	{
		std::vector<Point*> points = Model::instance()->getMovablePoints();

		if(key == GLUT_KEY_UP)
			for(auto it = points.begin(); it != points.end(); ++it)
				(*it)->x += 0.1;
		else if(key == GLUT_KEY_DOWN)
			for(auto it = points.begin(); it != points.end(); ++it)
				(*it)->x -= 0.1;
		else if(key == GLUT_KEY_RIGHT)
		{
			float* knot = surface->getMovableKnot();
			if(Model::instance()->knotMode() == "none")
			{
				for(auto it = points.begin(); it != points.end(); ++it)
					(*it)->z += 0.1;
			}
			else if(Model::instance()->knotMode() == "uknots")
			{
				if(*knot <= surface->getUpperKnot() - 1)
					(*knot)++;
				surface->printUKnots();
			}
			else if(Model::instance()->knotMode() == "vknots")
			{
				if(*knot <= surface->getUpperKnot() - 1)
					(*knot)++;
				surface->printVKnots();
			}
		}
		else if(key == GLUT_KEY_LEFT)
		{
			float * knot = surface->getMovableKnot();
			if(Model::instance()->knotMode() == "none")
			{
				for(auto it = points.begin(); it != points.end(); ++it)
					(*it)->z -= 0.1;
			}
			else if(Model::instance()->knotMode() == "uknots")
			{
				if(*knot >= surface->getLowerKnot() + 1)
					(*knot)--;
				surface->printUKnots();
			}
			else if(Model::instance()->knotMode() == "vknots")
			{
				if(*knot >= surface->getLowerKnot() + 1)
					(*knot)--;
				surface->printVKnots();
			}
		}
		else if(key == GLUT_KEY_PAGE_UP)
			for(auto it = points.begin(); it != points.end(); ++it)
				(*it)->y += 0.1;
		else if(key == GLUT_KEY_PAGE_DOWN)
			for(auto it = points.begin(); it != points.end(); ++it)
				(*it)->y -= 0.1;
	}
}

void mouseMove(int x, int y)
{
	Model::instance()->handleMouseMove(x, y);
}

void mouseButton(int button, int state, int x, int y)
{
	Model::instance()->handleMouseClick(button, state, x, y);
}

int main(int argc, char **argv)
{
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("NURBS - ECS178 Project 4");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeWindowSize);
	glutIdleFunc(renderScene);

	// Register mouse and keyboard callbacks
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(6.0);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
