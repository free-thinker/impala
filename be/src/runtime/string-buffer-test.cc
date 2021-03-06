// Copyright 2012 Cloudera Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <string>
#include <gtest/gtest.h>

#include "runtime/mem-pool.h"
#include "runtime/string-buffer.h"


using namespace std;

namespace impala {

void ValidateString(const string& std_str, const StringBuffer& str) {
  EXPECT_EQ(std_str.empty(), str.Empty());
  EXPECT_EQ((int)std_str.size(), str.Size());
  if (std_str.size() > 0) {
    EXPECT_EQ(strncmp(std_str.c_str(), str.str().ptr, std_str.size()), 0);
  }
}

TEST(StringBufferTest, Basic) {
  MemPool pool(NULL);
  StringBuffer str(&pool);
  string std_str;

  // Empty string
  ValidateString(std_str, str);

  // Clear empty string
  std_str.clear();
  str.Clear();
  ValidateString(std_str, str);

  // Append to empty
  std_str.append("Hello");
  str.Append("Hello", strlen("Hello"));
  ValidateString(std_str, str);

  // Append some more
  std_str.append("World");
  str.Append("World", strlen("World"));
  ValidateString(std_str, str);

  // Assign
  std_str.assign("foo");
  str.Assign("foo", strlen("foo"));
  ValidateString(std_str, str);
  
  // Clear
  std_str.clear();
  str.Clear();
  ValidateString(std_str, str);

  // Underlying buffer size should be the length of the max string during the test.
  EXPECT_EQ(str.buffer_size(), strlen("HelloWorld"));
}

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

