#include"input_gen.h"

void input_gen::generate(){
    std::srand(std::time(0));

    unsigned address = 0x00000000;
    int prob_of_anything = read + write + touch + grow + del;
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

        if(((total+=touch) > dice) || running.size() < 2){
            int deviation = rand()%range;
            fake_process proc(++address,  size*MEGABYTE + deviation*((rand()%2==0 || ((size*MEGABYTE-deviation)<=0) ? 1 : -1)));
            running.insert(proc);
            std::cout << "START " <<  std::to_string(proc.location) << " " << std::to_string(proc.size) << std::endl;
        }

        else if((total+=read) > dice){
            do{   
                t += std::rand()%(prob_of_anything-locality);
                t = t%(it->size);
                std::cout << "READ " << std::to_string(it->location) <<  " " <<std::to_string(t) << std::endl;
            }while((std::rand()%prob_of_anything) < locality);
        }
 
        else if( (total+=write) > dice){
            do{   
                t += std::rand()%(prob_of_anything-locality);
                t = t%(it->size);
                std::cout << "WRITE " << std::to_string(it->location) <<  " " <<std::to_string(t) << std::endl;
            }while((std::rand()%prob_of_anything) < locality);
        }
 
        else if( (total+=grow) > dice){
            int deviation = rand()%range;
            int old_add = it->location;
            int old_sz = it->size;
            running.erase(it);
            fake_process p(old_add,old_sz + deviation);

            std::cout << "GROW " << old_add <<  " " << deviation << std::endl;
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
