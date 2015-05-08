#include "standard.h"
#include "logfilesystem.h"
#include "segment.h"
using namespace std;
int main(int argc, char **argv) {   

	/*error check cmd line args*/
	/*Usages: ./program3 <num_segments> <segment_size> <min_life> <min_clean> <input_file>*/
	if(argc != 6)
	{
		cerr << "Usage: ./program3 <num_segments> <segment_size> <min_life> <min_clean> <input_file>" << endl;
		exit(0);
	}

	int num_segs = atoi(argv[1]);
	int seg_size = atoi(argv[2]);
	double min_life = atof(argv[3]);
	double min_clean = atof(argv[4]);
	std::cout << "num segs: " << num_segs << " seg_size " << seg_size << " min_lie " << min_life << " min clean " << min_clean << std::endl;
	if(num_segs < 0 || seg_size < 0 || min_life <= 0 || min_life > 1 || min_clean <= 0 || min_clean > 1)
	{	
		cerr << "<num_segments> and <segment_size> must be greater than 0." << endl;
		exit(0);
	}
	LogFileSystem lfs(num_segs, seg_size, min_life, min_clean);
	stringstream ss;
	ifstream in;
	in.open(argv[5], ifstream::in);
	string line, temp;
	int fid = 0, block_num = 0, size = 0;
	cerr << "opening file " << endl;
	while(in.good() && getline(in, line))	
	{
		ss << line;
		ss >> temp;

		//Check which type of command new line is
		//Start: create a new process and add to map
		if(!temp.compare("START"))
		{
			cerr << "IN START" << endl;		
			//First number is process number
			ss >> temp;
			fid  = atoi(temp.c_str());
			//Second number is size
			ss >> temp;
			size = atoi(temp.c_str());
			lfs.createFile(fid, size);	
		}
		else if(!temp.compare("TERMINATE"))
		{
			cerr << "IN TERMINATE" << endl;		
			//Fid
			ss >> temp;
			lfs.deleteFile(atoi(temp.c_str()));
		}
		else if(!temp.compare("GROW"))
		{
			cerr << "IN GROW" << endl;		
			//Fid
			ss >> temp;
			fid = atoi(temp.c_str());
			//Size
			ss >> temp;
			size = atoi(temp.c_str());
			lfs.growFile(fid, size);

		}
		else if(!temp.compare("WRITE"))
		{
			cerr << "IN WRITE" << endl;		
			//Fid
			ss >> temp;
			fid = atoi(temp.c_str());
			//block number
			ss >> temp;
			block_num = atoi(temp.c_str());
			lfs.writeBlock(fid, block_num);
		}
		else if(!temp.compare("READ"))
		{
			cerr << "IN READ" << endl;		
			//Fid
			ss >> temp;
			fid = atoi(temp.c_str());
			//block number
			ss >> temp;
			block_num = atoi(temp.c_str());
			lfs.readBlock(fid, block_num);
		}

		ss.clear();
	}
	return 0;

}
