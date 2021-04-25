#ifndef MODEL_HPP_
#define MODEL_HPP_

#include <string>

#include <nlohmann/json.hpp>

#include "NurbsSurface.hpp"
#include "Point.hpp"

// Camera viewing model for observing geometry in 3d space.
// TODO: Split this object into a camera view object and nurbs surfaces object.
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

	void toJson(nlohmann::json& json) const;
	void fromJson(const nlohmann::json& json);

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

void to_json(nlohmann::json& json, const Model& model);
void from_json(const nlohmann::json& json, Model& model);

#endif
