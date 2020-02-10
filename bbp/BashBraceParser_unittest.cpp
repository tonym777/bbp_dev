
#include <limits.h>
#include "BashBraceParser.hpp"
#include "gtest/gtest.h"

TEST(BashBraceParse, Postive) {
  EXPECT_EQ("A B C", BashBraceParse("{A,B,C}"));
  EXPECT_EQ("AC AD BC BD", BashBraceParse("{A,B}{C,D}"));
  EXPECT_EQ("A BC BD", BashBraceParse("{A,B{C,D}}"));
  EXPECT_EQ("ABC", BashBraceParse("{ABC}"));
  EXPECT_EQ("ABC", BashBraceParse("ABC"));

}

TEST(BashBraceParse, Negative) {
  EXPECT_EQ("Invalid Format", BashBraceParse("}ABC"));
  EXPECT_EQ("Invalid Format", BashBraceParse("{ABC"));
  EXPECT_EQ("Invalid Format", BashBraceParse("}{"));
  EXPECT_EQ("Invalid Format", BashBraceParse("{}"));
  EXPECT_EQ("Invalid Format", BashBraceParse("A,B,C"));
  EXPECT_EQ("Invalid Format", BashBraceParse("{A{BC}"));
  EXPECT_EQ("Invalid Format", BashBraceParse("A,"));
  EXPECT_EQ("Invalid Format", BashBraceParse("ABC}"));
  EXPECT_EQ("Invalid Format", BashBraceParse("ABC{"));
}
