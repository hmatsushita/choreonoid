/**
   \file
   \author Shin'ichiro Nakaoka
*/

#ifndef CNOID_BODY_ABSTRACT_BODY_LOADER_H
#define CNOID_BODY_ABSTRACT_BODY_LOADER_H

#include <boost/shared_ptr.hpp>
#include <iosfwd>
#include "exportdecl.h"

namespace cnoid {

class Body;

class CNOID_EXPORT AbstractBodyLoader
{
public:
    AbstractBodyLoader();
    virtual ~AbstractBodyLoader();

    /**
       \todo Modify the API for getting the format information so that multipule formats can be
       supported and more detailed information can be obtained.
    */
    virtual const char* format() const = 0;
    
    virtual void setMessageSink(std::ostream& os);
    virtual void setVerbose(bool on);
    virtual void setShapeLoadingEnabled(bool on);
    virtual void setDefaultDivisionNumber(int n);
    virtual void setDefaultCreaseAngle(double theta);
    virtual bool load(Body* body, const std::string& filename) = 0;
};

typedef boost::shared_ptr<AbstractBodyLoader> AbstractBodyLoaderPtr;

}

#endif
