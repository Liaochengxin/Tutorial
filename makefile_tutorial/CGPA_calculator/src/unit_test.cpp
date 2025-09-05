#include <gtest/gtest.h>
#include "Course.h"

// 测试百分成绩转换
TEST(CGPACalculatorTest, PercentageGrades) {
    CGPACalculator calc;

    EXPECT_DOUBLE_EQ(calc.gradeToPoint("100"), 5.0);
    EXPECT_DOUBLE_EQ(calc.gradeToPoint("90"), 4.0);
    EXPECT_DOUBLE_EQ(calc.gradeToPoint("80"), 3.0);
    EXPECT_DOUBLE_EQ(calc.gradeToPoint("70"), 2.0);
    EXPECT_DOUBLE_EQ(calc.gradeToPoint("60"), 1.0);
    EXPECT_DOUBLE_EQ(calc.gradeToPoint("59.9"), 0.0);
    EXPECT_DOUBLE_EQ(calc.gradeToPoint("0"), 0.0);
}


// 测试非法输入
TEST(CGPACalculatorTest, InvalidGrades) {
    CGPACalculator calc;

    EXPECT_DOUBLE_EQ(calc.gradeToPoint("XYZ"), 0.0);
    EXPECT_DOUBLE_EQ(calc.gradeToPoint(""), 0.0);
}

//  测试 addCourse + getCourses
TEST(CGPACalculatorTest, AddCourse) {
    CGPACalculator calc;

    Course c1 = {"CS101", 3, "95"};
    Course c2 = {"MATH202", 4, "90"};

    calc.addCourse(c1);
    calc.addCourse(c2);

    const auto& courses = calc.getCourses();
    ASSERT_EQ(courses.size(), 2);
    EXPECT_EQ(courses[0].code, "CS101");
    EXPECT_EQ(courses[1].credits, 4);
}

//  测试 sortCourses
TEST(CGPACalculatorTest, SortCourses) {
    CGPACalculator calc;

    Course c1 = {"MATH202", 3, "85"};
    Course c2 = {"CS101", 4, "90"};

    calc.addCourse(c1);
    calc.addCourse(c2);

    calc.sortCourses();

    const auto& courses = calc.getCourses();
    ASSERT_EQ(courses.size(), 2);
    EXPECT_EQ(courses[0].code, "CS101");
    EXPECT_EQ(courses[1].code, "MATH202");
}

//  测试 computeCGPA 正确性
TEST(CGPACalculatorTest, ComputeCGPA) {
    CGPACalculator calc;

    // 分别是：5.0 * 3，3.0 * 3，2.0 * 4
    calc.addCourse({"CS101", 3, "100"});
    calc.addCourse({"MATH202", 3, "80"});
    calc.addCourse({"PHYS303", 4, "70"});

    double cgpa = calc.computeAndDisplayCGPA();  // 期望：总分 (15+9+8)=32，总学分 10
    EXPECT_NEAR(cgpa, 3.2, 0.01);
}


//  测试空课程
TEST(CGPACalculatorTest, EmptyCGPA) {
    CGPACalculator calc;
    double cgpa = calc.computeAndDisplayCGPA();
    EXPECT_DOUBLE_EQ(cgpa, 0.0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
