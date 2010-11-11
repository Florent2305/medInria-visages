// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#ifndef DCMTKDATABASEPACSPLUGIN_H
#define DCMTKDATABASEPACSPLUGIN_H

#include <dtkCore/dtkPlugin.h>

#include "dcmtkDatabasePacsPluginExport.h"

class DCMTKDATABASEPACSPLUGIN_EXPORTS dcmtkDatabasePacsPluginPrivate;

class DCMTKDATABASEPACSPLUGIN_EXPORTS dcmtkDatabasePacsPlugin : public dtkPlugin
{
    Q_OBJECT
    Q_INTERFACES(dtkPlugin)

public:
     dcmtkDatabasePacsPlugin(QObject *parent = 0);
    ~dcmtkDatabasePacsPlugin(void);

    virtual bool initialize(void);
    virtual bool uninitialize(void);

    virtual QString name(void) const;
    virtual QString description(void) const;

    virtual QStringList tags(void) const;
    virtual QStringList types(void) const;

private:
     dcmtkDatabasePacsPluginPrivate *d;
};

#endif