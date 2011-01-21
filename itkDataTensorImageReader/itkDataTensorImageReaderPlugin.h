// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#ifndef ITKDATATENSORIMAGEREADERPLUGIN_H
#define ITKDATATENSORIMAGEREADERPLUGIN_H

#include <dtkCore/dtkPlugin.h>

#include "itkDataTensorImageReaderPluginExport.h"

class ITKDATATENSORIMAGEREADERPLUGIN_EXPORT itkDataTensorImageReaderPluginPrivate;

class ITKDATATENSORIMAGEREADERPLUGIN_EXPORT itkDataTensorImageReaderPlugin : public dtkPlugin
{
    Q_OBJECT
    Q_INTERFACES(dtkPlugin)

public:
     itkDataTensorImageReaderPlugin(QObject *parent = 0);
    ~itkDataTensorImageReaderPlugin(void);

    virtual bool initialize(void);
    virtual bool uninitialize(void);

    virtual QString name(void) const;
    virtual QString description(void) const;

    virtual QStringList tags(void) const;
    virtual QStringList types(void) const;

private:
     itkDataTensorImageReaderPluginPrivate *d;
};

#endif