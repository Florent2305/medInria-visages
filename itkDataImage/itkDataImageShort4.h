#ifndef _itk_DataImageShort4_h_
#define _itk_DataImageShort4_h_

#include <dtkCore/dtkAbstractDataImage.h>
#include <dtkCore/dtkGlobal.h>

#include "itkDataImagePluginExport.h"




class itkDataImageShort4Private;

class ITKDATAIMAGEPLUGIN_EXPORT itkDataImageShort4 : public dtkAbstractDataImage
{
  Q_OBJECT
    
 public:
    itkDataImageShort4(void);
    ~itkDataImageShort4(void);
    virtual QString description(void) const;
    static bool registered(void);

    virtual QImage        &thumbnail(void)   const;
    virtual QList<QImage> &thumbnails (void) const;

 public slots:
    // derived from dtkAbstractData
    
    void *output(void);
    void *data(void);
    void setData(void* data);
    void update(void);

 public:
    // derived from dtkAbstractDataImage

    int xDimension(void);
    int yDimension(void);
    int zDimension(void);

    int minRangeValue(void);
    int maxRangeValue(void);

    int scalarValueCount(int value);
    int scalarValueMinCount(void);
    int scalarValueMaxCount(void);
    
 private:

    itkDataImageShort4Private* d;
  
};

dtkAbstractData* createItkDataImageShort4 (void);

#endif