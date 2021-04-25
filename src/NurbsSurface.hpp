#ifndef NURBSSURFACE_HPP_
#define NURBSSURFACE_HPP_

#include <vector>

#include <nlohmann/json.hpp>

#include "Point.hpp"

class NurbsSurface
{
public:
	struct Index
	{
		int i;
		int j;
	};

	enum Mode { POINT, ROW, COLUMN, ALL };

	NurbsSurface();
	NurbsSurface(const std::vector<std::vector<Point> >& points);
	NurbsSurface(
		const std::vector<std::vector<Point> >& points,
		const std::vector<float>& uKnots,
		const std::vector<float>& vKnots,
		int uOrder,
		int vOrder
	);
	std::vector<std::vector<Point> > getPoints() const;
	Point* getPoint();

	Index getIndexSelected() const;
	void setIndexSelected(const Index& index);

	std::vector<float> getUKnots() const;
	void setUKnots(const std::vector<float>& knots);
	std::vector<float> getVKnots() const;
	void setVKnots(const std::vector<float>& knots);

	void insertRow(bool after = true);
	void insertColumn(bool after = true);
	void deleteRow();
	void deleteColumn();

	float* getMovableKnot();
	float getUpperKnot() const;
	float getLowerKnot() const;

	void incrementKnotIndex();

	int getUOrder() const;
	void setUOrder(int order);
	int getVOrder() const;
	void setVOrder(int order);

	Mode getMode() const;
	void setMode(Mode mode);

	float uMin() const;
	float uMax() const;
	float vMin() const;
	float vMax() const;

	void defaultUKnots();
	void defaultVKnots();

	void printUKnots() const;
	void printVKnots() const;

	std::vector<Point*> getMovablePoints();

	void toggleMode();
	void setSelectedKnotIndex(int index);
	int getSelectedKnotIndex() const;

	void toJson(nlohmann::json& json) const;
	void fromJson(const nlohmann::json& json);

private:
	int selectedKnotIndex;
	std::vector<std::vector<Point> > points_;
	std::vector<float> uKnots_;
	std::vector<float> vKnots_;
	int uOrder_;
	int vOrder_;
	Index selected_;
	Mode mode_;
};

void to_json(nlohmann::json& json, const NurbsSurface& nurbs);
void from_json(const nlohmann::json& json, NurbsSurface& nurbs);
void to_json(nlohmann::json& json, const NurbsSurface::Index& nurbs);
void from_json(const nlohmann::json& json, NurbsSurface::Index& nurbs);

#endif
