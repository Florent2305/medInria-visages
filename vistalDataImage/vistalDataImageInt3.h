// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#ifndef VISTALDATAIMAGEINT3_H
#define VISTALDATAIMAGEINT3_H

#include <dtkCore/dtkAbstractDataImage.h>

#include "vistalDataImagePluginExport.h"

class vistalDataImageInt3Private;

class VISTALDATAIMAGEPLUGIN_EXPORT vistalDataImageInt3 : public dtkAbstractDataImage
{
    Q_OBJECT

public:
             vistalDataImageInt3(void);
    virtual ~vistalDataImageInt3(void);

    virtual QString description(void) const;

    static bool registered(void);
	
		virtual QImage &thumbnail(void)   const;
		virtual QList<QImage> &thumbnails (void) const;
	
public slots:
    // derived from dtkAbstractData

    void *output(void);
    void *data(void);
    void setData(void* data);

 public:
    int xDimension(void);
    int yDimension(void);
    int zDimension(void);
    int tDimension(void);

	int minRangeValue(void);
	int maxRangeValue(void);
	
private:
    vistalDataImageInt3Private *d;
};

dtkAbstractData *createVistalDataImageInt3(void);

#endif
