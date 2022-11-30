#include "runlengthencoding.h"

RunLengthEncoding::RunLengthEncoding() {
}

std::vector<std::vector<Run>> RunLengthEncoding::run(const cv::Mat& matrix) {

  std::vector<std::vector<Run>> runs;
  std::vector<Run> finalRuns[matrix.rows];
  tbb::parallel_for(tbb::blocked_range<int>(0, matrix.rows, 119), [&](tbb::blocked_range<int>& r) {
    int runLenght;
    for (int i = r.begin(); i != r.end(); i++) {

      const uchar* pt = matrix.ptr<uchar>(i);
      std::vector<Run> line;

      for (int j = 0; j < matrix.cols; j++) {

        for (runLenght = 0; runLenght + j < matrix.cols && pt[j] == pt[j + runLenght]; runLenght++)
          ;

        Run current;
        current.start = j;
        current.color = pt[j];
        current.width = runLenght;
        current.areaBlob = current.width;
        current.parent = -1;
        current.sumX = i * current.width;
        current.sumY = current.width * ((current.width / 2) + current.start);

        if (current.color > NoCOL && current.color < ColorStrange)
          line.push_back(current);
        j += runLenght;
      }

      finalRuns[i] = line;
    }
  });

  for (int i = 0; i < matrix.rows; i++) {
    runs.push_back(finalRuns[i]);
  }

  return runs;
}
