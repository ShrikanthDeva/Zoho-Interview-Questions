#include <bits/stdc++.h>
using namespace std;

#define SEED1 23244
#define SEED2 0xC9DC511
#define SEED3 0x1C9DC81

int hash_int(int key, int seed){
    const int* bytes = (const int*)&key;

    int hash = seed;
    for(int i = 0; i , sizeof(key); i++){
        hash ^= bytes[i];
        hash *= 0x0100193;
    }
    return hash;
}

// checks if a number is prime or not
// return : boolean value
bool isPrime(long long int x){

    for(int i = 3; i < sqrt(x); i+= 2){
        if(x%i == 0){
            return false;
        }
    }
    return true;

}

// gets the largest prime possible
// returns : number
long long int get_largest_prime(){

    long long int x = 999999999;
    while (true){
        if(isPrime(x)){
            return x;
        }
        else{
            x-=2;
        }
    }
}



// hash_function
// return : hash_value (int)
int hash_num(int key){
    
    long long int Largest_prime = get_largest_prime(); 

    return key%Largest_prime;
}

int bit_no(int hash_key, int size){
    return (hash_key%size);
}

void print_bloom(vector<bool> &Bloom_filter, int size){

    cout << "Bloom Filter\n" ;
    for(int i = 0; i < size; i++){
        cout << Bloom_filter[i] << " ";
    }
    cout << endl;
}
int main(){
    
    int size;
    cout<<"Size of bloom filer : " ;
    cin >> size;

    vector<bool> Bloom_filter(size,false);

    cout << "Key : " ;
    
    int key;
    cin >> key;
    int hashed_key = hash_num(key);
    cout<< hashed_key << endl;
    int bit = bit_no(hashed_key, size);
    cout << bit << endl;
    Bloom_filter[bit] = true;
    print_bloom(Bloom_filter, size);
    

}