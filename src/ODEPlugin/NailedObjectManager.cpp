/*!
  @file
  @author 
*/

#include "NailedObjectManager.h"
#include <cnoid/NailDriver>

#include <cnoid/Device>
#include <cnoid/EigenUtil>

#include <cnoid/ValueTree>

#include "gettext.h"

#include <cnoid/MessageView>
#include <boost/format.hpp>

#include <iostream>

using namespace cnoid;
using namespace std;

NailedObject::~NailedObject()
{
    MessageView::instance()->putln("NailDriver: *** joint destroy ***");
    cout << "NailDriver: *** joint destroy  **" << endl;
    dJointSetFeedback(jointID, 0);
    dJointDestroy(jointID);
}

bool NailedObject::isLimited()
{
    dJointFeedback* fb = dJointGetFeedback(jointID);

    Vector3 f(fb->f1);
    double fasteningForce = n_.dot(f);

    // check fastening force
    if (fasteningForce > maxFasteningForce) {
        MessageView::instance()->putln(boost::format("FasteningForce limit exceeded: %f > %f") % fasteningForce % maxFasteningForce);
        cout << boost::format("FasteningForce limit exceeded: %f > %f") % fasteningForce % maxFasteningForce << endl;
        return true;
    }
    return false;
}


NailedObjectManager* NailedObjectManager::getInstance()
{
    static NailedObjectManager instance;
    return &instance;
}

/*
 */
NailedObjectManager::NailedObjectManager()
{
}

/*
 */
NailedObjectManager::~NailedObjectManager()
{
}

void NailedObjectManager::clear()
{
//TODO
}

void NailedObjectManager::addObject(NailedObjectPtr obj)
{
    objectMap.insert(make_pair(obj->getBodyID(), obj));
}

bool NailedObjectManager::find(dBodyID bodyID)
{
    NailedObjectMap::iterator p = objectMap.find(bodyID);
    if (p != objectMap.end()){
	return true;
    } else {
	return false;
    }
}

NailedObjectPtr NailedObjectManager::get(dBodyID bodyID)
{
    NailedObjectMap::iterator p = objectMap.find(bodyID);
    if (p != objectMap.end()){
        return p->second;
    }

    return 0;
}
