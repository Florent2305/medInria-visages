// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#ifndef QTDCMDATASOURCEPLUGIN_H
#define QTDCMDATASOURCEPLUGIN_H

#include <dtkCore/dtkPlugin.h>

#include "qtdcmDataSourcePluginExport.h"

class QTDCMDATASOURCEPLUGIN_EXPORT qtdcmDataSourcePluginPrivate;

class QTDCMDATASOURCEPLUGIN_EXPORT qtdcmDataSourcePlugin : public dtkPlugin
{
    Q_OBJECT
    Q_INTERFACES(dtkPlugin)

public:
     qtdcmDataSourcePlugin(QObject *parent = 0);
    ~qtdcmDataSourcePlugin(void);

    virtual bool initialize(void);
    virtual bool uninitialize(void);

    virtual QString name(void) const;
    virtual QString description(void) const;

    virtual QStringList tags(void) const;
    virtual QStringList types(void) const;

private:
     qtdcmDataSourcePluginPrivate *d;
};

#endif
