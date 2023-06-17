//
//  compressor.h
//  TestAudioProject
//
//  Created by Maxwell Griffith on 5/15/23.
//

#ifndef compressor_h
#define compressor_h
#include <math.h>

using namespace std;

class compressor
{
public:

    void set_attack(float new_attack);
    void set_release(float new_release);
    void set_threshold(float new_threshold);
    void set_ratio(float new_ration);
    void set_gain(float new_gain);

    compressor (float ratio, float threshold, float attack, float release, int sample_rate);
    float compress (float sample);
    float decreaselevel( float sample);
    float attack_coef;
    float release_coef;
private:

    const double FLOOR = 1e-20;
    float attack; //seconds >0
    float release;  //seconds >0
    float threshold; //db
    float ratio;
    float gain;
 
    float sample_rate;
    float last_gS=9999;
    
    // HELPER FUNCTIONS
    //Converts linear single to decibles
    float toDb( float sample);
    //Converts Db gain to Lin gain
    float DbtoLin(float sample);
    
    //set attack and release coefficients
    void set_attack_coef();
    void set_release_coef();
};

// IMPLEMENTATION //
compressor::compressor(float ratio, float threshold, float attack, float release, int sampleRate)
{
    set_ratio(ratio);
    set_threshold(threshold);
    set_attack(attack);
    set_release(release);
    sample_rate = sampleRate;
    set_attack_coef();
    set_release_coef();
}
void compressor:: set_attack(float new_attack){
    attack = new_attack;
}
void compressor:: set_release(float new_release){
    release = new_release;
}
void compressor:: set_threshold(float new_threshold){
    threshold = new_threshold;
}
void compressor:: set_ratio(float new_ratio){
    ratio = new_ratio;
}
void compressor:: set_gain(float new_gain){
    gain = new_gain;
}

float compressor::decreaselevel(float sample){
    return sample * gain;
}

void compressor:: set_attack_coef(){
    attack_coef = exp((-log(9))/(sample_rate*attack));
}

void compressor:: set_release_coef(){
    release_coef= exp((-log(9))/(sample_rate*release));
}

float compressor:: toDb(float sample){
    return 20*log10(abs(sample+FLOOR));
    //abs of sample as dB is measure of magnitude
    //add FLOOR so 0 amplitude doesn't return -inf
}

float compressor:: DbtoLin(float sample){
    return powf(10, sample/20);
}

float compressor:: compress(float sample)
{
    float xSC;
    float gS;
    
   float xdB = toDb(sample);
    
    //thresholding
    if (xdB>=threshold){
        xSC = threshold+((xdB-threshold)/ratio);
    }
    else {
        xSC=xdB;
    }
    
    //computed gain
    float gC = xSC - xdB;
    
    if (last_gS == 9999){
        gS=gC;
    }
    else{
        if (gC<=last_gS) {
            gS = (attack_coef*last_gS)+((1-attack_coef)*gC);
        } else {
            gS = release_coef*last_gS+(1-release_coef)*gC;
        }
    }
    last_gS=gS;
    
    //make up gain
   float gM = gS+2;
    
    //converstion back to lin gain
   float glin = DbtoLin(gM);
    
    //check if NAN
    if( isnan(glin))
    {
        cout << "error nan\n"
        << sample << "\n"
        << xdB << "\n"
        << xSC << "\n"
        << gC << "\n"
        << gS << "\n"
        << glin << "\n";
        
        exit(1);
    }
    
    return sample * glin;
}

#endif /* compressor_h */
