/**
   \file
   \author Shizuko Hattori
*/

#ifndef CNOID_ODEPLUGIN__ODE_COLLISION_DETECTOR_H_INCLUDED
#define CNOID_ODEPLUGIN__ODE_COLLISION_DETECTOR_H_INCLUDED

#include <cnoid/CollisionDetector>
#ifdef GAZEBO_ODE
#define ODECollisionDetector GazeboODECollisionDetector
#endif

namespace cnoid {

class ODECollisionDetectorImpl;

class ODECollisionDetector : public CollisionDetector
{
public:
    ODECollisionDetector();
    virtual ~ODECollisionDetector();
    virtual const char* name() const;
    virtual CollisionDetectorPtr clone() const;
    virtual void clearGeometries();
    virtual int numGeometries() const;
    virtual int addGeometry(SgNodePtr geometry);
    virtual void setGeometryStatic(int geometryId, bool isStatic = true);
    virtual bool enableGeometryCache(bool on);
    virtual void clearGeometryCache(SgNodePtr geometry);
    virtual void clearAllGeometryCaches();
    virtual void setNonInterfarenceGeometyrPair(int geometryId1, int geometryId2);
    virtual bool makeReady();
    virtual void updatePosition(int geometryId, const Position& position);
    virtual void detectCollisions(boost::function<void(const CollisionPair&)> callback);

private:
    ODECollisionDetectorImpl* impl;
};

typedef boost::shared_ptr<ODECollisionDetector> ODECollisionDetectorPtr;
}

#endif
