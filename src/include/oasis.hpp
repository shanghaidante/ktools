/*
* Copyright (c)2015 Oasis LMF Limited 
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*
*   * Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in
*     the documentation and/or other materials provided with the
*     distribution.
*
*   * Neither the original author of this software nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
* THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*/

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>

#if defined(_MSC_VER) || defined(__MINGW32__)
#include <fcntl.h>
#include <io.h>
#define flseek _fseeki64
#define fltell _ftelli64
#else
#define flseek fseek
#define fltell ftell
#endif 

//const int mean_idx = 1 << 24;
//const int std_dev_idx = -1;
const int mean_idx = -1;
const int std_dev_idx = -2;


// Stream types
const unsigned int cdfstream_id = 0;		// high byte is zero
const unsigned int gulstream_id = 1 << 24;
const unsigned int fmstream_id = 2 << 24;
const unsigned int outputstream_id = 3 << 24;

const unsigned int streamno_mask = 0x00FFFFFF;

#pragma pack(push, 1)
struct damagecdfrec {
        int event_id;
        int areaperil_id;
        int vulnerabilty_id;
};

struct damagebindictionary {
        int bin_index;
        float bin_from;
        float bin_to;
        float interpolation;
        int interval_type;
};

struct gulSampleslevel {
	int event_id;
	int item_id;
	int sidx;		// This has be stored for thresholds cannot be implied
	float gul;		// may want to cut down to singe this causes 4 byte padding for allignment
};

struct gulSampleslevelEventRec {
	int item_id;
	int sidx;		// This has be stored for thresholds cannot be implied
	float gul;		// may want to cut down to singe this causes 4 byte padding for allignment
};
struct gulSampleslevelHeader {
	int event_id;
	int item_id;
};

struct gulSampleslevelRec {
	int sidx;		// This has be stored for thresholds cannot be implied
	float gul;		// may want to cut down to singe this causes 4 byte padding for allignment
};

struct fmlevelhdr {
	int event_id;
	int prog_id;
	int layer_id;
	int output_id;
};

struct fmlevelrec {
	int sidx;
	float loss;
};

struct fmdata {
	int item_id;
	int agg_id;
	int prog_id;
	int level_id;
	int policytc_id;
	int layer_id;
	int calcrule_id;
	int allocrule_id;
	float deductible;
	float limits;
	float share_prop_of_lim;
	float deductible_prop_of_loss;
	float limit_prop_of_loss;
	float deductible_prop_of_tiv;
	float limit_prop_of_tiv;
	float deductible_prop_of_limit;
};


struct exposure{
	int item_id;
	int areaperil_id;
	int vulnerability_id;
	int group_id;
	float tiv;
};

#pragma pack(pop)
// -- UTILITY inline functions 

inline void initstreams(std::string inFile_, std::string outFile_)
{

   if (inFile_.length() > 0){
        if (freopen(inFile_.c_str(), "rb", stdin) == NULL) {
            std::cerr << "Error opening " << inFile_ << "\n";
            exit(-1);
         }
   }

   if (outFile_.length() > 0){
       if (freopen(outFile_.c_str(), "wb", stdout) == NULL) {
           std::cerr << "Error opening " << outFile_ << "\n";
           exit(-1);
        }
   }

#if defined(_MSC_VER) || defined(__MINGW32__)
	_setmode(_fileno(stdout), O_BINARY);
	_setmode(_fileno(stdin), O_BINARY);
#else
	freopen(NULL, "rb", stdin);
	freopen(NULL, "wb", stdout);
#endif

}
