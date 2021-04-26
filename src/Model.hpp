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
	static void init(const std::string& fileName);

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

	/** Load from file specified during model init. Creates file if not already existing. */
	void load();

	/** Save to file specified during model init. Creates file if not already existing. */
	void save() const;

private:
	Model(const std::string& fileName);
	~Model();

	void loadDefault();
	void toJson(nlohmann::json& json) const;
	void fromJson(const nlohmann::json& json);

	static Model * model_;

	std::string fileName_;

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
