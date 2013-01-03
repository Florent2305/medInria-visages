// /////////////////////////////////////////////////////////////////
// Generated by medPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "animaPyramidalBMRegistration.h"
#include "animaPyramidalBMRegistrationPlugin.h"
#include "animaPyramidalBMRegistrationToolBox.h"

#include <dtkLog/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// animaPyramidalBMRegistrationPluginPrivate
// /////////////////////////////////////////////////////////////////

class animaPyramidalBMRegistrationPluginPrivate
{
public:
    // Class variables go here.
    static const char *s_Name;
};

const char * animaPyramidalBMRegistrationPluginPrivate::s_Name = "animaPyramidalBMRegistration";

// /////////////////////////////////////////////////////////////////
// animaPyramidalBMRegistrationPlugin
// /////////////////////////////////////////////////////////////////

animaPyramidalBMRegistrationPlugin::animaPyramidalBMRegistrationPlugin(QObject *parent) : dtkPlugin(parent), d(new animaPyramidalBMRegistrationPluginPrivate)
{
    
}

animaPyramidalBMRegistrationPlugin::~animaPyramidalBMRegistrationPlugin(void)
{
    delete d;
    
    d = NULL;
}

bool animaPyramidalBMRegistrationPlugin::initialize(void)
{
    if(!animaPyramidalBMRegistration::registered())
    {
        dtkWarn() << "Unable to register animaPyramidalBMRegistration type";
    }
    
    if(!animaPyramidalBMRegistrationToolBox::registered())
    {
        dtkWarn() << "Unable to register animaPyramidalBMRegistration toolbox";
    }
    
    return true;
}

bool animaPyramidalBMRegistrationPlugin::uninitialize(void)
{
    return true;
}

QString animaPyramidalBMRegistrationPlugin::name(void) const
{
    return "animaPyramidalBMRegistrationPlugin";
}

QString animaPyramidalBMRegistrationPlugin::description(void) const
{
    return tr("");
}

QString animaPyramidalBMRegistrationPlugin::version(void) const
{
    return ANIMAPYRAMIDALBMREGISTRATIONPLUGIN_VERSION;
}

QString animaPyramidalBMRegistrationPlugin::contact(void) const
{
    return "";
}

QStringList animaPyramidalBMRegistrationPlugin::authors(void) const
{
    QStringList list;
    return list;
}

QStringList animaPyramidalBMRegistrationPlugin::contributors(void) const
{
    QStringList list;
    return list;
}

QString animaPyramidalBMRegistrationPlugin::identifier(void) const
{
    return animaPyramidalBMRegistrationPluginPrivate::s_Name;
}


QStringList animaPyramidalBMRegistrationPlugin::tags(void) const
{
    return QStringList();
}

QStringList animaPyramidalBMRegistrationPlugin::types(void) const
{
    return QStringList() << "animaPyramidalBMRegistration";
}
QStringList animaPyramidalBMRegistrationPlugin::dependencies(void) const
{
    return QStringList();
}

Q_EXPORT_PLUGIN2(animaPyramidalBMRegistrationPlugin, animaPyramidalBMRegistrationPlugin)
