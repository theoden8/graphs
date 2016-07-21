#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class NodeTest : public ::testing::Test {
protected:
	NodeTest() {}
	virtual ~NodeTest() {}
	virtual void SetUp() {}
	virtual void TearDown() {}
};
