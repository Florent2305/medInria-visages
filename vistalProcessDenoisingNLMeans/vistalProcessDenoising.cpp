// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "vistalProcessDenoising.h"

#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkAbstractDataFactory.h>

#include "NLMeans_class.hh"
#include <cstdlib>

// /////////////////////////////////////////////////////////////////
// vistalProcessDenoisingPrivate
// /////////////////////////////////////////////////////////////////

class vistalProcessDenoisingPrivate
{
public:
        dtkAbstractData *input;	
        dtkAbstractData *output;

        QString originDescription;

        double seuil;
        double beta;
        int seuil_adapt;
        int isotropic;
        double S;
        double M;
        int testmean;
        int testvar;
        double m_min;
        double v_min;
        int weight_method;
        int block;
        int b_space;
	unsigned int N_thread;
        //char* temp;
	
        // TO DO : temp directory for slice preview
};

// /////////////////////////////////////////////////////////////////
// vistalProcessDenoising
// /////////////////////////////////////////////////////////////////

vistalProcessDenoising::vistalProcessDenoising(void) : dtkAbstractProcess(), d(new vistalProcessDenoisingPrivate)
{
	d->input = NULL;
	d->output = NULL;  
    d->seuil = 0;
    d->beta = 1;
    d->seuil_adapt = 0;
    d->isotropic = 0;
    d->S = 1;
    d->M = 5;
    d->testmean = 1;
    d->testvar = 1;
    d->m_min = 0.95;
    d->v_min = 0.5;
    d->weight_method = 0;
    d->block = 1;
    d->b_space = 2;
	d->N_thread = 1;
    d->originDescription = "";
    //temp = NULL;
}

vistalProcessDenoising::~vistalProcessDenoising(void)
{                
    delete d->input;
	d->input = NULL;
	
    delete d->output;
	d->output = NULL;	
}

bool vistalProcessDenoising::registered(void)
{
    return dtkAbstractProcessFactory::instance()->registerProcessType("vistalProcessDenoisingNLMEANS", createVistalProcessDenoising);
}

QString vistalProcessDenoising::description(void) const
{  
    return "vistalProcessDenoisingNLMEANS";
}

void vistalProcessDenoising::setInput(dtkAbstractData *data)
{    
    if (!data)  
    {
        return;
    }
    
    d->originDescription = data->description();
    d->input = data->convert("vistalDataImageDouble3");

	if (!d->input)
	  return;  
}



void vistalProcessDenoising::setParameter(double  data, int channel)
{
    switch (channel){

        case (0):
                d->seuil = data;
                break;
        case (1):
                d->beta = data;
                break;
        case (2):
                d->seuil_adapt = data;
                break;
        case (3):
                d->isotropic =data;
                break;
        case (4):
                d->S = data;
                break;
        case (5):
                d->M =data;
                break;
        case (6):
                d->testmean = data;
                break;
        case (7):
                d->testvar = data;
                break;
        case (8):
                d->m_min = data;
                break;
        case (9):
                d->v_min = data;
                break;
        case (10):
                d->weight_method = data;
                break;
        case (11):
                d->block = data;
                break;
        case (12):
                d->b_space = data;
                break;
	case (13):
		d->N_thread = (unsigned int)data;
		qDebug() << "channel = " << channel << "  data = " << data;
		qDebug() << "number of threads : " << d->N_thread;
		break;
        default :
                return;
        }
}


int vistalProcessDenoising::update (void)
{        
    if (d->input == NULL)
	{
	    qDebug() << "in update method : d->input == NULL";	  
            return -1;
	}

    vistal::NLMeansDenoising<double> *nlmeans = new vistal::NLMeansDenoising<double>;
    if(nlmeans == NULL)
        return -1;

    nlmeans->setInput(static_cast<vistal::Image3D<double> * > (d->input->data()));
    nlmeans->setAdaptiveSlope(d->seuil_adapt);
    nlmeans->setSigma(d->seuil);
    nlmeans->setBeta(d->beta);
    nlmeans->setIsotropicNeighborhood(d->isotropic);
    nlmeans->setNeighborhoodSize(d->S);
    nlmeans->setSearchVolumeSize(d->M);
    nlmeans->setBlockApproach(d->block);
    nlmeans->setTestOnMean(d->testmean);
    nlmeans->setTestOnVar(d->testvar);
    nlmeans->setMeanMinRatio(d->m_min);
    nlmeans->setVarMinRatio(d->v_min);
    nlmeans->setWeightingMethod(d->weight_method);
    nlmeans->setDistanceBetweenBlocks(d->b_space);
    nlmeans->setNumberOfThreads(d->N_thread);

    nlmeans->run();

    vistal::Image3D<double> * result = new vistal::Image3D<double>(*nlmeans->getOutput());

    dtkAbstractData *temporaryOutput = dtkAbstractDataFactory::instance()->create("vistalDataImageDouble3");
    if (temporaryOutput == NULL)
        return -1;

    temporaryOutput->setData(result);

    if(temporaryOutput->data() == NULL)
        return -1;

    delete nlmeans;
    
    foreach(QString list, d->input->metaDataList())
        temporaryOutput->addMetaData(list, d->input->metaDataValues(list));
    foreach(QString list, d->input->propertyList())
        temporaryOutput->addProperty(list, d->input->propertyValues(list));

    d->output = temporaryOutput->convert(d->originDescription);

    return EXIT_SUCCESS;
}

dtkAbstractData * vistalProcessDenoising::output(void)
{	
	return (d->output);
}


// /////////////////////////////////////////////////////////////////
// Type instanciation
// /////////////////////////////////////////////////////////////////

dtkAbstractProcess * createVistalProcessDenoising(void)
{
    return new vistalProcessDenoising;
}
