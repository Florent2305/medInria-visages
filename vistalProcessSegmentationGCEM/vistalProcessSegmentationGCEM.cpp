// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "vistalProcessSegmentationGCEM.h"

#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkSmartPointer.h>

#include <medMetaDataKeys.h>
#include <QDebug>

#include "mstoolsFiniteModel.h"
#include "Matrice.hh"
#include "Image3D.hh"
#include "GIS.hh"


#include "Algebrique.hh" // ET function



#include "mstoolsGaussian.h"
#include "mstoolsStraInitializer.h"
#include "mstoolsHierarchicalInitializer.h"


#include "mstoolsClassificationFunctions.h"

#include "mstoolsAtlasRandomInitializer.h"
#include "mstoolsModelInitializer.h"
#include "mstoolsJointHistogramNdims.h"

#include "mstoolsClassEstimator.h"
#include "mstoolsGaussian.h"
#include "mstoolsGaussianREMEstimator.h"
#include "mstoolsGaussianEMEstimator.h"
#include "mstoolsGaussianCeleuxREMEstimator.h"
#include "mstoolsGaussianCeleuxEMEstimator.h"
#include "mstoolsImageClassifier.h"
#include "mstoolsRulesLesionClassifier.h"

#include "mstoolsClassificationStrategy.h"
#include "Labelize.hh"
#include "mstoolsRulesLesionClassifier.h"
#include "mstoolsMahalanobisThreshold.h"
#include "mstoolsChi2.h"

#include "vistalImageOperations.hh"
#include "Morpho.hh"
#include "Interpolation.hh"

#include "sgc.h"

//#include "mstoolsIO.h"


// /////////////////////////////////////////////////////////////////
// vistalProcessSegmentationGCEMPrivate
// /////////////////////////////////////////////////////////////////

class vistalProcessSegmentationGCEMPrivate
{
public:
    vistalProcessSegmentationGCEMPrivate();
    ~vistalProcessSegmentationGCEMPrivate();
    // Channel 0 to 2
    QList < dtkSmartPointer <dtkAbstractData> > input; // Expected Input image to segment (T1, PD , {T2, FLAIR} )
    vistal::Image3D<unsigned char> im1,im2, im3;
    // Channel 3
    vistal::Image3D<unsigned char> mask; // Mask image
    int imported;
    
    enum InitialisationMethod { StraInit, HierarchicalPD, HierarchicalFLAIR } initMethod; // Type of initialisation for the EM, D. Garcia used Hierachical PD or FLAIR depending on the input
    // Rejection Ratio
    double rejectionRatio;
    
    enum ApproachEM { GaussianEM, GaussianCeleuxREM, GaussianREM } approachEM;
    
    double minDistance; // = 1e-4;
    int emIter;
    int strem;
    
    /* nlesions parameterts*/
    double mahalanobisThreshold, rulesThreshold;
    int minsize, wmneighbor;
    
    
    double rulesMin, rulesMax;
    double alphap;
    
    dtkSmartPointer <dtkAbstractData> output;
    
};

vistalProcessSegmentationGCEMPrivate::vistalProcessSegmentationGCEMPrivate(): imported(0),
initMethod(HierarchicalFLAIR), rejectionRatio(0.2), approachEM(GaussianREM),
minDistance(1e-4), emIter(10), strem(0),
mahalanobisThreshold(.4), rulesThreshold(3.),
minsize(6), wmneighbor(0.05), rulesMin(2), rulesMax(3), alphap(10), output(0)

// -0 -iter 200 dist 1e-3
// show outliers, set iteration to 200, mindistance 1e-3,
{
}

vistalProcessSegmentationGCEMPrivate::~vistalProcessSegmentationGCEMPrivate()
{
}






// /////////////////////////////////////////////////////////////////
// vistalProcessSegmentationGCEM
// /////////////////////////////////////////////////////////////////

vistalProcessSegmentationGCEM::vistalProcessSegmentationGCEM(void) : dtkAbstractProcess(), d(new vistalProcessSegmentationGCEMPrivate)
{
}

vistalProcessSegmentationGCEM::~vistalProcessSegmentationGCEM(void)
{
    delete d;
}

bool vistalProcessSegmentationGCEM::registered(void)
{
    return dtkAbstractProcessFactory::instance()->registerProcessType("vistalProcessSegmentationGCEM", createVistalProcessSegmentationGCEM);
}

QString vistalProcessSegmentationGCEM::description(void) const
{
    return "vistalProcessSegmentationGCEM";
}

void vistalProcessSegmentationGCEM::setInput(dtkAbstractData *data, int channel)
{
    if (!data)	return;
    
    if (!d) return;
    if (d->input.size() != 3)
    {
        //		qDebug() << "Setting the size of temporary input";
        d->input.push_back(NULL);
        d->input.push_back(NULL);
        d->input.push_back(NULL);
    }
    
    dtkAbstractData *dU8 = data->convert("vistalDataImageUChar3");
    
    if (!dU8)
    {
        qDebug() << "DataType conversion error";
        return;
    }
    //	qDebug() << "channel:" << channel << "datapointers:"<< data << dU8;
    
    if (channel >= 0 && channel < 3)
    {
        d->input[channel] = dU8;
    }
    
    if (channel == 3)
    {
        vistal::Image3D<unsigned char>* ima = dynamic_cast<vistal::Image3D<unsigned char>* >((vistal::Image3D<unsigned char>* )dU8->data());
        if (!ima) { qDebug() << "What the fuck the image is fucked up here!!!"; return; }
        d->mask = *ima;
    }
    
    d->imported |= (1<< channel);
    
}


void vistalProcessSegmentationGCEM::setParameter(double  data, int channel)
{
    switch(channel){
            
        case(0):
            //if (data == 0)
            //					d->initMethod = vistalProcessSegmentationGCEMPrivate::Unset;
            //				else
            if (data == 0)
                d->initMethod = vistalProcessSegmentationGCEMPrivate::StraInit;
            else if (data == 1)
                d->initMethod = vistalProcessSegmentationGCEMPrivate::HierarchicalPD;
            else if (data == 2)
                d->initMethod = vistalProcessSegmentationGCEMPrivate::HierarchicalFLAIR;
            break;
            
        case 1:
            if (data > 0 && data < 1)
                d->rejectionRatio = data;
            else d->rejectionRatio = 0;
            
            break;
            
        case 2:
            if (data == 0)
                d->approachEM = vistalProcessSegmentationGCEMPrivate::GaussianEM;
            else if (data == 1)
                d->approachEM = vistalProcessSegmentationGCEMPrivate::GaussianCeleuxREM;
            else if (data == 2)
                d->approachEM = vistalProcessSegmentationGCEMPrivate::GaussianREM  ;
            break;
            
        case 3:
            d->minDistance = data;//1e-4;
            break;
            
        case 4:
            d->emIter = data;
            break;
            
        case 5:
            d->strem = data;
            break;
        case 6:
            d->mahalanobisThreshold = data;
            break;
        case 7:
            d->rulesThreshold = data;
            break;
        case 8:
            d->minsize = data;
            break;
        case 9:
            d->wmneighbor = data;
            break;
        case 10:
            d->rulesMin = data;
            break;
        case 11:
            d->rulesMax = data;
            break;
            
        case 12:
            d->alphap = data;
            break;
            
        default:
            return;
    }
}

//
template<class T>
inline  bool fuzzyConverter(vistal::Image3D<T> &in, vistal::Image3D<unsigned char> &mask, vistal::Image3D<float> &out,double t0,double t1,double t2,double t3)
{
    if(!test_dim(in,mask))
    {
        std::cerr<<" ** ERROR in fuzzyConverter: Sizes between Image in and Image mask differ"<<std::endl;
        return false;
    }
    
    if(!test_dim(in,out))
    {
        out.redimensionne(in.nbx,in.nby,in.nbz);
    }
    if(t0 > t1)
        t1=t0;
    if(t1 > t2)
        t2=t1;
    if(t2 > t3)
        t3=t2;
    
    for(int k=0; k < out.nbz; k++)
        for(int j=0; j < out.nby; j++)
            for(int i=0; i < out.nbx; i++)
            {
                if(!mask.ptr[k][j][i])
                {
                    out.ptr[k][j][i]=0.0;
                    continue;
                }
                double x=(double)in.ptr[k][j][i];
                if(      x < t0)
                    out.ptr[k][j][i]=0.0;
                else if( x >=  t1 && x <= t2)
                    out.ptr[k][j][i]=1.0;
                else if( x >  t3)
                    out.ptr[k][j][i]=0.0;
                else if( x < t1 && x > t0 )
                    out.ptr[k][j][i]=(x-t0)/(t1-t0);
                else if( x  > t2 && x < t3)
                    out.ptr[k][j][i]=(t3-x)/(t3-t2);
                else
                    out.ptr[k][j][i]=0.0;
                
            }
    return true;
    
}


// Run the GCEM Algorithm
int vistalProcessSegmentationGCEM::update(void)
{
    using namespace mstools;
    // Starting  strainit binary code
    
    if (!(d->imported & 15))
    {
        qDebug() << "Error data not properly imported";
        return -1;
    }
    
    std::vector<vistal::Image3D<unsigned char> > input;
    
    foreach (dtkAbstractData *image, d->input)
    {
        vistal::Image3D<unsigned char>* ima = dynamic_cast<vistal::Image3D<unsigned char>* >((vistal::Image3D<unsigned char>* )image->data());
        if (!ima) { qDebug() << "What the fuck the image is fucked up here!!!"; return -1; }
        
        input.push_back(*ima);
    }
    
    FiniteModel initia;
    
    for(unsigned int i=0; i<3; i++)
    {
        Distribution::Pointer p=Gaussian::New( 3);
        initia.push_back(p);
    }
    
    
    switch (d->initMethod) {
        case vistalProcessSegmentationGCEMPrivate::StraInit:
        {
            StraInitializer init(input,d->mask);
            init.setDebugMode(false);
            if(!init. getInitialization(initia))
            {
                qDebug() << "Error in initialisation";
                return -1;
            }
            break;
        }
        case vistalProcessSegmentationGCEMPrivate::HierarchicalPD: // If third image is T2 use this init
        {
            std::vector<std::string> seq;
            HierarchicalInitializer init(input,d->mask,seq,false,0.01, 0);
            if(!init. getInitialization(initia))
            {
                qDebug() << "Error in initialisation";
                return -1;
            }
            break;
        }
        case vistalProcessSegmentationGCEMPrivate::HierarchicalFLAIR: // If third image is FLAIR use this init
        {
            std::vector<std::string> seq;
            HierarchicalInitializer init(input, d->mask, seq, true, 0.01, 0);
            if(!init. getInitialization(initia)) 			{
                qDebug() << "Error in initialisation";
                return -1;
            }
            break;
        }
        default:
        {
            qDebug() << "Error in initialisation";
            
            return -1;
        }
    }
    
    // Starting Classification binary code
    
    int modalities = 3;
    
    JointHistogramNdims jointHistogram;
    std::vector<double> min( modalities, 255.0 ); //min values for random initialization
    std::vector<double> max( modalities, 0.0 ); //max values for random initialization
    
    for (unsigned i = 0; i < 3; ++i) min[i] = vistal::stats::GetMinPixelValue( input[ i ] , d->mask );
    for (unsigned i = 0; i < 3; ++i) max[i] = vistal::stats::GetMaxPixelValue( input[ i ] , d->mask );
    
    if (! jointHistogram.createJointHistogram( input, d->mask, false ))
    {
        qDebug() << "Error in Joint Histogram creation";
        return -1;  // Joint histogram construction failure
    }
    
    std::vector<unsigned int> emSteps( 1, 1 );
    std::vector<unsigned int> iterSteps( 1, 100 );
    
    ClassEstimator *estimator = NULL;
    
    switch (d->approachEM)
    {
        case vistalProcessSegmentationGCEMPrivate::GaussianCeleuxREM:
            estimator = new GaussianCeleuxREMEstimator( iterSteps[ 0 ], d->minDistance, d->emIter, d->strem );
            dynamic_cast<GaussianCeleuxREMEstimator *>( estimator ) ->setRejectionRatio( d->rejectionRatio );
            break;
        case vistalProcessSegmentationGCEMPrivate::GaussianEM:
            estimator = new GaussianEMEstimator( iterSteps[ 0 ], d->minDistance );
            break;
        case vistalProcessSegmentationGCEMPrivate::GaussianREM:
            estimator = new GaussianREMEstimator( iterSteps[ 0 ], d->minDistance, d->emIter, d->strem );
            dynamic_cast<GaussianREMEstimator *>( estimator ) ->setRejectionRatio( d->rejectionRatio );
            
            break;
    }
    
    estimator->setJointHistogram(jointHistogram);
    
    estimator->setModel(initia);
    
    unsigned iterations = 0;
    
    estimator->run(iterations);
    
    FiniteModel solution = estimator->getModel();
    
    // Got the segmentation ....
    
    
    delete estimator;
    
    // Do the msgcHelper
    // The outputs of msgcHelper
    vistal::Image3D<float> object(input[0] ,0.0);
    vistal::Image3D<float> background(input[0], 0.0);
    
    { // msgcHelper starts here
        //            vistal::Image3D<unsigned char> thImage;
        std::vector<vistal::Image3D<double> >floatImages(solution.size(),vistal::Image3D<double>(input[0], 0.0));
        
        MahalanobisThreshold threshold;
        threshold.setModel( solution );
        threshold.setThreshold( 0.4 ); // set as this
        
        if(!threshold.getMahalanobisImages( input, d->mask, floatImages ))
        {
            std::cout<<" ** ERROR in Mahalanobis threshold"<<std::endl;
            emit failure();
            return -1;
        }
        
        
        for(int k=0; k<d->mask.nbz; k++)
            for(int j=0; j<d->mask.nby; j++)
                for(int i=0; i<d->mask.nbx; i++)
                {
                    if(d->mask(i,j,k)==0)
                        continue;
                    for(unsigned int n=0; n<floatImages.size(); n++)
                    {
                        if(background(i,j,k) < floatImages[n](i,j,k))
                            background(i,j,k) = floatImages[n](i,j,k);
                    }
                    object(i,j,k) = 1.0 - background(i,j,k);
                }
        
        
        // FUZZY RULES
        std::vector<std::vector<double> >means(solution.size(),std::vector<double>(3,0.0));
        std::vector<std::vector<double> >stdev(solution.size(),std::vector<double>(3,0.0));
        int sequences=solution[0]->getDimension();
        
        for(unsigned int i=0; i<solution.size(); i++)
        {
            ColumnVector mean;
            Matrix covar;
            dynamic_cast<mstools::Gaussian *>(solution[i].get())->getMu(mean);
            dynamic_cast<mstools::Gaussian *>(solution[i].get())->getSigma(covar);
            
            for(int j=0; j<sequences; j++)
            {
                means[j][i]=mean(j+1);
                stdev[j][i]=sqrt(covar(j+1,j+1));
            }
        }
        
        
        std::vector<vistal::Image3D<float> >
        maps(sequences, vistal::Image3D<float>(d->mask, 0.0));
        
        // The fist we erase very dark points only... problably not necessary
        fuzzyConverter(input[0], d->mask, maps[0],
                       0.0,means[0][0]-2.0*stdev[0][0],255.0,260.0);
        
        // we start with the second... the first must be t1-w
        for(unsigned int i=1; i<solution.size(); i++)
        {
            fuzzyConverter(input[i], d->mask, maps[i],
                           means[i][2]+d->rulesMin*stdev[i][2],means[i][2]+d->rulesMax*stdev[i][2],255.0,260.0);
        }
        
        
        vistal::Image3D<float> fuzzy(d->mask,1.0);
        vistal::Image3D<float> tmp(maps[0]);
        for(unsigned int i=1; i<maps.size(); i++)
        {
            ET(tmp,maps[i],fuzzy);
            copie_pointeur(tmp,fuzzy);
        }
        // Merge Mahalanobis distance with Fuzzy Rules
        ET(object,fuzzy,tmp);
        copie_pointeur(object,tmp);
        
    }
    
    // Do the sgc
    
    vistal::Image3D<unsigned char> thImage;
    {
        GC( input[0], input[1], input[2], thImage, object, background, d->mask,d->alphap );
    }
    
    // Now apply the nlesions binary
    
    vistal::Image3D<unsigned char> rulesIma;
    double rules3[3];
    rules3[0]=d->rulesThreshold;
    rules3[1]=d->rulesThreshold;
    rules3[2]=d->rulesThreshold;
    
    // Lesions in rules Ima are ==5
    if(!rulesT2lesions(rulesIma, thImage, input, solution, rules3, false /* verbose*/ ))
    {
        qDebug() << "Error in Lesions Rules application";
        
        return -1;
    }
    vistal::Image3D<unsigned int > labels;
    int numLabels=0;
    vistal::Image3D<unsigned int> tmpIma(d->mask, 0);
    for (vistal::Image3D<unsigned>::iterator it = tmpIma.begin(); it != tmpIma.end(); ++it)
        if (rulesIma(it.Position()) == 5)
            *it = 1;
    
    numLabels = Labelize( tmpIma, labels, 0 );
    
    vistal::Image3D<unsigned int> biglesions(tmpIma);
    rulesLesionSize(biglesions,d->mask,labels, d->minsize,/* verbose = */ false);
    
    // Removing border lesions
    //////////////////////////////
    vistal::Image3D<unsigned int> noborderlesions;
    
    if(!rulesBorder( noborderlesions, d->mask, biglesions,/* verbose = */false ))
    {
        std::cout<<" ** ERROR in rulesBorder"<<std::endl;
        return -1;
    }
    
    vistal::Image3D<unsigned char> classifIma;
    ImageClassifier classifier;
    classifier.setModel( solution );
    classifier.getOutputImage( input , d->mask, classifIma );
    
    
    vistal::Image3D<unsigned char> classifplus(classifIma);
    Voxel p;
    
    
    for (vistal::Image3D<unsigned char>::iterator it = classifplus.begin(); it != classifplus.end(); ++it)
    {
        if(noborderlesions(it.Position()))
            *it = solution.size()+1;
    }
    // Choose and remove small GM regions
    
    vistal::Image3D<unsigned char> nclassif;
    int minGMsize=15;
    //			std::cout<<" -- Cleaning GM in classification: minsize: "<<minGMsize<<std::endl;
    rules4GM(nclassif,classifplus,minGMsize,solution.size()-1,/*verbose=*/false);
    
    
    //			std::cout<<" -- Cleaning lesions that are not neighbors to the WM!"<<std::endl;
    vistal::Image3D<unsigned char> *fclassif = new vistal::Image3D<unsigned char>;
    rulesWM4lesions(*fclassif,noborderlesions,nclassif,solution.size()+1,d->wmneighbor,/*verbose=*/false);
    
    dtkAbstractData *tmpData = dtkAbstractDataFactory::instance()->create("vistalDataImageUChar3");
    tmpData->setData(fclassif);
    d->output = tmpData->convert("itkDataImageUChar3");
    
    foreach(QString list, d->input[0]->metaDataList())
        d->output->addMetaData(list, d->input[0]->metaDataValues(list));
    
    QString newSeriesDescription = d->output->metadata(medMetaDataKeys::SeriesDescription.key());
    newSeriesDescription += " GCEM lesions segmentation";
    
    d->output->setMetaData(medMetaDataKeys::SeriesDescription.key(),newSeriesDescription);
    
    return EXIT_SUCCESS;
}

dtkAbstractData * vistalProcessSegmentationGCEM::output(void)
{
    return d->output;
}

// /////////////////////////////////////////////////////////////////
// Type instantiation
// /////////////////////////////////////////////////////////////////

dtkAbstractProcess *createVistalProcessSegmentationGCEM(void)
{
    return new vistalProcessSegmentationGCEM;
}
