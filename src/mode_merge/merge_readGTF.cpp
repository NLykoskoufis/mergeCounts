#include "merge_data.h"

void mergeCounts::readGTF(std::string fgtf)
{
    std::string buffer;
    std::vector < std::string > tokens; 

    input_file fd (fgtf);
    if (fd.fail()) std::cout << "Cannot open file" << std::endl;
    unsigned int linecount = 0;
    // Read GTF file 
    while (getline(fd, buffer))
    {   
        if (buffer[0] == '#') continue;
        boost::split(tokens, buffer, boost::is_any_of(" \t;"));
        if (linecount % 1000000 == 0 ) std::cout << "Read " << std::to_string(linecount) << "\n";
        linecount++;

        if (tokens[2] == "gene")
        {
            std::string gene_id = tokens[9].substr(1,tokens[9].size() -2);
            
            geneInfo info; 
            info.chrom = tokens[0];
            info.gene_name = tokens[12].substr(1,tokens[12].size() -2);
            info.gene_type = tokens[18].substr(1,tokens[18].size() -2);
            info.strand = tokens[6];
            info.start = std::stoi(tokens[3]);
            info.end = std::stoi(tokens[4]);
            info.tss = (tokens[6] == "+") ? std::stoi(tokens[3]) : std::stoi(tokens[4]);
            //std::cout << gene_id << " " << info.gene_name << " " << info.gene_type << " " << info.strand << " " << std::to_string(info.start) << " " << std::to_string(info.end) << " " << std::to_string(info.tss) << "\n";
            annotationMap.insert(std::make_pair(gene_id, info));
        }else if (tokens[1] == "transpo_element")
        {
            std::string gene_id = tokens[9].substr(1,tokens[9].size() -2);
            
            geneInfo info; 
            info.chrom = tokens[0];
            info.gene_name = tokens[12].substr(1,tokens[12].size() -2);
            info.gene_type = "transposable_element";
            info.strand = tokens[6];
            info.start = std::stoi(tokens[3]);
            info.end = std::stoi(tokens[4]);
            info.tss = (tokens[6] == "+") ? std::stoi(tokens[3]) : std::stoi(tokens[4]);
            //std::cout << gene_id << " " << info.gene_name << " " << info.gene_type << " " << info.strand << " " << std::to_string(info.start) << " " << std::to_string(info.end) << " " << std::to_string(info.tss) << "\n";
            annotationMap.insert(std::make_pair(gene_id, info));
        }else{
            continue;
        }
    }
}
