#pragma once

#include "Eigen/Core"
#include "avaverse/config.hpp"

namespace avaverse {

using Skeleton = Eigen::Matrix<double, kNumPose, kDim>;

using ColorChannel = Eigen::Matrix<uint8_t, Eigen::Dynamic, Eigen::Dynamic>;

};  // namespace avaverse