// /////////////////////////////////////////////////////////////////
// Generated by medPluginGenerator
// /////////////////////////////////////////////////////////////////

#ifndef ANIMANONLOCALMEANSFILTERTOOLBOX_H
#define ANIMANONLOCALMEANSFILTERTOOLBOX_H

#include <medToolBoxFilteringCustom.h>
#include "animaNonLocalMeansFilterPluginExport.h"

class animaNonLocalMeansFilterToolBoxPrivate;

class ANIMANONLOCALMEANSFILTERPLUGIN_EXPORT animaNonLocalMeansFilterToolBox : public medToolBoxFilteringCustom
{
    Q_OBJECT

public:
    animaNonLocalMeansFilterToolBox(QWidget *parent = 0);
    ~animaNonLocalMeansFilterToolBox(void);

    dtkAbstractData *processOutput();

    static bool registered(void);

signals:
    void success(void);
    void failure(void);

    public slots:
    void run(void);
    void update(dtkAbstractView *view);

private:
    animaNonLocalMeansFilterToolBoxPrivate *d;
};

#endif
