#include"input_gen.h"

void input_gen::generate(){
    std::srand(std::time(0));
    std::string read = "READ ";
    std::string write = "WRITE ";
    int i(-1);

    unsigned address = 0x00000000;
    unsigned prob_of_anything = r_and_w + locality;
        std::set<fake_process> running;
    for(int i = 0; i < 5; ++i){
            int deviation = rand()%range;
            fake_process p(++address,  size*MEGABYTE + deviation*(rand()%2==0 || ((size*MEGABYTE-deviation)<=0) ? 1 : -1));
             running.insert(p);
            std::cout << "START " <<  std::to_string(p.location) << " " << std::to_string(p.size) << std::endl;
    }

    
    for(unsigned i = 0; i < instructions; ++i){
      
        int total(0), t(0);
        int dice(std::rand()%prob_of_anything);
        auto it = running.begin();
        int add = rand()%running.size();
        std::advance(it, add);

        if(((total+=locality) > dice) || running.size() < 2){
            int deviation = rand()%range;
            fake_process p(++address,  size*MEGABYTE + deviation*((rand()%2==0 || ((size*MEGABYTE-deviation)<=0) ? 1 : -1)));
            running.insert(p);
            std::cout << "START " <<  std::to_string(p.location) << " " << std::to_string(p.size) << std::endl;
        }

        else if( (total+=r_and_w) > dice){
            do{   
                t += std::rand()%(prob_of_anything-locality);
                t = t%(it->size);
                std::string type = rand()%2==0 ? "READ " : "WRITE ";
                std::cout << type << std::to_string(it->location) <<  " " <<std::to_string(t) << std::endl;
            }while((std::rand()%prob_of_anything) < locality);
        }
        else{
            std::cout << "TERMINATE " <<  std::to_string(it->location) << std::endl;
            running.erase(it);
        }
    }
}
void input_gen::print_me(){
    for(auto it : output){
        std::cout << it << "\n" << std::endl;
    }
}
