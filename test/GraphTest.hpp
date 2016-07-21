#pragma once

#include <Graph.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class MatrixTest : public ::testing::Test {
protected:
	MatrixTest() {}
	virtual ~MatrixTest() {}
	virtual void SetUp() {}
	virtual void TearDown() {}
};
