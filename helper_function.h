#ifndef HELPER_H
#define HELPER_H

using namespace std;

//Hashed algorithm for PC: Cyclic Redundancy Check (CRC)
uint64_t CRC(uint64_t address){
	unsigned long long crcPolynomial = 3988292384ULL;  //Decimal value for 0xEDB88320 hex value
    unsigned long long result = address;
    for(unsigned int i = 0; i < 32; i++ )
    	if((result & 1 ) == 1 ){
    		result = (result >> 1) ^ crcPolynomial;
    	}
    	else{
    		result >>= 1;
    	}
    return result;
}

//Information for each address
struct HISTORY{
    uint64_t address;
    uint64_t PCval;
    uint32_t previousVal;
    uint32_t lru;
    bool prefetching;

    //TODO: modified and test!
    void init(){
        PCval = 0;
        previousVal = 0;
        lru = 0;
        prefetching = false;
    }

    //TODO: modified and test!
    void update(unsigned int currentVal, uint64_t PC){
        previousVal = currentVal;
        PCval = PC;
    }

    void is_prefetch(){
        prefetching = true;
    }
};

//Update cache history
void update_cache_history(unsigned int sample_set, unsigned int currentVal){
    for(map<uint64_t, HISTORY>::iterator it = cache_history_sampler[sample_set].begin(); it != cache_history_sampler[sample_set].end(); it++){
        if((it->second).lru < currentVal){
            (it->second).lru++;
        }
    }
}

#endif