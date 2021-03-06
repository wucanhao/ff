// Copyright 2016 The FilterForward Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef FILTERFORWARD_UTILS_NNBENCH_H_
#define FILTERFORWARD_UTILS_NNBENCH_H_

#include <memory>
#include <string>
#include <vector>

#include "saf.h"

// A NnBench is a Operator
class NnBench : public Operator {
 public:
  NnBench(const ModelDesc& model_desc, const Shape& input_shape, int batch_size,
          int num_copies);

  static std::shared_ptr<NnBench> Create(const FactoryParamsType& params);

  virtual std::string GetName() const override;

  void SetSource(StreamPtr stream);
  using Operator::SetSource;

  StreamPtr GetSink();
  using Operator::GetSink;

 protected:
  virtual bool Init() override;
  virtual bool OnStop() override;
  virtual void Process() override;

 private:
  size_t batch_size_;
  std::string input_layer_;
  std::string output_layer_;
  std::vector<std::unique_ptr<Model>> models_;
  std::vector<std::unique_ptr<Frame>> buf_;
};

#endif  // FILTERFORWARD_UTILS_NNBENCH_H_
