// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#ifndef VISTALPROCESSSEGMENTATION_H
#define VISTALPROCESSSEGMENTATION_H

#include <dtkCore/dtkAbstractProcess.h>

#include "vistalProcessSegmentationSTREMPluginExport.h"
#include "Image3D.hh"

class vistalProcessSegmentationSTREMPrivate;
class medAbstractData;

/**
* @class vistalProcessSegmentation
* @brief Image segmentation based on the GraphCuts method
* @TODO Input/Output type conversions
* @TODO Only use method setInput
**/

class VISTALPROCESSSEGMENTATIONSTREMPLUGIN_EXPORT vistalProcessSegmentationSTREM : public dtkAbstractProcess
{
    Q_OBJECT

public:
             vistalProcessSegmentationSTREM(void);
    virtual ~vistalProcessSegmentationSTREM(void);

    virtual QString description(void) const;

    static bool registered(void);

public slots:

    void setInputImage(medAbstractData *data, int channel);

    void setParameter(double  data, int channel);

    int update(void);

    dtkAbstractData *output(void);

private:
    vistalProcessSegmentationSTREMPrivate *d;
};

dtkAbstractProcess *createVistalProcessSegmentationSTREM(void);

#endif
