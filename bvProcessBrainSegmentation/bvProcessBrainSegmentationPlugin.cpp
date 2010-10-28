// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "bvProcessBrainSegmentation.h"
#include "bvProcessBrainSegmentationPlugin.h"

#include <dtkCore/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// bvProcessBrainSegmentationPluginPrivate
// /////////////////////////////////////////////////////////////////

class bvProcessBrainSegmentationPluginPrivate 
{
public:
    // Class variables go here.
};

// /////////////////////////////////////////////////////////////////
// bvProcessBrainSegmentationPlugin
// /////////////////////////////////////////////////////////////////

bvProcessBrainSegmentationPlugin::bvProcessBrainSegmentationPlugin(QObject *parent) : dtkPlugin(parent), d(new bvProcessBrainSegmentationPluginPrivate)
{

}

bvProcessBrainSegmentationPlugin::~bvProcessBrainSegmentationPlugin(void)
{
    delete d;

    d = NULL;
}

bool bvProcessBrainSegmentationPlugin::initialize(void)
{
    if(!bvProcessBrainSegmentation::registered())
	dtkWarning() << "Unable to register bvProcessBrainSegmentation type";

    return true;
}

bool bvProcessBrainSegmentationPlugin::uninitialize(void)
{
    return true;
}

QString bvProcessBrainSegmentationPlugin::name(void) const
{
    return "bvProcessBrainSegmentationPlugin";
}

QString bvProcessBrainSegmentationPlugin::description(void) const
{
    return "Brainvisa plugin";
}

QStringList bvProcessBrainSegmentationPlugin::tags(void) const
{
    return QStringList() << "brainvisa";
}

QStringList bvProcessBrainSegmentationPlugin::types(void) const
{
    return QStringList() << "bvProcessBrainSegmentation";
}

Q_EXPORT_PLUGIN2(bvProcessBrainSegmentationPlugin, bvProcessBrainSegmentationPlugin)
