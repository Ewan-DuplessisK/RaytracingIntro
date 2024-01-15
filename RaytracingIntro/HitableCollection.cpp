#include "HitableCollection.h"

using namespace std;

bool HitableCollection::Hit(const Ray& rRay, Interval rayTime, HitInfo& hitInfo) const
{
    HitInfo tempInfo;
    bool hasHit = false;
    auto closestHit = rayTime.max;

    for (const shared_ptr<Hitable>& hitable : mPool) {
        if (hitable->Hit(rRay, Interval(rayTime.min, closestHit), tempInfo)) {
            hasHit = true;
            closestHit = tempInfo.time;
            hitInfo = tempInfo;
        }
    }

    return hasHit;
}
