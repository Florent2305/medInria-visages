
#ifndef VISTALPROCESSDENOISINGTOOLBOX_H
#define VISTALPROCESSDENOISINGTOOLBOX_H

#include <medGui/toolboxes/medToolBoxFilteringCustom.h>

class vistalProcessDenoisingToolBoxPrivate;

class vistalProcessDenoisingToolBox : public medToolBoxFilteringCustom
{
    Q_OBJECT

public:
     vistalProcessDenoisingToolBox(QWidget *parent = 0);
    ~vistalProcessDenoisingToolBox(void);

public:
    static bool registered(void);
    dtkAbstractData* processOutput();
   
signals:
    void success(void);
    void failure(void);
    
public slots:

    void run(void);

private:
    vistalProcessDenoisingToolBoxPrivate *d;
};

#endif

