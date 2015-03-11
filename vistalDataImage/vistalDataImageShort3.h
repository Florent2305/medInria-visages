// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#ifndef VISTALDATAIMAGESHORT3_H
#define VISTALDATAIMAGESHORT3_H

#include <medAbstractImageData.h>

#include <vistalDataImagePluginExport.h>

class vistalDataImageShort3Private;

class VISTALDATAIMAGEPLUGIN_EXPORT vistalDataImageShort3 : public medAbstractImageData
{
    Q_OBJECT
    MED_DATA_INTERFACE("Vistal Image (Short3)",
                       "Vistal Image (Short3)")

public:
    vistalDataImageShort3(void);
    virtual ~vistalDataImageShort3(void);

    static bool registered(void);

public slots:
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
    vistalDataImageShort3Private *d;
};


#endif
