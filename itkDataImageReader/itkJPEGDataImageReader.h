#ifndef ITKJPEGDATAIMAGEREADER_H
#define ITKJPEGDATAIMAGEREADER_H

#include "itkDataImageReaderBase.h"

#include "itkDataImageReaderPluginExport.h"

class ITKDATAIMAGEREADERPLUGIN_EXPORT itkJPEGDataImageReader : public itkDataImageReaderBase
{
    Q_OBJECT
	
public:
    itkJPEGDataImageReader(void);
    virtual ~itkJPEGDataImageReader(void);
	
    virtual QString description(void) const;
	
    static bool registered(void);	
};

dtkAbstractDataReader *createItkJPEGDataImageReader(void);

#endif