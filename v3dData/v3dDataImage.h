// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#ifndef V3DDATAIMAGE_H
#define V3DDATAIMAGE_H

#include <dtkCore/dtkAbstractData.h>

#include "v3dDataPluginExport.h"

class v3dDataImagePrivate;

class V3DDATAPLUGIN_EXPORT v3dDataImage : public dtkAbstractData
{
    Q_OBJECT

public:
             v3dDataImage(void);
    virtual ~v3dDataImage(void);

    virtual QString description(void) const;

    static bool registered(void);

public:
    bool read(QString file);
    bool write(QString file);

    void *data(void);

    void setData(void *data);

private:
    v3dDataImagePrivate *d;
};

dtkAbstractData *createV3dDataImage(void);

#endif