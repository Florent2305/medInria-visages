
#ifndef VISTALPROCESSSegmentationSTREMTOOLBOX_H
#define VISTALPROCESSSegmentationSTREMTOOLBOX_H

#include <medToolBoxFilteringCustom.h>

class vistalProcessSegmentationSTREMToolBoxPrivate;

class vistalProcessSegmentationSTREMToolBox : public medToolBoxFilteringCustom
{
    Q_OBJECT

public:
     vistalProcessSegmentationSTREMToolBox(QWidget *parent = 0);
    ~vistalProcessSegmentationSTREMToolBox(void);

public:
    static bool registered(void);
    dtkAbstractData* processOutput();

signals:
    void success(void);
    void failure(void);

public slots:

    void onT1ImageDropped(void);
    void onPDImageDropped(void);
    void onT2orFLAIRImageDropped(void);

    void onMaskImageDropped(void);

    void run(void);

private:
    vistalProcessSegmentationSTREMToolBoxPrivate *d;
};

medToolBoxFilteringCustom *createVistalProcessSegmentationSTREMToolBox(QWidget *parent);

#endif

