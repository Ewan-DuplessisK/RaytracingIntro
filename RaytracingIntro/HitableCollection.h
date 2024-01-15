#pragma once
#include "Hitable.h"
#include <memory>
#include <vector>

class HitableCollection : public Hitable
{
private:
	std::vector<std::shared_ptr<Hitable>> mPool;
public:

	HitableCollection() = default;
	HitableCollection(std::shared_ptr<Hitable> hittable) { Add(hittable); }

	void Clear() { mPool.clear(); }
	void Add(std::shared_ptr<Hitable> hittable) { mPool.push_back(hittable); }

	bool Hit(const Ray& rRay, Interval rayTime, HitInfo& hitInfo) const override;
};
