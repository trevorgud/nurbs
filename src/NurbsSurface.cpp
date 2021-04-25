#include "NurbsSurface.hpp"

#include "Model.hpp"

#include <iostream>
#include <stdexcept>

NurbsSurface::NurbsSurface()
{}

NurbsSurface::NurbsSurface(const std::vector<std::vector<Point> >& points)
	: points_(points), uOrder_(3), vOrder_(3), mode_(NurbsSurface::POINT)
{
	defaultUKnots();
	defaultVKnots();

		selected_.i = 0;
		selected_.j = 0;
		selectedKnotIndex = 0;
}

NurbsSurface::NurbsSurface(
	const std::vector<std::vector<Point> >& points,
	const std::vector<float>& uKnots,
	const std::vector<float>& vKnots,
	int uOrder,
	int vOrder
)
	: points_(points),
		uKnots_(uKnots),
		vKnots_(vKnots),
		uOrder_(uOrder),
		vOrder_(vOrder),
		mode_(NurbsSurface::POINT),
		selectedKnotIndex(0)
{}

float* NurbsSurface::getMovableKnot()
{
	if(Model::instance()->knotMode() == "uknots" && selectedKnotIndex >= 0 && selectedKnotIndex < uKnots_.size())
		return &(uKnots_[selectedKnotIndex]);
	else if(Model::instance()->knotMode() == "vknots" && selectedKnotIndex >= 0 && selectedKnotIndex < vKnots_.size())
		return &(vKnots_[selectedKnotIndex]);
	else
		return nullptr;
}

float NurbsSurface::getUpperKnot() const
{
	if(Model::instance()->knotMode() == "uknots" && selectedKnotIndex >= 0 && selectedKnotIndex < uKnots_.size())
	{
		if(selectedKnotIndex == uKnots_.size() - 1)
			return 100000.0;
		else
			return uKnots_[selectedKnotIndex + 1];
	}
	else if(Model::instance()->knotMode() == "vknots" && selectedKnotIndex >= 0 && selectedKnotIndex < vKnots_.size())
	{
		if(selectedKnotIndex == vKnots_.size() - 1)
			return 100000.0;
		else
			return vKnots_[selectedKnotIndex + 1];
	}
	else
		throw std::runtime_error("NurbsSurface: Invalid internal state. Model knot mode or knot indexes invalid.");
}

float NurbsSurface::getLowerKnot() const
{
	if(Model::instance()->knotMode() == "uknots" && selectedKnotIndex >= 0 && selectedKnotIndex < uKnots_.size())
	{
		if(selectedKnotIndex == 0)
			return -100000.0;
		else
			return uKnots_[selectedKnotIndex - 1];
	}
	else if(Model::instance()->knotMode() == "vknots" && selectedKnotIndex >= 0 && selectedKnotIndex < vKnots_.size())
	{
		if(selectedKnotIndex == 0)
			return -100000.0;
		else
			return vKnots_[selectedKnotIndex - 1];
	}
	else
		throw std::runtime_error("NurbsSurface: Invalid internal state. Model knot mode or knot indexes invalid.");
}

void NurbsSurface::setSelectedKnotIndex(int index)
{
	if(Model::instance()->knotMode() == "uknots" && index >= 0 && uKnots_.size() < index)
		selectedKnotIndex = index;
	else if(Model::instance()->knotMode() == "vknots" && index >= 0 && vKnots_.size() < index)
		selectedKnotIndex = index;
}

int NurbsSurface::getSelectedKnotIndex() const
{
	return selectedKnotIndex;
}

void NurbsSurface::incrementKnotIndex()
{
	if(Model::instance()->knotMode() == "uknots" && selectedKnotIndex >= 0 && selectedKnotIndex < uKnots_.size() - 1)
		selectedKnotIndex++;
	else if(Model::instance()->knotMode() == "uknots")
		selectedKnotIndex = 0;
	else if(Model::instance()->knotMode() == "vknots" && selectedKnotIndex >= 0 && selectedKnotIndex < vKnots_.size() - 1)
		selectedKnotIndex++;
	else if(Model::instance()->knotMode() == "vknots")
		selectedKnotIndex = 0;
}

void NurbsSurface::defaultUKnots()
{
	uKnots_.clear();
	for(int i = 0; i < points_.size() + uOrder_; i++)
				uKnots_.push_back((float) i);
}

void NurbsSurface::defaultVKnots()
{
	vKnots_.clear();
	for(int j = 0; j < points_[0].size() + vOrder_; j++)
			vKnots_.push_back((float) j);
}

std::vector<std::vector<Point> > NurbsSurface::getPoints() const
{
	return points_;
}

Point* NurbsSurface::getPoint()
{
	return &(points_[selected_.i][selected_.j]);
}

NurbsSurface::Index NurbsSurface::getIndexSelected() const
{
	return selected_;
}

void NurbsSurface::setIndexSelected(const NurbsSurface::Index& index)
{
	if(index.i < points_.size())
	{
		if(index.j < points_[index.i].size())
			selected_ = index;
	}
}

std::vector<float> NurbsSurface::getUKnots() const
{
	return uKnots_;
}

void NurbsSurface::setUKnots(const std::vector<float>& knots)
{
	uKnots_ = knots;
}

std::vector<float> NurbsSurface::getVKnots() const
{
	return vKnots_;
}

void NurbsSurface::setVKnots(const std::vector<float>& knots)
{
	vKnots_ = knots;
}

int NurbsSurface::getUOrder() const
{
	return uOrder_;
}

void NurbsSurface::setUOrder(int order)
{
	uOrder_ = order;
}

int NurbsSurface::getVOrder() const
{
	return vOrder_;
}

void NurbsSurface::setVOrder(int order)
{
	vOrder_ = order;
}

void NurbsSurface::insertRow(bool after)
{
	if(mode_ != ROW)
		return;

	std::vector<Point> row = points_[selected_.i];
	if(after)
		points_.insert(points_.begin() + selected_.i + 1, row);
	else
		points_.insert(points_.begin() + selected_.i, row);

	defaultUKnots();
}

void NurbsSurface::insertColumn(bool after)
{
	if(mode_ != COLUMN)
		return;

	for(auto it = points_.begin(); it != points_.end(); ++it)
	{
		Point p = (*it)[selected_.j];
		if(after)
			it->insert(it->begin() + selected_.j + 1, p);
		else
			it->insert(it->begin() + selected_.j, p);
	}

	defaultVKnots();
}

void NurbsSurface::deleteRow()
{
	if(mode_ != ROW)
		return;

	points_.erase(points_.begin() + selected_.i);

	defaultUKnots();
}

void NurbsSurface::deleteColumn()
{
	if(mode_ != COLUMN)
		return;

	for(auto it = points_.begin(); it != points_.end(); ++it)
		it->erase(it->begin() + selected_.j);

	defaultVKnots();
}

NurbsSurface::Mode NurbsSurface::getMode() const
{
	return mode_;
}

void NurbsSurface::setMode(NurbsSurface::Mode mode)
{
	mode_ = mode;
}

float NurbsSurface::uMin() const
{
	if(uKnots_.size() > uOrder_ - 1)
		return uKnots_[(uKnots_.size() - 1) - (uOrder_ - 1)];
	else
		return 0.0;
}

float NurbsSurface::uMax() const
{
	if(uKnots_.size() > uOrder_ - 1)
		return uKnots_[uOrder_ - 1];
	else
		return 0.0;
}

float NurbsSurface::vMin() const
{
	if(vKnots_.size() > vOrder_ - 1)
		return vKnots_[(vKnots_.size() - 1) - (vOrder_ - 1)];
	else
		return 0.0;
}

float NurbsSurface::vMax() const
{
	if(vKnots_.size() > vOrder_ - 1)
		return vKnots_[vOrder_ - 1];
	else
		return 0.0;
}

void NurbsSurface::printUKnots() const
{
	std::cout << "uknots:";
	int i = 0;
	for(auto it = uKnots_.begin(); it != uKnots_.end() && (it + 1) != uKnots_.end(); ++it)
	{
		if(i == selectedKnotIndex)
			std::cout << "*";
		std::cout << *it;
		int dist = (int)((*(it + 1)) - (*it));
		for(int i = 0; i < dist; i++)
			std::cout << " ";
		i++;
	}
	if(i == selectedKnotIndex)
		std::cout << "*";
	std::cout << uKnots_.back() << std::endl;
}

void NurbsSurface::printVKnots() const
{
	std::cout << "vknots:";
	int i = 0;
	for(auto it = vKnots_.begin(); it != vKnots_.end() && (it + 1) != vKnots_.end(); ++it)
	{
		if(i == selectedKnotIndex)
			std::cout << "*";
		std::cout << *it;
		int dist = (int)((*(it + 1)) - (*it));
		for(int i = 0; i < dist; i++)
			std::cout << " ";
		i++;
	}
	if(i == selectedKnotIndex)
		std::cout << "*";
	std::cout << vKnots_.back() << std::endl;
}

std::vector<Point*> NurbsSurface::getMovablePoints()
{
	std::vector<Point*> points;

	if(mode_ == NurbsSurface::POINT)
		points.push_back(&points_[selected_.i][selected_.j]);
	else if(mode_ == NurbsSurface::ROW)
	{
		for(auto it = points_[selected_.i].begin(); it != points_[selected_.i].end(); ++it)
			points.push_back(&(*it));
	}
	else if(mode_ == NurbsSurface::COLUMN)
	{
		for(auto it = points_.begin(); it != points_.end(); ++it)
			points.push_back(&((*it)[selected_.j]));
	}
	else if(mode_ == NurbsSurface::ALL)
	{
		for(auto row = points_.begin(); row != points_.end(); ++row)
			for(auto point = row->begin(); point != row->end(); ++point)
				points.push_back(&(*point));
	}

	return points;
}

void NurbsSurface::toggleMode()
{
	if(mode_ == POINT)
		mode_ = ROW;
	else if(mode_ == ROW)
		mode_ = COLUMN;
	else if(mode_ == COLUMN)
		mode_ = ALL;
	else if(mode_ == ALL)
		mode_ = POINT;
}

void NurbsSurface::toJson(nlohmann::json& json) const
{
	json = nlohmann::json {
		{"selectedKnotIndex", selectedKnotIndex},
		{"points", points_},
		{"uKnots", uKnots_},
		{"vKnots", vKnots_},
		{"uOrder", uOrder_},
		{"vOrder", vOrder_},
		{"selected", selected_},
		{"mode", mode_}
	};
}

void NurbsSurface::fromJson(const nlohmann::json& json)
{
	json.at("selectedKnotIndex").get_to(selectedKnotIndex);
	json.at("points").get_to(points_);
	json.at("uKnots").get_to(uKnots_);
	json.at("vKnots").get_to(vKnots_);
	json.at("uOrder").get_to(uOrder_);
	json.at("vOrder").get_to(vOrder_);
	json.at("selected").get_to(selected_);
	json.at("mode").get_to(mode_);
}

void to_json(nlohmann::json& json, const NurbsSurface::Index& index)
{
	json = nlohmann::json {
		{"i", index.i},
		{"j", index.j}
	};
}

void from_json(const nlohmann::json& json, NurbsSurface::Index& index)
{
	json.at("i").get_to(index.i);
	json.at("j").get_to(index.j);
}

void to_json(nlohmann::json& json, const NurbsSurface& nurbs) { nurbs.toJson(json); }

void from_json(const nlohmann::json& json, NurbsSurface& nurbs) { nurbs.fromJson(json); }
