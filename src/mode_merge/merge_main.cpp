#include "merge_data.h"


void merge_main(vector < string > & argv)
{

    mergeCounts D;
    boost::program_options::options_description opt_basic ("\x1B[32mBasics\33[0m");
	opt_basic.add_options()
		("help", "Produces option description");

    boost::program_options::options_description opt_files ("\x1B[32mI/O\33[0m");
	opt_files.add_options()
		("ftxt", boost::program_options::value< std::vector < std::string > >()->multitoken(), "list of files to merge. featureCounts .txt format required !!!Txt files need to contain the same features (not necessarily same order)!!!!!")
		("gtf", boost::program_options::value< std::string >(), "annotation file in gtf format")
		("out", boost::program_options::value< string >(), "Output file.");

	/*(boost::program_options::options_description opt_parameters ("\x1B[32mParameters\33[0m");
    opt_parameters.add_options()
		("random_var",boost::program_options::value< unsigned int >()->default_value(10), "The number of random_variants to use")
		("window_size", boost::program_options::value< unsigned int >()->default_value(2500), "Size of the cis-window.")
        ("maf_window", boost::program_options::value< float >()->default_value(0.01), "Size of the maf_window");
    
    D.option_descriptions.add(opt_basic).add(opt_files).add(opt_parameters);
    */
    D.option_descriptions.add(opt_basic).add(opt_files);
    //-------------------
	// 2. PARSE OPTIONS
	//-------------------
	try {
		boost::program_options::store(boost::program_options::command_line_parser(argv).options(D.option_descriptions).run(), D.options);
		boost::program_options::notify(D.options);
	} catch ( const boost::program_options::error& e ) {
		cerr << "Error parsing [enrich] command line :" << string(e.what()) << endl;
		exit(0);
	}

    std::cout << "\n" << "\x1B[32;1m" << "Merge featureCounts files to multi-sample bed file" << "\033[0m" << endl;
    if(D.options.count("help")) {
        cout << D.option_descriptions << endl;
        exit(0);
    }    

    if (D.options.count("ftxt") && D.options.count("gtf") && D.options.count("out"))
    {
        std::vector < std::string > fileList = D.options["ftxt"].as < std::vector < std::string > >();
        std::cout << fileList.size() << "\n";
        D.sampleNumber = fileList.size();
        std::string fgtf = D.options["gtf"].as < std::string>();
        std::cout << fgtf << "\n";
        D.readGTF(fgtf);        
        for (unsigned int i = 0; i < fileList.size(); i++)
        {
            std::cout << "Reading [" << fileList[i] << "]\n";
            D.readPhenotypes(fileList[i],i);
        }
    }

    D.writeMerged(D.options["out"].as < std::string >());

}
   