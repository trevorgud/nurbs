#ifndef MODEL_HPP_
#define MODEL_HPP_

#include "NurbsSurface.hpp"
#include "Point.hpp"

#include <string>

// Camera viewing model for observing geometry in 3d space.
class Model
{
public:
	// Implements the singleton design pattern. Only one static Model instance will be defined.
	static Model* instance();

	Point getCameraPoint() const;
	void setCameraPoint(const Point& cameraPoint);
	Point getAtPoint() const;
	void setAtPoint(const Point& atPoint);
	Vector getUpVector() const;
	void handleMouseClick(int button, int state, int x, int y);
	void handleMouseScroll(int button, int state);
	void handleMouseMove(int x, int y);

	int getIndexSelected() const;
	void setIndexSelected(int index);

	NurbsSurface* getSurface();
	std::vector<Point*> getMovablePoints();

	void toggleKnotEditMode();
	bool knotEditMode() const;
	std::string knotMode() const;

private:

	Model();
	static Model * model_;

	bool ctrlPressed;

	Point cameraPoint_;
	Point atPoint_;
	Point2d click_;

	float uResolution_;
	float vResolution_;

	std::vector<NurbsSurface> surfaces_;
	int selectedSurface_;

	bool knotEditMode_;
	std::string knotMode_;
};

#endif
