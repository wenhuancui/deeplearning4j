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

//
// @author raver119@gmail.com
//

#include <ops/declarable/CustomOperations.h>
#if NOT_EXCLUDED(OP_less)

namespace sd {
namespace ops {
BROADCASTABLE_BOOL_OP_IMPL(less, 0, 0) {
  auto x = INPUT_VARIABLE(0);
  auto y = INPUT_VARIABLE(1);
  auto z = OUTPUT_VARIABLE(0);

  BROADCAST_CHECK_EMPTY(x, y, z);

  auto tZ = BroadcastHelper::broadcastApply(BROADCAST_BOOL(LessThan), x, y, z);
  if (tZ == nullptr)
    return sd::Status::KERNEL_FAILURE;
  else if (tZ != z) {
    OVERWRITE_RESULT(tZ);
  }

  return sd::Status::OK;
}

DECLARE_TYPES(less) {
  getOpDescriptor()
      ->setAllowedInputTypes(0, DataType::ANY)
      ->setAllowedInputTypes(1, DataType::ANY)
      ->setAllowedOutputTypes(0, DataType::BOOL);
}
}  // namespace ops
}  // namespace sd
#endif
