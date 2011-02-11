// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#ifndef ITKDATAIMAGEPLUGIN_H
#define ITKDATAIMAGEPLUGIN_H

#include <dtkCore/dtkPlugin.h>

#include "itkDataImagePluginExport.h"

class itkDataImagePluginPrivate;

class ITKDATAIMAGEPLUGIN_EXPORT itkDataImagePlugin : public dtkPlugin
{
    Q_OBJECT
    Q_INTERFACES(dtkPlugin)

public:
     itkDataImagePlugin(QObject *parent = 0);
    ~itkDataImagePlugin(void);

    virtual bool initialize(void);
    virtual bool uninitialize(void);

    virtual QString name(void) const;
    virtual QString description(void) const;

    virtual QStringList tags(void) const;
    virtual QStringList types(void) const;

private:
    itkDataImagePluginPrivate *d;
};

#endif
