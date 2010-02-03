#ifndef ITKMETADATAIMAGEREADER_H
#define ITKMETADATAIMAGEREADER_H

#include "itkDataImageReaderBase.h"

#include "itkDataImageReaderPluginExport.h"

class ITKDATAIMAGEREADERPLUGIN_EXPORT itkMetaDataImageReader : public itkDataImageReaderBase
{
    Q_OBJECT
	
public:
	itkMetaDataImageReader(void);
    virtual ~itkMetaDataImageReader(void);
	
    virtual QString description(void) const;
	
    virtual QStringList handled(void) const;
    static bool registered(void);	
};

dtkAbstractDataReader *createItkMetaDataImageReader(void);

#endif