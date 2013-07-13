// -*- coding: utf-8 -*-
/* Copyright (c) 2013, Ondrej Platek, Ufal MFF UK <oplatek@ufal.mff.cuni.cz>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED
 * WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
 * MERCHANTABLITY OR NON-INFRINGEMENT.
 * See the Apache 2 License for the specific language governing permissions and
 * limitations under the License. */
#ifndef KALDI_ONLINE_PYTHON_GMM_DECODE_FASTER_H_
#define KALDI_ONLINE_PYTHON_GMM_DECODE_FASTER_H_

#include <string>
#include <vector>
#include "feat/feature-mfcc.h"
#include "online/online-audio-source.h"
#include "online/online-feat-input.h"
#include "online/online-decodable.h"
#include "online/online-faster-decoder.h"

/*****************
 *  C interface  *
 *****************/

typedef void CKaldiDecoderWrapper;

#ifdef __cplusplus
extern "C" {
#endif

// explicit constructor and destructor
CKaldiDecoderWrapper* new_KaldiDecoderWrapper(int argc, char **argv);
void del_KaldiDecoderWrapper(CKaldiDecoderWrapper *d);

// methods
void Setup(CKaldiDecoderWrapper *d, int argc, char **argv);
void Reset(CKaldiDecoderWrapper *d);
void InputFinished(CKaldiDecoderWrapper *d);
void FrameIn(CKaldiDecoderWrapper *d, unsigned char *frame, size_t frame_len);
bool Decode(CKaldiDecoderWrapper *d);
size_t PrepareHypothesis(CKaldiDecoderWrapper *d, int * is_full);
void GetHypothesis(CKaldiDecoderWrapper *d, int * word_ids, size_t size);

// function types for loading functions from shared library
typedef CKaldiDecoderWrapper* (*CKDW_constructor_t)(int, char **);
typedef void (*CKDW_void_t)(CKaldiDecoderWrapper*);
typedef bool (*CKDW_decode_t)(CKaldiDecoderWrapper*);
typedef void (*CKDW_setup_t)(CKaldiDecoderWrapper*, int, char **);
typedef void (*CKDW_frame_in_t)(CKaldiDecoderWrapper*, unsigned char *, size_t);
typedef size_t (*CKDW_prep_hyp_t)(CKaldiDecoderWrapper*, int *);
typedef void (*CKDW_get_hyp_t)(CKaldiDecoderWrapper*, int *, size_t);


#ifdef __cplusplus
}
#endif


#ifdef __cplusplus

/*******************
 *  C++ interface  *
 *******************/

namespace kaldi {

typedef OnlineFeInput<OnlineBlockSource, Mfcc> BlockFeatInput;

/** @brief A class for setting up and using Online Decoder.
 *
 *  This class provides an interface to Online Decoder.
 *  It exposes C++ as well as C API. 
 *
 *  It is absolutelly thread unsafe! */
class KaldiDecoderWrapper {
 public:
  // methods designed also for calls from C
  KaldiDecoderWrapper(int argc, char **argv);  
  void Setup(int argc, char **argv);
  void Reset(void);
  void FrameIn(unsigned char *frame, size_t frame_len);
  bool Decode(void);
  void InputFinished();
  bool GetHypothesis();
  bool GetHypothesis(std::vector<int32> & word_ids);
  virtual ~KaldiDecoderWrapper();
  bool UtteranceEnded();

  std::vector<int32> last_word_ids;

 private:
  int ParseArgs(int argc, char **argv);

  bool resetted_;
  bool ready_;
  OnlineFasterDecoder::DecodeState dstate_;

  const int32 kSampleFreq_;
  BaseFloat acoustic_scale_;
  int32 cmn_window_;
  int32 min_cmn_window_;
  int32 right_context_;
  int32 left_context_;

  OnlineFasterDecoderOpts decoder_opts_;
  OnlineFeatureMatrixOptions feature_reading_opts_;
  DeltaFeaturesOptions delta_feat_opts_;
  std::string model_rxfilename_;
  std::string fst_rxfilename_;
  std::string word_syms_filename_;
  std::string lda_mat_rspecifier_;


  Mfcc *mfcc_;
  OnlineBlockSource *source_;
  BlockFeatInput *fe_input_;
  OnlineCmnInput *cmn_input_;
  TransitionModel *trans_model_;
  fst::Fst<fst::StdArc> *decode_fst_;
  // FIXME change to my own decoder
  // I need to handle start (and end of utterance) of utterance myself!
  // OnlineFasterDecoder.Reset should be called mostly by KaldiDecoderWrapper 
  OnlineFasterDecoder *decoder_;
  OnlineFeatInputItf *feat_transform_;
  OnlineFeatureMatrix *feature_matrix_;
  OnlineDecodableDiagGmmScaled *decodable_;
  std::vector<int32> silence_phones_;
  AmDiagGmm am_gmm_;

  KALDI_DISALLOW_COPY_AND_ASSIGN(KaldiDecoderWrapper);
};

} // namespace kaldi

#endif  // __cplusplus

#endif  // #ifndef KALDI_ONLINE_PYTHON_GMM_DECODE_FASTER_H_
