#ifndef _itk_DataImageChar3_h_
#define _itk_DataImageChar3_h_

#include <dtkCore/dtkAbstractDataImage.h>
#include <dtkCore/dtkGlobal.h>

#include "itkDataImagePluginExport.h"

class itkDataImageChar3Private;

class ITKDATAIMAGEPLUGIN_EXPORT itkDataImageChar3 : public dtkAbstractDataImage
{
  Q_OBJECT
    
 public:
    itkDataImageChar3(void);
    ~itkDataImageChar3(void);
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

    itkDataImageChar3Private* d;
  
};

dtkAbstractData* createItkDataImageChar3 (void);

#endif