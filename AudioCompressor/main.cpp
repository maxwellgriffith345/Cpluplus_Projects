//
//  main.cpp
//  TestAudioProject
//
//  Created by Maxwell Griffith on 4/16/23.
//

#include <iostream>
#include <AudioFile.h>
#include "compressor.h"

using namespace std;

int main(int argc, const char * argv[]) {
    const string filePath = "/Users/maxwellgriffith/my_projects/TestAudioProject/MONODRUMS_LOOPS_107_1.wav";
    
    AudioFile<float> a;
    
    bool loadedOK = a.load(filePath);
    
    assert(loadedOK);
   
    int sampleRate = a.getSampleRate();
    
   // float gain = 0.5f;
    float threshold = -15;
    float ratio = 5;
    float attack = .05;
    float release = .02;
    
    compressor mycompressor(ratio, threshold, attack, release, sampleRate);
 
    for (int i=0; i < a.getNumSamplesPerChannel(); i++)
    {
        for (int channel =0; channel < a.getNumChannels(); channel++)
        {
            a.samples[channel][i] = mycompressor.compress(a.samples[channel][i]);
        }
    }
    
    string outputFilePath = "/Users/maxwellgriffith/my_projects/TestAudioProject/MONODRUMS_comp.wav";
    
    a.save(outputFilePath, AudioFileFormat::Wave);
    
    cout << "congrats! it runs\n";
    return 0;
}


// /Users/maxwellgriffith/my_projects/TestAudioProject/MONODRUMS_LOOPS_107_1.wav
// 9 seconds, stereo, 48kHz, bit depth 24
