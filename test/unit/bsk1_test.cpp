/*
 * bsk_test.cpp
 *
 *  Created on: Oct 18, 2016
 *      Author: timppa
 */

#include "gtest_inc.h"

#include "chip.h"

#include "bsk.h"

namespace BSK1_test_namespace {
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
#include "../src/bsk1.cpp"
}

using ::testing::Test;

/**********************************************************************
 *
 * GoogleTest test-class for 7-segment display testing
 *
 **********************************************************************/
class unittest_BSK1 : public Test
{
public:
	//
	// constructor just resets attributes to some default values
	//
	unittest_BSK1()
{
		mRc = -1;
}
	virtual ~unittest_BSK1(){}
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
	friend int BSK1_test_namespace::disp_show_decimal( int value );
	static int mRecorded_Disp_Show_Decimal_Value;

	friend int BSK1_test_namespace::i2c_read(int address,
			char* reg,int reglen,
			char* buffer,int length);
	static int mPlay_i2c_read_value;
	static int mRecorded_i2c_read_address;
};

//
// for use by disp_show_decimal
//
int unittest_BSK1::mRecorded_Disp_Show_Decimal_Value = 0;
//
// for use by i2c_read
//
int unittest_BSK1::mPlay_i2c_read_value = 0;
int unittest_BSK1::mRecorded_i2c_read_address = 0;

int BSK1_test_namespace::disp_show_decimal( int value )
{
	unittest_BSK1::mRecorded_Disp_Show_Decimal_Value = value;
	return 10;	// returns same amount as what gets sent to I2C
}

int BSK1_test_namespace::i2c_read(int address,
		char* reg,int reglen,
		char* buffer,int length)
{
	unittest_BSK1::mRecorded_i2c_read_address = address;
	if ( 0!=buffer && length>0 ){
		buffer[0]=unittest_BSK1::mPlay_i2c_read_value;
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
TEST_F( unittest_BSK1, test_fixture )
{
	EXPECT_EQ( -1, mRc );
}

/**********************************************************************
 *
 * quick verification of test setup/construction
 * - this helps detect problems in test setup
 *
 **********************************************************************/

TEST_F( unittest_BSK1, test_constructor )
{
}

/**********************************************************************
 *
 * test cases
 *
 **********************************************************************/

//
// test that the disp_show_decimal forms correct data to I2C
//
// these example tests PASS against non-implemented target
//   => the test is not complete, nor is the implementation
//

TEST_F( unittest_BSK1, get_data_for_throw )
{
	bsk_frame_t frame;
	frame.first_throw = 0;
	frame.second_throw = 0;

	set_next_i2c_read_value( 3 );
	mRc = BSK1_test_namespace::bsk_get_throw( &frame,1 );
	EXPECT_EQ( -2, mRc );
	EXPECT_EQ( 0, frame.first_throw );

	set_next_i2c_read_value( 5 );
	mRc = BSK1_test_namespace::bsk_get_throw( &frame, 2 );
	EXPECT_EQ( -2, mRc );
	EXPECT_EQ( 0, frame.second_throw );
}
