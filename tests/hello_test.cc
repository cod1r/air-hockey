#include <gtest/gtest.h>
#include "../src/Renderer.h"
#include "../src/OpenGLFunctions.h"
#include "../src/AirHockey.h"
// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}
TEST(INIT, basic_shit) {
    AirHockey ah;
}