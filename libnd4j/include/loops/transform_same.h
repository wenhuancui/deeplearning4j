/* ******************************************************************************
 *
 *
 * This program and the accompanying materials are made available under the
 * terms of the Apache License, Version 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 *
 *  See the NOTICE file distributed with this work for additional
 *  information regarding copyright ownership.
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 ******************************************************************************/

/*
 * transform.h
 *
 *  Created on: Dec 28, 2015
 *  @author: agibsonccc
 *  @author: raver119@gmail.com
 */

#ifndef TRANSFORM_SAME_H_
#define TRANSFORM_SAME_H_
#include <helpers/OmpLaunchHelper.h>
#include <math/templatemath.h>
#include <ops/ops.h>

#include <vector>

//#include <loops/reduce.h>
//#include <loops/scalar.h>
//#include <loops/indexreduce.h>
//#include <loops/broadcasting.h>

#include <loops/legacy_ops.h>

namespace functions {
namespace transform {

template <typename X>
class TransformSame {
 public:
#ifdef __CUDACC__

  template <typename OpType>
  static SD_DEVICE void transformCuda(const void *dy, const sd::LongType *shapeInfo, void *params, void *result,
                                      const sd::LongType *resultShapeInfo, int *allocationPointer,
                                      void *reductionPointer, const sd::LongType *tadShapeInfo,
                                      const sd::LongType *tadOffsets);

  template <typename OpType>
  static SD_HOST void intermediateShaped(dim3 launchDims, cudaStream_t *stream, const void *x,
                                         const sd::LongType *xShape, int xRank, void *extraParams, void *z,
                                         const sd::LongType *zShape, int zRank, int *allocationPointer,
                                         void *reductionPointer, const sd::LongType *tadShapeInfo,
                                         const sd::LongType *tadOffsets);

  static SD_HOST void executeTransformShaped(dim3 launchDims, cudaStream_t *stream, int opNum, const void *x,
                                             const sd::LongType *xShape, int xRank, void *extraParams, void *z,
                                             const sd::LongType *zShape, int zRank, int *allocationPointer,
                                             void *reductionPointer, const sd::LongType *tadShapeInfo,
                                             const sd::LongType *tadOffsets);

#else
  static void exec(int opNum, const void *dx, const sd::LongType *xShapeInfo, void *result,
                   const sd::LongType *resultShapeInfo, void *extraParams, uint64_t threadId, uint64_t numThreads);

  template <typename OpType>
  static SD_LIB_EXPORT void exec(const void *dx, const sd::LongType *xShapeInfo, void *result,
                                 const sd::LongType *resultShapeInfo, void *extraParams, uint64_t threadId,
                                 uint64_t numThreads);
#endif
};
}  // namespace transform
}  // namespace functions

#endif /* TRANSFORM_H_ */
