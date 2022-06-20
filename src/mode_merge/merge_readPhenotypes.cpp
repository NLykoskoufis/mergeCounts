#include "merge_data.h"

void mergeCounts::readPhenotypes(std::string fbed, unsigned int fileIndex)
{
    std::string buffer;
    std::vector < std::string > tokens; 
    unsigned int phenotypeCount = 0;
    unsigned int linecount = 0;

    input_file fd (fbed);
    if (fd.fail()) std::cout << "Cannot open file" << std::endl;
    
    // Read GTF file 
    while (getline(fd, buffer))
    {   
        //if (linecount % 1000000 == 0) std::cout << "Read " << linecount << "\n";
        linecount++;
        if (buffer[0] == '#') continue;
        boost::split(tokens, buffer, boost::is_any_of("\t"));
        if(tokens[0] == "Geneid")
        {
            std::cout << tokens[6] << "\n";
            sampleID.push_back(tokens[6]);
        }else{
        phenotypeCount++;
        std::string gene_id = tokens[0];
        
        std::map<std::string,std::vector < double > >::iterator got = expression_map.find(gene_id);
        if (got == expression_map.end())
        {
            std::vector < double > expressionVector(sampleNumber, 0.0); 
            //expressionVector.back(std::stod(tokens[6]));
            expressionVector.back(fileIndex, std::stod(tokens[6]));
            expression_map.insert(std::make_pair(gene_id, expressionVector));
        }else
        {
            //got->second.push_back(std::stod(tokens[6]));
            got->second.back(fileIndex, std::stod(tokens[6]));
        }
        }
    }

} // End of function