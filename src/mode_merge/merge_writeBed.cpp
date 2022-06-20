#include "merge_data.h"

void mergeCounts::writeMerged(std::string fout)
{
    // Loop over expression map and for each gene id get all info from annotation Map and create bed File. 

    output_file fdo (fout);
    fdo << "#chr\tstart\tend\tid\tinfo\tstrand";
    for (auto x: sampleID)
    {
        fdo << "\t" << x; 
    }
    fdo << "\n";
    
    
    std::map < std::string, std::vector < double > >::iterator it;
    for (it = expression_map.begin(); it!=expression_map.end(); it++)
    {
        //std::cout << it->first << "\n";
        std::unordered_map < std::string, geneInfo >::iterator got = annotationMap.find(it->first);
        if (got != annotationMap.end())
        {
            //std:: cout << got->first << " " << got->second.gene_name << " " << got->second.gene_type << "\n";
            
            //std::string info;
            //info = "L=...;T=...;R=...;N=...";

           fdo << got->second.chrom << "\t";
           fdo <<  std::to_string(got->second.tss - 1) << "\t";
           fdo << std::to_string(got->second.tss) << "\t";
           fdo << got->first << "\t";
           fdo << "L=" << std::to_string(got->second.end - got->second.start) << ";T=" << got->second.gene_type << ";R=" << got->second.chrom << ":" << got->second.start << "-" << got->second.end << ";N=" << got->second.gene_name << "\t";
           fdo << got->second.strand; 
           for (unsigned int i=0; i < it->second.size(); i++)
           {
            fdo << "\t" << it->second[i];
           }
            fdo << "\n";
        }
    }

}