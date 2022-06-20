#pragma once 

#include "../../lib/compression_io.h"

//INCLUDE STANDARD TEMPLATE LIBRARY USEFULL STUFFS (STL)
#include <vector>
#include <numeric>
#include <string>
#include <cmath>
#include <map> 
#include <iterator>
#include <unordered_map>
#include <limits>
#include <set> 
#include <algorithm>
#include <random> 
#include <iomanip> 

//INCLUDE BOOST LIBRARIES
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>

#include <htslib/hts.h>
#include <htslib/kseq.h>
#include <htslib/sam.h>

extern "C" {
	#include <htslib/vcf_sweep.h>
	#include <htslib/synced_bcf_reader.h>
	#include <htslib/vcf.h>
	#include <htslib/vcfutils.h>
}

class mergeCounts 
{
public:
    // OPTIONS 
    boost::program_options::options_description option_descriptions;
	boost::program_options::variables_map options;

    // FUNCTIONS 
    void readPhenotypes(std::string,unsigned int);
    void writeMerged(std::string);
    void readGTF(std::string);
    
    // PHENOTYPES 
    std::vector < std::string > sampleID;
    
    // ANNOTATION SPECIFIC 
    struct geneInfo
    {
        std::string gene_name; 
        std::string gene_type;
        std::string chrom;
        unsigned int start; 
        unsigned int end; 
        std::string strand; 
        unsigned int tss;
    };

    std::unordered_map < std::string, struct geneInfo > annotationMap;

    // MERGED 
    unsigned int sampleNumber;
    std::map < std::string, std::vector < double > > expression_map;

    //CONSTRUCTOR / DESTRUCTOR 
    mergeCounts(){sampleNumber = 0};
    ~mergeCounts();


};

//void merge_main(std::vector < std::string > & argv);
void merge_main(vector < string > & argv);
//void merge_main("/srv/beegfs/scratch/users/l/lykoskou/TE/V4/data_syscol/info_files/hg19_genes_TE_1811_s.gtf");