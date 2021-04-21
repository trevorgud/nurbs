#include "Model.hpp"

#include "Line.hpp"
#include "Point.hpp"
#include "Transform.hpp"

#include <GL/glut.h>

#define GLUT_MOUSE_WHEEL_SCROLL_UP 3
#define GLUT_MOUSE_WHEEL_SCROLL_DOWN 4
// How much to zoom camera in/out when scrolling.
#define SCROLL_ZOOM_FACTOR 0.9

Model* Model::model_ = 0;

Model* Model::instance()
{
	if(model_ == nullptr)
		model_ = new Model;
	return model_;
}

Model::Model()
{
	cameraPoint_ = Point(10.0, 2.0, 10.0);
	atPoint_ = Point(0.0, 0.0, 0.0);
	click_.x = -1;
	click_.y = -1;
	ctrlPressed = false;
	std::vector<std::vector<Point> > points =
		{
			{ {-2.0, 0.0, -2.0, 1.0}, {0.0, 0.0, -2.0, 1.0}, {2.0, 0.0, -2.0, 1.0} },
			{ {-2.0, 0.0, 0.0, 1.0}, {0.0, 0.0, 0.0, 1.0}, {2.0, 0.0, 0.0, 1.0} },
			{ {-2.0, 0.0, 2.0, 1.0}, {0.0, 0.0, 2.0, 1.0}, {2.0, 0.0, 2.0, 1.0} },
			{ {-2.0, 0.0, 4.0, 1.0}, {0.0, 0.0, 4.0, 1.0}, {2.0, 0.0, 4.0, 1.0} }
		};
	NurbsSurface surface(points);
	surfaces_.push_back(surface);
	selectedSurface_ = 0;
	knotEditMode_ = false;
	knotMode_ = "none";
}

Point Model::getCameraPoint() const
{
	return cameraPoint_;
}

void Model::setCameraPoint(const Point& cameraPoint)
{
	cameraPoint_ = cameraPoint;
}

Point Model::getAtPoint() const
{
	return atPoint_;
}

void Model::setAtPoint(const Point& atPoint)
{
	atPoint_ = atPoint;
}

Vector Model::getUpVector() const
{
	Vector lookVector = atPoint_ - cameraPoint_;
	Vector sideways = crossProduct(Vector(0.0, 1.0, 0.0), lookVector);
	Vector up = crossProduct(lookVector, sideways);
	return unitVector(up);
}

void Model::toggleKnotEditMode()
{
	if(knotEditMode_)
		knotEditMode_ = false;
	else
		knotEditMode_ = true;
}

bool Model::knotEditMode() const
{
	return knotEditMode_;
}

std::string Model::knotMode() const
{
	return knotMode_;
}

void Model::handleMouseClick(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON)
	{
		if(state == GLUT_UP)
		{
			click_.x = -1.0;
			click_.y = -1.0;
		}
		else
		{
			click_.x = x;
			click_.y = y;
		}
	}
	else if(button == GLUT_MOUSE_WHEEL_SCROLL_UP || button == GLUT_MOUSE_WHEEL_SCROLL_DOWN)
	{
		if(state == GLUT_DOWN)
			handleMouseScroll(button, state);
	}
}

void Model::handleMouseScroll(int button, int state) {
	Vector lookVector = atPoint_ - cameraPoint_;

	if(button == GLUT_MOUSE_WHEEL_SCROLL_UP)
		// Shrink the look vector when scrolling up to zoom in.
		lookVector = lookVector * SCROLL_ZOOM_FACTOR;
	else if(button == GLUT_MOUSE_WHEEL_SCROLL_DOWN)
		// Shrink the look vector when scrolling up to zoom in.
		lookVector = lookVector * (1 / SCROLL_ZOOM_FACTOR);

	cameraPoint_ = atPoint_ - lookVector;
}

void Model::handleMouseMove(int x, int y)
{
	if(click_.x >= 0 && click_.y >= 0)
	{
		float dx = x - click_.x;
		float dy = y - click_.y;

		Vector lookVector = atPoint_ - cameraPoint_;
		Vector sideways = crossProduct(Vector(0.0, 1.0, 0.0), lookVector);

		// Handle verticle rotation.
		cameraPoint_ = rotate(cameraPoint_, Line(atPoint_, atPoint_ + sideways), dy);

		// Handle horizontal rotation.
		cameraPoint_ = rotate(cameraPoint_, Line(atPoint_, atPoint_ + Vector(0.0, 1.0, 0.0)), -dx);

		click_.x = x;
		click_.y = y;
	}
}

int Model::getIndexSelected() const
{
	return selectedSurface_;
}
void Model::setIndexSelected(int index)
{
	if(index >= 0 && index < surfaces_.size())
		selectedSurface_ = index;
}

NurbsSurface* Model::getSurface()
{
	if(selectedSurface_ >= 0 && selectedSurface_ < surfaces_.size())
		return &(surfaces_[selectedSurface_]);
	else
		return nullptr;
}

std::vector<Point*> Model::getMovablePoints()
{
	return getSurface()->getMovablePoints();
}
