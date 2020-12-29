#ifndef __OCR_DBNET_H__
#define __OCR_DBNET_H__

#include "OcrStruct.h"
#include "onnxruntime_cxx_api.h"
#include <opencv/cv.hpp>

class DbNet {
public:
    DbNet();

    ~DbNet();

    void setNumThread(int numOfThread);

    bool initModel(std::string &pathStr);

    std::vector<TextBox> getTextBoxes(cv::Mat &src, ScaleParam &s, float boxScoreThresh,
                                      float boxThresh, float minArea, float unClipRatio);

private:
    Ort::Session *session;
    Ort::Env *env;
    Ort::SessionOptions *sessionOptions;
    int numThread = 0;
    std::vector<const char *> inputNames;
    std::vector<const char *> outputNames;

    const float meanValues[3] = {0.485 * 255, 0.456 * 255, 0.406 * 255};
    const float normValues[3] = {1.0 / 0.229 / 255.0, 1.0 / 0.224 / 255.0, 1.0 / 0.225 / 255.0};
};


#endif //__OCR_DBNET_H__
