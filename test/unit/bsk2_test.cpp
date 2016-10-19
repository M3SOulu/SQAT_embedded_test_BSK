/*
 * bsk_test.cpp
 *
 *  Created on: Oct 18, 2016
 *      Author: timppa
 */

#include "gtest_inc.h"

#include "chip.h"

#include "bsk.h"

namespace BSK2_test_namespace {
	//
	// dependency injections
	//
int disp_show_decimal( int );
int i2c_read(int address,
		char* reg,int reglen,
		char* buffer,int length);
	//
	// delay dependency
	//
//subroutine_signature();
	//
	// target code is included instead of (direct) compilation:
	//   This allows to cut the dependencies (such as I2C_write above)
	//
	#include "../src/bsk2.cpp"
}

using ::testing::Test;

/**********************************************************************
 *
 * GoogleTest test-class for 7-segment display testing
 *
 **********************************************************************/
class unittest_BSK2 : public Test
{
public:
	//
	// constructor just resets attributes to some default values
	//
	unittest_BSK2()
	{
		mRc = -1;
	}
	virtual ~unittest_BSK2(){}
protected:
	//
	// SetUp performs the per-test initialization/setup of test instance
	//
	virtual void SetUp()
	{
		mRc = -1;
	}
	//
	// TearDown cleans-up test instance
	//
	virtual void TearDown()
	{
	}
	static int getRecorded_Disp_Show_Decimal_Value()
	{
		return mRecorded_Disp_Show_Decimal_Value;
	}
	static void set_next_i2c_read_value( int i2c_rd )
	{
		mPlay_i2c_read_value = i2c_rd;
	}
protected:
	int mRc;
	// allow disp_show_decimal to modify attributes such as mRecorded_Disp_Show_Value
	friend int BSK2_test_namespace::disp_show_decimal( int value );
	static int mRecorded_Disp_Show_Decimal_Value;

	friend int BSK2_test_namespace::i2c_read(int address,
			char* reg,int reglen,
			char* buffer,int length);
	static int mPlay_i2c_read_value;
	static int mRecorded_i2c_read_address;
};

//
// for use by disp_show_decimal
//
int unittest_BSK2::mRecorded_Disp_Show_Decimal_Value = 0;
//
// for use by i2c_read
//
int unittest_BSK2::mPlay_i2c_read_value = 0;
int unittest_BSK2::mRecorded_i2c_read_address = 0;

int BSK2_test_namespace::disp_show_decimal( int value )
{
	unittest_BSK2::mRecorded_Disp_Show_Decimal_Value = value;
}

int BSK2_test_namespace::i2c_read(int address,
		char* reg,int reglen,
		char* buffer,int length)
{
	unittest_BSK2::mRecorded_i2c_read_address = address;
	if ( 0!=buffer && length>0 ){
		buffer[0]=unittest_BSK2::mPlay_i2c_read_value;
		return 1;
	}
	return -1;
}
/**********************************************************************
 *
 * quick verification of test fixture
 * - this helps detect problems in test setup
 *
 **********************************************************************/
TEST_F( unittest_BSK2, test_fixture )
{
	EXPECT_EQ( -1, mRc );
}

/**********************************************************************
 *
 * quick verification of test setup/construction
 * - this helps detect problems in test setup
 *
 **********************************************************************/

TEST_F( unittest_BSK2, test_constructor )
{
}

/**********************************************************************
 *
 * test cases
 *
 **********************************************************************/

//
// test matches the empty implementation
//
TEST_F( unittest_BSK2, calculate_frame_score )
{
	bsk_game_t game;
	game.frames[0].first_throw = 1;
	game.frames[0].second_throw = 2;

	mRc = BSK2_test_namespace::bsk_calculate(&game,1);

	EXPECT_EQ(3,mRc);
}
