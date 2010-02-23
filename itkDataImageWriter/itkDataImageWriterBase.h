#ifndef ITKDATAIMAGEWRITERBASE_H
#define ITKDATAIMAGEWRITERBASE_H

#include <dtkCore/dtkAbstractDataWriter.h>

#include "itkDataImageWriterPluginExport.h"
#include "itkImageIOBase.h"

class ITKDATAIMAGEWRITERPLUGIN_EXPORT itkDataImageWriterBase : public dtkAbstractDataWriter
{
    Q_OBJECT

public:
             itkDataImageWriterBase(void);
    virtual ~itkDataImageWriterBase(void);

    virtual QStringList handled(void) const;
    static  QStringList s_handled (void);
    
public slots:
    bool write    (QString path);
    bool canWrite (QString path);

 protected:
    itk::ImageIOBase::Pointer io;
    
};

#endif