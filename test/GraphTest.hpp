#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class GraphTest : public ::testing::Test {
protected:
	GraphTest() {}
	virtual ~GraphTest() {}
	virtual void SetUp() {}
	virtual void TearDown() {}
};
