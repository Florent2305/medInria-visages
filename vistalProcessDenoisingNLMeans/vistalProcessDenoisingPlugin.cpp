// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "vistalProcessDenoising.h"
#include "vistalProcessDenoisingPlugin.h"
#include "vistalProcessDenoisingToolBox.h"

#include <vistalProcessDenoisingNLMeansDefinitions.h>

#include <dtkCore/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// vistalProcessDenoisingPluginPrivate
// /////////////////////////////////////////////////////////////////

class vistalProcessDenoisingPluginPrivate 
{
public:
    // Class variables go here.
};

// /////////////////////////////////////////////////////////////////
// vistalProcessDenoisingPlugin
// /////////////////////////////////////////////////////////////////

vistalProcessDenoisingPlugin::vistalProcessDenoisingPlugin(QObject *parent) : dtkPlugin(parent), d(new vistalProcessDenoisingPluginPrivate)
{

}

vistalProcessDenoisingPlugin::~vistalProcessDenoisingPlugin(void)
{
    delete d;

    d = NULL;
}

bool vistalProcessDenoisingPlugin::initialize(void)
{
    if(!vistalProcessDenoising::registered())
	dtkWarning() << "Unable to register vistalProcessDenoising type";
    
    if(!vistalProcessDenoisingToolBox::registered())
	dtkWarning() << "Unable to register vistalProcessDenoising toolbox";

    return true;
}

bool vistalProcessDenoisingPlugin::uninitialize(void)
{
    return true;
}

QString vistalProcessDenoisingPlugin::name(void) const
{
    return "vistalProcessDenoisingNLMEANSPlugin";
}

QString vistalProcessDenoisingPlugin::description(void) const
{
    return "This plugin provides the NL-Means denoising filter as proposed by Coupe et al.: <a href=\"http://dx.doi.org/10.1109/TMI.2007.906087\">http://dx.doi.org/10.1109/TMI.2007.906087</a>. It is also implementing ultrasound image denoising as proposed in <a href=\"http://dx.doi.org/10.1109/TIP.2009.2024064\">http://dx.doi.org/10.1109/TIP.2009.2024064</a>.";
}

QStringList vistalProcessDenoisingPlugin::authors ( void ) const
{
    return QStringList() << "Clement Philipot <Clement.Philipot@inria.fr>";
}

QString vistalProcessDenoisingPlugin::contact ( void ) const
{
    return "Clement Philipot <Clement.Philipot@inria.fr>";
}

QStringList vistalProcessDenoisingPlugin::contributors ( void ) const
{
    return QStringList() << "";
}

QStringList vistalProcessDenoisingPlugin::dependencies ( void ) const
{
    return QStringList() << "VISTAL";
}

QString vistalProcessDenoisingPlugin::version ( void ) const
{
    return PLUGIN_VERSION;
}

QStringList vistalProcessDenoisingPlugin::tags(void) const
{
    return QStringList() << "vistal" << "process" << "nlmeans" << "denoising" << "preprocessing";
}

QStringList vistalProcessDenoisingPlugin::types(void) const
{
    return QStringList() << "vistalProcessDenoising";
}

Q_EXPORT_PLUGIN2(vistalProcessDenoisingPlugin, vistalProcessDenoisingPlugin)
